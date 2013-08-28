;/*******************************************************************************
; *                                 Wind River
; *      Work based on x-loader sources from STMicroelectronics which has the
; *      following notice:
; *
; *      Reproduction and Communication of this document is strictly prohibited
; *      unless specifically authorized in writing by STMicroelectronics.
; *
; *      This work, however, has made significant changes to the original
; *      baseline. In fact, there is very little code left from the original.
; *      The above notice has been retained, however, to avoid any issues.
; * 
; *		All Rights reserved by Wind River.
; *
; ******************************************************************************/

	.set Mode_USR, 0x10
	.set Mode_FIQ, 0x11
	.set Mode_IRQ, 0x12
	.set Mode_SVC, 0x13
	.set Mode_ABT, 0x17
	.set Mode_UND, 0x1B
	.set Mode_SYS, 0x1F

	.set I_Bit, 0x80
	.set F_Bit, 0x40

;/*****************************************************************************/

	.text
	.code 32

	.global _start

_start:
	b		Reset_Handler
	b		Undefined_Handler
	b		SWI_Handler
	b		Prefetch_Handler
	b		Abort_Handler
	nop
	b		IRQ_Handler
	b		FIQ_Handler

	.string "Copyright (c) STMicroelectronics. All Rights Reserved."
	.align 4

;/*****************************************************************************/

Reset_Handler:
	mrc		p15, 0, r1, c1, c0, 0	; /* Get processor special register */
	bic		r1, r1, #0x1			; /* MMU disable */
	orr		r1, r1, #(0x1 << 12)	; /* Icache enable */
	orr		r1, r1, #(0x1 << 2)		; /* Dcache enable */
	bic		r1, r1, #(0x1 << 3)		; /* Write buffer disable */
	mcr		p15, 0, r1, c1, c0, 0	; /* Store processor special register */

	; /* Fill stack with pattern */
	ldr		r1,=__SP_START
	ldr		r2,=__SP_END
	ldr		r3,StackFill
1:
	cmp		r1,r2
	stmltia	r1!,{r3}
	blt		1b

	; /* Check to see if the backup RAM has our magic key. */
	ldr		r2, BackupRAM
	ldr		r1, MagicKey
	ldr		r0, [r2]
	cmp		r0, r1
	beq		InitStacks
	str		r1, [r2]

	; /* Clear uninitialized data segment */
	ldr		r1,=__BSS_START
	ldr		r2,=__BSS_END
	mov		r3,#0
1:
	cmp		r1,r2
	stmltia	r1!,{r3}
	blt		1b

;/***************************************************************************/

InitStacks:
	msr		CPSR_c, #(Mode_IRQ | I_Bit | F_Bit)
	ldr		sp,=__IRQ_STACK_INIT

	msr		CPSR_c, #(Mode_FIQ | I_Bit | F_Bit)
	ldr		sp,=__FIQ_STACK_INIT

	msr		CPSR_c, #(Mode_SVC | I_Bit | F_Bit)
	ldr		sp,=__SVC_STACK_INIT

	msr		CPSR_c, #(Mode_ABT | I_Bit | F_Bit)
	ldr		sp,=__ABT_STACK_INIT

	msr		CPSR_c, #(Mode_UND| I_Bit | F_Bit)
	ldr		sp,=__UND_STACK_INIT

	msr		CPSR_c,#(Mode_SYS | I_Bit | F_Bit)
	ldr		sp,=__SP_END

	.extern main

	b		main

	swi		0xFFFFFF

Undefined_Handler:
	mov		r0,#'U'
	b		uart_out
SWI_Handler:
	mov		pc, lr
Prefetch_Handler:
	mov		r0,#'P'
	b		uart_out
Abort_Handler:
	mov		r0,#'A'
	b		uart_out
IRQ_Handler:
	mov		r0,#'I'
	b		uart_out
FIQ_Handler:
	mov		r0,#'F'
	b		uart_out

uart_out:
	ldr		r1,uart
1:
	str		r0,[r1]
	b		1b

	.global	MagicKey

BackupRAM:	.word	0x80010000
MagicKey:	.word	0x5aa555aa
StackFill:	.word	0xAAAAAAAA
uart:		.word	0x101FB000

	.size   _start, . - _start
	.end
