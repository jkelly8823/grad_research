static struct omap_hwmod omap54xx_dma_system_hwmod = {
	.name		= "dma_system",
	.class		= &omap54xx_dma_hwmod_class,
	.clkdm_name	= "dma_clkdm",
	.mpu_irqs	= omap54xx_dma_system_irqs,
	.main_clk	= "l3_iclk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DMA_DMA_SYSTEM_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_DMA_DMA_SYSTEM_CONTEXT_OFFSET,
		},
	},
	.dev_attr	= &dma_dev_attr,
};

/*
 * 'dmic' class
 * digital microphone controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_dmic_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_dmic_hwmod_class = {
	.name	= "dmic",
	.sysc	= &omap54xx_dmic_sysc,
};

/* dmic */
static struct omap_hwmod omap54xx_dmic_hwmod = {
	.name		= "dmic",
	.class		= &omap54xx_dmic_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "dmic_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_DMIC_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_DMIC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'dss' class
 * display sub-system
 */
static struct omap_hwmod_class_sysconfig omap54xx_dss_sysc = {
	.rev_offs	= 0x0000,
	.syss_offs	= 0x0014,
	.sysc_flags	= SYSS_HAS_RESET_STATUS,
};

static struct omap_hwmod_class omap54xx_dss_hwmod_class = {
	.name	= "dss",
	.sysc	= &omap54xx_dss_sysc,
	.reset	= omap_dss_reset,
};

/* dss */
static struct omap_hwmod_opt_clk dss_opt_clks[] = {
	{ .role = "32khz_clk", .clk = "dss_32khz_clk" },
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
	{ .role = "hdmi_clk", .clk = "dss_48mhz_clk" },
};

static struct omap_hwmod omap54xx_dss_hwmod = {
	.name		= "dss_core",
	.class		= &omap54xx_dss_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_DSS_DSS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= dss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_opt_clks),
};

/*
 * 'dispc' class
 * display controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_dispc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_dispc_hwmod_class = {
	.name	= "dispc",
	.sysc	= &omap54xx_dispc_sysc,
};

/* dss_dispc */
static struct omap_hwmod_opt_clk dss_dispc_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

/* dss_dispc dev_attr */
static struct omap_dss_dispc_dev_attr dss_dispc_dev_attr = {
	.has_framedonetv_irq	= 1,
	.manager_count		= 4,
};

static struct omap_hwmod omap54xx_dss_dispc_hwmod = {
	.name		= "dss_dispc",
	.class		= &omap54xx_dispc_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
	.opt_clks	= dss_dispc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dispc_opt_clks),
	.dev_attr	= &dss_dispc_dev_attr,
	.parent_hwmod	= &omap54xx_dss_hwmod,
};

/*
 * 'dsi1' class
 * display serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_dsi1_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_dsi1_hwmod_class = {
	.name	= "dsi1",
	.sysc	= &omap54xx_dsi1_sysc,
};

/* dss_dsi1_a */
static struct omap_hwmod_opt_clk dss_dsi1_a_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap54xx_dss_dsi1_a_hwmod = {
	.name		= "dss_dsi1",
	.class		= &omap54xx_dsi1_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
	.opt_clks	= dss_dsi1_a_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_a_opt_clks),
	.parent_hwmod	= &omap54xx_dss_hwmod,
};

/* dss_dsi1_c */
static struct omap_hwmod_opt_clk dss_dsi1_c_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap54xx_dss_dsi1_c_hwmod = {
	.name		= "dss_dsi2",
	.class		= &omap54xx_dsi1_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
	.opt_clks	= dss_dsi1_c_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_c_opt_clks),
	.parent_hwmod	= &omap54xx_dss_hwmod,
};

/*
 * 'hdmi' class
 * hdmi controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_hdmi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_hdmi_hwmod_class = {
	.name	= "hdmi",
	.sysc	= &omap54xx_hdmi_sysc,
};

static struct omap_hwmod_opt_clk dss_hdmi_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap54xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap54xx_hdmi_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap54xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap54xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap54xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_iclk_div" },
};

static struct omap_hwmod omap54xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap54xx_rfbi_hwmod_class,
	.clkdm_name	= "dss_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSS_DSS_CLKCTRL_OFFSET,
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap54xx_dss_hwmod,
};

/*
 * 'emif' class
 * external memory interface no1 (wrapper)
 */

static struct omap_hwmod_class_sysconfig omap54xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap54xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap54xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap54xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap54xx_emif_hwmod_class,
	.clkdm_name	= "emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_core_h11x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_EMIF_EMIF1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_EMIF_EMIF1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap54xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap54xx_emif_hwmod_class,
	.clkdm_name	= "emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_core_h11x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_EMIF_EMIF2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_EMIF_EMIF2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap54xx_gpio_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0114,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap54xx_gpio_sysc,
	.rev	= 2,
};

/* gpio dev_attr */
static struct omap_gpio_dev_attr gpio_dev_attr = {
	.bank_width	= 32,
	.dbck_flag	= true,
};

/* gpio1 */
static struct omap_hwmod_opt_clk gpio1_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio1_dbclk" },
};

static struct omap_hwmod omap54xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "wkupaon_clkdm",
	.main_clk	= "wkupaon_iclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_WKUPAON_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_WKUPAON_GPIO1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio1_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio2 */
static struct omap_hwmod_opt_clk gpio2_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio2_dbclk" },
};

static struct omap_hwmod omap54xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio2_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio3 */
static struct omap_hwmod_opt_clk gpio3_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio3_dbclk" },
};

static struct omap_hwmod omap54xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio3_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio4 */
static struct omap_hwmod_opt_clk gpio4_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio4_dbclk" },
};

static struct omap_hwmod omap54xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio4_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio5 */
static struct omap_hwmod_opt_clk gpio5_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio5_dbclk" },
};

static struct omap_hwmod omap54xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio5_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio5_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio6 */
static struct omap_hwmod_opt_clk gpio6_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio6_dbclk" },
};

static struct omap_hwmod omap54xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio7 */
static struct omap_hwmod_opt_clk gpio7_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio7_dbclk" },
};

static struct omap_hwmod omap54xx_gpio7_hwmod = {
	.name		= "gpio7",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO7_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio7_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio7_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/* gpio8 */
static struct omap_hwmod_opt_clk gpio8_opt_clks[] = {
	{ .role = "dbclk", .clk = "gpio8_dbclk" },
};

static struct omap_hwmod omap54xx_gpio8_hwmod = {
	.name		= "gpio8",
	.class		= &omap54xx_gpio_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_GPIO8_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_GPIO8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio8_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio8_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_i2c_sysc = {
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0090,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap54xx_i2c_sysc,
	.reset	= &omap_i2c_reset,
	.rev	= OMAP_I2C_IP_VERSION_2,
};

/* i2c dev_attr */
static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap54xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap54xx_i2c_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap54xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap54xx_i2c_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap54xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap54xx_i2c_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap54xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap54xx_i2c_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c5 */
static struct omap_hwmod omap54xx_i2c5_hwmod = {
	.name		= "i2c5",
	.class		= &omap54xx_i2c_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_I2C5_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_I2C5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap54xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap54xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap54xx_kbd_hwmod_class,
	.clkdm_name	= "wkupaon_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_WKUPAON_KBD_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_WKUPAON_KBD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap54xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap54xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap54xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap54xx_mailbox_hwmod_class,
	.clkdm_name	= "l4cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap54xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap54xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap54xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_MCBSP1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp1_opt_clks),
};

/* mcbsp2 */
static struct omap_hwmod_opt_clk mcbsp2_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp2_sync_mux_ck" },
};

static struct omap_hwmod omap54xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap54xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_MCBSP2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp2_opt_clks),
};

/* mcbsp3 */
static struct omap_hwmod_opt_clk mcbsp3_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp3_sync_mux_ck" },
};

static struct omap_hwmod omap54xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap54xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap54xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap54xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap54xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap54xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.  XXX This is
	 * really a hardware issue workaround: every IP block should
	 * be able to source its main functional clock from either
	 * on-chip or off-chip sources.  McPDM seems to be the only
	 * current exception.
	 */

	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_MCPDM_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_MCPDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap54xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap54xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap54xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap54xx_mcspi_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap54xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap54xx_mcspi_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap54xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap54xx_mcspi_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap54xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap54xx_mcspi_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_mmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap54xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_opt_clk mmc1_opt_clks[] = {
	{ .role = "32khz_clk", .clk = "mmc1_32khz_clk" },
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap54xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap54xx_mmc_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.main_clk	= "mmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mmc1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mmc1_opt_clks),
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod omap54xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap54xx_mmc_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.main_clk	= "mmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod omap54xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap54xx_mmc_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MMC3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MMC3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod omap54xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap54xx_mmc_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MMC4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MMC4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod omap54xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap54xx_mmc_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_MMC5_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_MMC5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig omap54xx_mmu_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &omap54xx_mmu_sysc,
};

static struct omap_hwmod_rst_info omap54xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod omap54xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap54xx_mmu_hwmod_class,
	.clkdm_name	= "dsp_clkdm",
	.rst_lines	= omap54xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap54xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_h11x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_DSP_DSP_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP54XX_RM_DSP_RSTCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_DSP_DSP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* mmu ipu */
static struct omap_hwmod_rst_info omap54xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod omap54xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap54xx_mmu_hwmod_class,
	.clkdm_name	= "ipu_clkdm",
	.rst_lines	= omap54xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap54xx_mmu_ipu_resets),
	.main_clk	= "dpll_core_h22x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_IPU_IPU_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP54XX_RM_IPU_RSTCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_IPU_IPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap54xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap54xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap54xx_mpu_hwmod_class,
	.clkdm_name	= "mpu_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap54xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap54xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap54xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap54xx_spinlock_hwmod_class,
	.clkdm_name	= "l4cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4CFG_SPINLOCK_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4CFG_SPINLOCK_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap54xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap54xx_ocp2scp_sysc,
};

/* ocp2scp1 */
static struct omap_hwmod omap54xx_ocp2scp1_hwmod = {
	.name		= "ocp2scp1",
	.class		= &omap54xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_OCP2SCP1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_OCP2SCP1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap54xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
	.clockact	= CLOCKACT_TEST_ICLK,
};

static struct omap_hwmod_class omap54xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap54xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap54xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap54xx_timer_sysc,
};

/* timer1 */
static struct omap_hwmod omap54xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap54xx_timer_1ms_hwmod_class,
	.clkdm_name	= "wkupaon_clkdm",
	.main_clk	= "timer1_gfclk_mux",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_WKUPAON_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_WKUPAON_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer2 */
static struct omap_hwmod omap54xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap54xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer2_gfclk_mux",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap54xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer3_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap54xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer4_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap54xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer6 */
static struct omap_hwmod omap54xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer7 */
static struct omap_hwmod omap54xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer8 */
static struct omap_hwmod omap54xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer9 */
static struct omap_hwmod omap54xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer9_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer10 */
static struct omap_hwmod omap54xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap54xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer10_gfclk_mux",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer11 */
static struct omap_hwmod omap54xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap54xx_timer_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "timer11_gfclk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_TIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_TIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap54xx_uart_sysc = {
	.rev_offs	= 0x0050,
	.sysc_offs	= 0x0054,
	.syss_offs	= 0x0058,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap54xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap54xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap54xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap54xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap54xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart5 */
static struct omap_hwmod omap54xx_uart5_hwmod = {
	.name		= "uart5",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART5_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart6 */
static struct omap_hwmod omap54xx_uart6_hwmod = {
	.name		= "uart6",
	.class		= &omap54xx_uart_hwmod_class,
	.clkdm_name	= "l4per_clkdm",
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L4PER_UART6_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L4PER_UART6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap54xx_usb_host_hs_sysc,
};

static struct omap_hwmod omap54xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap54xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	/*
	 * Errata: USBHOST Configured In Smart-Idle Can Lead To a Deadlock
	 * id: i660
	 *
	 * Description:
	 * In the following configuration :
	 * - USBHOST module is set to smart-idle mode
	 * - PRCM asserts idle_req to the USBHOST module ( This typically
	 *   happens when the system is going to a low power mode : all ports
	 *   have been suspended, the master part of the USBHOST module has
	 *   entered the standby state, and SW has cut the functional clocks)
	 * - an USBHOST interrupt occurs before the module is able to answer
	 *   idle_ack, typically a remote wakeup IRQ.
	 * Then the USB HOST module will enter a deadlock situation where it
	 * is no more accessible nor functional.
	 *
	 * Workaround:
	 * Don't use smart idle; use only force idle, hence HWMOD_SWSUP_SIDLE
	 */

	/*
	 * Errata: USB host EHCI may stall when entering smart-standby mode
	 * Id: i571
	 *
	 * Description:
	 * When the USBHOST module is set to smart-standby mode, and when it is
	 * ready to enter the standby state (i.e. all ports are suspended and
	 * all attached devices are in suspend mode), then it can wrongly assert
	 * the Mstandby signal too early while there are still some residual OCP
	 * transactions ongoing. If this condition occurs, the internal state
	 * machine may go to an undefined state and the USB link may be stuck
	 * upon the next resume.
	 *
	 * Workaround:
	 * Don't use smart standby; use only force standby,
	 * hence HWMOD_SWSUP_MSTANDBY
	 */

	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "l3init_60m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_USB_HOST_HS_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_USB_HOST_HS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap54xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap54xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap54xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap54xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.main_clk	= "l4_root_clk_div",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_USB_TLL_HS_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_USB_TLL_HS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'usb_otg_ss' class
 * 2.0 super speed (usb_otg_ss) controller
 */

static struct omap_hwmod_class_sysconfig omap54xx_usb_otg_ss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_DMADISABLE | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_usb_otg_ss_hwmod_class = {
	.name	= "usb_otg_ss",
	.sysc	= &omap54xx_usb_otg_ss_sysc,
};

/* usb_otg_ss */
static struct omap_hwmod_opt_clk usb_otg_ss_opt_clks[] = {
	{ .role = "refclk960m", .clk = "usb_otg_ss_refclk960m" },
};

static struct omap_hwmod omap54xx_usb_otg_ss_hwmod = {
	.name		= "usb_otg_ss",
	.class		= &omap54xx_usb_otg_ss_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE,
	.main_clk	= "dpll_core_h13x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_USB_OTG_SS_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_USB_OTG_SS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_ss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_ss_opt_clks),
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap54xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap54xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap54xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
};

/* wd_timer2 */
static struct omap_hwmod omap54xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap54xx_wd_timer_hwmod_class,
	.clkdm_name	= "wkupaon_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_WKUPAON_WD_TIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_WKUPAON_WD_TIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */
/* ocp2scp3 */
static struct omap_hwmod omap54xx_ocp2scp3_hwmod;
/* l4_cfg -> ocp2scp3 */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__ocp2scp3 = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_ocp2scp3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap54xx_ocp2scp3_hwmod = {
	.name		= "ocp2scp3",
	.class		= &omap54xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_OCP2SCP3_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_OCP2SCP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'sata' class
 * sata:  serial ata interface  gen2 compliant   ( 1 rx/ 1 tx)
 */

static struct omap_hwmod_class_sysconfig omap54xx_sata_sysc = {
	.sysc_offs	= 0x0000,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap54xx_sata_hwmod_class = {
	.name	= "sata",
	.sysc	= &omap54xx_sata_sysc,
};

/* sata */
static struct omap_hwmod omap54xx_sata_hwmod = {
	.name		= "sata",
	.class		= &omap54xx_sata_hwmod_class,
	.clkdm_name	= "l3init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "func_48m_fclk",
	.mpu_rt_idx	= 1,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP54XX_CM_L3INIT_SATA_CLKCTRL_OFFSET,
			.context_offs = OMAP54XX_RM_L3INIT_SATA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* l4_cfg -> sata */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__sata = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_sata_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/*
 * Interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__dmm = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_dmm_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap54xx_l3_main_3__l3_instr = {
	.master		= &omap54xx_l3_main_3_hwmod,
	.slave		= &omap54xx_l3_instr_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__l3_main_1 = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_l3_main_1_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__l3_main_1 = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_l3_main_1_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mmu_dsp */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__mmu_dsp = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_mmu_dsp_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap54xx_mpu__l3_main_1 = {
	.master		= &omap54xx_mpu_hwmod,
	.slave		= &omap54xx_l3_main_1_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__l3_main_2 = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_l3_main_2_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__l3_main_2 = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_l3_main_2_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__mmu_ipu = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_mmu_ipu_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__l3_main_3 = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_l3_main_3_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__l3_main_3 = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_l3_main_3_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__l3_main_3 = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_l3_main_3_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__l4_abe = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_l4_abe_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap54xx_mpu__l4_abe = {
	.master		= &omap54xx_mpu_hwmod,
	.slave		= &omap54xx_l4_abe_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__l4_cfg = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_l4_cfg_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__l4_per = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_l4_per_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_wkup */
static struct omap_hwmod_ocp_if omap54xx_l3_main_1__l4_wkup = {
	.master		= &omap54xx_l3_main_1_hwmod,
	.slave		= &omap54xx_l4_wkup_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap54xx_mpu__mpu_private = {
	.master		= &omap54xx_mpu_hwmod,
	.slave		= &omap54xx_mpu_private_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap54xx_l4_wkup__counter_32k = {
	.master		= &omap54xx_l4_wkup_hwmod,
	.slave		= &omap54xx_counter_32k_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap54xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__dma_system = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_dma_system_hwmod,
	.clk		= "l4_root_clk_div",
	.addr		= omap54xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__dmic = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_dmic_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss_dispc = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_dispc_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> dss_dsi1_a */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss_dsi1_a = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_dsi1_a_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> dss_dsi1_c */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss_dsi1_c = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_dsi1_c_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss_hdmi = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_hdmi_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap54xx_l3_main_2__dss_rfbi = {
	.master		= &omap54xx_l3_main_2_hwmod,
	.slave		= &omap54xx_dss_rfbi_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap54xx_mpu__emif1 = {
	.master		= &omap54xx_mpu_hwmod,
	.slave		= &omap54xx_emif1_hwmod,
	.clk		= "dpll_core_h11x2_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap54xx_mpu__emif2 = {
	.master		= &omap54xx_mpu_hwmod,
	.slave		= &omap54xx_emif2_hwmod,
	.clk		= "dpll_core_h11x2_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap54xx_l4_wkup__gpio1 = {
	.master		= &omap54xx_l4_wkup_hwmod,
	.slave		= &omap54xx_gpio1_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio2_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio5 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio5_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio6 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio6_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio7 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio7 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio7_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio8 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__gpio8 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_gpio8_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__i2c1 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_i2c1_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__i2c2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_i2c2_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__i2c3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_i2c3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__i2c4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_i2c4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c5 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__i2c5 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_i2c5_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap54xx_l4_wkup__kbd = {
	.master		= &omap54xx_l4_wkup_hwmod,
	.slave		= &omap54xx_kbd_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__mailbox = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_mailbox_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__mcbsp1 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_mcbsp1_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__mcbsp2 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_mcbsp2_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__mcbsp3 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_mcbsp3_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__mcpdm = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_mcpdm_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mcspi1 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mcspi1_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mcspi2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mcspi2_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mcspi3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mcspi3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mcspi4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mcspi4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mmc1 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mmc1_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mmc2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mmc2_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mmc3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mmc3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mmc4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mmc4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__mmc5 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_mmc5_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mpu */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__mpu = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_mpu_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__spinlock = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_spinlock_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp1 */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__ocp2scp1 = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_ocp2scp1_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap54xx_l4_wkup__timer1 = {
	.master		= &omap54xx_l4_wkup_hwmod,
	.slave		= &omap54xx_timer1_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer2_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__timer5 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_timer5_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__timer6 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_timer6_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__timer7 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_timer7_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap54xx_l4_abe__timer8 = {
	.master		= &omap54xx_l4_abe_hwmod,
	.slave		= &omap54xx_timer8_hwmod,
	.clk		= "abe_iclk",
	.user		= OCP_USER_MPU,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer9 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer9_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer10 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer10_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__timer11 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_timer11_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart1 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart1_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart2 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart2_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart3 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart3_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart4 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart4_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart5 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart5 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart5_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart6 */
static struct omap_hwmod_ocp_if omap54xx_l4_per__uart6 = {
	.master		= &omap54xx_l4_per_hwmod,
	.slave		= &omap54xx_uart6_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__usb_host_hs = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_usb_host_hs_hwmod,
	.clk		= "l3_iclk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__usb_tll_hs = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_usb_tll_hs_hwmod,
	.clk		= "l4_root_clk_div",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_ss */
static struct omap_hwmod_ocp_if omap54xx_l4_cfg__usb_otg_ss = {
	.master		= &omap54xx_l4_cfg_hwmod,
	.slave		= &omap54xx_usb_otg_ss_hwmod,
	.clk		= "dpll_core_h13x2_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap54xx_l4_wkup__wd_timer2 = {
	.master		= &omap54xx_l4_wkup_hwmod,
	.slave		= &omap54xx_wd_timer2_hwmod,
	.clk		= "wkupaon_iclk_mux",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap54xx_hwmod_ocp_ifs[] __initdata = {
	&omap54xx_l3_main_1__dmm,
	&omap54xx_l3_main_3__l3_instr,
	&omap54xx_l3_main_2__l3_main_1,
	&omap54xx_l4_cfg__l3_main_1,
	&omap54xx_mpu__l3_main_1,
	&omap54xx_l3_main_1__l3_main_2,
	&omap54xx_l4_cfg__l3_main_2,
	&omap54xx_l3_main_1__l3_main_3,
	&omap54xx_l3_main_2__l3_main_3,
	&omap54xx_l4_cfg__l3_main_3,
	&omap54xx_l3_main_1__l4_abe,
	&omap54xx_mpu__l4_abe,
	&omap54xx_l3_main_1__l4_cfg,
	&omap54xx_l3_main_2__l4_per,
	&omap54xx_l3_main_1__l4_wkup,
	&omap54xx_mpu__mpu_private,
	&omap54xx_l4_wkup__counter_32k,
	&omap54xx_l4_cfg__dma_system,
	&omap54xx_l4_abe__dmic,
	&omap54xx_l4_cfg__mmu_dsp,
	&omap54xx_l3_main_2__dss,
	&omap54xx_l3_main_2__dss_dispc,
	&omap54xx_l3_main_2__dss_dsi1_a,
	&omap54xx_l3_main_2__dss_dsi1_c,
	&omap54xx_l3_main_2__dss_hdmi,
	&omap54xx_l3_main_2__dss_rfbi,
	&omap54xx_mpu__emif1,
	&omap54xx_mpu__emif2,
	&omap54xx_l4_wkup__gpio1,
	&omap54xx_l4_per__gpio2,
	&omap54xx_l4_per__gpio3,
	&omap54xx_l4_per__gpio4,
	&omap54xx_l4_per__gpio5,
	&omap54xx_l4_per__gpio6,
	&omap54xx_l4_per__gpio7,
	&omap54xx_l4_per__gpio8,
	&omap54xx_l4_per__i2c1,
	&omap54xx_l4_per__i2c2,
	&omap54xx_l4_per__i2c3,
	&omap54xx_l4_per__i2c4,
	&omap54xx_l4_per__i2c5,
	&omap54xx_l3_main_2__mmu_ipu,
	&omap54xx_l4_wkup__kbd,
	&omap54xx_l4_cfg__mailbox,
	&omap54xx_l4_abe__mcbsp1,
	&omap54xx_l4_abe__mcbsp2,
	&omap54xx_l4_abe__mcbsp3,
	&omap54xx_l4_abe__mcpdm,
	&omap54xx_l4_per__mcspi1,
	&omap54xx_l4_per__mcspi2,
	&omap54xx_l4_per__mcspi3,
	&omap54xx_l4_per__mcspi4,
	&omap54xx_l4_per__mmc1,
	&omap54xx_l4_per__mmc2,
	&omap54xx_l4_per__mmc3,
	&omap54xx_l4_per__mmc4,
	&omap54xx_l4_per__mmc5,
	&omap54xx_l4_cfg__mpu,
	&omap54xx_l4_cfg__spinlock,
	&omap54xx_l4_cfg__ocp2scp1,
	&omap54xx_l4_wkup__timer1,
	&omap54xx_l4_per__timer2,
	&omap54xx_l4_per__timer3,
	&omap54xx_l4_per__timer4,
	&omap54xx_l4_abe__timer5,
	&omap54xx_l4_abe__timer6,
	&omap54xx_l4_abe__timer7,
	&omap54xx_l4_abe__timer8,
	&omap54xx_l4_per__timer9,
	&omap54xx_l4_per__timer10,
	&omap54xx_l4_per__timer11,
	&omap54xx_l4_per__uart1,
	&omap54xx_l4_per__uart2,
	&omap54xx_l4_per__uart3,
	&omap54xx_l4_per__uart4,
	&omap54xx_l4_per__uart5,
	&omap54xx_l4_per__uart6,
	&omap54xx_l4_cfg__usb_host_hs,
	&omap54xx_l4_cfg__usb_tll_hs,
	&omap54xx_l4_cfg__usb_otg_ss,
	&omap54xx_l4_wkup__wd_timer2,
	&omap54xx_l4_cfg__ocp2scp3,
	&omap54xx_l4_cfg__sata,
	NULL,
};

int __init omap54xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap54xx_hwmod_ocp_ifs);
}