// SPDX-License-Identifier: GPL-2.0+
/*
 * Board init for the VD-RD Glasnost M9260.
 */

#include <fdtdec.h>
#include <init.h>
#include <asm/global_data.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_boot_params = gd->dram[0].start + 0x100;

	return 0;
}

int board_late_init(void)
{
	return 0;
}

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}
