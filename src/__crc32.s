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

		; /* Speed up CRC calculation by fetching 32 bytes at a time. */
		; /* Measurements show this is 2x faster than C version. */

		.global		__crc32
		; /* uint32_t __crc32(uint32_t crc, uint8_t *buf, uint32_t len, uint32_t *tbl); */

__crc32:
		push	{r4-r12}

		; /* crc ^= 0xffffffff */
		mov		r4, #0xffffffff
		eor		r0, r0, r4

		; /* crc = tbl[(crc ^ *buf++) & 0xff] ^ (crc >> 8) */
odd:	ands	r4, r1, #3				; /* on an odd boundry? */
		beq		even
		subs	r2, r2, #1
		blt		done
		ldrb	r4, [r1], #1			; /* do up to 3 bytes here */
		eor		r4, r0, r4
		and		r4, r4, #255
		ldr		r4, [r3, r4, lsl #2]
		eor		r0, r4, r0, lsr #8
		b		odd

loop:	ldmia	r1!,{r4-r11}			; /* grab 8 longs, 32 bytes */
		eor		r12, r0 ,r4				; /* do 1st byte of r4 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r4, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r4, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r4, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r5				; /* do 1st byte of r5 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r5, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r5, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r5, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r6				; /* do 1st byte of r6 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r6, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r6, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r6, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r7				; /* do 1st byte of r7 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r7, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r7, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r7, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r8				; /* do 1st byte of r8 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r8, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r8, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r8, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r9				; /* do 1st byte of r9 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r9, lsr #8		; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r9, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0 ,r9, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r10			; /* do 1st byte of r10 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r10, lsr #8	; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r10, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r10, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r11			; /* do 1st byte of r11 */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r11, lsr #8	; /* do 2nd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r11, lsr #16	; /* do 3rd byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

		eor		r12, r0, r11, lsr #24	; /* do 4th byte */
		and		r12, r12, #255
		ldr		r12, [r3, r12, lsl #2]
		eor		r0, r12, r0, lsr #8

even:	subs	r2, r2, #32				; /* can we do 32 bytes at a time? */
		bge		loop					; /* yes! */

		adds	r2, r2, #32				; /* no, so get back how much is left */
		ble		done					; /* any? */

		; /* one byte at a time */
one:	ldrb	r4, [r1], #1
		eor		r4, r0, r4
		and		r4, r4, #255
		ldr		r4, [r3, r4, lsl #2]
		eor		r0, r4, r0, lsr #8
		subs	r2, r2, #1
		bne		one

		; /* crc ^= 0xffffffff */
done:	mov		r3, #0xffffffff
		eor		r0, r0, r3

		pop		{r4-r12}
		mov		pc, lr
