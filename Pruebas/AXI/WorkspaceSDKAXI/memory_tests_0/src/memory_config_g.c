/* This file is automatically generated based on your hardware design. */
#include "memory_config.h"

struct memory_range_s memory_ranges[] = {
	/* microblaze_0_d_bram_ctrl memory will not be tested since application resides in the same memory */
	{
		"MCB_DDR2",
		"axi_s6_ddrx",
		0xa8000000,
		134217728,
	},
};

int n_memory_ranges = 1;
