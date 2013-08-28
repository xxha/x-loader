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

#ifndef _IRQ_H_
#define _IRQ_H_

#ifdef __GNUC__
/*
 * Enable IRQs
 */
static void irq_enable(void)
{
	__asm__ ("mrs	r0, cpsr");
	__asm__ ("bic	r0, r0, #128");
	__asm__ ("msr	cpsr_c, r0");
}

/*
 * Disable IRQs
 */
static void irq_disable(void)
{
	__asm__ ("mrs	r0, cpsr");
	__asm__ ("orr	r0, r0, #128");
	__asm__ ("msr	cpsr_c, r0");
}

/*
 * Enable FIQs
 */
static void fiq_enable(void)
{
	__asm__ ("mrs	r0, cpsr");
	__asm__ ("bic	r0, r0, #64");
	__asm__ ("msr	cpsr_c, r0");
}

/*
 * Disable FIQs
 */
static void fiq_disable(void)
{
	__asm__ ("mrs	r0, cpsr");
	__asm__ ("orr	r0, r0, #64");
	__asm__ ("msr	cpsr_c, r0");
}
#else
/*
 * Enable IRQs
 */
asm static void irq_enable(void)
{
	mrs	r0, cpsr
	bic	r0, r0, #128
	msr	cpsr_c, r0
}

/*
 * Disable IRQs
 */
asm static void irq_disable(void)
{
	mrs	r0, cpsr
	orr	r0, r0, #128
	msr	cpsr_c, r0
}

/*
 * Enable FIQs
 */
asm static void fiq_enable(void)
{
	mrs	r0, cpsr
	bic	r0, r0, #64
	msr	cpsr_c, r0
}

/*
 * Disable FIQs
 */
asm static void fiq_disable(void)
{
	mrs	r0, cpsr
	orr	r0, r0, #64
	msr	cpsr_c, r0
}
#endif

#endif // _IRQ_H_
