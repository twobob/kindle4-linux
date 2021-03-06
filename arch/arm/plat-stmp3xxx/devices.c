/*
* Freescale STMP37XX/STMP378X platform devices
*
* Embedded Alley Solutions, Inc <source@embeddedalley.com>
*
* Copyright 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
* Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
*/

/*
* The code contained herein is licensed under the GNU General Public
* License. You may obtain a copy of the GNU General Public License
* Version 2 or later at the following locations:
*
* http://www.opensource.org/licenses/gpl-license.html
* http://www.gnu.org/copyleft/gpl.html
*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/fsl_devices.h>
#include <linux/list.h>
#include <linux/delay.h>

#include <mach/dma.h>
#include <mach/platform.h>
#include <mach/stmp3xxx.h>
#include <mach/lcdif.h>
#include <mach/regs-lcdif.h>
#include <mach/regs-uartapp.h>
#include <mach/regs-gpmi.h>
#include <mach/regs-usbctrl.h>
#include <mach/regs-ssp.h>
#include <mach/regs-rtc.h>
#include <mach/regs-digctl.h>
#include <mach/regs-ocotp.h>
#include <mach/lcdif.h>
#include <mach/regs-power.h>
#include <mach/regs-clkctrl.h>

static u64 common_dmamask = DMA_BIT_MASK(32);

static void mxc_nop_release(struct device *dev)
{
	/* Nothing */
}

static struct resource appuart_resources[] = {
	{
		.start = IRQ_UARTAPP_INTERNAL,
		.end = IRQ_UARTAPP_INTERNAL,
		.flags = IORESOURCE_IRQ,
	}, {
		.start = IRQ_UARTAPP_RX_DMA,
		.end = IRQ_UARTAPP_RX_DMA,
		.flags = IORESOURCE_IRQ,
	}, {
		.start = IRQ_UARTAPP_TX_DMA,
		.end = IRQ_UARTAPP_TX_DMA,
		.flags = IORESOURCE_IRQ,
	}, {
		.start = REGS_UARTAPP1_PHYS,
		.end = REGS_UARTAPP1_PHYS + REGS_UARTAPP_SIZE - 1,
		.flags = IORESOURCE_MEM,
	}, {
		/* Rx DMA channel */
		.start = STMP3XXX_DMA(6, STMP3XXX_BUS_APBX),
		.end = STMP3XXX_DMA(6, STMP3XXX_BUS_APBX),
		.flags = IORESOURCE_DMA,
	}, {
		/* Tx DMA channel */
		.start = STMP3XXX_DMA(7, STMP3XXX_BUS_APBX),
		.end = STMP3XXX_DMA(7, STMP3XXX_BUS_APBX),
		.flags = IORESOURCE_DMA,
	},
};


struct platform_device stmp3xxx_appuart = {
	.name = "stmp3xxx-appuart",
	.id = 0,
	.resource = appuart_resources,
	.num_resources = ARRAY_SIZE(appuart_resources),
	.dev = {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

struct platform_device stmp3xxx_dbguart = {
	.name = "stmp3xxx-dbguart",
	.id = -1,
	.dev = {
		.release = mxc_nop_release,
		},
};

struct platform_device stmp3xxx_watchdog = {
      .name   = "stmp3xxx_wdt",
      .id     = -1,
	.dev = {
		.release = mxc_nop_release,
		},
};

static struct resource ts_resource[] = {
	{
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_TOUCH_DETECT,
		.end    = IRQ_TOUCH_DETECT,
	}, {
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_LRADC_CH5,
		.end    = IRQ_LRADC_CH5,
	},
};

struct platform_device stmp3xxx_touchscreen = {
	.name		= "stmp3xxx_ts",
	.id		= -1,
	.dev = {
		.release = mxc_nop_release,
		},
	.resource	= ts_resource,
	.num_resources	= ARRAY_SIZE(ts_resource),
};

static struct resource keyboard_resource[] = {
	{
	.flags  = IORESOURCE_IRQ,
	.start  = IRQ_LRADC_CH0,
	.end    = IRQ_LRADC_CH0,
	},
};

/*
* Keypad device
*/
struct platform_device stmp3xxx_keyboard = {
	.name		= "stmp3xxx-keyboard",
	.id		= -1,
	.dev = {
		.release = mxc_nop_release,
		},
	.resource	= keyboard_resource,
	.num_resources	= ARRAY_SIZE(keyboard_resource),
};

static struct resource gpmi_resources[] = {
	{
		.flags = IORESOURCE_MEM,
		.start = REGS_GPMI_PHYS,
		.end = REGS_GPMI_PHYS + REGS_GPMI_SIZE - 1,
	}, {
		.flags = IORESOURCE_IRQ,
		.start = IRQ_GPMI_DMA,
		.end = IRQ_GPMI_DMA,
	}, {
		.flags = IORESOURCE_DMA,
		.start = STMP3XXX_DMA(4, STMP3XXX_BUS_APBH),
		.end = STMP3XXX_DMA(8, STMP3XXX_BUS_APBH),
	},
};

struct platform_device stmp3xxx_gpmi = {
	.name = "gpmi",
	.id = -1,
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource = gpmi_resources,
	.num_resources = ARRAY_SIZE(gpmi_resources),
};

static struct resource mmc1_resource[] = {
	{
		.flags	= IORESOURCE_MEM,
		.start	= REGS_SSP1_PHYS,
		.end	= REGS_SSP1_PHYS + REGS_SSP_SIZE - 1,
	}, {
		.flags	= IORESOURCE_DMA,
		.start	= STMP3XXX_DMA(1, STMP3XXX_BUS_APBH),
		.end	= STMP3XXX_DMA(1, STMP3XXX_BUS_APBH),
	}, {
		.flags	= IORESOURCE_IRQ,
		.start	= IRQ_SSP1_DMA,
		.end	= IRQ_SSP1_DMA,
	}, {
		.flags	= IORESOURCE_IRQ,
		.start	= IRQ_SSP_ERROR,
		.end	= IRQ_SSP_ERROR,
	},
};

struct platform_device stmp3xxx_mmc = {
	.name	= "stmp3xxx-mmc",
	.id	= -1,
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource = mmc1_resource,
	.num_resources = ARRAY_SIZE(mmc1_resource),
};

static struct resource rtc_resources[] = {
	{
		.start	= REGS_RTC_PHYS,
		.end	= REGS_RTC_PHYS + REGS_RTC_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_RTC_ALARM,
		.end	= IRQ_RTC_ALARM,
		.flags	= IORESOURCE_IRQ,
	}, {
		.start	= IRQ_RTC_1MSEC,
		.end	= IRQ_RTC_1MSEC,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device stmp3xxx_rtc = {
	.name		= "stmp3xxx-rtc",
	.id		= -1,
	.dev = {
		.release = mxc_nop_release,
		},
	.resource	= rtc_resources,
	.num_resources	= ARRAY_SIZE(rtc_resources),
};

static struct resource ssp1_resources[] = {
	{
		.start	= REGS_SSP1_PHYS,
		.end	= REGS_SSP1_PHYS + REGS_SSP_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_SSP1_DMA,
		.end	= IRQ_SSP1_DMA,
		.flags	= IORESOURCE_IRQ,
	}, {
		.start	= STMP3XXX_DMA(1, STMP3XXX_BUS_APBH),
		.end	= STMP3XXX_DMA(1, STMP3XXX_BUS_APBH),
		.flags	= IORESOURCE_DMA,
	},
};

static struct resource ssp2_resources[] = {
	{
		.start	= REGS_SSP2_PHYS,
		.end	= REGS_SSP2_PHYS + REGS_SSP_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_SSP2_DMA,
		.end	= IRQ_SSP2_DMA,
		.flags	= IORESOURCE_IRQ,
	}, {
		.start	= STMP3XXX_DMA(2, STMP3XXX_BUS_APBH),
		.end	= STMP3XXX_DMA(2, STMP3XXX_BUS_APBH),
		.flags	= IORESOURCE_DMA,
	},
};

struct platform_device stmp3xxx_spi1 = {
	.name	= "stmp3xxx_ssp",
	.id	= 1,
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource = ssp1_resources,
	.num_resources = ARRAY_SIZE(ssp1_resources),
};

struct platform_device stmp3xxx_spi2 = {
	.name	= "stmp3xxx_ssp",
	.id	= 2,
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource = ssp2_resources,
	.num_resources = ARRAY_SIZE(ssp2_resources),
};

static struct resource fb_resource[] = {
	{
		.flags	= IORESOURCE_IRQ,
		.start	= IRQ_LCDIF_DMA,
		.end	= IRQ_LCDIF_DMA,
	}, {
		.flags	= IORESOURCE_IRQ,
		.start	= IRQ_LCDIF_ERROR,
		.end	= IRQ_LCDIF_ERROR,
	}, {
		.flags	= IORESOURCE_MEM,
		.start	= REGS_LCDIF_PHYS,
		.end	= REGS_LCDIF_PHYS + REGS_LCDIF_SIZE - 1,
	},
};

static struct stmp3xxx_platform_fb_data stmp3xxx_framebuffer_pdata = {
	.list = LIST_HEAD_INIT(stmp3xxx_framebuffer_pdata.list),
};

struct platform_device stmp3xxx_framebuffer = {
	.name		= "stmp3xxx-fb",
	.id		= -1,
	.dev		= {
		.release = mxc_nop_release,
		.dma_mask		= &common_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &stmp3xxx_framebuffer_pdata,
	},
	.num_resources	= ARRAY_SIZE(fb_resource),
	.resource	= fb_resource,
};

#define CMDLINE_DEVICE_CHOOSE(name, dev1, dev2)			\
	static char *cmdline_device_##name;			\
	static int cmdline_device_##name##_setup(char *dev)	\
	{							\
		cmdline_device_##name = dev + 1;		\
		return 0;					\
	}							\
	__setup(#name, cmdline_device_##name##_setup);		\
	int stmp3xxx_##name##_device_register(void)		\
	{							\
		struct platform_device *d = NULL;		\
		if (!cmdline_device_##name ||			\
			!strcmp(cmdline_device_##name, #dev1))	\
				d = &stmp3xxx_##dev1;		\
		else if (!strcmp(cmdline_device_##name, #dev2))	\
				d = &stmp3xxx_##dev2;		\
		else						\
			printk(KERN_ERR"Unknown %s assignment '%s'.\n",	\
				#name, cmdline_device_##name);	\
		return d ? platform_device_register(d) : -ENOENT;	\
	}

CMDLINE_DEVICE_CHOOSE(ssp1, mmc, spi1)
CMDLINE_DEVICE_CHOOSE(ssp2, gpmi, spi2)

struct platform_device stmp3xxx_backlight = {
	.name		= "stmp3xxx-bl",
	.id		= -1,
	.dev = {
		.release = mxc_nop_release,
		},
};

struct platform_device stmp3xxx_rotdec = {
	.name	= "stmp3xxx-rotdec",
	.id	= -1,
	.dev = {
		.release = mxc_nop_release,
		},
};

static const struct stmp3xxx_persistent_bit_config
stmp3xxx_persistent_bit_tab[] = {
	{ .reg = 0, .start =  0, .width =  1,
		.name = "CLOCKSOURCE" },
	{ .reg = 0, .start =  1, .width =  1,
		.name = "ALARM_WAKE_EN" },
	{ .reg = 0, .start =  2, .width =  1,
		.name = "ALARM_EN" },
	{ .reg = 0, .start =  3, .width =  1,
		.name = "CLK_SECS" },
	{ .reg = 0, .start =  4, .width =  1,
		.name = "XTAL24MHZ_PWRUP" },
	{ .reg = 0, .start =  5, .width =  1,
		.name = "XTAL32MHZ_PWRUP" },
	{ .reg = 0, .start =  6, .width =  1,
		.name = "XTAL32_FREQ" },
	{ .reg = 0, .start =  7, .width =  1,
		.name = "ALARM_WAKE" },
	{ .reg = 0, .start =  8, .width =  5,
		.name = "MSEC_RES" },
	{ .reg = 0, .start = 13, .width =  1,
		.name = "DISABLE_XTALOK" },
	{ .reg = 0, .start = 14, .width =  2,
		.name = "LOWERBIAS" },
	{ .reg = 0, .start = 16, .width =  1,
		.name = "DISABLE_PSWITCH" },
	{ .reg = 0, .start = 17, .width =  1,
		.name = "AUTO_RESTART" },
	{ .reg = 0, .start = 18, .width = 14,
		.name = "SPARE_ANALOG" },

	{ .reg = 1, .start =  0, .width =  1,
		.name = "FORCE_RECOVERY" },
	{ .reg = 1, .start =  1, .width =  1,
		.name = "NAND_SECONDARY_BOOT" },
	{ .reg = 1, .start =  2, .width =  1,
		.name = "NAND_SDK_BLOCK_REWRITE" },
	{ .reg = 1, .start =  3, .width =  1,
		.name = "SD_SPEED_ENABLE" },
	{ .reg = 1, .start =  4, .width =  1,
		.name = "SD_INIT_SEQ_1_DISABLE" },
	{ .reg = 1, .start =  5, .width =  1,
		.name = "SD_CMD0_DISABLE" },
	{ .reg = 1, .start =  6, .width =  1,
		.name = "SD_INIT_SEQ_2_ENABLE" },
	{ .reg = 1, .start =  7, .width =  1,
		.name = "OTG_ATL_ROLE_BIT" },
	{ .reg = 1, .start =  8, .width =  1,
		.name = "OTG_HNP_BIT" },
	{ .reg = 1, .start =  9, .width =  1,
		.name = "USB_LOW_POWER_MODE" },
	{ .reg = 1, .start = 10, .width =  1,
		.name = "SKIP_CHECKDISK" },
	{ .reg = 1, .start = 11, .width =  1,
		.name = "USB_BOOT_PLAYER_MODE" },
	{ .reg = 1, .start = 12, .width =  1,
		.name = "ENUMERATE_500MA_TWICE" },
	{ .reg = 1, .start = 13, .width = 19,
		.name = "SPARE_GENERAL" },

	{ .reg = 2, .start =  0, .width = 32,
		.name = "SPARE_2" },
	{ .reg = 3, .start =  0, .width = 32,
		.name = "SPARE_3" },
	{ .reg = 4, .start =  0, .width = 32,
		.name = "SPARE_4" },
	{ .reg = 5, .start =  0, .width = 32,
		.name = "SPARE_5" },
};

static struct stmp3xxx_platform_persistent_data stmp3xxx_persistent_data = {
	.bit_config_tab = stmp3xxx_persistent_bit_tab,
	.bit_config_cnt = ARRAY_SIZE(stmp3xxx_persistent_bit_tab),
};

struct platform_device stmp3xxx_persistent = {
	.name			= "stmp3xxx-persistent",
	.id			= -1,
	.dev = {
		.release = mxc_nop_release,
		.platform_data	= &stmp3xxx_persistent_data,
		},
};

struct platform_device stmp3xxx_dcp_bootstream = {
	.name			= "stmp3xxx-dcpboot",
	.id			= -1,
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

static struct resource dcp_resources[] = {
	{
		.start = IRQ_DCP_VMI,
		.end = IRQ_DCP_VMI,
		.flags = IORESOURCE_IRQ,
	}, {
		.start = IRQ_DCP,
		.end = IRQ_DCP,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device stmp3xxx_dcp = {
	.name			= "stmp3xxx-dcp",
	.id			= -1,
	.resource		= dcp_resources,
	.num_resources		= ARRAY_SIZE(dcp_resources),
	.dev	= {
		.release = mxc_nop_release,
		.dma_mask	= &common_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

static struct resource battery_resource[] = {
	{/* 0 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_VDD5V,
		.end    = IRQ_VDD5V,
	},
	{/* 1 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_DCDC4P2_BO,
		.end    = IRQ_DCDC4P2_BO,
	},
	{/* 2 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_BATT_BRNOUT,
		.end    = IRQ_BATT_BRNOUT,
	},
	{/* 3 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_VDDD_BRNOUT,
		.end    = IRQ_VDDD_BRNOUT,
	},
	{/* 4 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_VDD18_BRNOUT,
		.end    = IRQ_VDD18_BRNOUT,
	},
	{/* 5 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_VDDIO_BRNOUT,
		.end    = IRQ_VDDIO_BRNOUT,
	},
	{/* 6 */
		.flags  = IORESOURCE_IRQ,
		.start  = IRQ_VDD5V_DROOP,
		.end    = IRQ_VDD5V_DROOP,
	},

};

struct platform_device stmp3xxx_battery = {
	.name   = "stmp3xxx-battery",
	.resource = battery_resource,
	.dev	= {
		.release = mxc_nop_release,
		} ,
	.num_resources = ARRAY_SIZE(battery_resource),
};

struct resource viim_resources[] = {
	[0] = {
		.start  = REGS_DIGCTL_PHYS,
		.end    = REGS_DIGCTL_PHYS + PAGE_SIZE - 1,
		.flags  = IORESOURCE_MEM,
	},
	[1] = {
		.start  = REGS_OCOTP_PHYS,
		.end    = REGS_OCOTP_PHYS + PAGE_SIZE - 1,
		.flags  = IORESOURCE_MEM,
	},
};

struct platform_device stmp3xxx_viim = {
	.name   = "mxs_viim",
	.id     = 0,
	.dev	= {
		.release = mxc_nop_release,
		} ,
	.resource = viim_resources,
	.num_resources = ARRAY_SIZE(viim_resources),
};

struct platform_device stmp3xxx_spdif = {
	.name = "stmp3xxx-spdif",
	.id = -1,
	.dev	= {
		.release = mxc_nop_release,
		} ,
};
