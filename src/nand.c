/*******************************************************************************
 *                                 Wind River
 *      Work based on x-loader sources from STMicroelectronics which has the
 *      following notice:
 *
 *      Reproduction and Communication of this document is strictly prohibited
 *      unless specifically authorized in writing by STMicroelectronics.
 *
 *      This work, however, has made significant changes to the original
 *      baseline. In fact, there is very little code left from the original.
 *      The above notice has been retained, however, to avoid any issues.
 * 
 *		All Rights reserved by Wind River.
 *
 ******************************************************************************/

#include "aquarius.h"
#include "config.h"
#include "dma.h"
#include "uart.h"
#include "nand.h"
#include "gpio.h"
#include "string.h"

#define CONFIG_ECC

static nand_system_context_t nand;

static void cacheEnd(void)
{
	  *(nand.addr.pCommand) = 0x3f;
}

static void cacheNext(void)
{
	  *(nand.addr.pCommand) = 0x31;
}

static void seekBlock(uint32_t BlockAddress)
{
	  *(nand.addr.pCommand) = 0x00;
	  SET_BLOCK_ADDRESSING(nand.addr.pCommonArea, 0, BlockAddress);
	  *(nand.addr.pCommand) = 0x30;
}

static int getBlockStatus(void)
{
  uint32_t Data;

  // Position to OOB area
  *(nand.addr.pCommand) = 0x05;
  SET_BLOCK_OFFSET(nand.addr.pCommonArea, DATA_BYTES_PER_SECTOR);
  *(nand.addr.pCommand) = 0xE0;

  // Read the first word
  Data = (*nand.addr.pBase);

  // -----------------------------------------------------------------------------
  // Verify if the block is bad (return 1 in this case)
  // -----------------------------------------------------------------------------
  // The first byte of the first page spare area tells us if a block is bad (0x00)
  // -----------------------------------------------------------------------------
  return ((0xFF & Data) != 0xFF) ? ERROR_NAND_BAD_BLOCK : 0;
}

#define ERROR_COUNT_MASK	0x3C
#define ERROR_COUNT_POS		0x2
#define ERROR_COUNT_MAX		0x8

#ifdef CONFIG_ECC
static int correctData(uint8_t *buf)
{
	const uint8_t flip[8] = {3, 2, 1, 0, 7, 6, 5, 4};
	const struct {
		uint32_t start;
		int shift;
	} pos13[8] = {
	  {0, 0}, {1, 5}, {3, 2}, {4, 7},
	  {6, 4}, {8, 1}, {9, 6}, {11, 3}
	};
	uint32_t val;
	int i;
	int error_count;
	uint16_t pos;
	uint16_t change;
	uint16_t invert;
	uint8_t ecc_code[14];

    // -----------------------------------------------------
    // Wait for the ECC to be ready
    // -----------------------------------------------------
    while (!(nand.regs->FSMC_PISR0 & 0x8000));

	val = nand.regs->FSMC_ECCR0;
	ecc_code[0] = (val >>  0) & 0xFF;
	ecc_code[1] = (val >>  8) & 0xFF;
	ecc_code[2] = (val >> 16) & 0xFF;
	ecc_code[3] = (val >> 24) & 0xFF;

	val = nand.regs->FSMC_ECC2R0;
	ecc_code[4] = (val >>  0) & 0xFF;
	ecc_code[5] = (val >>  8) & 0xFF;
	ecc_code[6] = (val >> 16) & 0xFF;
	ecc_code[7] = (val >> 24) & 0xFF;

	val = nand.regs->FSMC_ECC3R0;
	ecc_code[8]  = (val >>  0) & 0xFF;
	ecc_code[9]  = (val >>  8) & 0xFF;
	ecc_code[10] = (val >> 16) & 0xFF;
	ecc_code[11] = (val >> 24) & 0xFF;

	val = nand.regs->FSMC_PISR0;
	if (!(val & 0x4000)) {
		ecc_code[12] = (val >>  8) & 0xFF;
		ecc_code[13] = (val >> 16) & 0xFF;
	} else {
		ecc_code[12] = (val >> 16) & 0xFF;
		ecc_code[13] = 0xFF;
	}

    // --------------------------
    // Clear CodeReady status bit
    // --------------------------
    nand.regs->FSMC_PISR0 &= ~0x00008000;

    error_count = (ecc_code[3] & ERROR_COUNT_MASK) >> ERROR_COUNT_POS;

	/* If there are too many ECC errors, then we can't correct this block */
	if (error_count > ERROR_COUNT_MAX)
		return -1;

	for (i = 0; i < error_count; i++) {

		pos  = (ecc_code[pos13[i].start]   >> pos13[i].shift);
		pos |= (ecc_code[pos13[i].start+1] << (8 - pos13[i].shift));
		pos |= (ecc_code[pos13[i].start+2] << (16 - pos13[i].shift));
		pos &= 0x1fff;

		if (pos <= 4095) {

			change = pos / 8;
			invert = pos % 8;
			if (buf[change] & 1<<flip[invert])
				/* inversion 1->0 */
				buf[change] = (buf[change] & ~(1<<flip[invert]));
			else
				/* inversion 0->1 */
				buf[change] = (buf[change] | 1<<flip[invert]);
		}
	}

	return error_count;
}
#endif

static int readPage(uint16_t *buf)
{
#ifdef CONFIG_ECC
  uint32_t data_pos = 0;
  uint32_t ecc_pos = PAGE_SIZE + ECC_OOB_START;
  int ErrorCounter;
  int block, i, t;

  for (block = 0; block < ECC_BLOCKS_PER_PAGE; block++, buf += ECC_WORD_LIMIT) {

      // Position to read block
      *(nand.addr.pCommand) = 0x05;
      SET_BLOCK_OFFSET(nand.addr.pCommonArea, data_pos);
      *(nand.addr.pCommand) = 0xE0;
      data_pos += SIZE_BYTE_SUB_BLOCK;

      // reset ECC calculation
      nand.regs->FSMC_PCR0 &= ~0x00000040;
      nand.regs->FSMC_PCR0 |=  0x00000040;

      // ----------------------------------
      // Read 512 Bytes of data (128 WORDS)
      // ----------------------------------
      dma_copy16 (buf, (void *)nand.addr.pBase, ECC_WORD_LIMIT, DMA_CR_DSTI);

      // Position to ECC in the OOB area
      *(nand.addr.pCommand) = 0x05;
      SET_BLOCK_OFFSET(nand.addr.pCommonArea, ecc_pos);
      *(nand.addr.pCommand) = 0xE0;
      ecc_pos += ECC_BYTES_PER_SUB_BLOCK;

      // -------------------------------------------------
      // Read 16 Bytes of data (4 WORDS). 14 bytes are ecc
      // -------------------------------------------------
      for (i = 0; i < ECC_WORD_PER_SUB_BLOCK; i++)
        t = *(nand.addr.pBase);

      ErrorCounter = correctData((uint8_t *)buf);

      // -----------------------------
      // 0 or positive means we are OK
      // -----------------------------
      if (ErrorCounter < 0) {
          // ---------------------
          // Impossible to correct
          // ---------------------
          puts("RNP: IMPOSSIBLE TO CORRECT SECTOR SUB_BLOCK\r\n");
          return -1;
      }
  }
#else
  // Position to read block
  *(nand.addr.pCommand) = 0x05;
  SET_BLOCK_OFFSET(nand.addr.pCommonArea, 0);
  *(nand.addr.pCommand) = 0xE0;

  dma_copy16 (buf, (void *)nand.addr.pBase, ECC_WORD_LIMIT * ECC_BLOCKS_PER_PAGE, DMA_CR_DSTI);
#endif

  return 0;
}

int NandInit(void)
{
  // -------------------------------
  // Configure GPIO9 in Alt Funct. A
  // -------------------------------
  *((uint32_t *) (GPIO0_REG_START_ADDR + 0x20)) |= 0x00000200;

  nand.addr.pBase       = (volatile uint16_t *) NAND_FLASH_CS0_START_ADDR;
  nand.addr.pCommand    = (volatile uint8_t *) NAND_FLASH_CS0_START_ADDR + 0x00810000;
  nand.addr.pCommonArea = (volatile uint8_t *) NAND_FLASH_CS0_START_ADDR + 0x01020000;

  // Map The Space for FSMC Registers
  nand.regs = (FSMCRegs *) 0x10100000;

  // --------------------------------------------------
  // Disable all the other CS that we do not use (NOR),
  // keeping high bit 7 for disabling WP.
  // This is a temporary solution to avoid conflicts
  // --------------------------------------------------
  // Bank NOR 0, 1, 2, 3 (to be removed when NOR comes)
  // --------------------------------------------------
  nand.regs->FSMC_BCR1 &= 0x00000080;
  nand.regs->FSMC_BCR2 &= 0x00000080;
  nand.regs->FSMC_BCR3 &= 0x00000080;

  // -----------------------------------------------
  // Set NAND Control Values depending on the CS
  // -----------------------------------------------
  // CONTROL REGISTER
  // -----------------------------------------------
  // address_low        : 0
  // page_length        : 512 (for ECC calculation)
  // ecc_logic          : 0   (enabled when required)
  // bus_width          : 16
  // mem_type           : 1	  (NAND)
  // wait_feature       : 1   (linked to GPIO9 Alt. Func. "A")
  // pc_reset           : 0
  // -----------------------------------------------

  nand.regs->FSMC_PCR0 = FMSC_PCR_BUS_WIDTH_16 | FMSC_PCR_MEM_TYPE_NAND
      | FMSC_PCR_BANK_ENABLE | FMSC_PCR_WAIT_ENABLE;

  // ----------------------------------------------
  // Set NAND Timings Registers depending on the CS.
  // -----------------------------------------------
  // COMMON AREA
  // -----------------------------------------------
  // data_bus_hiz_phase 	: 0x0D
  // addr_hold_phase		: 0x0D
  // wait_phase				: 0x0D
  // addr_setup_phase		: 0x0D
  // -----------------------------------------------

  nand.regs->FSMC_PMEM0 = FMSC_PMEM_MEM0HIZ | FMSC_PMEM_MEM0HOLD
      | FMSC_PMEM_MEM0WAIT | FMSC_PMEM_MEM0SET;

  // -----------------------------------------
  // Reset the device and wait till it's ready
  // -----------------------------------------
  *(nand.addr.pCommand) = 0xff;

  // ---------------------------------------------
  // Write the specific command for reading the ID
  // ---------------------------------------------
  *(nand.addr.pCommand)    = 0x90;
  *(nand.addr.pCommonArea) = 0x00;

  // --------------------------------------------
  // Assign the Device ID and the Manifacturer ID
  // --------------------------------------------
  nand.id.uiManID    = (*(nand.addr.pBase) & 0xff);
  nand.id.uiDeviceID = (*(nand.addr.pBase) & 0xff);

  if (nand.id.uiManID != MAKER_ID || nand.id.uiDeviceID != DEVICE_ID)
	  return -1;

  // -------------------------------------------------------------------
  // Let's assume that the ECC is implementation is supported by default
  // -------------------------------------------------------------------
  // We support BCH8 (8 correctable bits every 512 bytes of data)
  // -------------------------------------------------------------------

  return 0;
}

uint32_t ReadNandPages(uint32_t page, uint8_t *buf, int pageCount, int endPage)
{
  int err;

  seekBlock(page);

  while (pageCount && page <= endPage) {
      cacheNext();
	  while (getBlockStatus()) {
          // --------------------------------------------------
          // Every time we meet a bad block, jump to next one
          // --------------------------------------------------
          page++;

          if (page > endPage) {
              puts("ERROR: Too many BAD BLOCKS for this image copy\r\n");
              cacheEnd();
              return 0;
          }

          cacheNext();
      }

      err = readPage((uint16_t *)buf);
      if (err)
        return 0;

      buf += PAGE_SIZE;
      pageCount--;
      page++;
  }

  cacheEnd();

  if (pageCount) {
      puts("ERROR: Partition too small for this image copy\r\n");
      return 0;
  }

  return page;
}
