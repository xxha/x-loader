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

#ifndef _INC_GPIO_H_
#define _INC_GPIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "boot.h"

/*Total number of available GPIO pin */
#define GPIO_TOTAL_COUNT    160		/* 32 pin more for STA2065 */

/*GPIO DEVICE ID */
typedef enum
{
    GPIO_DEVICE_ID_INVALID  = 0x0,
    GPIO_DEVICE_ID_0        = 0x01,
    GPIO_DEVICE_ID_1        = 0x02,
    GPIO_DEVICE_ID_2        = 0x04,
    GPIO_DEVICE_ID_3        = 0x08,
    GPIO_DEVICE_ID_4        = 0x10	/* for STA2065 */
} t_gpio_device_id;

/* Error values returned by functions */
typedef enum
{
    GPIO_OK                     = HCL_OK,                       /* (0) */
    GPIO_INVALID_PARAMETER      = HCL_INVALID_PARAMETER         /* (-4) */
} gpio_error_t;

/*Pin description
  To be used in SOFTWARE mode: refers to a pin. */
typedef enum
{
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_16,
    GPIO_PIN_17,
    GPIO_PIN_18,
    GPIO_PIN_19,
    GPIO_PIN_20,
    GPIO_PIN_21,
    GPIO_PIN_22,
    GPIO_PIN_23,
    GPIO_PIN_24,
    GPIO_PIN_25,
    GPIO_PIN_26,
    GPIO_PIN_27,
    GPIO_PIN_28,
    GPIO_PIN_29,
    GPIO_PIN_30,
    GPIO_PIN_31,
    GPIO_PIN_32,
    GPIO_PIN_33,
    GPIO_PIN_34,
    GPIO_PIN_35,
    GPIO_PIN_36,
    GPIO_PIN_37,
    GPIO_PIN_38,
    GPIO_PIN_39,
    GPIO_PIN_40,
    GPIO_PIN_41,
    GPIO_PIN_42,
    GPIO_PIN_43,
    GPIO_PIN_44,
    GPIO_PIN_45,
    GPIO_PIN_46,
    GPIO_PIN_47,
    GPIO_PIN_48,
    GPIO_PIN_49,
    GPIO_PIN_50,
    GPIO_PIN_51,
    GPIO_PIN_52,
    GPIO_PIN_53,
    GPIO_PIN_54,
    GPIO_PIN_55,
    GPIO_PIN_56,
    GPIO_PIN_57,
    GPIO_PIN_58,
    GPIO_PIN_59,
    GPIO_PIN_60,
    GPIO_PIN_61,
    GPIO_PIN_62,
    GPIO_PIN_63,
    GPIO_PIN_64,
    GPIO_PIN_65,
    GPIO_PIN_66,
    GPIO_PIN_67,
    GPIO_PIN_68,
    GPIO_PIN_69,
    GPIO_PIN_70,
    GPIO_PIN_71,
    GPIO_PIN_72,
    GPIO_PIN_73,
    GPIO_PIN_74,
    GPIO_PIN_75,
    GPIO_PIN_76,
    GPIO_PIN_77,
    GPIO_PIN_78,
    GPIO_PIN_79,
    GPIO_PIN_80,
    GPIO_PIN_81,
    GPIO_PIN_82,
    GPIO_PIN_83,
    GPIO_PIN_84,
    GPIO_PIN_85,
    GPIO_PIN_86,
    GPIO_PIN_87,
    GPIO_PIN_88,
    GPIO_PIN_89,
    GPIO_PIN_90,
    GPIO_PIN_91,
    GPIO_PIN_92,
    GPIO_PIN_93,
    GPIO_PIN_94,
    GPIO_PIN_95,
    GPIO_PIN_96,
    GPIO_PIN_97,
    GPIO_PIN_98,
    GPIO_PIN_99,
    GPIO_PIN_100,
    GPIO_PIN_101,
    GPIO_PIN_102,
    GPIO_PIN_103,
    GPIO_PIN_104,
    GPIO_PIN_105,
    GPIO_PIN_106,
    GPIO_PIN_107,
    GPIO_PIN_108,
    GPIO_PIN_109,
    GPIO_PIN_110,
    GPIO_PIN_111,
    GPIO_PIN_112,
    GPIO_PIN_113,
    GPIO_PIN_114,
    GPIO_PIN_115,
    GPIO_PIN_116,
    GPIO_PIN_117,
    GPIO_PIN_118,
    GPIO_PIN_119,
    GPIO_PIN_120,
    GPIO_PIN_121,
    GPIO_PIN_122,
    GPIO_PIN_123,
    GPIO_PIN_124,
    GPIO_PIN_125,
    GPIO_PIN_126,
    GPIO_PIN_127,
/* for STA2065 */
    GPIO_PIN_128,
    GPIO_PIN_129,
    GPIO_PIN_130,
    GPIO_PIN_131,
    GPIO_PIN_132,
    GPIO_PIN_133,
    GPIO_PIN_134,
    GPIO_PIN_135,
    GPIO_PIN_136,
    GPIO_PIN_137,
    GPIO_PIN_138,
    GPIO_PIN_139,
    GPIO_PIN_140,
    GPIO_PIN_141,
    GPIO_PIN_142,
    GPIO_PIN_143,
    GPIO_PIN_144,
    GPIO_PIN_145,
    GPIO_PIN_146,
    GPIO_PIN_147,
    GPIO_PIN_148,
    GPIO_PIN_149,
    GPIO_PIN_150,
    GPIO_PIN_151,
    GPIO_PIN_152,
    GPIO_PIN_153,
    GPIO_PIN_154,
    GPIO_PIN_155,
    GPIO_PIN_156,
    GPIO_PIN_157,
    GPIO_PIN_158,
    GPIO_PIN_159
/* for STA2065 */
} gpio_pin_t;

/* Defines pin assignment(Software mode or Alternate mode) */
typedef enum
{
    GPIO_MODE_LEAVE_UNCHANGED,      /* Parameter will be ignored by the function. */
    GPIO_MODE_SOFTWARE,             /* Pin connected to GPIO (SW controlled) */
    GPIO_MODE_ALT_FUNCTION_A,       /* Pin connected to alternate function 1 (HW periph 1) */
    GPIO_MODE_ALT_FUNCTION_B,       /* Pin connected to alternate function 2 (HW periph 2) */
    GPIO_MODE_ALT_FUNCTION_C        /* Pin connected to alternate function 3 (HW periph 3) */
} gpio_mode_t;

/* Defines GPIO pin direction */
typedef enum
{
    GPIO_DIR_LEAVE_UNCHANGED,       /* Parameter will be ignored by the function. */
    GPIO_DIR_INPUT,                 /* GPIO set as input */
    GPIO_DIR_OUTPUT                 /* GPIO set as output */
} gpio_direction_t;

/* Debounce logic state */
typedef enum
{
    GPIO_DEBOUNCE_UNCHANGED,        /* Parameter will be ignored by the function. */
    GPIO_DEBOUNCE_DISABLE,          /* Debounce is disabled. */
    GPIO_DEBOUNCE_ENABLE            /* Debounce is enabled. It is not the case for STA_2062 */
} gpio_debounce_t;


/* This enumeration contains members for all gpio controller instances
   and is used in GPIO_Init() / GPIO_SetBaseAddress APIs. */
typedef enum
{
    GPIO_CTRL_ID_INVALID= 0x0,
    GPIO_CTRL_ID_0,
    GPIO_CTRL_ID_1,
    GPIO_CTRL_ID_2,
    GPIO_CTRL_ID_3,
    GPIO_CTRL_ID_4, /* Not for STn8815 and STA2062 and STA2064 but for STA2065 */
    GPIO_CTRL_ID_5, /* Not for STn8815 and STA2062 and STA2064 and STA2065 */
    GPIO_CTRL_ID_6, /* Not for STn8815 and STA2062 and STA2064 and STA2065 */
    GPIO_CTRL_ID_7  /* Not for STn8815 and STA2062 and STA2064 and STA2065 */
} gpio_ctrl_id_t;

/* Interrupt trigger mode */
typedef enum
{
    GPIO_TRIG_LEAVE_UNCHANGED,      /* Parameter will be ignored by the function */
    GPIO_TRIG_DISABLE,              /* Triggers no IT */
    GPIO_TRIG_RISING_EDGE,          /* Triggers an IT on a rising edge */
    GPIO_TRIG_FALLING_EDGE,         /* Triggers an IT on a falling edge */
    GPIO_TRIG_BOTH_EDGES           /* Triggers an IT on a rising and a falling edge */
//    GPIO_TRIG_HIGH_LEVEL,           /* Triggers an IT on a high level */
//    GPIO_TRIG_LOW_LEVEL             /* Triggers an IT on a low level */
} gpio_trig_t;

/* Configuration parameters for one GPIO pin.*/
typedef struct
{
    gpio_mode_t         mode;           /* Defines mode (SOFTWARE or Alternate). */
    gpio_direction_t    direction;      /* Define pin direction (in SOFTWARE mode only). */
    gpio_trig_t         trig;           /* Interrupt trigger (in SOFTWARE mode only) */
    gpio_debounce_t     debounce;       /* Debounce logic control for pin (in SOFTWARE mode only) */
} gpio_config_t;

/* GPIO pin data*/
typedef enum
{
    GPIO_DATA_LOW,                      /* GPIO pin status is low. */
    GPIO_DATA_HIGH                      /* GPIO pin status is high. */
} gpio_data_t;

/* GPIO behaviour in sleep mode */
typedef enum
{
    GPIO_SLEEP_MODE_LEAVE_UNCHANGED,    /* Parameter will be ignored by the function. */
    GPIO_SLEEP_MODE_INPUT_DEFAULTVOLT,  /* GPIO is an input with pull up/down enabled
									   when in sleep mode. */
    GPIO_SLEEP_MODE_CONTROLLED_BY_GPIO  /* GPIO pin  is controlled by GPIO IP. So mode,
									   direction and data values for GPIO pin in
									   sleep mode are determined by configuration
									   set to GPIO pin before entering to sleep mode. */
} gpio_sleep_mode_t;

/* GPIO ability to wake the system up from sleep mode.*/
typedef enum
{
    GPIO_WAKE_LEAVE_UNCHANGED,          /* Parameter will be ignored by the function. */
    GPIO_WAKE_DISABLE,                  /* GPIO will not wake the system from sleep mode. */
    GPIO_WAKE_LOW_LEVEL,                /* GPIO will wake the system up on a LOW level. */
    GPIO_WAKE_HIGH_LEVEL,                /* GPIO will wake the system up on a HIGH level. */
    GPIO_WAKE_RISING_EDGE,                /* GPIO will wake the system up on a RISING edge. */
    GPIO_WAKE_FALLING_EDGE,                /* GPIO will wake the system up on a FALLING edge. */
    GPIO_WAKE_BOTH_EDGES				      /* GPIO will wake the system up on both RISING and FALLING edge. */
} gpio_wake_t;

/* Configuration parameters for one GPIO pin in sleep mode.*/
typedef struct
{
    gpio_sleep_mode_t   sleep_mode; /* GPIO behaviour in sleep mode. */
    gpio_wake_t         wake;       /* GPIO ability to wake up the system. */
} gpio_sleep_config_t;

/* Enumeration t_gpio_device_id or ORing of enumeration t_gpio_device_id */
typedef uint32_t    gpio_multiple_device_id_t;

typedef uint32_t gpio_wakeup_status_t;

/* Interrupt status for all GPIO pins */
typedef struct
{
    bool_t gpio[GPIO_TOTAL_COUNT];
} gpio_pin_irq_status_t;    /* Interrupt status for all GPIO pins */


/*------------------------------------------------------------------------
 * Functions declaration
 *----------------------------------------------------------------------*/
gpio_error_t GPIO_Init(void);
gpio_error_t GPIO_SetPinConfig(gpio_pin_t, gpio_config_t);
gpio_data_t GPIO_ReadGpioPin(gpio_pin_t);
void GPIO_WriteGpioPin(gpio_pin_t pin, gpio_data_t Value);
void GPIO_SetGpioDir(gpio_pin_t pin, bool_t dir_output);

#ifdef __cplusplus
}                               /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif // __INC_GPIO_H_
