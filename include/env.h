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

#ifndef _ENV_H_
#define _ENV_H_

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

int readenv(uint8_t *buf, uint32_t start, uint32_t end);
char *envVar (uint8_t *env, char *name);

#endif // _ENV_H_
