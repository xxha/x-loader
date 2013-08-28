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
#include "nand.h"
#include "gpio.h"
#include "crc32.h"
#include "config.h"
#include "support.h"
#include "uart.h"

extern uint32_t MagicKey;

static struct partInfo {
	int magic;
	range_t list[5];
	int current;
	int size;
} *parts = (struct partInfo *)0x80010000;

int main(unsigned int magic)
{
	uint32_t entry;

	// ----------------------
	// Disable all interrupts
	// ----------------------
	*(uint32_t *) 0x10140014 = 0xFFFFFFFF;
	*(uint32_t *) 0x10140034 = 0xFFFFFFFF;

	make_crc_table();

	// ---------
	// Init GPIO
	// ---------
	GPIO_Init();

	// -----------------
	// Init the DBG UART
	// -----------------
	UART_Init(BR115200BAUD, NOPARITY_BIT, ONE_STOPBIT, DATABITS_8);

	// -----------------
	// Init the platform
	// -----------------
	BL_InitPlatform();

	// ---------------------------
	// Initialize the NAND device.
	// ---------------------------
	if (NandInit())
	{
		puts("Unable to init the NAND device!\r\n");
		goto error_exit_point;
	}

	// --------------------------
	// Let's try to configure DDR
	// --------------------------
	if (BL_InitDDRMemory())
	{
		puts("Unable to configure DDR memory!\r\n");
		goto error_exit_point;
	}

	puts(START_MESSAGE);

	/*
	 * NOTE:
	 * ENV is stored in RAM and it is possible that the uImage
	 * to get loaded on top of it. This is bad, but not much
	 * we can do except place it where we think a uImage won't
	 * overwrite it. See support function loadEnv() and config.h.
	 */
	loadEnv(ENV_NAND_START, ENV_NAND_END);

	if (magic != MagicKey) {
		puts("magic != MagicKey\r\n");
		parts->size = bootPart(parts->list);
		parts->current = 0;
	}

	puts("magic = MagicKey\r\n");
try_part:
	if (parts->current < parts->size) {
		puts(" 111111111 \r\n");
		entry = loadImage(parts->list[parts->current].start,
						  parts->list[parts->current].end);

		if (entry == ~0) {
			puts("Unble to load from 0x");
			writeHex(parts->list[parts->current].start);
			puts("!\r\n");
			parts->current++;
			goto try_part;
		}
	} else {
		puts(" 2222222222222 \r\n");
		entry = loadImage(OS_NAND_START, OS_NAND_END);

		if (entry == ~0) {
			puts("Unble to load last resort image!\r\n");
			goto error_exit_point;
		}
	}

	// if we fail watchdog, try the next partition.
	parts->current++;

	/*
	 * The kernel only has a certain amount of time to take over.
	 * If it doesn't do it soon enough, we will reset.
	 */
	if (wdEnabled())
		wdtEnable();

	/*
	 * Now lets boot the kernel...
	 */
	jumpTo(entry);

error_exit_point:
	puts("Failure!\r\n");
	return 0;
}
