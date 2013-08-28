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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef	__cplusplus
extern "C"
{
#endif

#include "MT29F2G16A.h"

#define VERSION				"1.0"
#define START_MESSAGE		"WindRiver STA2065 X-loader Version " VERSION "\r\n"

#define OS_NAND_START		0x00080000
#define OS_NAND_END			0x004fffff

#define ENV_NAND_START		0x00020000
#define ENV_NAND_END		0x00040000
#define ENV_RAM_ADDR		0x07000000

#define MACH_TYPE			2131
#define BOOT_PARAMS_OFFSET	0x100

#define BANK0_START			0x00000000
#define BANK0_SIZE			0x08000000

#define DEFAULT_ENV \
	"    " \
	"bootpart=0x80000:0x4fffff,0x6180000:0xeffffff\0" \
	"bootargs=console=ttyAMA1,115200n8 kgdboc=ttyAMA1 mtdoops.mtddev=Panic_Info" \
	" root=/dev/mtdblock4 rootfstype=romfs init=/linuxrc lpj=3112960 quiet\0" \
	"\0"

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _CONFIG_H_
