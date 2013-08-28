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

#include "aquarius.h"
#include "gpio_p.h"

static gpio_system_context_t gpio = {
		(gpio_register_t *) GPIO0_REG_START_ADDR,
		(gpio_register_t *) GPIO1_REG_START_ADDR,
		(gpio_register_t *) GPIO2_REG_START_ADDR,
		(gpio_register_t *) GPIO3_REG_START_ADDR,
		(gpio_register_t *) GPIO4_REG_START_ADDR
};

static const gpio_config_t GPIO_IN_Config = {
		GPIO_MODE_SOFTWARE,
		GPIO_DIR_INPUT,
		GPIO_TRIG_LEAVE_UNCHANGED,
		GPIO_DEBOUNCE_UNCHANGED
};

gpio_error_t GPIO_Init(void)
{
	/* Initializing the registers structure */
	return GPIO_SetPinConfig(GPIO_PIN_82, GPIO_IN_Config);
}

gpio_error_t GPIO_SetPinConfig(gpio_pin_t pin, gpio_config_t config)
{
	uint32_t block = ((uint32_t) pin / GPIO_NO_OF_PINS);
	uint32_t mask = (uint32_t) (1 << ((uint32_t) pin % GPIO_NO_OF_PINS));

	switch (config.mode)
	{
	case GPIO_MODE_SOFTWARE:
		gpio.reg[block]->gpio_afsla &= ~mask;
		gpio.reg[block]->gpio_afslb &= ~mask;

		switch (config.direction)
		{
		case GPIO_DIR_INPUT:
			gpio.reg[block]->gpio_dirc = mask;
			break;

		case GPIO_DIR_OUTPUT:
			gpio.reg[block]->gpio_dirs = mask;
			break;

		case GPIO_DIR_LEAVE_UNCHANGED:
			break;

		default:
			return GPIO_INVALID_PARAMETER;
		}

		break;

	case GPIO_MODE_ALT_FUNCTION_A:
		gpio.reg[block]->gpio_afsla |= mask;
		gpio.reg[block]->gpio_afslb &= ~mask;
		break;

	case GPIO_MODE_ALT_FUNCTION_B:
		gpio.reg[block]->gpio_afsla &= ~mask;
		gpio.reg[block]->gpio_afslb |= mask;
		break;

	case GPIO_MODE_ALT_FUNCTION_C:
		gpio.reg[block]->gpio_afsla |= mask;
		gpio.reg[block]->gpio_afslb |= mask;
		break;

	case GPIO_MODE_LEAVE_UNCHANGED:
		break;

	default:
		return GPIO_INVALID_PARAMETER;
	}

	return GPIO_OK;
}

gpio_data_t GPIO_ReadGpioPin(gpio_pin_t pin)
{
	uint32_t block = ((uint32_t) pin / GPIO_NO_OF_PINS);
	uint32_t mask = (uint32_t) (1 << ((uint32_t) pin % GPIO_NO_OF_PINS));

	return ((gpio.reg[block]->gpio_dat & mask) != GPIO_ALL_ZERO) ?
			GPIO_DATA_HIGH : GPIO_DATA_LOW;
}

void GPIO_WriteGpioPin(gpio_pin_t pin, gpio_data_t Value)
{
	uint32_t block = ((uint32_t) pin / GPIO_NO_OF_PINS);
	uint32_t mask = (uint32_t) (1 << ((uint32_t) pin % GPIO_NO_OF_PINS));

	if (Value == GPIO_DATA_HIGH)
		gpio.reg[block]->gpio_dats = mask;
	else
		gpio.reg[block]->gpio_datc = mask;
}

void GPIO_SetGpioDir(gpio_pin_t pin, bool_t dir_output)
{
	uint32_t block = ((uint32_t) pin / GPIO_NO_OF_PINS);
	uint32_t mask = (uint32_t) (1 << ((uint32_t) pin % GPIO_NO_OF_PINS));

	if (dir_output)
		gpio.reg[block]->gpio_dirs = mask;
	else
		gpio.reg[block]->gpio_dirc = mask;
}
