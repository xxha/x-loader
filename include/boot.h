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

#ifndef _BOOT_H_
#define _BOOT_H_

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

#define MASK_ALL16							0xFFFF

#define HCL_INTERNAL_ERROR					(-8)
#define HCL_NOT_CONFIGURED					(-7)
#define HCL_REQUEST_PENDING					(-6)
#define HCL_REQUEST_NOT_APPLICABLE			(-5)
#define HCL_INVALID_PARAMETER				(-4)
#define HCL_UNSUPPORTED_FEATURE				(-3)
#define HCL_UNSUPPORTED_HW					(-2)
#define HCL_ERROR							(-1)
#define HCL_OK								( 0)

typedef unsigned int bitfield_t;

#if !defined(FALSE) &&  !defined(TRUE)
typedef enum {FALSE = 0, TRUE = 1} bool_t;
#endif

int BL_InitPlatform (void);
int BL_WdtEnable (void);
int BL_InitDDRMemory (void);

#endif /* _BOOT_H_ */
