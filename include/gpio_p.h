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

#ifndef _INC_GPIOP_H_
#define _INC_GPIOP_H_

#include "aquarius.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------*/
/* Peripheral Ids and PCell Ids */
#define GPIO_PERIPH_ID_0    0x60
#define GPIO_PERIPH_ID_1    0x00
#define GPIO_PERIPH_ID_2    0x18
#define GPIO_PERIPH_ID_3    0x1F
#define GPIO_PCELL_ID_0     0x0D
#define GPIO_PCELL_ID_1     0xF0
#define GPIO_PCELL_ID_2     0x05
#define GPIO_PCELL_ID_3     0xB1

#define GPIO_ALL_ZERO   	0x00000000

#define GPIO_BLOCKS_COUNT   5	/* one more for STA2065 */
#define GPIO_NO_OF_PINS     32

#define GPIO_DAT_OFFSET		0x00	
#define GPIO_DATS_OFFSET	0x04
#define GPIO_PDIS_OFFSET	0x0C
#define GPIO_SLPM_OFFSET	0x1C
#define GPIO_RIMSC_OFFSET	0x40
#define GPIO_FIMSC_OFFSET	0x44
#define GPIO_MIS_OFFSET		0x48
#define GPIO_MIC_OFFSET		0x4C

#define GPIO_PIN16_HIGH		0x00010000
#define GPIO_PIN82_HIGH		0x00040000

/* GPIO register structure */
typedef struct
{
	gpio_register_t *reg[GPIO_BLOCKS_COUNT];
} gpio_system_context_t;

#ifdef __cplusplus
}   /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif // _INC_GPIOP_H_
