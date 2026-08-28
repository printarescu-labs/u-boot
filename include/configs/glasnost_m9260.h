/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration settings for the VD-RD Glasnost M9260 board (AT91SAM9260).
 *
 * AT91Bootstrap is the first-stage bootloader for this board: it performs
 * SoC clock/SDRAM init and loads U-Boot proper directly into SDRAM. U-Boot
 * itself does not redo that init (CONFIG_SKIP_LOWLEVEL_INIT).
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/hardware.h>
#include <linux/sizes.h>

/* ARM asynchronous clock. */
#define CFG_SYS_AT91_SLOW_CLOCK	32768		/* slow clock xtal */
#define CFG_SYS_AT91_MAIN_CLOCK	18432000	/* main clock xtal */

/*
 * SDRAM: 1 bank, already initialized by AT91Bootstrap.
 * TODO: size not yet confirmed against the real schematic.
 */
#define CFG_SYS_SDRAM_BASE		ATMEL_BASE_CS1
#define CFG_SYS_SDRAM_SIZE		(64 * SZ_1M)

/*
 * Note: the pre-relocation stack does NOT live here - the defconfig sets
 * CONFIG_HAS_CUSTOM_SYS_INIT_SP_ADDR / CONFIG_CUSTOM_SYS_INIT_SP_ADDR to put
 * it in SDRAM just below CONFIG_TEXT_BASE instead. The AT91SAM9260 has only
 * 4 KiB of internal SRAM at ATMEL_BASE_SRAM1 (0x00300000), so the default
 * SYS_INIT_SP_ADDR (CFG_SYS_INIT_RAM_ADDR + CFG_SYS_INIT_RAM_SIZE - GD) would
 * place the stack, GD and the 8 KiB SYS_MALLOC_F_LEN arena at
 * 0x00301E00..0x00303F00 - entirely past the end of that SRAM, working only
 * by AHB address aliasing folding it back onto itself. AT91Bootstrap has
 * SDRAM up before it loads us, so there is no reason to rely on that.
 */
#define CFG_SYS_INIT_RAM_SIZE	(16 * 1024)
#define CFG_SYS_INIT_RAM_ADDR	ATMEL_BASE_SRAM1

/*
 * Standard Boot (bootstd) device priority: try MMC first, fall back to the
 * SPI-NOR recovery bootflow (read via CONFIG_BOOTMETH_SCRIPT/sf_bootdev) only
 * if MMC yields nothing bootable.
 */
#define CFG_EXTRA_ENV_SETTINGS \
	"boot_targets=mmc0 spi_flash0\0"

#endif
