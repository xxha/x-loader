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
#include "support.h"

static const uint32_t DDRConfig[] = {
		0x00000101, 0x01000100, 0x00010001, 0x01010100, //  0- 3
		0x00000001, 0x01010000, 0x00010001, 0x01000100, //  4- 7
		0x01010000, 0x00010001, 0x03030303, 0x01000303, //  8-11
		0x02000000, 0x00010201, 0x03000301, 0x03030103, // 12-15
		0x03010102, 0x03040300, 0x03030503, 0x00000005, // 16-19
		0x04000300, 0x00000003, 0x06060606, 0x06060606, // 20-23
		0x05050505, 0x05050505,	0x04040404,	0x04040404, // 24-27
		0x03030303,	0x03030303,	0x02020202,	0x02020202, // 28-31
		0x01010101,	0x01010101,	0x040a0a0a,	0x00050002, // 32-35
		0x00070102,	0x05020002,	0x00040403,	0x00000000, // 36-39
		0x100a0000,	0x3f051202,	0x0d04003f,	0x00002805, // 40-43
		0x00640064,	0x00640064,	0x00640064,	0x00000000, // 44-47
		0x00000000,	0x00200020,	0x00200020,	0x00200020, // 48-51
		0x00200020,	0x00200020,	0x00200020,	0x00000000, // 52-55
		0x06590000,	0x00040000,	0x00000004,	0x00000000, // 56-59
		0x00000000,	0x00000000,	0x00000000,	0x08520852, // 60-63
		0x00c8007d,	0x55250002,	0x00c8002b,	0x00000000, // 64-67
		0x0000f362,	0x00000000,	0x00000000,	0x00000000, // 68-71
		0x00000000,	0x00407803,	0x00407803,	0x00407803, // 72-75
		0x00407803,	0x00111e01,	0x00111e01,	0x00111e01, // 76-79
		0x00111e01,	0x00000000,	0x00000000,	0x00000000, // 80-83
		0x00000000,	0x00000000,	0x0E148401,	0xf4013b27, // 84-87
		0xf4013b27,	0xf4013b27,	0xf4013b27,	0x07800301, // 88-91
		0x07800301,	0x07800301,	0x07800301,	0x00000005  // 92-95
};

#define SRCCR				0x10401A07
#define PLLFR				0x18003001
#define SCCLKDIVCR			0x000084f2
#define ENABLE_DDR_CMD		0x01010100

int BL_InitPlatform(void)
{
	// ---------------------
	// Remove fast boot flag
	// ---------------------
	*((uint32_t *)0x101E000c) &= ~(1 << 21);

	// ----------------------
	// Patch for clock change
	// ----------------------
	*((uint32_t *)0x101F6100) |= 0x8;
	*((uint32_t *)0x101F5100) |= 0x8;

	return 0;
}

int BL_InitDDRMemory(void)
{
	uint32_t *i;
	int k;

	*((uint32_t *)0x101E0000) = 0x00021003;

	// ---------------------
	// Waiting for slow mode
	// ---------------------
	while ((*((volatile uint32_t *)0x101E0000) & 0x78) != 0x10);

	*((uint32_t *)0x101E0014) = PLLFR;
	*((uint32_t *)0x101E0058) = SCCLKDIVCR;
	*((uint32_t *)0x101E0010) = 0x10000000; // enable PLL2
	*((uint32_t *)0x101E0000) = SRCCR;

	// ---------------------------
	// Waiting for PLL2 stabilized
	// ---------------------------
	while (!(*((volatile uint32_t *)0x101E0010) & 0x20000000));

	// --------------------
	// Wait for normal mode
	// --------------------
	while ((*((volatile uint32_t *)0x101E0000) & 0x78) != 0x20);

	k = 0;
	for (i = (uint32_t *)0x10110000; i < (uint32_t *)0x10110180; i++)
		*i = DDRConfig[k++]; // Load DDR configuration data

	*((uint32_t *)0x10110020) = ENABLE_DDR_CMD; // Used on C+

	// ------------
	// Remap memory
	// ------------
	*((uint32_t *)0x101E0000) = SRCCR | 0x00000100;

	// ------------------------------
	// Waiting for DRAM init complete
	// ------------------------------
	while ((*((volatile uint32_t *)0x101100C0) & 0x04) != 0x04);

	// ---------------------
	// Waiting for DDLs lock
	// ---------------------
	while (!(*((volatile uint32_t *)0x10110144) & 1));
	while (!(*((volatile uint32_t *)0x10110148) & 1));
	while (!(*((volatile uint32_t *)0x1011014C) & 1));
	while (!(*((volatile uint32_t *)0x10110150) & 1));

	// ------------------------------------------------------
	// Remove remap to ensure a correct wakeup from deepsleep
	// ------------------------------------------------------
	*((uint32_t *)0x101E0000) = SRCCR & ~0x00000100;

	return 0;
}
