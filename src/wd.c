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

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

#include "irq.h"

#define CARTESIO_VIC_BASE	0x10140000
#define CARTESIO_WDT_BASE	0x101E1000

#define VIC_IRQSR(x)	((x) * 0x20 + 0x000)	/* IRQ Status Register X (X = 0-1)         */
#define VIC_FIQSR(x)	((x) * 0x20 + 0x004)	/* FIQ Status Register X (X = 0-1)         */
#define VIC_RIS(x)		((x) * 0x20 + 0x008)	/* Raw Interrupt Status Reg. X (X = 0-1)   */
#define VIC_ISEL(x)		((x) * 0x20 + 0x00C)	/* Interrupt Selection Reg. X (X = 0-1)    */
#define VIC_IENS(x)		((x) * 0x20 + 0x010)	/* Interrupt Enable Set Reg. X (X = 0-1)   */
#define VIC_IENC(x)		((x) * 0x20 + 0x014)	/* Interrupt Enable Clear Reg. X (X = 0-1) */
#define VIC_SWISR(x)	((x) * 0x20 + 0x018)	/* SW Interrupt Set Register X (X = 0-1)   */
#define VIC_SWICR(x)	((x) * 0x20 + 0x01C)	/* SW Interrupt Clear Reg. X (X = 0-1)     */
#define VIC_PER		0x40						/* Protection Enable Register              */
#define VIC_CVAR	0x50						/* Current Vector Address Register         */
#define VIC_DVAR	0x54						/* Default Vector Address Register         */
#define VIC_VAR(x)	((x) * 0x04 + 0x100)		/* Vector Address Register X (X = 0-15)    */
#define VIC_VCR(x)	((x) * 0x04 + 0x200)		/* Vector Control Register X (X = 0-15)    */

#define NR_VECTOR_IRQS	16
#define NR_IRQ_BLOCKS	2

/*
 * WDT register map (offsets)
 */
#define WDT_LR		0x00		/* Watchdog Timer Load Register     */
#define WDT_VAL		0x04		/* Watchdog Timer Value Register    */
#define WDT_CR		0x08		/* Watchdog Timer Control Register  */
#define WDT_ICR		0x0C		/* Interrupt Clear Register         */
#define WDT_RIS		0x10		/* Raw Interrupt Status Register    */
#define WDT_MIS		0x14		/* Masked Interrupt Status Register */
#define WDT_LOCK	0x18		/* Watchdog Timer Lock Register     */

/*
 * WDT Control Register bits
 */
#define CR_INTEN	(1 << 0)	/* Watchdog Timer Interrupt Enable  */
#define CR_RESEN	(1 << 1)	/* Watchdog Timer Reset Enable      */

static void writel(uint32_t value, uint32_t addr)
{
	*((volatile uint32_t *)addr) = value;
}

int wdtEnable(void)
{
	unsigned int i;

	/* Reset VIC and disable all interrupts */
	for (i = 0; i < NR_IRQ_BLOCKS; i++) {
		writel( 0, CARTESIO_VIC_BASE + VIC_ISEL(i));
		writel(~0, CARTESIO_VIC_BASE + VIC_IENC(i));
		writel(~0, CARTESIO_VIC_BASE + VIC_SWICR(i));
	}
	for (i = 0; i < NR_VECTOR_IRQS; i++) {
		writel(0, CARTESIO_VIC_BASE + VIC_VCR(i));
		writel(0, CARTESIO_VIC_BASE + VIC_VAR(i));
	}
	writel(0, CARTESIO_VIC_BASE + VIC_CVAR);
	writel(0, CARTESIO_VIC_BASE + VIC_DVAR);

	// ------------------------------
	// enable IRQ for WDT
	// ------------------------------
	writel(1, CARTESIO_VIC_BASE + VIC_IENS(0));

	// ------------------
	// set WDTLOAD = 4s
	// ------------------
	writel(0xffff, CARTESIO_WDT_BASE + WDT_LR);

	// ------------------------------
	// enable WDT reset and interrupt
	// ------------------------------
	writel(CR_RESEN | CR_INTEN, CARTESIO_WDT_BASE + WDT_CR);

	irq_enable();

	return 0;
}
