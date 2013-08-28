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

#ifndef __DMA_H_
#define __DMA_H_

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

#ifdef	__cplusplus
extern "C"
{
#endif

/*
 * DMA Channel X Control Register bitfields
 */
#define DMA_CR_TSIZE(x)		(((x) & 0xFFF) <<  0)	/* Transfer Size               */
#define DMA_CR_SBSIZE(x)	(((x) & 0x007) << 12)	/* Source Burst Size           */
#define DMA_CR_DBSIZE(x)	(((x) & 0x007) << 15)	/* Destination Burst Size      */
#define DMA_CR_SWIDTH(x)	(((x) & 0x007) << 18)	/* Source Transfer Width       */
#define DMA_CR_DWIDTH(x)	(((x) & 0x007) << 21)	/* Destination Transfer Width  */
#define DMA_CR_SAHBM(x)		(((x) & 0x001) << 24)	/* Source AHB Master           */
#define DMA_CR_DAHBM(x)		(((x) & 0x001) << 25)	/* Destination AHB Master      */
#define DMA_CR_SRCI			(1 << 26)				/* Source Address Increment    */
#define DMA_CR_DSTI			(1 << 27)				/* Destination Addr. Increment */
#define DMA_CR_PROT_PAM		(1 << 28)				/* Privileged Access Mode      */
#define DMA_CR_PROT_BUF		(1 << 29)				/* Bufferable Access Mode      */
#define DMA_CR_PROT_CAC		(1 << 30)				/* Cacheable Access Mode       */
#define DMA_CR_TCIE			(1 << 31)				/* Terminal Count Int. Enable  */

/*
 * Length is in 16-bit words
 */
void dma_copy16 (void *dest, void *src, int len, uint32_t flags);

#ifdef	__cplusplus
}
#endif

#endif // _DMA_H_
