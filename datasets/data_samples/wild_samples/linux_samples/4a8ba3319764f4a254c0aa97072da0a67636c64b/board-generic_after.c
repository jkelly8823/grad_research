static const char *const omap243x_boards_compat[] __initconst = {
	"ti,omap2430",
	NULL,
};

DT_MACHINE_START(OMAP243X_DT, "Generic OMAP2430 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap243x_map_io,
	.init_early	= omap2430_init_early,
	.init_machine	= omap_generic_init,
	.init_time	= omap2_sync32k_timer_init,
	.dt_compat	= omap243x_boards_compat,
	.restart	= omap2xxx_restart,
MACHINE_END
#endif

#ifdef CONFIG_ARCH_OMAP3
/* Some boards need board name for legacy userspace in /proc/cpuinfo */
static const char *const n900_boards_compat[] __initconst = {
	"nokia,omap3-n900",
	NULL,
};

DT_MACHINE_START(OMAP3_N900_DT, "Nokia RX-51 board")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_time	= omap3_sync32k_timer_init,
	.dt_compat	= n900_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

/* Generic omap3 boards, most boards can use these */
static const char *const omap3_boards_compat[] __initconst = {
	"ti,omap3430",
	"ti,omap3",
	NULL,
};

DT_MACHINE_START(OMAP3_DT, "Generic OMAP3 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_time	= omap3_sync32k_timer_init,
	.dt_compat	= omap3_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

static const char *const omap36xx_boards_compat[] __initconst = {
	"ti,omap36xx",
	NULL,
};

DT_MACHINE_START(OMAP36XX_DT, "Generic OMAP36xx (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3630_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_time	= omap3_sync32k_timer_init,
	.dt_compat	= omap36xx_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

static const char *const omap3_gp_boards_compat[] __initconst = {
	"ti,omap3-beagle",
	"timll,omap3-devkit8000",
	NULL,
};

DT_MACHINE_START(OMAP3_GP_DT, "Generic OMAP3-GP (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_time	= omap3_secure_sync32k_timer_init,
	.dt_compat	= omap3_gp_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

static const char *const am3517_boards_compat[] __initconst = {
	"ti,am3517",
	NULL,
};

DT_MACHINE_START(AM3517_DT, "Generic AM3517 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= am35xx_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_time	= omap3_gptimer_timer_init,
	.dt_compat	= am3517_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END
#endif

#ifdef CONFIG_SOC_AM33XX
static const char *const am33xx_boards_compat[] __initconst = {
	"ti,am33xx",
	NULL,
};

DT_MACHINE_START(AM33XX_DT, "Generic AM33XX (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= am33xx_map_io,
	.init_early	= am33xx_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= am33xx_init_late,
	.init_time	= omap3_gptimer_timer_init,
	.dt_compat	= am33xx_boards_compat,
	.restart	= am33xx_restart,
MACHINE_END
#endif

#ifdef CONFIG_ARCH_OMAP4
static const char *const omap4_boards_compat[] __initconst = {
	"ti,omap4460",
	"ti,omap4430",
	"ti,omap4",
	NULL,
};

DT_MACHINE_START(OMAP4_DT, "Generic OMAP4 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= omap4_map_io,
	.init_early	= omap4430_init_early,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_late	= omap4430_init_late,
	.init_time	= omap4_local_timer_init,
	.dt_compat	= omap4_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#endif

#ifdef CONFIG_SOC_OMAP5
static const char *const omap5_boards_compat[] __initconst = {
	"ti,omap5432",
	"ti,omap5430",
	"ti,omap5",
	NULL,
};

DT_MACHINE_START(OMAP5_DT, "Generic OMAP5 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= omap5_map_io,
	.init_early	= omap5_init_early,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_late	= omap5_init_late,
	.init_time	= omap5_realtime_timer_init,
	.dt_compat	= omap5_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#endif

#ifdef CONFIG_SOC_AM43XX
static const char *const am43_boards_compat[] __initconst = {
	"ti,am4372",
	"ti,am43",
	NULL,
};

DT_MACHINE_START(AM43_DT, "Generic AM43 (Flattened Device Tree)")
	.map_io		= am33xx_map_io,
	.init_early	= am43xx_init_early,
	.init_late	= am43xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_time	= omap3_gptimer_timer_init,
	.dt_compat	= am43_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#endif

#ifdef CONFIG_SOC_DRA7XX
static const char *const dra74x_boards_compat[] __initconst = {
	"ti,am5728",
	"ti,am5726",
	"ti,dra742",
	"ti,dra7",
	NULL,
};

DT_MACHINE_START(DRA74X_DT, "Generic DRA74X (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= omap5_map_io,
	.init_early	= dra7xx_init_early,
	.init_late	= dra7xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_time	= omap5_realtime_timer_init,
	.dt_compat	= dra74x_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END

static const char *const dra72x_boards_compat[] __initconst = {
	"ti,am5718",
	"ti,am5716",
	"ti,dra722",
	NULL,
};

DT_MACHINE_START(DRA72X_DT, "Generic DRA72X (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap5_map_io,
	.init_early	= dra7xx_init_early,
	.init_late	= dra7xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_time	= omap5_realtime_timer_init,
	.dt_compat	= dra72x_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#endif