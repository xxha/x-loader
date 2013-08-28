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

#include <string.h>

#include "aquarius.h"
#include "uart.h"
#include "gpio_p.h"

extern char __LOG_START;
extern char __LOG_END;

static char *logBuffer;

static bool_t IsRxfifoEmpty(void)
{
	uart_register_t *pUartRegs = (uart_register_t *) UART1_REG_START_ADDR;

	return (pUartRegs->FR.ReceiveFifoEmpty) ? TRUE : FALSE;
}

static bool_t IsTxfifoFull(void)
{
	uart_register_t *pUartRegs = (uart_register_t *) UART1_REG_START_ADDR;

	return (pUartRegs->FR.TransmitFifoFull) ? TRUE : FALSE;
}

static bool_t IsTxfifoEmpty(void)
{
	uart_register_t *pUartRegs = (uart_register_t *) UART1_REG_START_ADDR;

	return (pUartRegs->FR.TransmitFifoEmpty) ? TRUE : FALSE;
}

uart_error_t UART_Init(uart_baudrate_t baudrate, uart_parity_bit_t parity_bit,
		uart_stop_bits_t stop_bits, uart_data_bits_t data_bits)
{
	/* Variable to flush Rx fifo */
	volatile uint32_t dataflushed;

	uart_register_t *pUartRegs = (uart_register_t *) UART1_REG_START_ADDR;
	gpio_register_t *pGpio0Regs = (gpio_register_t *) GPIO0_REG_START_ADDR;

	logBuffer = &__LOG_START;
	memset(logBuffer, 0, &__LOG_END - logBuffer);

	// Reset main registers : really need ?
	pUartRegs->CR.Reg = 0; /* RTL 4 : reset value = 0x300 */
	pUartRegs->RSR = 0;
	pUartRegs->IMSC.Reg = 0;

	// Control register
	pUartRegs->CR.Bit.UartEnable = 1; /* enable Uart functionality */

	//configure baudrate (MUST be performed before a LCRH write)
	pUartRegs->IBRD = (uint32_t) (baudrate & MASK_ALL16); /* program baudrate: integer part	*/
	pUartRegs->FBRD = (uint32_t) (baudrate >> 16); /* program baudrate: fractional part*/

	//configure line control register
	pUartRegs->LCRH.Reg = 0;
	pUartRegs->LCRH.Bit.SendBreak = 0; /* Disable sendbreak 					*/
	pUartRegs->LCRH.Bit.FifoEnable = 1; /* enable Fifo 							*/
	pUartRegs->LCRH.Bit.WordLength = (data_bits >> 1 - 1); /* 00=5bits 01=6bits 10=7bits 11=8bits 	*/
	pUartRegs->LCRH.Bit.TwoStopBitsSelect = stop_bits; /* 0=1 stop bits 1=2 stop bits			*/

	pUartRegs->LCRH.Bit.ParityEnable = 0;
	pUartRegs->LCRH.Bit.StickParitySelect = 0;
	pUartRegs->LCRH.Bit.EvenParitySelect = 0;

	/* Enable Alternate function A : GPIO[56-57] are under control of UART1 */
	pGpio0Regs->gpio_afsla |= 0xC000; /* Alt A: Set bits 14 & 15: UART1 Transmitted Serial Data and UART1 Received Serial Data */
	pGpio0Regs->gpio_afslb &= ~((uint32_t) 0xC000); /* Alt A: Set bits 14 & 15: UART1 Transmitted Serial Data and UART1 Received Serial Data */

	/* Set to 4 characters the interrupt FIFO level for transmit and receive */
	pUartRegs->IFLS.TxIntFifoLevel = 2;
	pUartRegs->IFLS.RxIntFifoLevel = 2;

	/* All It are cleared */
	pUartRegs->ICR.Bit.ReceivedTimeout = 1;
	pUartRegs->ICR.Bit.Received = 1;
	pUartRegs->ICR.Bit.FramingError = 1;
	pUartRegs->ICR.Bit.OverrunError = 1;
	pUartRegs->ICR.Bit.ParityError = 1;
	pUartRegs->ICR.Bit.BreakError = 1;
	pUartRegs->ICR.Bit.ReceivedTimeout = 1;
	pUartRegs->ICR.Bit.Received = 1;
	pUartRegs->ICR.Bit.Transmit = 1;

	/* Enable IT */
	pUartRegs->IMSC.Reg = 0;
	pUartRegs->IMSC.Bit.BreakError = 1;
	pUartRegs->IMSC.Bit.ParityError = 1;
	pUartRegs->IMSC.Bit.FramingError = 1;
	pUartRegs->IMSC.Bit.OverrunError = 1;

	pUartRegs->CR.Bit.ReceiveEnable = 1; /* enable RX */

	while (!IsRxfifoEmpty())
		dataflushed = pUartRegs->DATA.Data;

	pUartRegs->CR.Bit.TransmitEnable = 1; /* enable TX */

	while (!IsTxfifoEmpty());

	return UART_OK;
}

int puts(const char *buf)
{
	uart_register_t *pUartRegs = (uart_register_t *) UART1_REG_START_ADDR;

	while (*buf)
	{
		while (IsTxfifoFull());
		*logBuffer++ = *buf;
		if (logBuffer >= &__LOG_END)
			logBuffer = &__LOG_START;
		pUartRegs->DATA.Data = *buf++;
	}
	*logBuffer = 0;
}

void UART_flush(void)
{
	while (!IsTxfifoEmpty());
}
