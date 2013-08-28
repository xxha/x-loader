/* -------------------------------------------------------------------------
 * File: conf/default.dld
 *
 * This is the linker command file which dld uses by default if no linker
 * command file is specified.
 *
 * It specifies how the object files in a build will be linked and located.
 * Combined with other linker command files provided with the compiler, it
 * provides a base to build your own file for your particular system.
 *
 * For a description of the different statements in this file, please refer
 * to the D-LD section of the User's Guide

 * ------------------------------------------------------------------------ */

/* The MEMORY command defines a single memory area using a name intended
 * to suggest its purpose:
 *
 *   32k RAM at address 0xA0000000
 *		Bootstrap is loaded from offet 0 and can be 3800 in length
 *		The remainer is used for uninitialized data and stacks.
 * ------------------------------------------------------------------------ */

MEMORY	/* memory map of sta2065 init sram */
{
	boot (rw):	org = 0xA0000000, len = 0x3800
	ram  (rw):	org = 0xA0003800, len = 0x4800
}

/* The sizes of the stacks used by the application. NOTE: you need to adjust */
LOG_SIZE       = 2048;
C_STACK_SIZE   = 4096;
IRQ_STACK_SIZE = 32;
FIQ_STACK_SIZE = 32;
SVC_STACK_SIZE = 32;
ABT_STACK_SIZE = 32;
UND_STACK_SIZE = 32;

SECTIONS
{
	.text : {
		/* Take all code from all objects and libraries. */
		src/crt0.o
		*(.text)
		*(.rdata)
		*(.rodata)
		*(.frame_info)
		*(.j_class_table)
		*(.init)
		*(.fini)
		. = ALIGN(4);
	} > boot

	.const : {
		*(.sdata2)		/* small CONST area for some targets */
	} > boot

	.data BLOCK(4) : {
		__DATA_ROM	= .;
		__DATA_RAM	= .;
		*(.data)
		*(.j_pdata)
	} > boot

	/* constructor and destructor function ptrs */
	.ctors ALIGN(4) : { *(.ctors) } > boot
	.dtors ALIGN(4) : { *(.dtors) } > boot

	/* .sdata is the "small data area" for some targets. */
	.sdata ALIGN(4) : { *(.sdata) *(.j_spdata) } > boot

	__DATA_END	= .;
	
	.log : {
		__LOG_START = .;
		. += LOG_SIZE;
		__LOG_END = .;
	} > ram

	/* Allocate uninitialized sections.			    */

	.bss : {
		__BSS_START	= .;
		*(.sbss)
		*(.bss)
		*(.tibss)
		__BSS_END = .;
	} > ram

	.stacks : {
		/* Special stacks which shouldn't normally be used */
		. += IRQ_STACK_SIZE;
		. = ALIGN (4);
		__IRQ_STACK_INIT = . ;

		. += FIQ_STACK_SIZE;
		. = ALIGN (4);
		__FIQ_STACK_INIT = . ;

		. += SVC_STACK_SIZE;
		. = ALIGN (4);
		__SVC_STACK_INIT = . ;

        . += ABT_STACK_SIZE;
        . = ALIGN (4);
        __ABT_STACK_INIT = . ;

        . += UND_STACK_SIZE;
        . = ALIGN (4);
        __UND_STACK_INIT = . ;

		/* Any remaining space will be used as a heap.		    */

		__HEAP_START	= .;
	} > ram
}

__SP_END		= 0xA0008000;
__SP_START		= __SP_END - C_STACK_SIZE;		/* Stack size (defined above).	*/
__HEAP_END		= __SP_START;		    		/* Heap contiguous with stack.	*/
