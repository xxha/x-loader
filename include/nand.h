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

#ifndef _NAND_H_
#define _NAND_H_

#ifdef	__cplusplus
extern "C"
{
#endif

#include "aquarius.h"
#include "support.h"
#include "config.h"

#define PAGE_SIZE					DATA_BYTES_PER_SECTOR
#define NAND_SECTOR_SIZE			PAGE_SIZE		
#define NAND_SECTORS_PER_BLOCK 		SECTORS_PER_BLOCK;
#define ECC_WORD_LIMIT				256				// 512 Byte data is the max length for ECC.
#define ECC_BYTES_PER_SUB_BLOCK		16				// Effective number of ECC Byte per block.
#define	ECC_WORD_PER_SUB_BLOCK		8				// Number of ECC Word per block with padding.
#define SIZE_BYTE_SUB_BLOCK			512				// Size in Byte per ECC data block.

#define PAGE(x)						((x + PAGE_SIZE - 1) / PAGE_SIZE)

  /* --------FSMC--PCR------ */
#define	FMSC_PCR_BUS_WIDTH_8		(0x0)
#define	FMSC_PCR_BUS_WIDTH_16		(0x10)
#define	FMSC_PCR_MEM_TYPE_NAND		(0x8)
#define	FMSC_PCR_BANK_ENABLE		(0x4)
#define	FMSC_PCR_WAIT_ENABLE		(0x2)
#define	FMSC_PCR_PC_RESET			(0x0)

/* --------FSMC--PMEM  0------ */
#define	FMSC_PMEM_MEM0HIZ   		(0x00<<24)
#define	FMSC_PMEM_MEM0HOLD  		(NAND_TIMING_1<<16)
#define	FMSC_PMEM_MEM0WAIT   		(NAND_TIMING_2<<8)
#define	FMSC_PMEM_MEM0SET    		(0x00)

#define ERROR_NAND_BAD_BLOCK				-6

typedef struct
{
	uint8_t uiManID;
	uint8_t uiDeviceID;
} NAND_Id;

typedef struct
{
	volatile uint8_t	*pCommand; // Pointer to command area
	volatile uint8_t	*pCommonArea;// Pointer to common area
	volatile uint8_t	*pAttributeArea;// Pointer to attribute area
	volatile uint16_t	*pBase;// Pointer to I/O area
} NAND_Address;

typedef struct
{
	FSMCRegs		*regs;       // Virtual Address of the mapped register space (FSMC)
	NAND_Id			id;           // Identity Card for the current device
	NAND_Address	addr;    // Logical Addresses associated to the current NAND device
} nand_system_context_t;

int NandInit(void);
uint32_t ReadNandPages(uint32_t page, uint8_t *buf, int pageCount, int endPage);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NAND_H_ */
