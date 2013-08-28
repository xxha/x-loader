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

#ifndef _BOOT_CRC_H_
#define _BOOT_CRC_H_

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

// Ethernet FCS algorithm, accumulating the result from a previous CRC calculation
uint32_t crc32(uint32_t, uint8_t *, uint32_t);

#endif /* _BOOT_CRC_H_ */
