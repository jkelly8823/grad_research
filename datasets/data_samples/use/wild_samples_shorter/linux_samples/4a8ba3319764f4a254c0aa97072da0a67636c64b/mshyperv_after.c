	.rating		= 400, /* use this when running on Hyperv*/
	.read		= read_hv_clock,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

static void __init ms_hyperv_init_platform(void)
{