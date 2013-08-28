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

#ifndef _SUPPORT_H_
#define _SUPPORT_H_

#ifdef __GNUC__
#include <stdint.h>
#else
#include "cnew/stdint.h"
#endif

typedef struct {
	uint32_t start;
	uint32_t end;
} range_t;

void writeHex(uint32_t data);
void jumpTo(uint32_t entry);
int bootPart(range_t *range);
uint32_t loadImage(uint32_t start, uint32_t end);
void loadEnv(uint32_t start, uint32_t end);
int wdEnabled(void);

#endif // _SUPPORT_H_
