	}

static struct rockchip_cpuclk_rate_table rk3288_cpuclk_rates[] __initdata = {
	RK3288_CPUCLK_RATE(1800000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1704000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1608000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1512000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1416000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1200000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE(1008000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 816000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 696000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 600000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 408000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 312000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 216000000, 2, 4, 2, 4, 4),
	RK3288_CPUCLK_RATE( 126000000, 2, 4, 2, 4, 4),
};

static const struct rockchip_cpuclk_reg_data rk3288_cpuclk_data = {
	.core_reg = RK3288_CLKSEL_CON(0),