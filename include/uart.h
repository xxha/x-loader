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

#ifndef _UART_H_
#define _UART_H_

#include "boot.h"

typedef enum
{
  /* standard error defines */
  UART_UNSUPPORTED_HW	= HCL_UNSUPPORTED_HW,	/* (-2) */
  UART_ERROR			= HCL_ERROR,			/* (-1) */
  UART_OK				= HCL_OK				/* (0)  */
} uart_error_t;

// Parity definition
typedef enum
{
	NOPARITY_BIT,
	EVEN_PARITY_BIT,
	ODD_PARITY_BIT,
	PARITY_0_BIT,
	PARITY_1_BIT
} uart_parity_bit_t;

// Data bits number
typedef enum
{
	DATABITS_5 = 0x0,
	DATABITS_6 = 0x1,
	DATABITS_7 = 0x2,
	DATABITS_8 = 0x3
} uart_data_bits_t;

// Stop bits number
typedef enum
{
	ONE_STOPBIT = 0x0,
	TWO_STOPBITS = 0x1
} uart_stop_bits_t;

typedef enum
{
	BR110BAUD		= 0x2F6A88,
	BR1200BAUD		= 0x0009C4,
	BR2400BAUD		= 0x0004E2,
	BR9600BAUD		= 0x200138,
	BR38400BAUD		= 0x08004E,
	BR115200BAUD	= 0x03001A,
	BR230400BAUD	= 0x02000D,
	BR460800BAUD	= 0x210006,
	BR921600BAUD	= 0x110003,
	BR1843200BAUD	= 0x290001,
	BR3000000BAUD	= 0x000001
} uart_baudrate_t;

uart_error_t UART_Init(uart_baudrate_t, uart_parity_bit_t,
		uart_stop_bits_t, uart_data_bits_t);

int puts(const char *buf);
void UART_flush(void);

#endif /* _UART_H_ */
