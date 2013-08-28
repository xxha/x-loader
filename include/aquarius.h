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

#ifndef _AQUARIUS_H_
#define _AQUARIUS_H_

#include "boot.h"

/* -------------------------------------------------------------- */
/* Memory Mapping for AQUARIUS  */
/* -------------------------------------------------------------- */

/* Embedded SRAM bank 0 (32 kByte mapped only) */
#define BOOT_RAM_BANK0_START_ADDR       0xA0000000
#define BOOT_RAM_BANK0_LENGTH           0x00008000
#define BOOT_RAM_BANK0_END_ADDR         (BOOT_RAM_BANK0_START_ADDR+BOOT_RAM_BANK0_LENGTH-1)

/* Embedded backup RAM (512 bytes mapped only) */
#define BACKUP_RAM_START_ADDR           0x80010000
#define BACKUP_RAM_LENGTH               0x00000200
#define BACKUP_RAM_END_ADDR             (BACKUP_RAM_START_ADDR+BACKUP_RAM_LENGTH-1)

/* Embedded boot ROM (32 Kbyte mapped only) */
#define BOOT_ROM_START_ADDR             0x80000000
#define BOOT_ROM_LENGTH                 0x00008000
#define BOOT_ROM_END_ADDR               (BOOT_ROM_START_ADDR+BOOT_ROM_LENGTH-1)

/* CF/CF+/NAND Flash chip-select 0 (SMPS0n LOW) */
#define NAND_FLASH_CS0_START_ADDR       0x40000000
#define NAND_FLASH_CS0_LENGTH           0x10000000
#define NAND_FLASH_CS0_END_ADDR         (NAND_FLASH_CS0_START_ADDR+NAND_FLASH_CS0_LENGTH-1)

/* CF/CF+/NAND Flash chip-select 1 (SMPS1n LOW) */
#define NAND_FLASH_CS1_START_ADDR       0x50000000
#define NAND_FLASH_CS1_LENGTH           0x10000000
#define NAND_FLASH_CS1_END_ADDR         (NAND_FLASH_CS1_START_ADDR+NAND_FLASH_CS1_LENGTH-1)

/* SDRAM chip-select 0 */
#define SDRAM_CS0_START_ADDR            0x00000000
#define SDRAM_CS0_LENGTH                0x08000000
#define SDRAM_CS0_END_ADDR              (SDRAM_CS0_START_ADDR+SDRAM_CS0_LENGTH-1)

/* SDRAM chip-select 1 */
#define SDRAM_CS1_START_ADDR            0x08000000
#define SDRAM_CS1_LENGTH                0x08000000
#define SDRAM_CS1_END_ADDR              (SDRAM_CS1_START_ADDR+SDRAM_CS1_LENGTH-1)

/* Static Memory Ctrl. configuration registers */
#define FSMC_REG_START_ADDR             0x10100000
#define FSMC_REG_LENGTH                 CNTRL_REG_SIZE
#define FSMC_REG_END_ADDR               (FSMC_REG_START_ADDR+FSMC_REG_LENGTH-1)

/* ------------------------------------------------------------ */
/* CORE APB peripheral address mapping                          */
/* ------------------------------------------------------------ */

/* General Purpose I/Os 128...159 (only for STA2065) */
#define GPIO4_REG_START_ADDR            0x101EA000
#define GPIO4_REG_LENGTH                CNTRL_REG_SIZE
#define GPIO4_REG_END_ADDR              (GPIO4_REG_START_ADDR+GPIO4_REG_LENGTH-1)

/* General Purpose I/Os 96...127 */
#define GPIO3_REG_START_ADDR            0x101E7000
#define GPIO3_REG_LENGTH                CNTRL_REG_SIZE
#define GPIO3_REG_END_ADDR              (GPIO3_REG_START_ADDR+GPIO3_REG_LENGTH-1)

/* General Purpose I/Os 64...95 */
#define GPIO2_REG_START_ADDR            0x101E6000
#define GPIO2_REG_LENGTH                CNTRL_REG_SIZE
#define GPIO2_REG_END_ADDR              (GPIO2_REG_START_ADDR+GPIO2_REG_LENGTH-1)

/* General Purpose I/Os 32...63 */
#define GPIO1_REG_START_ADDR            0x101E5000
#define GPIO1_REG_LENGTH                CNTRL_REG_SIZE
#define GPIO1_REG_END_ADDR              (GPIO1_REG_START_ADDR+GPIO1_REG_LENGTH-1)

/* General Purpose I/Os 0...31 */
#define GPIO0_REG_START_ADDR            0x101E4000
#define GPIO0_REG_LENGTH                CNTRL_REG_SIZE
#define GPIO0_REG_END_ADDR              (GPIO0_REG_START_ADDR+GPIO0_REG_LENGTH-1)

/* Multi Timer Unit (Timers 4...7) */
#define MTU1_REG_START_ADDR             0x101E3000
#define MTU1_REG_LENGTH                 CNTRL_REG_SIZE
#define MTU1_REG_END_ADDR               (MTU1_REG_START_ADDR+MTU1_REG_LENGTH-1)

/* Multi Timer Unit (Timers 0...3) */
#define MTU0_REG_START_ADDR             0x101E2000
#define MTU0_REG_LENGTH                 CNTRL_REG_SIZE
#define MTU0_REG_END_ADDR               (MTU0_REG_START_ADDR+MTU0_REG_LENGTH-1)

/* System and Reset controller */
#define SRC_REG_START_ADDR              0x101E0000
#define SRC_REG_LENGTH                  CNTRL_REG_SIZE
#define SRC_REG_END_ADDR                (SRC_REG_START_ADDR+SRC_REG_LENGTH-1)

/* ------------------------------------------------------------ */
/* Core DMA APB peripheral address mapping                      */
/* ------------------------------------------------------------ */

/* UART0 interface */
#define UART0_REG_START_ADDR            0x101FD000
#define UART0_REG_LENGTH                CNTRL_REG_SIZE
#define UART0_REG_END_ADDR              (UART0_REG_START_ADDR+UART0_REG_LENGTH-1)

/* UART1 interface */
#define UART1_REG_START_ADDR            0x101FB000
#define UART1_REG_LENGTH                CNTRL_REG_SIZE
#define UART1_REG_END_ADDR              (UART1_REG_START_ADDR+UART1_REG_LENGTH-1)

/* UART2 interface */
#define UART2_REG_START_ADDR            0x101F2000
#define UART2_REG_LENGTH                CNTRL_REG_SIZE
#define UART2_REG_END_ADDR              (UART2_REG_START_ADDR+UART2_REG_LENGTH-1)

/* UART3 interface */
#define UART3_REG_START_ADDR            0x101FE000
#define UART3_REG_LENGTH                CNTRL_REG_SIZE
#define UART3_REG_END_ADDR              (UART3_REG_START_ADDR+UART3_REG_LENGTH-1)

/*------------------------------------------------------------------------
 * Flexible Static Memory Controller (FSMC)
 *----------------------------------------------------------------------*/
/* Aquarius FSMC 8 v1.0 register definition */
/* Common Memory Space Timing Register */
typedef struct
{
	bitfield_t Tset :8;           /* common memory Set up time: read and write cycle */
	bitfield_t Twait :8;          /* common memory wait time: read and write cycle  */
	bitfield_t Thold :8;          /* common memory hold time: read and write cycle  */
	bitfield_t Thiz :8;           /* common memory data bus HiZ time: write cycle only */
} gmc_comm_attr_ioata_reg_t;

/* PC-Card/NAND/ATA-Flash Interrupts and FIFO register */
typedef struct
{
	bitfield_t intris :1;         /* Interrupt rising edge */
	bitfield_t intlev :1;         /* interrupt level  */
	bitfield_t intfal :1;         /* Interrupt falling edge */
	bitfield_t enaris :1;         /* Enable rising edge           */
	bitfield_t enalev :1;         /* Enable level   */
	bitfield_t enafal :1;         /* Enable falling edge  */
	bitfield_t fifemp :1;         /* FIFO empty   */
	bitfield_t ecctyp :3;         /* ECC type   */
	bitfield_t errfnd :4;         /* Errors found   */
	bitfield_t codtyp :1;         /* Code type   */
	bitfield_t codrdy :1;         /* Code ready   */
	bitfield_t bytbch8 :8;        /* Byte 13 of BCH8: trailer of the ECC NAND */
	bitfield_t unused :8;         /* unused    */
} gmc_status_reg_t;

/* PC-Card/NAND/ATA-Flash Control register */
typedef struct
{
	bitfield_t reset :1;          /* Software reset for PCcard #1   */
	bitfield_t wait_on :1;        /* Wait sensitivity enable bit         */
	bitfield_t enable :1;         /* PC-Card/NAND/ATA enable device */
	bitfield_t devtyp :1;         /* Device type                          */
	bitfield_t devwid :2;         /* Device width for all type of memories */
	bitfield_t eccen :1;          /* ECC computation logic enable bit      */
	bitfield_t eccplen :1;        /* ECC page Length                     */
	bitfield_t addrmux :1;        /* PCcard: muxed address         */
	bitfield_t tclr :4;           /* NAND Flash: CLE to REb delay           */
	bitfield_t tar :4;            /* NAND Flash: ALE to REb delay            */
	bitfield_t pagesize :3;       /* NAND Flash, extended ECC only      */
	bitfield_t unused :12;        /* unused     */
} gmc_pc_reg_t;

typedef volatile struct
{
	gmc_pc_reg_t PC;                      /* Control Register                                     0x40 */
	gmc_status_reg_t STATUS;              /* Interrupts and FIFO status                           0x44 */
	gmc_comm_attr_ioata_reg_t COMM;       /* Timings for PCcard Common mode and NAND              0x48 */
	gmc_comm_attr_ioata_reg_t ATTRIB;     /* Timings for PCcard Attribute mode and wait mode NAND 0x4C */
	gmc_comm_attr_ioata_reg_t IO_ATA;     /* Timings for PCcard I/O mode and ATA                  0x50 */
	uint32_t ECCr;                        /* 1st 32 ECC bytes for NAND                            0x54 */
	uint32_t ECC2r;                       /* 2nd 32 ECC bytes for NAND                            0x58 */
	uint32_t ECC3r;                       /* 3rd 32 ECC bytes for NAND                            0x5C */
} fsmc_nand_ata_pccard_aquarius_reg_t;

typedef volatile struct
{
	uint32_t FSMC_BCR0;   // 0x00
	uint32_t FSMC_BTR0;   // 0x04
	uint32_t FSMC_BCR1;   // 0x08
	uint32_t FSMC_BTR1;   // 0x0C
	uint32_t FSMC_BCR2;   // 0x10
	uint32_t FSMC_BTR2;   // 0x14
	uint32_t FSMC_BCR3;   // 0x18
	uint32_t FSMC_BTR3;   // 0x1C
	uint32_t UNUSED0[8];  // [0x18 - 0x40]
	uint32_t FSMC_PCR0;   // 0x40
	uint32_t FSMC_PISR0;  // 0x44
	uint32_t FSMC_PMEM0;  // 0x48
	uint32_t FSMC_PATT0;  // 0x4C
	uint32_t FSMC_PIO0;   // 0x50
	uint32_t FSMC_ECCR0;  // 0x54
	uint32_t FSMC_ECC2R0; // 0x58
	uint32_t FSMC_ECC3R0; // 0x5C
} FSMCRegs;

/*------------------------------------------------------------------------
 * System & Reset Controler (SRC)
 *----------------------------------------------------------------------*/
/* SRC control register */
typedef struct
{
	bitfield_t modeControl :3;
	bitfield_t modeStatus :4;
	bitfield_t batOk :1;
	bitfield_t remapClrReq :1;
	bitfield_t remapStatus :1;
	bitfield_t unused1 :1;
	bitfield_t fstartnbypstat :1;
	bitfield_t dclksync :1;
	bitfield_t unused2 :2;
	bitfield_t tim0Sel :1;
	bitfield_t unused3 :1;
	bitfield_t tim1Sel :1;
	bitfield_t unused4 :1;
	bitfield_t tim2Sel :1;
	bitfield_t unused5 :1;
	bitfield_t tim3Sel :1;
	bitfield_t unused6 :1;
	bitfield_t tim4Sel :1;
	bitfield_t pll2pbo :1;
	bitfield_t tim5Sel :1;
	bitfield_t pll1pbo :1;
	bitfield_t tim6Sel :1;
	bitfield_t hclksrc :1;
	bitfield_t tim7Sel :1;
	bitfield_t dclksrc :2;
} src_control_reg_t;

/* SRC Interupt Mode Control Register */
typedef struct
{
	bitfield_t itEnable :1;
	bitfield_t itMode :3;
	bitfield_t itType :1;
	bitfield_t itPriority :1;
	bitfield_t Pll1Mask :1;
	bitfield_t Pll2Mask :1;
	bitfield_t unused :24;
} src_it_mode_ctrl_reg_t;

/* SRC Interupt Mode Status Register */
typedef struct
{
	bitfield_t itStatus :1;
	bitfield_t Pll1Mis :1;
	bitfield_t Pll2Mis :1;
	bitfield_t unused :29;
} src_it_mode_sta_reg_t;

/* SRC Xtal Control Register */
typedef struct
{
	bitfield_t xtalCtrlOverride :1;
	bitfield_t xtalEnable :1;
	bitfield_t xtalStatus :1;
	bitfield_t xtalTimeout :16;
	bitfield_t sxtalenable :1;
	bitfield_t xtalTimen :1;
	bitfield_t fStart :1;
	bitfield_t unused :10;
} src_xtal_control_reg_t;

/* SRC PLL Control Register */
typedef struct
{
	bitfield_t pll1CtrlOverride :1;
	bitfield_t pll1Enable :1;
	bitfield_t pll1Status :1;
	bitfield_t pll1Timeout :25;
	bitfield_t pll2Enable :1;
	bitfield_t pll2Status :1;
	bitfield_t pllLockTimen :1;
	bitfield_t unused :1;
} src_pll_control_reg_t;

/* SRC PLL Frequency Register */
typedef struct
{
	bitfield_t pll1PDiv :3;
	bitfield_t unused1 :5;
	bitfield_t pll1NMul :6;
	bitfield_t unused2 :2;
	bitfield_t pll2PDiv :1;
	bitfield_t unused3 :7;
	bitfield_t pll2NMul :6;
	bitfield_t unused4 :2;
} src_pll_freq_reg_t;

/* SRC Reset Status Register */
typedef struct
{
	bitfield_t powerOnReset :1;
	bitfield_t unused1 :1;
	bitfield_t watchdogReset :1;
	bitfield_t softReset :1;
	bitfield_t sleepReset :1;
	bitfield_t remap0 :1;
	bitfield_t remap1 :1;
	bitfield_t unused :25;
} src_reset_status_reg_t;

/* SRC Clock Output Config Register */
typedef struct
{
	bitfield_t clkDiv0 :6;
	bitfield_t clkSel0 :3;
	bitfield_t unused1 :7;
	bitfield_t clkDiv1 :6;
	bitfield_t clkSel1 :3;
	bitfield_t unused2 :7;
} src_clk_output_conf_reg_t;

/* SRC Clock Divider Control register */
typedef struct
{
	bitfield_t gpsclk4xdiv :4;
	bitfield_t gpssclk16sel :1;
	bitfield_t clcdclkdivsel :5;
	bitfield_t sclkdivsel :2;
	bitfield_t unused1 :3;
	bitfield_t dclkdivsel :2;
	bitfield_t unused2 :2;
	bitfield_t sdmmc52sel :3;
	bitfield_t unused3 :6;
	bitfield_t traceclkmuxsel :3;
	bitfield_t unused4 :1;
} src_clk_divider_ctrl_reg_t;

/* SRC registers */
typedef volatile struct
{
	src_control_reg_t Control;                    /* System control register                      0x000 */
	src_it_mode_ctrl_reg_t ItControl;             /* Interrupt mode control register              0x004 */
	src_it_mode_sta_reg_t ItStatus;               /* Interrupt mode status register               0x008 */
	src_xtal_control_reg_t XtalControl;           /* Crystal control register                     0x00C */
	src_pll_control_reg_t PllControl;             /* PLL control register                         0x010 */
	src_pll_freq_reg_t PllFreq;                   /* PLL frequency register                       0x014 */
	src_reset_status_reg_t ResetStatus;           /* Reset status register                        0x018 */
	uint32_t unused_1[(0x024 - 0x01C) >> 2];      /* unused */
	uint32_t PeriphClkEn0;                        /* Peripheral clock enable register 0           0x024 */
	uint32_t PeriphClkDis0;                       /* Peripheral clock disable register 0          0x028 */
	uint32_t PeriphEnStatus0;                     /* Peripheral clock enable status register 0    0x02C */
	uint32_t PeriphClkStatus0;                    /* Peripheral clock status register 0           0x030 */
	uint32_t PeriphClkEn1;                        /* Peripheral clock enable register 1           0x034 */
	uint32_t PeriphClkDis1;                       /* Peripheral clock disable register 1          0x038 */
	uint32_t PeriphEnStatus1;                     /* Peripheral clock enable status register 1    0x03C */
	uint32_t PeriphClkStatus1;                    /* Peripheral clock status register 1           0x040 */
	src_clk_output_conf_reg_t ClockOutConfig;     /* Clock Output Configuration register          0x044 */
	uint32_t PeriphClkEn2;                        /* Peripheral clock enable register 2           0x048 */
	uint32_t PeriphClkDis2;                       /* Peripheral clock disable register 2          0x04C */
	uint32_t PeriphEnStatus2;                     /* Peripheral clock enable status register 2    0x050 */
	uint32_t PeriphClkStatus2;                    /* Peripheral clock status register 2           0x054 */
	src_clk_divider_ctrl_reg_t ScClkDivCr;        /* SRC Clock Divider Control register           0x058 */
	uint32_t unused_2[(0xFE0 - 0x05C) >> 2];      /* unused */
	const uint32_t PeriphID[4];                   /* Peripheral id registers                      0xFE0 */
	const uint32_t PCellID[4];                    /* PrimeCell id registers                       0xFF0 */
} src_register_t;

/*------------------------------------------------------------------------
 * General Purpose IOs (GPIO)
 *----------------------------------------------------------------------*/
/* GPIO registers */
typedef volatile struct
{
	uint32_t gpio_dat;                            /* 0x000 GPIO data register */
	uint32_t gpio_dats;                           /* 0x004 GPIO data Set register */
	uint32_t gpio_datc;                           /* 0x008 GPIO data Clear register */
	uint32_t gpio_pdis;                           /* 0x00C GPIO Pull disable register */
	uint32_t gpio_dir;                            /* 0x010 GPIO data direction register */
	uint32_t gpio_dirs;                           /* 0x014 GPIO data direction Set register */
	uint32_t gpio_dirc;                           /* 0x018 GPIO data direction Clear register */
	uint32_t gpio_slpm;                           /* 0x01C GPIO Sleep mode register */
	uint32_t gpio_afsla;                          /* 0x020 GPIO Alternate Function Select register A*/
	uint32_t gpio_afslb;                          /* 0x024 GPIO Alternate Function Select register B*/
	uint32_t reserved_1[(0x040 - 0x028) >> 2];    /* unused */
	uint32_t gpio_rimsc;                          /* 0x040 GPIO rising edge interrupt set/clear*/
	uint32_t gpio_fimsc;                          /* 0x044 GPIO falling edge interrupt set/clear register*/
	uint32_t gpio_is;                             /* 0x048 GPIO masked interrupt status register*/
	uint32_t gpio_ic;                             /* 0x04C GPIO Interrupt Clear register*/
	uint32_t reserved_2[(0xFE0 - 0x050) >> 2];    /* unused */
	uint32_t gpio_periph_id_0;                    /* 0xFE0 Peripheral identification register bits 7:0*/
	uint32_t gpio_periph_id_1;                    /* 0xFE4 Peripheral identification register bits 15:8*/
	uint32_t gpio_periph_id_2;                    /* 0xFE8 Peripheral identification register bits 23:16*/
	uint32_t gpio_periph_id_3;                    /* 0xFEC Peripheral identification register bits 31:24*/
	uint32_t gpio_pcell_id_0;                     /* 0xFF0 Peripheral identification register bits 7:0*/
	uint32_t gpio_pcell_id_1;                     /* 0xFF4 Peripheral identification register bits 15:8*/
	uint32_t gpio_pcell_id_2;                     /* 0xFF8 Peripheral identification register bits 23:16*/
	uint32_t gpio_pcell_id_3;                     /* 0xFFC Peripheral identification register bits 31:24*/
} gpio_register_t;

/*------------------------------------------------------------------------
 * Timers Unit (MTU)
 *----------------------------------------------------------------------*/
/* MTU Control register */
typedef volatile struct
{
	bitfield_t OneShot :1;
	bitfield_t Size :1;
	bitfield_t Prescaler :2;
	bitfield_t unused1 :2;
	bitfield_t Mode :1;
	bitfield_t Enable :1;
	bitfield_t unused2 :24;
} tmr_ctrl_reg_t;

/* MTU registers */
typedef volatile struct
{
	uint32_t IMSC;                        /* @0x00 */
	uint32_t RIS;                         /* @0x04 */
	uint32_t MIS;                         /* @0x08 */
	uint32_t IntClr;                      /* @0x0C */
	uint32_t TMR1Load;                    /* @0x10 */
	uint32_t TMR1Value;                   /* @0x14 */
	tmr_ctrl_reg_t TMR1Control;           /* @0x18 */
	uint32_t TMR1BGLoad;                  /* @0x1C */
	uint32_t TMR2Load;                    /* @0x20 */
	uint32_t TMR2Value;                   /* @0x24 */
	tmr_ctrl_reg_t TMR2Control;           /* @0x28 */
	uint32_t TMR2BGLoad;                  /* @0x2C */
	uint32_t TMR3Load;                    /* @0x30 */
	uint32_t TMR3Value;                   /* @0x34 */
	tmr_ctrl_reg_t TMR3Control;           /* @0x38 */
	uint32_t TMR3BGLoad;                  /* @0x3C */
	uint32_t TMR4Load;                    /* @0x40 */
	uint32_t TMR4Value;                   /* @0x44 */
	tmr_ctrl_reg_t TMR4Control;           /* @0x48 */
	uint32_t TMR4BGLoad;                  /* @0x4C */
	uint32_t unused[(0xFE0 - 0x50) >> 2];
	uint32_t PeriphID0;                   /* @0xFE0 */
	uint32_t PeriphID1;                   /* @0xFE4 */
	uint32_t PeriphID2;                   /* @0xFE8 */
	uint32_t PeriphID3;                   /* @0xFEC */
	uint32_t PCellID0;                    /* @0xFF0 */
	uint32_t PCellID1;                    /* @0xFF4 */
	uint32_t PCellID2;                    /* @0xFF8 */
	uint32_t PCellID3;                    /* @0xFFC */
} mtu_register_t;

/*------------------------------------------------------------------------
 * Universal asynchronous eEcevier and Transmitter (UART)
 *----------------------------------------------------------------------*/
/* UART Data register Register */
typedef struct
{
	bitfield_t    Data   :8;
	bitfield_t    Error  :4;
	bitfield_t    unused :20;
} uart_dr_reg_t;

/* UART Flag Register */
typedef struct
{
	bitfield_t ClearToSend :1;
	bitfield_t DataSetReady :1;
	bitfield_t DataCarrierDetect :1;
	bitfield_t Busy :1;
	bitfield_t ReceiveFifoEmpty :1;
	bitfield_t TransmitFifoFull :1;
	bitfield_t ReceiveFifoFull :1;
	bitfield_t TransmitFifoEmpty :1;
	bitfield_t RingIndicator :1;
	bitfield_t DCTS :1;
	bitfield_t DDSR :1;
	bitfield_t DDCD :1;
	bitfield_t TERI :1;
	bitfield_t RTXDIS :1;
	bitfield_t unused :18;
} uart_flag_reg_t;

/* UART Line Control Register */
typedef union
{
	struct
	{
		bitfield_t SendBreak :1;
		bitfield_t ParityEnable :1;
		bitfield_t EvenParitySelect :1;
		bitfield_t TwoStopBitsSelect :1;
		bitfield_t FifoEnable :1;
		bitfield_t WordLength :2;
		bitfield_t StickParitySelect :1;
		bitfield_t unused :24;
	} Bit;
	uint32_t Reg;
} uart_lcr_reg_t;

/* UART Control Register */
typedef union
{
	struct
	{
		bitfield_t UartEnable :1;
		bitfield_t Unused1 :2;
		bitfield_t OversamplingFactor :1;
		bitfield_t Unused2 :3;
		bitfield_t LoopBackEnable :1;
		bitfield_t TransmitEnable :1;
		bitfield_t ReceiveEnable :1;
		bitfield_t DataTransmitReady :1;
		bitfield_t RequestToSend :1;
		bitfield_t Unused3 :2;
		bitfield_t RTSEnable :1;
		bitfield_t CTSEnable :1;
		bitfield_t unused3 :16;
	} Bit;
	uint32_t Reg;
} uart_cr_reg_t;

/* UART Interrupt Clear/Mask Register */
typedef struct
{
	bitfield_t TxIntFifoLevel :3;
	bitfield_t RxIntFifoLevel :3;
	bitfield_t unused2 :26;
} uart_ifls_reg_t;

/* UART Interrupt Clear/Mask Register */
typedef union
{
	struct
	{
		bitfield_t RingIndicatorModem :1;
		bitfield_t ClearToSendModem :1;
		bitfield_t DataCarrierDetectModem :1;
		bitfield_t DataSetReadyModem :1;
		bitfield_t Received :1;
		bitfield_t Transmit :1;
		bitfield_t ReceivedTimeout :1;
		bitfield_t FramingError :1;
		bitfield_t ParityError :1;
		bitfield_t BreakError :1;
		bitfield_t OverrunError :1;
		bitfield_t XOFFInterrupt :1;
		bitfield_t unused :20;
	} Bit;
	uint32_t Reg;
} uart_int_reg_t;

/* UART registers */
typedef volatile struct
{
	uart_dr_reg_t DATA;                           /* data register                                0x000 */
	uint32_t RSR;                                 /* Receive status/Error clear register          0x004 */
	uint32_t unused_1[(0x018 - 0x008) >> 2];      /* unused */
	uart_flag_reg_t FR;                           /* Flag register                                0x018 */
	uint32_t unused_2[(0x024 - 0x01C) >> 2];      /* unused */
	uint32_t IBRD;                                /* Integer baud rate register                   0x024 */
	uint32_t FBRD;                                /* Fractional baud rate register                0x028 */
	uart_lcr_reg_t LCRH;                          /* Line Control register                        0x02C */
	uart_cr_reg_t CR;                             /* Control register                             0x030 */
	uart_ifls_reg_t IFLS;                         /* Interrupt Fifo level select register         0x034 */
	uart_int_reg_t IMSC;                          /* Interrupt mask set/clear register            0x038 */
	uint32_t RIS;                                 /* Raw Interrupt register                       0x03C */
	uart_int_reg_t MIS;                           /* Masked Interrupt register                    0x040 */
	uart_int_reg_t ICR;                           /* Interrupt Clear register                     0x044 */
	uint32_t DMACR;                               /* DMA Control register                         0x048 */
	uint32_t unused_3;                            /* unused */
	uint32_t XFCR;                                /* XON/XOFF Control register                    0x050 */
	uint32_t XON1;                                /* Xon1 character for sw flow control           0x054 */
	uint32_t XON2;                                /* Xon2 character for sw flow control           0x058 */
	uint32_t XOFF1;                               /* Xoff1 character for sw flow control          0x05C */
	uint32_t XOFF2;                               /* Xoff2 character for sw flow control          0x060 */
	uint32_t unused_4[(0x100 - 0x064) >> 2];      /* unused */
	uint32_t ABCR;                                /* Autobaud Control register                    0x100 */
	uint32_t ABSR;                                /* Autobaud Status register                     0x104 */
	uint32_t ABFMT;                               /* Autobaud Format register                     0x108 */
	uint32_t unused_5[(0x150 - 0x10C) >> 2];      /* unused */
	uint32_t ABDR;                                /* Autobaud Divisor register                    0x150 */
	uint32_t ABDFR;                               /* Autobaud Divisor Fraction register           0x154 */
	uint32_t ABMR;                                /* Autobaud Measurement register                0x158 */
	uint32_t ABIMSC;                              /* Autobaud Interrupt Mask register             0x15C */
	uint32_t ABRIS;                               /* Autobaud Raw Interrupt status register       0x160 */
	uint32_t ABMIS;                               /* Autobaud Masked Interrupt register           0x164 */
	uint32_t ABICR;                               /* Autobaud Interrupt Clear register            0x168 */
	uint32_t unused_6[(0xFE0 - 0x16C) >> 2];      /* unused */
	uint32_t PeriphID0;                           /* Peripheral id register0                      0xFE0 */
	uint32_t PeriphID1;                           /* Peripheral id register1                      0xFE4 */
	uint32_t PeriphID2;                           /* Peripheral id register2                      0xFE8 */
	uint32_t PeriphID3;                           /* Peripheral id register3                      0xFEC */
	uint32_t PCellID0;                            /* PrimeCell id register0                       0xFF0 */
	uint32_t PCellID1;                            /* PrimeCell id register1                       0xFF4 */
	uint32_t PCellID2;                            /* PrimeCell id register2                       0xFF8 */
	uint32_t PCellID3;                            /* PrimeCell id register3                       0xFFC */
} uart_register_t;

#endif /* _AQUARIUS_H_ */
