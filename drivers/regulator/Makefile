#
# Makefile for regulator drivers.
#

obj-$(CONFIG_REGULATOR) += core.o
obj-$(CONFIG_REGULATOR_FIXED_VOLTAGE) += fixed.o
obj-$(CONFIG_REGULATOR_VIRTUAL_CONSUMER) += virtual.o
obj-$(CONFIG_REGULATOR_USERSPACE_CONSUMER) += userspace-consumer.o

obj-$(CONFIG_REGULATOR_BQ24022) += bq24022.o
obj-$(CONFIG_REGULATOR_LP3971) += lp3971.o
obj-$(CONFIG_REGULATOR_MAX1586) += max1586.o
obj-$(CONFIG_REGULATOR_TWL4030) += twl4030-regulator.o
obj-$(CONFIG_REGULATOR_WM8350) += wm8350-regulator.o
obj-$(CONFIG_REGULATOR_WM8400) += wm8400-regulator.o
obj-$(CONFIG_REGULATOR_DA903X)	+= da903x.o
obj-$(CONFIG_REGULATOR_PCF50633) += pcf50633-regulator.o
obj-$(CONFIG_REGULATOR_MAX17135) += max17135-regulator.o
obj-$(CONFIG_REGULATOR_PAPYRUS) += papyrus-regulator.o
obj-$(CONFIG_REGULATOR_PAPYRUS_V2) += papyrus-regulator-v2.o

obj-$(CONFIG_REGULATOR_MC13892) += reg-mc13892.o
obj-$(CONFIG_REGULATOR_MC13783) += reg-mc13783.o
obj-$(CONFIG_REGULATOR_MC34704) += reg-mc34704.o
obj-$(CONFIG_REGULATOR_STMP3XXX) += stmp3xxx.o
obj-$(CONFIG_REGULATOR_MXS) += mxs-regulator.o
obj-$(CONFIG_REGULATOR_MC34708) += reg-mc34708.o

obj-$(CONFIG_REGULATOR_MC9S08DZ60) += reg-mc9s08dz60.o

ccflags-$(CONFIG_REGULATOR_DEBUG) += -DDEBUG
