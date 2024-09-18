static struct omap_hwmod omap44xx_dma_system_hwmod = {
	.name		= "dma_system",
	.class		= &omap44xx_dma_hwmod_class,
	.clkdm_name	= "l3_dma_clkdm",
	.mpu_irqs	= omap44xx_dma_system_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.main_clk	= "l3_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_SDMA_SDMA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_SDMA_SDMA_CONTEXT_OFFSET,
		},
	},
	.dev_attr	= &dma_dev_attr,
};

/*
 * 'dmic' class
 * digital microphone controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_dmic_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_dmic_hwmod_class = {
	.name	= "dmic",
	.sysc	= &omap44xx_dmic_sysc,
};

/* dmic */
static struct omap_hwmod omap44xx_dmic_hwmod = {
	.name		= "dmic",
	.class		= &omap44xx_dmic_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_dmic_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_DMIC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_DMIC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'dsp' class
 * dsp sub-system
 */

static struct omap_hwmod_class omap44xx_dsp_hwmod_class = {
	.name	= "dsp",
};

/* dsp */
static struct omap_hwmod_rst_info omap44xx_dsp_resets[] = {
	{ .name = "dsp", .rst_shift = 0 },
};

static struct omap_hwmod omap44xx_dsp_hwmod = {
	.name		= "dsp",
	.class		= &omap44xx_dsp_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'dss' class
 * display sub-system
 */

static struct omap_hwmod_class_sysconfig omap44xx_dss_sysc = {
	.rev_offs	= 0x0000,
	.syss_offs	= 0x0014,
	.sysc_flags	= SYSS_HAS_RESET_STATUS,
};

static struct omap_hwmod_class omap44xx_dss_hwmod_class = {
	.name	= "dss",
	.sysc	= &omap44xx_dss_sysc,
	.reset	= omap_dss_reset,
};

/* dss */
static struct omap_hwmod_opt_clk dss_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
	{ .role = "tv_clk", .clk = "dss_tv_clk" },
	{ .role = "hdmi_clk", .clk = "dss_48mhz_clk" },
};

static struct omap_hwmod omap44xx_dss_hwmod = {
	.name		= "dss_core",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.class		= &omap44xx_dss_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
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

static struct omap_hwmod_class_sysconfig omap44xx_dispc_sysc = {
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

static struct omap_hwmod_class omap44xx_dispc_hwmod_class = {
	.name	= "dispc",
	.sysc	= &omap44xx_dispc_sysc,
};

/* dss_dispc */
static struct omap_hwmod_irq_info omap44xx_dss_dispc_irqs[] = {
	{ .irq = 25 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dispc_sdma_reqs[] = {
	{ .dma_req = 5 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_dss_dispc_dev_attr omap44xx_dss_dispc_dev_attr = {
	.manager_count		= 3,
	.has_framedonetv_irq	= 1
};

static struct omap_hwmod omap44xx_dss_dispc_hwmod = {
	.name		= "dss_dispc",
	.class		= &omap44xx_dispc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dispc_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dispc_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.dev_attr	= &omap44xx_dss_dispc_dev_attr,
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'dsi' class
 * display serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_dsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_dsi_hwmod_class = {
	.name	= "dsi",
	.sysc	= &omap44xx_dsi_sysc,
};

/* dss_dsi1 */
static struct omap_hwmod_irq_info omap44xx_dss_dsi1_irqs[] = {
	{ .irq = 53 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dsi1_sdma_reqs[] = {
	{ .dma_req = 74 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_dsi1_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_dsi1_hwmod = {
	.name		= "dss_dsi1",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi1_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi1_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/* dss_dsi2 */
static struct omap_hwmod_irq_info omap44xx_dss_dsi2_irqs[] = {
	{ .irq = 84 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dsi2_sdma_reqs[] = {
	{ .dma_req = 83 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_dsi2_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_dsi2_hwmod = {
	.name		= "dss_dsi2",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi2_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi2_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi2_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'hdmi' class
 * hdmi controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdmi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_hdmi_hwmod_class = {
	.name	= "hdmi",
	.sysc	= &omap44xx_hdmi_sysc,
};

/* dss_hdmi */
static struct omap_hwmod_irq_info omap44xx_dss_hdmi_irqs[] = {
	{ .irq = 101 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_hdmi_sdma_reqs[] = {
	{ .dma_req = 75 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_hdmi_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap44xx_hdmi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	/*
	 * HDMI audio requires to use no-idle mode. Hence,
	 * set idle mode by software.
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
	.mpu_irqs	= omap44xx_dss_hdmi_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_hdmi_sdma_reqs,
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap44xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap44xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_dma_info omap44xx_dss_rfbi_sdma_reqs[] = {
	{ .dma_req = 13 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_div_ck" },
};

static struct omap_hwmod omap44xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap44xx_rfbi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.sdma_reqs	= omap44xx_dss_rfbi_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'venc' class
 * video encoder
 */

static struct omap_hwmod_class omap44xx_venc_hwmod_class = {
	.name	= "venc",
};

/* dss_venc */
static struct omap_hwmod omap44xx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.class		= &omap44xx_venc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_tv_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'elm' class
 * bch error location module
 */

static struct omap_hwmod_class_sysconfig omap44xx_elm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_elm_hwmod_class = {
	.name	= "elm",
	.sysc	= &omap44xx_elm_sysc,
};

/* elm */
static struct omap_hwmod omap44xx_elm_hwmod = {
	.name		= "elm",
	.class		= &omap44xx_elm_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_ELM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'emif' class
 * external memory interface no1
 */

static struct omap_hwmod_class_sysconfig omap44xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap44xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap44xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap44xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap44xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'fdif' class
 * face detection hw accelerator module
 */

static struct omap_hwmod_class_sysconfig omap44xx_fdif_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * FDIF needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_fdif_hwmod_class = {
	.name	= "fdif",
	.sysc	= &omap44xx_fdif_sysc,
};

/* fdif */
static struct omap_hwmod omap44xx_fdif_hwmod = {
	.name		= "fdif",
	.class		= &omap44xx_fdif_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "fdif_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_FDIF_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpio_sysc = {
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

static struct omap_hwmod_class omap44xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap44xx_gpio_sysc,
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

static struct omap_hwmod omap44xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "l4_wkup_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_GPIO1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO3_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO4_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO5_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'gpmc' class
 * general purpose memory controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_gpmc_hwmod_class = {
	.name	= "gpmc",
	.sysc	= &omap44xx_gpmc_sysc,
};

/* gpmc */
static struct omap_hwmod omap44xx_gpmc_hwmod = {
	.name		= "gpmc",
	.class		= &omap44xx_gpmc_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	/*
	 * XXX HWMOD_INIT_NO_RESET should not be needed for this IP
	 * block.  It is not being added due to any known bugs with
	 * resetting the GPMC IP block, but rather because any timings
	 * set by the bootloader are not being correctly programmed by
	 * the kernel from the board file or DT data.
	 * HWMOD_INIT_NO_RESET should be removed ASAP.
	 */
	.flags		= HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_GPMC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpu' class
 * 2d/3d graphics accelerator
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpu_sysc = {
	.rev_offs	= 0x1fc00,
	.sysc_offs	= 0x1fc10,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_gpu_hwmod_class = {
	.name	= "gpu",
	.sysc	= &omap44xx_gpu_sysc,
};

/* gpu */
static struct omap_hwmod omap44xx_gpu_hwmod = {
	.name		= "gpu",
	.class		= &omap44xx_gpu_hwmod_class,
	.clkdm_name	= "l3_gfx_clkdm",
	.main_clk	= "sgx_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_GFX_GFX_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hdq1w' class
 * hdq / 1-wire serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdq1w_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0014,
	.syss_offs	= 0x0018,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hdq1w_hwmod_class = {
	.name	= "hdq1w",
	.sysc	= &omap44xx_hdq1w_sysc,
};

/* hdq1w */
static struct omap_hwmod omap44xx_hdq1w_hwmod = {
	.name		= "hdq1w",
	.class		= &omap44xx_hdq1w_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_INIT_NO_RESET, /* XXX temporary */
	.main_clk	= "func_12m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_HDQ1W_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hsi' class
 * mipi high-speed synchronous serial interface (multichannel and full-duplex
 * serial if)
 */

static struct omap_hwmod_class_sysconfig omap44xx_hsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hsi_hwmod_class = {
	.name	= "hsi",
	.sysc	= &omap44xx_hsi_sysc,
};

/* hsi */
static struct omap_hwmod omap44xx_hsi_hwmod = {
	.name		= "hsi",
	.class		= &omap44xx_hsi_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "hsi_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_HSI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_i2c_sysc = {
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

static struct omap_hwmod_class omap44xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap44xx_i2c_sysc,
	.rev	= OMAP_I2C_IP_VERSION_2,
	.reset	= &omap_i2c_reset,
};

static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap44xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap44xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap44xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap44xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'ipu' class
 * imaging processor unit
 */

static struct omap_hwmod_class omap44xx_ipu_hwmod_class = {
	.name	= "ipu",
};

/* ipu */
static struct omap_hwmod_rst_info omap44xx_ipu_resets[] = {
	{ .name = "cpu0", .rst_shift = 0 },
	{ .name = "cpu1", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_ipu_hwmod = {
	.name		= "ipu",
	.class		= &omap44xx_ipu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'iss' class
 * external images sensor pixel data processor
 */

static struct omap_hwmod_class_sysconfig omap44xx_iss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * ISS needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_iss_hwmod_class = {
	.name	= "iss",
	.sysc	= &omap44xx_iss_sysc,
};

/* iss */
static struct omap_hwmod_opt_clk iss_opt_clks[] = {
	{ .role = "ctrlclk", .clk = "iss_ctrlclk" },
};

static struct omap_hwmod omap44xx_iss_hwmod = {
	.name		= "iss",
	.class		= &omap44xx_iss_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_ISS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= iss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(iss_opt_clks),
};

/*
 * 'iva' class
 * multi-standard video encoder/decoder hardware accelerator
 */

static struct omap_hwmod_class omap44xx_iva_hwmod_class = {
	.name	= "iva",
};

/* iva */
static struct omap_hwmod_rst_info omap44xx_iva_resets[] = {
	{ .name = "seq0", .rst_shift = 0 },
	{ .name = "seq1", .rst_shift = 1 },
	{ .name = "logic", .rst_shift = 2 },
};

static struct omap_hwmod omap44xx_iva_hwmod = {
	.name		= "iva",
	.class		= &omap44xx_iva_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.rst_lines	= omap44xx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_iva_resets),
	.main_clk	= "dpll_iva_m5x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_IVAHD_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_IVAHD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap44xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap44xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap44xx_kbd_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_KEYBOARD_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_KEYBOARD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap44xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap44xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap44xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap44xx_mailbox_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcasp' class
 * multi-channel audio serial port controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_mcasp = {
	.sidle_shift	= 0,
};

static struct omap_hwmod_class_sysconfig omap44xx_mcasp_sysc = {
	.sysc_offs	= 0x0004,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_mcasp,
};

static struct omap_hwmod_class omap44xx_mcasp_hwmod_class = {
	.name	= "mcasp",
	.sysc	= &omap44xx_mcasp_sysc,
};

/* mcasp */
static struct omap_hwmod omap44xx_mcasp_hwmod = {
	.name		= "mcasp",
	.class		= &omap44xx_mcasp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcasp_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCASP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCASP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap44xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/* mcbsp4 */
static struct omap_hwmod_opt_clk mcbsp4_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp4_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "per_mcbsp4_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCBSP4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp4_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap44xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap44xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap44xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.
	 *
	 * Also, McPDM needs to be configured to NO_IDLE mode when it
	 * is in used otherwise vital clocks will be gated which
	 * results 'slow motion' audio playback.
	 */
	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_PDM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_PDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap44xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
static struct omap_hwmod_dma_info omap44xx_mcspi1_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 34 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 35 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 36 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 37 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx2", .dma_req = 38 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx2", .dma_req = 39 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx3", .dma_req = 40 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx3", .dma_req = 41 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap44xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi1_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
static struct omap_hwmod_dma_info omap44xx_mcspi2_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 42 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 43 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 44 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 45 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi2_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
static struct omap_hwmod_dma_info omap44xx_mcspi3_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 14 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 15 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 22 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 23 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
static struct omap_hwmod_dma_info omap44xx_mcspi4_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 69 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 70 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap44xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mmc_sysc = {
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

static struct omap_hwmod_class omap44xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap44xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_dma_info omap44xx_mmc1_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 60 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 61 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap44xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc1_sdma_reqs,
	.main_clk	= "hsmmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod_dma_info omap44xx_mmc2_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 46 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 47 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc2_sdma_reqs,
	.main_clk	= "hsmmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod_dma_info omap44xx_mmc3_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 76 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 77 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod_dma_info omap44xx_mmc4_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 56 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 57 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod_dma_info omap44xx_mmc5_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 58 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 59 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc5_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig mmu_sysc = {
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &mmu_sysc,
};

/* mmu ipu */

static struct omap_mmu_dev_attr mmu_ipu_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_ipu_addrs[] = {
	{
		.pa_start	= 0x55082000,
		.pa_end		= 0x550820ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__mmu_ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_mmu_ipu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_mmu_ipu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_ipu_dev_attr,
};

/* mmu dsp */

static struct omap_mmu_dev_attr mmu_dsp_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_dsp_addrs[] = {
	{
		.pa_start	= 0x4a066000,
		.pa_end		= 0x4a0660ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mmu_dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mmu_dsp_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_mmu_dsp_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_dsp_dev_attr,
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap44xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap44xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap44xx_mpu_hwmod_class,
	.clkdm_name	= "mpuss_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocmc_ram' class
 * top-level core on-chip ram
 */

static struct omap_hwmod_class omap44xx_ocmc_ram_hwmod_class = {
	.name	= "ocmc_ram",
};

/* ocmc_ram */
static struct omap_hwmod omap44xx_ocmc_ram_hwmod = {
	.name		= "ocmc_ram",
	.class		= &omap44xx_ocmc_ram_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_OCMC_RAM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap44xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap44xx_ocp2scp_sysc,
};

/* ocp2scp_usb_phy */
static struct omap_hwmod omap44xx_ocp2scp_usb_phy_hwmod = {
	.name		= "ocp2scp_usb_phy",
	.class		= &omap44xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	/*
	 * ocp2scp_usb_phy_phy_48m is provided by the OMAP4 PRCM IP
	 * block as an "optional clock," and normally should never be
	 * specified as the main_clk for an OMAP IP block.  However it
	 * turns out that this clock is actually the main clock for
	 * the ocp2scp_usb_phy IP block:
	 * http://lists.infradead.org/pipermail/linux-arm-kernel/2012-September/119943.html
	 * So listing ocp2scp_usb_phy_phy_48m as a main_clk here seems
	 * to be the best workaround.
	 */
	.main_clk	= "ocp2scp_usb_phy_phy_48m",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USBPHYOCP2SCP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'prcm' class
 * power and reset manager (part of the prcm infrastructure) + clock manager 2
 * + clock manager 1 (in always on power domain) + local prm in mpu
 */

static struct omap_hwmod_class omap44xx_prcm_hwmod_class = {
	.name	= "prcm",
};

/* prcm_mpu */
static struct omap_hwmod omap44xx_prcm_mpu_hwmod = {
	.name		= "prcm_mpu",
	.class		= &omap44xx_prcm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core_aon */
static struct omap_hwmod omap44xx_cm_core_aon_hwmod = {
	.name		= "cm_core_aon",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core */
static struct omap_hwmod omap44xx_cm_core_hwmod = {
	.name		= "cm_core",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* prm */
static struct omap_hwmod_rst_info omap44xx_prm_resets[] = {
	{ .name = "rst_global_warm_sw", .rst_shift = 0 },
	{ .name = "rst_global_cold_sw", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_prm_hwmod = {
	.name		= "prm",
	.class		= &omap44xx_prcm_hwmod_class,
	.rst_lines	= omap44xx_prm_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_prm_resets),
};

/*
 * 'scrm' class
 * system clock and reset manager
 */

static struct omap_hwmod_class omap44xx_scrm_hwmod_class = {
	.name	= "scrm",
};

/* scrm */
static struct omap_hwmod omap44xx_scrm_hwmod = {
	.name		= "scrm",
	.class		= &omap44xx_scrm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/*
 * 'sl2if' class
 * shared level 2 memory interface
 */

static struct omap_hwmod_class omap44xx_sl2if_hwmod_class = {
	.name	= "sl2if",
};

/* sl2if */
static struct omap_hwmod omap44xx_sl2if_hwmod = {
	.name		= "sl2if",
	.class		= &omap44xx_sl2if_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_SL2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'slimbus' class
 * bidirectional, multi-drop, multi-channel two-line serial interface between
 * the device and external components
 */

static struct omap_hwmod_class_sysconfig omap44xx_slimbus_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_slimbus_hwmod_class = {
	.name	= "slimbus",
	.sysc	= &omap44xx_slimbus_sysc,
};

/* slimbus1 */
static struct omap_hwmod_opt_clk slimbus1_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus1_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus1_fclk_0" },
	{ .role = "fclk_2", .clk = "slimbus1_fclk_2" },
	{ .role = "slimbus_clk", .clk = "slimbus1_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus1_hwmod = {
	.name		= "slimbus1",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_SLIMBUS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_SLIMBUS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus1_opt_clks),
};

/* slimbus2 */
static struct omap_hwmod_opt_clk slimbus2_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus2_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus2_fclk_0" },
	{ .role = "slimbus_clk", .clk = "slimbus2_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus2_hwmod = {
	.name		= "slimbus2",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_SLIMBUS2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus2_opt_clks),
};

/*
 * 'smartreflex' class
 * smartreflex module (monitor silicon performance and outputs a measure of
 * performance error)
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_smartreflex = {
	.sidle_shift	= 24,
	.enwkup_shift	= 26,
};

static struct omap_hwmod_class_sysconfig omap44xx_smartreflex_sysc = {
	.sysc_offs	= 0x0038,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_smartreflex,
};

static struct omap_hwmod_class omap44xx_smartreflex_hwmod_class = {
	.name	= "smartreflex",
	.sysc	= &omap44xx_smartreflex_sysc,
	.rev	= 2,
};

/* smartreflex_core */
static struct omap_smartreflex_dev_attr smartreflex_core_dev_attr = {
	.sensor_voltdm_name   = "core",
};

static struct omap_hwmod omap44xx_smartreflex_core_hwmod = {
	.name		= "smartreflex_core",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",

	.main_clk	= "smartreflex_core_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_CORE_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_core_dev_attr,
};

/* smartreflex_iva */
static struct omap_smartreflex_dev_attr smartreflex_iva_dev_attr = {
	.sensor_voltdm_name	= "iva",
};

static struct omap_hwmod omap44xx_smartreflex_iva_hwmod = {
	.name		= "smartreflex_iva",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_iva_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_IVA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_iva_dev_attr,
};

/* smartreflex_mpu */
static struct omap_smartreflex_dev_attr smartreflex_mpu_dev_attr = {
	.sensor_voltdm_name	= "mpu",
};

static struct omap_hwmod omap44xx_smartreflex_mpu_hwmod = {
	.name		= "smartreflex_mpu",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_mpu_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_MPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_mpu_dev_attr,
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap44xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap44xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap44xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap44xx_spinlock_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_HW_SEM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap44xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap44xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_sysc,
};

/* always-on timers dev attribute */
static struct omap_timer_capability_dev_attr capability_alwon_dev_attr = {
	.timer_capability	= OMAP_TIMER_ALWON,
};

/* pwm timers dev attribute */
static struct omap_timer_capability_dev_attr capability_pwm_dev_attr = {
	.timer_capability	= OMAP_TIMER_HAS_PWM,
};

/* timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ,
};

/* pwm timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_pwm_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ | OMAP_TIMER_HAS_PWM,
};

/* timer1 */
static struct omap_hwmod omap44xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "dmt1_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_alwon_dev_attr,
};

/* timer2 */
static struct omap_hwmod omap44xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm2_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap44xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm3_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap44xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm4_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap44xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer6 */
static struct omap_hwmod omap44xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer7 */
static struct omap_hwmod omap44xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer8 */
static struct omap_hwmod omap44xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_pwm_dev_attr,
};

/* timer9 */
static struct omap_hwmod omap44xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm9_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer10 */
static struct omap_hwmod omap44xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm10_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer11 */
static struct omap_hwmod omap44xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm11_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap44xx_uart_sysc = {
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

static struct omap_hwmod_class omap44xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap44xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap44xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap44xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap44xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap44xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_fs' class
 * full-speed usb host controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_usb_host_fs = {
	.midle_shift	= 4,
	.sidle_shift	= 2,
	.srst_shift	= 1,
};

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_fs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0210,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_usb_host_fs,
};

static struct omap_hwmod_class omap44xx_usb_host_fs_hwmod_class = {
	.name	= "usb_host_fs",
	.sysc	= &omap44xx_usb_host_fs_sysc,
};

/* usb_host_fs */
static struct omap_hwmod omap44xx_usb_host_fs_hwmod = {
	.name		= "usb_host_fs",
	.class		= &omap44xx_usb_host_fs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_fs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_FS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap44xx_usb_host_hs_sysc,
};

/* usb_host_hs */
static struct omap_hwmod omap44xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap44xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_hs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},

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
};

/*
 * 'usb_otg_hs' class
 * high-speed on-the-go universal serial bus (usb_otg_hs) controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_otg_hs_sysc = {
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_otg_hs_hwmod_class = {
	.name	= "usb_otg_hs",
	.sysc	= &omap44xx_usb_otg_hs_sysc,
};

/* usb_otg_hs */
static struct omap_hwmod_opt_clk usb_otg_hs_opt_clks[] = {
	{ .role = "xclk", .clk = "usb_otg_hs_xclk" },
};

static struct omap_hwmod omap44xx_usb_otg_hs_hwmod = {
	.name		= "usb_otg_hs",
	.class		= &omap44xx_usb_otg_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "usb_otg_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_OTG_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_hs_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_hs_opt_clks),
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap44xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap44xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap44xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_tll_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_TLL_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap44xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap44xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
	.reset		= &omap2_wd_timer_reset,
};

/* wd_timer2 */
static struct omap_hwmod omap44xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_WDT2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_WDT2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* wd_timer3 */
static struct omap_hwmod omap44xx_wd_timer3_hwmod = {
	.name		= "wd_timer3",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_WDT3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_WDT3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};


/*
 * interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__dmm = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_SDMA,
};

/* mpu -> dmm */
static struct omap_hwmod_ocp_if omap44xx_mpu__dmm = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* iva -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_instr = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_l3_main_3__l3_instr = {
	.master		= &omap44xx_l3_main_3_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ocp_wp_noc -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_ocp_wp_noc__l3_instr = {
	.master		= &omap44xx_ocp_wp_noc_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dsp__l3_main_1 = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dss -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dss__l3_main_1 = {
	.master		= &omap44xx_dss_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_1 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc1 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc1__l3_main_1 = {
	.master		= &omap44xx_mmc1_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc2__l3_main_1 = {
	.master		= &omap44xx_mmc2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__l3_main_1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* debugss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_debugss__l3_main_2 = {
	.master		= &omap44xx_debugss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "dbgclk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dma_system -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_dma_system__l3_main_2 = {
	.master		= &omap44xx_dma_system_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* fdif -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_fdif__l3_main_2 = {
	.master		= &omap44xx_fdif_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* gpu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_gpu__l3_main_2 = {
	.master		= &omap44xx_gpu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* hsi -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_hsi__l3_main_2 = {
	.master		= &omap44xx_hsi_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ipu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_ipu__l3_main_2 = {
	.master		= &omap44xx_ipu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iss__l3_main_2 = {
	.master		= &omap44xx_iss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_main_2 = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_2 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_2 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_fs -> l3_main_2 */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_usb_host_fs__l3_main_2 = {
	.master		= &omap44xx_usb_host_fs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_host_hs__l3_main_2 = {
	.master		= &omap44xx_usb_host_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_otg_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_otg_hs__l3_main_2 = {
	.master		= &omap44xx_usb_otg_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_3 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_3 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_3 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* aess -> l4_abe */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_aess__l4_abe = {
	.master		= &omap44xx_aess_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_dsp__l4_abe = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_abe = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_mpu__l4_abe = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_cfg = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_cfg_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l4_per = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l4_per_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l4_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l4_wkup = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l4_wkup_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap44xx_mpu__mpu_private = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_mpu_private_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp_wp_noc */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp_wp_noc = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp_wp_noc_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_aess_addrs[] = {
	{
		.name		= "dmem",
		.pa_start	= 0x40180000,
		.pa_end		= 0x4018ffff
	},
	{
		.name		= "cmem",
		.pa_start	= 0x401a0000,
		.pa_end		= 0x401a1fff
	},
	{
		.name		= "smem",
		.pa_start	= 0x401c0000,
		.pa_end		= 0x401c5fff
	},
	{
		.name		= "pmem",
		.pa_start	= 0x401e0000,
		.pa_end		= 0x401e1fff
	},
	{
		.name		= "mpu",
		.pa_start	= 0x401f1000,
		.pa_end		= 0x401f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_aess_dma_addrs[] = {
	{
		.name		= "dmem_dma",
		.pa_start	= 0x49080000,
		.pa_end		= 0x4908ffff
	},
	{
		.name		= "cmem_dma",
		.pa_start	= 0x490a0000,
		.pa_end		= 0x490a1fff
	},
	{
		.name		= "smem_dma",
		.pa_start	= 0x490c0000,
		.pa_end		= 0x490c5fff
	},
	{
		.name		= "pmem_dma",
		.pa_start	= 0x490e0000,
		.pa_end		= 0x490e1fff
	},
	{
		.name		= "dma",
		.pa_start	= 0x490f1000,
		.pa_end		= 0x490f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess (dma) */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l3_main_2 -> c2c */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__c2c = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_c2c_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__counter_32k = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_counter_32k_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_core_addrs[] = {
	{
		.pa_start	= 0x4a002000,
		.pa_end		= 0x4a0027ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_core_addrs[] = {
	{
		.pa_start	= 0x4a100000,
		.pa_end		= 0x4a1007ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_pad_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_pad_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_pad_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_wkup_addrs[] = {
	{
		.pa_start	= 0x4a30c000,
		.pa_end		= 0x4a30c7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_wkup_addrs[] = {
	{
		.pa_start	= 0x4a31e000,
		.pa_end		= 0x4a31e7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_pad_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_pad_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_pad_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_instr -> debugss */
static struct omap_hwmod_ocp_if omap44xx_l3_instr__debugss = {
	.master		= &omap44xx_l3_instr_hwmod,
	.slave		= &omap44xx_debugss_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dma_system = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dma_system_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__dmic = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_dmic_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> iva */
static struct omap_hwmod_ocp_if omap44xx_dsp__iva = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* dsp -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_dsp__sl2if = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dsp_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dma_addrs[] = {
	{
		.pa_start	= 0x58000000,
		.pa_end		= 0x5800007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_addrs[] = {
	{
		.pa_start	= 0x48040000,
		.pa_end		= 0x4804007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_dma_addrs[] = {
	{
		.pa_start	= 0x58001000,
		.pa_end		= 0x58001fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dispc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dispc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48041000,
		.pa_end		= 0x48041fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dispc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dispc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_dma_addrs[] = {
	{
		.pa_start	= 0x58004000,
		.pa_end		= 0x580041ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_addrs[] = {
	{
		.pa_start	= 0x48044000,
		.pa_end		= 0x480441ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_dma_addrs[] = {
	{
		.pa_start	= 0x58005000,
		.pa_end		= 0x580051ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi2 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi2_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_addrs[] = {
	{
		.pa_start	= 0x48045000,
		.pa_end		= 0x480451ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi2_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_dma_addrs[] = {
	{
		.pa_start	= 0x58006000,
		.pa_end		= 0x58006fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_hdmi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_hdmi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_addrs[] = {
	{
		.pa_start	= 0x48046000,
		.pa_end		= 0x48046fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_hdmi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_hdmi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_dma_addrs[] = {
	{
		.pa_start	= 0x58002000,
		.pa_end		= 0x580020ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_rfbi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_rfbi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48042000,
		.pa_end		= 0x480420ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_rfbi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_rfbi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_dma_addrs[] = {
	{
		.pa_start	= 0x58003000,
		.pa_end		= 0x580030ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_venc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_venc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48043000,
		.pa_end		= 0x480430ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_venc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_venc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_elm_addrs[] = {
	{
		.pa_start	= 0x48078000,
		.pa_end		= 0x48078fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> elm */
static struct omap_hwmod_ocp_if omap44xx_l4_per__elm = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_elm_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_elm_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_fdif_addrs[] = {
	{
		.pa_start	= 0x4a10a000,
		.pa_end		= 0x4a10a1ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> fdif */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__fdif = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_fdif_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_fdif_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__gpio1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_gpio1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio6 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio6_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> gpmc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpmc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpmc_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_gpu_addrs[] = {
	{
		.pa_start	= 0x56000000,
		.pa_end		= 0x5600ffff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> gpu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_gpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hdq1w_addrs[] = {
	{
		.pa_start	= 0x480b2000,
		.pa_end		= 0x480b201f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> hdq1w */
static struct omap_hwmod_ocp_if omap44xx_l4_per__hdq1w = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_hdq1w_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hdq1w_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hsi_addrs[] = {
	{
		.pa_start	= 0x4a058000,
		.pa_end		= 0x4a05bfff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> hsi */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__hsi = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_hsi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hsi_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ipu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_iss_addrs[] = {
	{
		.pa_start	= 0x52000000,
		.pa_end		= 0x520000ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> iss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_iss_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_iva__sl2if = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_IVA,
};

/* l3_main_2 -> iva */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iva = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__kbd = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_kbd_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mailbox = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mailbox_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_addrs[] = {
	{
		.pa_start	= 0x40128000,
		.pa_end		= 0x401283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_dma_addrs[] = {
	{
		.pa_start	= 0x49028000,
		.pa_end		= 0x490283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp1_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp2 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp2_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp3_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcbsp4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcbsp4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcbsp4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcpdm = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcpdm_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ocmc_ram */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ocmc_ram = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ocmc_ram_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp_usb_phy */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp2scp_usb_phy = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp2scp_usb_phy_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu_private -> prcm_mpu */
static struct omap_hwmod_ocp_if omap44xx_mpu_private__prcm_mpu = {
	.master		= &omap44xx_mpu_private_hwmod,
	.slave		= &omap44xx_prcm_mpu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> cm_core_aon */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__cm_core_aon = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_cm_core_aon_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> cm_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__cm_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_cm_core_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> prm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__prm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_prm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> scrm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__scrm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_scrm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l3_main_2__sl2if = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_addrs[] = {
	{
		.pa_start	= 0x4012c000,
		.pa_end		= 0x4012c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_dma_addrs[] = {
	{
		.pa_start	= 0x4902c000,
		.pa_end		= 0x4902c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus2_addrs[] = {
	{
		.pa_start	= 0x48076000,
		.pa_end		= 0x480763ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> slimbus2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__slimbus2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_slimbus2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_slimbus2_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_core_addrs[] = {
	{
		.pa_start	= 0x4a0dd000,
		.pa_end		= 0x4a0dd03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_iva_addrs[] = {
	{
		.pa_start	= 0x4a0db000,
		.pa_end		= 0x4a0db03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_iva */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_iva = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_iva_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_iva_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_mpu_addrs[] = {
	{
		.pa_start	= 0x4a0d9000,
		.pa_end		= 0x4a0d903f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_mpu */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_mpu = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_mpu_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_mpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_spinlock_addrs[] = {
	{
		.pa_start	= 0x4a0f6000,
		.pa_end		= 0x4a0f6fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__spinlock = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_spinlock_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_spinlock_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__timer1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_timer1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer5 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer5_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer6 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer6_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer7 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer7_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer8 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer8_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer9 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer9_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer10 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer10_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer11 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer11_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_fs */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_cfg__usb_host_fs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_fs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_host_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_otg_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_otg_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_tll_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_tll_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__wd_timer2 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_wd_timer2_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_addrs[] = {
	{
		.pa_start	= 0x40130000,
		.pa_end		= 0x4013007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_dma_addrs[] = {
	{
		.pa_start	= 0x49030000,
		.pa_end		= 0x4903007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif2 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap44xx_hwmod_ocp_ifs[] __initdata = {
	&omap44xx_l3_main_1__dmm,
	&omap44xx_mpu__dmm,
	&omap44xx_iva__l3_instr,
	&omap44xx_l3_main_3__l3_instr,
	&omap44xx_ocp_wp_noc__l3_instr,
	&omap44xx_dsp__l3_main_1,
	&omap44xx_dss__l3_main_1,
	&omap44xx_l3_main_2__l3_main_1,
	&omap44xx_l4_cfg__l3_main_1,
	&omap44xx_mmc1__l3_main_1,
	&omap44xx_mmc2__l3_main_1,
	&omap44xx_mpu__l3_main_1,
	&omap44xx_debugss__l3_main_2,
	&omap44xx_dma_system__l3_main_2,
	&omap44xx_fdif__l3_main_2,
	&omap44xx_gpu__l3_main_2,
	&omap44xx_hsi__l3_main_2,
	&omap44xx_ipu__l3_main_2,
	&omap44xx_iss__l3_main_2,
	&omap44xx_iva__l3_main_2,
	&omap44xx_l3_main_1__l3_main_2,
	&omap44xx_l4_cfg__l3_main_2,
	/* &omap44xx_usb_host_fs__l3_main_2, */
	&omap44xx_usb_host_hs__l3_main_2,
	&omap44xx_usb_otg_hs__l3_main_2,
	&omap44xx_l3_main_1__l3_main_3,
	&omap44xx_l3_main_2__l3_main_3,
	&omap44xx_l4_cfg__l3_main_3,
	&omap44xx_aess__l4_abe,
	&omap44xx_dsp__l4_abe,
	&omap44xx_l3_main_1__l4_abe,
	&omap44xx_mpu__l4_abe,
	&omap44xx_l3_main_1__l4_cfg,
	&omap44xx_l3_main_2__l4_per,
	&omap44xx_l4_cfg__l4_wkup,
	&omap44xx_mpu__mpu_private,
	&omap44xx_l4_cfg__ocp_wp_noc,
	&omap44xx_l4_abe__aess,
	&omap44xx_l4_abe__aess_dma,
	&omap44xx_l3_main_2__c2c,
	&omap44xx_l4_wkup__counter_32k,
	&omap44xx_l4_cfg__ctrl_module_core,
	&omap44xx_l4_cfg__ctrl_module_pad_core,
	&omap44xx_l4_wkup__ctrl_module_wkup,
	&omap44xx_l4_wkup__ctrl_module_pad_wkup,
	&omap44xx_l3_instr__debugss,
	&omap44xx_l4_cfg__dma_system,
	&omap44xx_l4_abe__dmic,
	&omap44xx_dsp__iva,
	/* &omap44xx_dsp__sl2if, */
	&omap44xx_l4_cfg__dsp,
	&omap44xx_l3_main_2__dss,
	&omap44xx_l4_per__dss,
	&omap44xx_l3_main_2__dss_dispc,
	&omap44xx_l4_per__dss_dispc,
	&omap44xx_l3_main_2__dss_dsi1,
	&omap44xx_l4_per__dss_dsi1,
	&omap44xx_l3_main_2__dss_dsi2,
	&omap44xx_l4_per__dss_dsi2,
	&omap44xx_l3_main_2__dss_hdmi,
	&omap44xx_l4_per__dss_hdmi,
	&omap44xx_l3_main_2__dss_rfbi,
	&omap44xx_l4_per__dss_rfbi,
	&omap44xx_l3_main_2__dss_venc,
	&omap44xx_l4_per__dss_venc,
	&omap44xx_l4_per__elm,
	&omap44xx_l4_cfg__fdif,
	&omap44xx_l4_wkup__gpio1,
	&omap44xx_l4_per__gpio2,
	&omap44xx_l4_per__gpio3,
	&omap44xx_l4_per__gpio4,
	&omap44xx_l4_per__gpio5,
	&omap44xx_l4_per__gpio6,
	&omap44xx_l3_main_2__gpmc,
	&omap44xx_l3_main_2__gpu,
	&omap44xx_l4_per__hdq1w,
	&omap44xx_l4_cfg__hsi,
	&omap44xx_l4_per__i2c1,
	&omap44xx_l4_per__i2c2,
	&omap44xx_l4_per__i2c3,
	&omap44xx_l4_per__i2c4,
	&omap44xx_l3_main_2__ipu,
	&omap44xx_l3_main_2__iss,
	/* &omap44xx_iva__sl2if, */
	&omap44xx_l3_main_2__iva,
	&omap44xx_l4_wkup__kbd,
	&omap44xx_l4_cfg__mailbox,
	&omap44xx_l4_abe__mcasp,
	&omap44xx_l4_abe__mcasp_dma,
	&omap44xx_l4_abe__mcbsp1,
	&omap44xx_l4_abe__mcbsp2,
	&omap44xx_l4_abe__mcbsp3,
	&omap44xx_l4_per__mcbsp4,
	&omap44xx_l4_abe__mcpdm,
	&omap44xx_l4_per__mcspi1,
	&omap44xx_l4_per__mcspi2,
	&omap44xx_l4_per__mcspi3,
	&omap44xx_l4_per__mcspi4,
	&omap44xx_l4_per__mmc1,
	&omap44xx_l4_per__mmc2,
	&omap44xx_l4_per__mmc3,
	&omap44xx_l4_per__mmc4,
	&omap44xx_l4_per__mmc5,
	&omap44xx_l3_main_2__mmu_ipu,
	&omap44xx_l4_cfg__mmu_dsp,
	&omap44xx_l3_main_2__ocmc_ram,
	&omap44xx_l4_cfg__ocp2scp_usb_phy,
	&omap44xx_mpu_private__prcm_mpu,
	&omap44xx_l4_wkup__cm_core_aon,
	&omap44xx_l4_cfg__cm_core,
	&omap44xx_l4_wkup__prm,
	&omap44xx_l4_wkup__scrm,
	/* &omap44xx_l3_main_2__sl2if, */
	&omap44xx_l4_abe__slimbus1,
	&omap44xx_l4_abe__slimbus1_dma,
	&omap44xx_l4_per__slimbus2,
	&omap44xx_l4_cfg__smartreflex_core,
	&omap44xx_l4_cfg__smartreflex_iva,
	&omap44xx_l4_cfg__smartreflex_mpu,
	&omap44xx_l4_cfg__spinlock,
	&omap44xx_l4_wkup__timer1,
	&omap44xx_l4_per__timer2,
	&omap44xx_l4_per__timer3,
	&omap44xx_l4_per__timer4,
	&omap44xx_l4_abe__timer5,
	&omap44xx_l4_abe__timer6,
	&omap44xx_l4_abe__timer7,
	&omap44xx_l4_abe__timer8,
	&omap44xx_l4_per__timer9,
	&omap44xx_l4_per__timer10,
	&omap44xx_l4_per__timer11,
	&omap44xx_l4_per__uart1,
	&omap44xx_l4_per__uart2,
	&omap44xx_l4_per__uart3,
	&omap44xx_l4_per__uart4,
	/* &omap44xx_l4_cfg__usb_host_fs, */
	&omap44xx_l4_cfg__usb_host_hs,
	&omap44xx_l4_cfg__usb_otg_hs,
	&omap44xx_l4_cfg__usb_tll_hs,
	&omap44xx_l4_wkup__wd_timer2,
	&omap44xx_l4_abe__wd_timer3,
	&omap44xx_l4_abe__wd_timer3_dma,
	&omap44xx_mpu__emif1,
	&omap44xx_mpu__emif2,
	NULL,
};

int __init omap44xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap44xx_hwmod_ocp_ifs);
}

static struct omap_hwmod omap44xx_dss_dispc_hwmod = {
	.name		= "dss_dispc",
	.class		= &omap44xx_dispc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dispc_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dispc_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.dev_attr	= &omap44xx_dss_dispc_dev_attr,
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'dsi' class
 * display serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_dsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_dsi_hwmod_class = {
	.name	= "dsi",
	.sysc	= &omap44xx_dsi_sysc,
};

/* dss_dsi1 */
static struct omap_hwmod_irq_info omap44xx_dss_dsi1_irqs[] = {
	{ .irq = 53 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dsi1_sdma_reqs[] = {
	{ .dma_req = 74 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_dsi1_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_dsi1_hwmod = {
	.name		= "dss_dsi1",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi1_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi1_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/* dss_dsi2 */
static struct omap_hwmod_irq_info omap44xx_dss_dsi2_irqs[] = {
	{ .irq = 84 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dsi2_sdma_reqs[] = {
	{ .dma_req = 83 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_dsi2_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_dsi2_hwmod = {
	.name		= "dss_dsi2",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi2_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi2_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi2_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'hdmi' class
 * hdmi controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdmi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_hdmi_hwmod_class = {
	.name	= "hdmi",
	.sysc	= &omap44xx_hdmi_sysc,
};

/* dss_hdmi */
static struct omap_hwmod_irq_info omap44xx_dss_hdmi_irqs[] = {
	{ .irq = 101 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_hdmi_sdma_reqs[] = {
	{ .dma_req = 75 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_hdmi_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap44xx_hdmi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	/*
	 * HDMI audio requires to use no-idle mode. Hence,
	 * set idle mode by software.
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
	.mpu_irqs	= omap44xx_dss_hdmi_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_hdmi_sdma_reqs,
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap44xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap44xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_dma_info omap44xx_dss_rfbi_sdma_reqs[] = {
	{ .dma_req = 13 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_div_ck" },
};

static struct omap_hwmod omap44xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap44xx_rfbi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.sdma_reqs	= omap44xx_dss_rfbi_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'venc' class
 * video encoder
 */

static struct omap_hwmod_class omap44xx_venc_hwmod_class = {
	.name	= "venc",
};

/* dss_venc */
static struct omap_hwmod omap44xx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.class		= &omap44xx_venc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_tv_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'elm' class
 * bch error location module
 */

static struct omap_hwmod_class_sysconfig omap44xx_elm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_elm_hwmod_class = {
	.name	= "elm",
	.sysc	= &omap44xx_elm_sysc,
};

/* elm */
static struct omap_hwmod omap44xx_elm_hwmod = {
	.name		= "elm",
	.class		= &omap44xx_elm_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_ELM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'emif' class
 * external memory interface no1
 */

static struct omap_hwmod_class_sysconfig omap44xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap44xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap44xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap44xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap44xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'fdif' class
 * face detection hw accelerator module
 */

static struct omap_hwmod_class_sysconfig omap44xx_fdif_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * FDIF needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_fdif_hwmod_class = {
	.name	= "fdif",
	.sysc	= &omap44xx_fdif_sysc,
};

/* fdif */
static struct omap_hwmod omap44xx_fdif_hwmod = {
	.name		= "fdif",
	.class		= &omap44xx_fdif_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "fdif_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_FDIF_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpio_sysc = {
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

static struct omap_hwmod_class omap44xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap44xx_gpio_sysc,
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

static struct omap_hwmod omap44xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "l4_wkup_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_GPIO1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO3_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO4_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO5_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'gpmc' class
 * general purpose memory controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_gpmc_hwmod_class = {
	.name	= "gpmc",
	.sysc	= &omap44xx_gpmc_sysc,
};

/* gpmc */
static struct omap_hwmod omap44xx_gpmc_hwmod = {
	.name		= "gpmc",
	.class		= &omap44xx_gpmc_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	/*
	 * XXX HWMOD_INIT_NO_RESET should not be needed for this IP
	 * block.  It is not being added due to any known bugs with
	 * resetting the GPMC IP block, but rather because any timings
	 * set by the bootloader are not being correctly programmed by
	 * the kernel from the board file or DT data.
	 * HWMOD_INIT_NO_RESET should be removed ASAP.
	 */
	.flags		= HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_GPMC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpu' class
 * 2d/3d graphics accelerator
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpu_sysc = {
	.rev_offs	= 0x1fc00,
	.sysc_offs	= 0x1fc10,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_gpu_hwmod_class = {
	.name	= "gpu",
	.sysc	= &omap44xx_gpu_sysc,
};

/* gpu */
static struct omap_hwmod omap44xx_gpu_hwmod = {
	.name		= "gpu",
	.class		= &omap44xx_gpu_hwmod_class,
	.clkdm_name	= "l3_gfx_clkdm",
	.main_clk	= "sgx_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_GFX_GFX_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hdq1w' class
 * hdq / 1-wire serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdq1w_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0014,
	.syss_offs	= 0x0018,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hdq1w_hwmod_class = {
	.name	= "hdq1w",
	.sysc	= &omap44xx_hdq1w_sysc,
};

/* hdq1w */
static struct omap_hwmod omap44xx_hdq1w_hwmod = {
	.name		= "hdq1w",
	.class		= &omap44xx_hdq1w_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_INIT_NO_RESET, /* XXX temporary */
	.main_clk	= "func_12m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_HDQ1W_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hsi' class
 * mipi high-speed synchronous serial interface (multichannel and full-duplex
 * serial if)
 */

static struct omap_hwmod_class_sysconfig omap44xx_hsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hsi_hwmod_class = {
	.name	= "hsi",
	.sysc	= &omap44xx_hsi_sysc,
};

/* hsi */
static struct omap_hwmod omap44xx_hsi_hwmod = {
	.name		= "hsi",
	.class		= &omap44xx_hsi_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "hsi_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_HSI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_i2c_sysc = {
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

static struct omap_hwmod_class omap44xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap44xx_i2c_sysc,
	.rev	= OMAP_I2C_IP_VERSION_2,
	.reset	= &omap_i2c_reset,
};

static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap44xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap44xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap44xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap44xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'ipu' class
 * imaging processor unit
 */

static struct omap_hwmod_class omap44xx_ipu_hwmod_class = {
	.name	= "ipu",
};

/* ipu */
static struct omap_hwmod_rst_info omap44xx_ipu_resets[] = {
	{ .name = "cpu0", .rst_shift = 0 },
	{ .name = "cpu1", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_ipu_hwmod = {
	.name		= "ipu",
	.class		= &omap44xx_ipu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'iss' class
 * external images sensor pixel data processor
 */

static struct omap_hwmod_class_sysconfig omap44xx_iss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * ISS needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_iss_hwmod_class = {
	.name	= "iss",
	.sysc	= &omap44xx_iss_sysc,
};

/* iss */
static struct omap_hwmod_opt_clk iss_opt_clks[] = {
	{ .role = "ctrlclk", .clk = "iss_ctrlclk" },
};

static struct omap_hwmod omap44xx_iss_hwmod = {
	.name		= "iss",
	.class		= &omap44xx_iss_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_ISS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= iss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(iss_opt_clks),
};

/*
 * 'iva' class
 * multi-standard video encoder/decoder hardware accelerator
 */

static struct omap_hwmod_class omap44xx_iva_hwmod_class = {
	.name	= "iva",
};

/* iva */
static struct omap_hwmod_rst_info omap44xx_iva_resets[] = {
	{ .name = "seq0", .rst_shift = 0 },
	{ .name = "seq1", .rst_shift = 1 },
	{ .name = "logic", .rst_shift = 2 },
};

static struct omap_hwmod omap44xx_iva_hwmod = {
	.name		= "iva",
	.class		= &omap44xx_iva_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.rst_lines	= omap44xx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_iva_resets),
	.main_clk	= "dpll_iva_m5x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_IVAHD_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_IVAHD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap44xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap44xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap44xx_kbd_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_KEYBOARD_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_KEYBOARD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap44xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap44xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap44xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap44xx_mailbox_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcasp' class
 * multi-channel audio serial port controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_mcasp = {
	.sidle_shift	= 0,
};

static struct omap_hwmod_class_sysconfig omap44xx_mcasp_sysc = {
	.sysc_offs	= 0x0004,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_mcasp,
};

static struct omap_hwmod_class omap44xx_mcasp_hwmod_class = {
	.name	= "mcasp",
	.sysc	= &omap44xx_mcasp_sysc,
};

/* mcasp */
static struct omap_hwmod omap44xx_mcasp_hwmod = {
	.name		= "mcasp",
	.class		= &omap44xx_mcasp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcasp_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCASP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCASP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap44xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/* mcbsp4 */
static struct omap_hwmod_opt_clk mcbsp4_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp4_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "per_mcbsp4_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCBSP4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp4_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap44xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap44xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap44xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.
	 *
	 * Also, McPDM needs to be configured to NO_IDLE mode when it
	 * is in used otherwise vital clocks will be gated which
	 * results 'slow motion' audio playback.
	 */
	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_PDM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_PDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap44xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
static struct omap_hwmod_dma_info omap44xx_mcspi1_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 34 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 35 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 36 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 37 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx2", .dma_req = 38 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx2", .dma_req = 39 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx3", .dma_req = 40 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx3", .dma_req = 41 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap44xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi1_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
static struct omap_hwmod_dma_info omap44xx_mcspi2_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 42 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 43 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 44 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 45 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi2_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
static struct omap_hwmod_dma_info omap44xx_mcspi3_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 14 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 15 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 22 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 23 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
static struct omap_hwmod_dma_info omap44xx_mcspi4_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 69 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 70 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap44xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mmc_sysc = {
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

static struct omap_hwmod_class omap44xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap44xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_dma_info omap44xx_mmc1_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 60 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 61 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap44xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc1_sdma_reqs,
	.main_clk	= "hsmmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod_dma_info omap44xx_mmc2_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 46 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 47 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc2_sdma_reqs,
	.main_clk	= "hsmmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod_dma_info omap44xx_mmc3_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 76 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 77 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod_dma_info omap44xx_mmc4_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 56 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 57 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod_dma_info omap44xx_mmc5_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 58 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 59 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc5_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig mmu_sysc = {
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &mmu_sysc,
};

/* mmu ipu */

static struct omap_mmu_dev_attr mmu_ipu_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_ipu_addrs[] = {
	{
		.pa_start	= 0x55082000,
		.pa_end		= 0x550820ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__mmu_ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_mmu_ipu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_mmu_ipu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_ipu_dev_attr,
};

/* mmu dsp */

static struct omap_mmu_dev_attr mmu_dsp_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_dsp_addrs[] = {
	{
		.pa_start	= 0x4a066000,
		.pa_end		= 0x4a0660ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mmu_dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mmu_dsp_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_mmu_dsp_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_dsp_dev_attr,
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap44xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap44xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap44xx_mpu_hwmod_class,
	.clkdm_name	= "mpuss_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocmc_ram' class
 * top-level core on-chip ram
 */

static struct omap_hwmod_class omap44xx_ocmc_ram_hwmod_class = {
	.name	= "ocmc_ram",
};

/* ocmc_ram */
static struct omap_hwmod omap44xx_ocmc_ram_hwmod = {
	.name		= "ocmc_ram",
	.class		= &omap44xx_ocmc_ram_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_OCMC_RAM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap44xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap44xx_ocp2scp_sysc,
};

/* ocp2scp_usb_phy */
static struct omap_hwmod omap44xx_ocp2scp_usb_phy_hwmod = {
	.name		= "ocp2scp_usb_phy",
	.class		= &omap44xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	/*
	 * ocp2scp_usb_phy_phy_48m is provided by the OMAP4 PRCM IP
	 * block as an "optional clock," and normally should never be
	 * specified as the main_clk for an OMAP IP block.  However it
	 * turns out that this clock is actually the main clock for
	 * the ocp2scp_usb_phy IP block:
	 * http://lists.infradead.org/pipermail/linux-arm-kernel/2012-September/119943.html
	 * So listing ocp2scp_usb_phy_phy_48m as a main_clk here seems
	 * to be the best workaround.
	 */
	.main_clk	= "ocp2scp_usb_phy_phy_48m",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USBPHYOCP2SCP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'prcm' class
 * power and reset manager (part of the prcm infrastructure) + clock manager 2
 * + clock manager 1 (in always on power domain) + local prm in mpu
 */

static struct omap_hwmod_class omap44xx_prcm_hwmod_class = {
	.name	= "prcm",
};

/* prcm_mpu */
static struct omap_hwmod omap44xx_prcm_mpu_hwmod = {
	.name		= "prcm_mpu",
	.class		= &omap44xx_prcm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core_aon */
static struct omap_hwmod omap44xx_cm_core_aon_hwmod = {
	.name		= "cm_core_aon",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core */
static struct omap_hwmod omap44xx_cm_core_hwmod = {
	.name		= "cm_core",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* prm */
static struct omap_hwmod_rst_info omap44xx_prm_resets[] = {
	{ .name = "rst_global_warm_sw", .rst_shift = 0 },
	{ .name = "rst_global_cold_sw", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_prm_hwmod = {
	.name		= "prm",
	.class		= &omap44xx_prcm_hwmod_class,
	.rst_lines	= omap44xx_prm_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_prm_resets),
};

/*
 * 'scrm' class
 * system clock and reset manager
 */

static struct omap_hwmod_class omap44xx_scrm_hwmod_class = {
	.name	= "scrm",
};

/* scrm */
static struct omap_hwmod omap44xx_scrm_hwmod = {
	.name		= "scrm",
	.class		= &omap44xx_scrm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/*
 * 'sl2if' class
 * shared level 2 memory interface
 */

static struct omap_hwmod_class omap44xx_sl2if_hwmod_class = {
	.name	= "sl2if",
};

/* sl2if */
static struct omap_hwmod omap44xx_sl2if_hwmod = {
	.name		= "sl2if",
	.class		= &omap44xx_sl2if_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_SL2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'slimbus' class
 * bidirectional, multi-drop, multi-channel two-line serial interface between
 * the device and external components
 */

static struct omap_hwmod_class_sysconfig omap44xx_slimbus_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_slimbus_hwmod_class = {
	.name	= "slimbus",
	.sysc	= &omap44xx_slimbus_sysc,
};

/* slimbus1 */
static struct omap_hwmod_opt_clk slimbus1_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus1_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus1_fclk_0" },
	{ .role = "fclk_2", .clk = "slimbus1_fclk_2" },
	{ .role = "slimbus_clk", .clk = "slimbus1_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus1_hwmod = {
	.name		= "slimbus1",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_SLIMBUS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_SLIMBUS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus1_opt_clks),
};

/* slimbus2 */
static struct omap_hwmod_opt_clk slimbus2_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus2_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus2_fclk_0" },
	{ .role = "slimbus_clk", .clk = "slimbus2_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus2_hwmod = {
	.name		= "slimbus2",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_SLIMBUS2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus2_opt_clks),
};

/*
 * 'smartreflex' class
 * smartreflex module (monitor silicon performance and outputs a measure of
 * performance error)
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_smartreflex = {
	.sidle_shift	= 24,
	.enwkup_shift	= 26,
};

static struct omap_hwmod_class_sysconfig omap44xx_smartreflex_sysc = {
	.sysc_offs	= 0x0038,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_smartreflex,
};

static struct omap_hwmod_class omap44xx_smartreflex_hwmod_class = {
	.name	= "smartreflex",
	.sysc	= &omap44xx_smartreflex_sysc,
	.rev	= 2,
};

/* smartreflex_core */
static struct omap_smartreflex_dev_attr smartreflex_core_dev_attr = {
	.sensor_voltdm_name   = "core",
};

static struct omap_hwmod omap44xx_smartreflex_core_hwmod = {
	.name		= "smartreflex_core",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",

	.main_clk	= "smartreflex_core_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_CORE_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_core_dev_attr,
};

/* smartreflex_iva */
static struct omap_smartreflex_dev_attr smartreflex_iva_dev_attr = {
	.sensor_voltdm_name	= "iva",
};

static struct omap_hwmod omap44xx_smartreflex_iva_hwmod = {
	.name		= "smartreflex_iva",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_iva_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_IVA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_iva_dev_attr,
};

/* smartreflex_mpu */
static struct omap_smartreflex_dev_attr smartreflex_mpu_dev_attr = {
	.sensor_voltdm_name	= "mpu",
};

static struct omap_hwmod omap44xx_smartreflex_mpu_hwmod = {
	.name		= "smartreflex_mpu",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_mpu_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_MPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_mpu_dev_attr,
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap44xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap44xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap44xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap44xx_spinlock_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_HW_SEM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap44xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap44xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_sysc,
};

/* always-on timers dev attribute */
static struct omap_timer_capability_dev_attr capability_alwon_dev_attr = {
	.timer_capability	= OMAP_TIMER_ALWON,
};

/* pwm timers dev attribute */
static struct omap_timer_capability_dev_attr capability_pwm_dev_attr = {
	.timer_capability	= OMAP_TIMER_HAS_PWM,
};

/* timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ,
};

/* pwm timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_pwm_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ | OMAP_TIMER_HAS_PWM,
};

/* timer1 */
static struct omap_hwmod omap44xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "dmt1_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_alwon_dev_attr,
};

/* timer2 */
static struct omap_hwmod omap44xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm2_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap44xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm3_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap44xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm4_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap44xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer6 */
static struct omap_hwmod omap44xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer7 */
static struct omap_hwmod omap44xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer8 */
static struct omap_hwmod omap44xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_pwm_dev_attr,
};

/* timer9 */
static struct omap_hwmod omap44xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm9_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer10 */
static struct omap_hwmod omap44xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm10_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer11 */
static struct omap_hwmod omap44xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm11_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap44xx_uart_sysc = {
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

static struct omap_hwmod_class omap44xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap44xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap44xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap44xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap44xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap44xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_fs' class
 * full-speed usb host controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_usb_host_fs = {
	.midle_shift	= 4,
	.sidle_shift	= 2,
	.srst_shift	= 1,
};

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_fs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0210,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_usb_host_fs,
};

static struct omap_hwmod_class omap44xx_usb_host_fs_hwmod_class = {
	.name	= "usb_host_fs",
	.sysc	= &omap44xx_usb_host_fs_sysc,
};

/* usb_host_fs */
static struct omap_hwmod omap44xx_usb_host_fs_hwmod = {
	.name		= "usb_host_fs",
	.class		= &omap44xx_usb_host_fs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_fs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_FS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap44xx_usb_host_hs_sysc,
};

/* usb_host_hs */
static struct omap_hwmod omap44xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap44xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_hs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},

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
};

/*
 * 'usb_otg_hs' class
 * high-speed on-the-go universal serial bus (usb_otg_hs) controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_otg_hs_sysc = {
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_otg_hs_hwmod_class = {
	.name	= "usb_otg_hs",
	.sysc	= &omap44xx_usb_otg_hs_sysc,
};

/* usb_otg_hs */
static struct omap_hwmod_opt_clk usb_otg_hs_opt_clks[] = {
	{ .role = "xclk", .clk = "usb_otg_hs_xclk" },
};

static struct omap_hwmod omap44xx_usb_otg_hs_hwmod = {
	.name		= "usb_otg_hs",
	.class		= &omap44xx_usb_otg_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "usb_otg_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_OTG_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_hs_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_hs_opt_clks),
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap44xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap44xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap44xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_tll_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_TLL_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap44xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap44xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
	.reset		= &omap2_wd_timer_reset,
};

/* wd_timer2 */
static struct omap_hwmod omap44xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_WDT2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_WDT2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* wd_timer3 */
static struct omap_hwmod omap44xx_wd_timer3_hwmod = {
	.name		= "wd_timer3",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_WDT3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_WDT3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};


/*
 * interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__dmm = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_SDMA,
};

/* mpu -> dmm */
static struct omap_hwmod_ocp_if omap44xx_mpu__dmm = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* iva -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_instr = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_l3_main_3__l3_instr = {
	.master		= &omap44xx_l3_main_3_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ocp_wp_noc -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_ocp_wp_noc__l3_instr = {
	.master		= &omap44xx_ocp_wp_noc_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dsp__l3_main_1 = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dss -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dss__l3_main_1 = {
	.master		= &omap44xx_dss_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_1 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc1 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc1__l3_main_1 = {
	.master		= &omap44xx_mmc1_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc2__l3_main_1 = {
	.master		= &omap44xx_mmc2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__l3_main_1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* debugss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_debugss__l3_main_2 = {
	.master		= &omap44xx_debugss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "dbgclk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dma_system -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_dma_system__l3_main_2 = {
	.master		= &omap44xx_dma_system_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* fdif -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_fdif__l3_main_2 = {
	.master		= &omap44xx_fdif_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* gpu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_gpu__l3_main_2 = {
	.master		= &omap44xx_gpu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* hsi -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_hsi__l3_main_2 = {
	.master		= &omap44xx_hsi_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ipu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_ipu__l3_main_2 = {
	.master		= &omap44xx_ipu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iss__l3_main_2 = {
	.master		= &omap44xx_iss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_main_2 = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_2 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_2 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_fs -> l3_main_2 */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_usb_host_fs__l3_main_2 = {
	.master		= &omap44xx_usb_host_fs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_host_hs__l3_main_2 = {
	.master		= &omap44xx_usb_host_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_otg_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_otg_hs__l3_main_2 = {
	.master		= &omap44xx_usb_otg_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_3 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_3 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_3 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* aess -> l4_abe */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_aess__l4_abe = {
	.master		= &omap44xx_aess_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_dsp__l4_abe = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_abe = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_mpu__l4_abe = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_cfg = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_cfg_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l4_per = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l4_per_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l4_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l4_wkup = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l4_wkup_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap44xx_mpu__mpu_private = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_mpu_private_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp_wp_noc */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp_wp_noc = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp_wp_noc_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_aess_addrs[] = {
	{
		.name		= "dmem",
		.pa_start	= 0x40180000,
		.pa_end		= 0x4018ffff
	},
	{
		.name		= "cmem",
		.pa_start	= 0x401a0000,
		.pa_end		= 0x401a1fff
	},
	{
		.name		= "smem",
		.pa_start	= 0x401c0000,
		.pa_end		= 0x401c5fff
	},
	{
		.name		= "pmem",
		.pa_start	= 0x401e0000,
		.pa_end		= 0x401e1fff
	},
	{
		.name		= "mpu",
		.pa_start	= 0x401f1000,
		.pa_end		= 0x401f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_aess_dma_addrs[] = {
	{
		.name		= "dmem_dma",
		.pa_start	= 0x49080000,
		.pa_end		= 0x4908ffff
	},
	{
		.name		= "cmem_dma",
		.pa_start	= 0x490a0000,
		.pa_end		= 0x490a1fff
	},
	{
		.name		= "smem_dma",
		.pa_start	= 0x490c0000,
		.pa_end		= 0x490c5fff
	},
	{
		.name		= "pmem_dma",
		.pa_start	= 0x490e0000,
		.pa_end		= 0x490e1fff
	},
	{
		.name		= "dma",
		.pa_start	= 0x490f1000,
		.pa_end		= 0x490f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess (dma) */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l3_main_2 -> c2c */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__c2c = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_c2c_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__counter_32k = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_counter_32k_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_core_addrs[] = {
	{
		.pa_start	= 0x4a002000,
		.pa_end		= 0x4a0027ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_core_addrs[] = {
	{
		.pa_start	= 0x4a100000,
		.pa_end		= 0x4a1007ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_pad_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_pad_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_pad_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_wkup_addrs[] = {
	{
		.pa_start	= 0x4a30c000,
		.pa_end		= 0x4a30c7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_wkup_addrs[] = {
	{
		.pa_start	= 0x4a31e000,
		.pa_end		= 0x4a31e7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_pad_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_pad_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_pad_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_instr -> debugss */
static struct omap_hwmod_ocp_if omap44xx_l3_instr__debugss = {
	.master		= &omap44xx_l3_instr_hwmod,
	.slave		= &omap44xx_debugss_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dma_system = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dma_system_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__dmic = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_dmic_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> iva */
static struct omap_hwmod_ocp_if omap44xx_dsp__iva = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* dsp -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_dsp__sl2if = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dsp_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dma_addrs[] = {
	{
		.pa_start	= 0x58000000,
		.pa_end		= 0x5800007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_addrs[] = {
	{
		.pa_start	= 0x48040000,
		.pa_end		= 0x4804007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_dma_addrs[] = {
	{
		.pa_start	= 0x58001000,
		.pa_end		= 0x58001fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dispc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dispc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48041000,
		.pa_end		= 0x48041fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dispc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dispc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_dma_addrs[] = {
	{
		.pa_start	= 0x58004000,
		.pa_end		= 0x580041ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_addrs[] = {
	{
		.pa_start	= 0x48044000,
		.pa_end		= 0x480441ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_dma_addrs[] = {
	{
		.pa_start	= 0x58005000,
		.pa_end		= 0x580051ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi2 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi2_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_addrs[] = {
	{
		.pa_start	= 0x48045000,
		.pa_end		= 0x480451ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi2_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_dma_addrs[] = {
	{
		.pa_start	= 0x58006000,
		.pa_end		= 0x58006fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_hdmi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_hdmi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_addrs[] = {
	{
		.pa_start	= 0x48046000,
		.pa_end		= 0x48046fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_hdmi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_hdmi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_dma_addrs[] = {
	{
		.pa_start	= 0x58002000,
		.pa_end		= 0x580020ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_rfbi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_rfbi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48042000,
		.pa_end		= 0x480420ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_rfbi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_rfbi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_dma_addrs[] = {
	{
		.pa_start	= 0x58003000,
		.pa_end		= 0x580030ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_venc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_venc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48043000,
		.pa_end		= 0x480430ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_venc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_venc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_elm_addrs[] = {
	{
		.pa_start	= 0x48078000,
		.pa_end		= 0x48078fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> elm */
static struct omap_hwmod_ocp_if omap44xx_l4_per__elm = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_elm_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_elm_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_fdif_addrs[] = {
	{
		.pa_start	= 0x4a10a000,
		.pa_end		= 0x4a10a1ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> fdif */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__fdif = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_fdif_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_fdif_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__gpio1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_gpio1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio6 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio6_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> gpmc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpmc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpmc_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_gpu_addrs[] = {
	{
		.pa_start	= 0x56000000,
		.pa_end		= 0x5600ffff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> gpu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_gpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hdq1w_addrs[] = {
	{
		.pa_start	= 0x480b2000,
		.pa_end		= 0x480b201f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> hdq1w */
static struct omap_hwmod_ocp_if omap44xx_l4_per__hdq1w = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_hdq1w_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hdq1w_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hsi_addrs[] = {
	{
		.pa_start	= 0x4a058000,
		.pa_end		= 0x4a05bfff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> hsi */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__hsi = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_hsi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hsi_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ipu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_iss_addrs[] = {
	{
		.pa_start	= 0x52000000,
		.pa_end		= 0x520000ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> iss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_iss_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_iva__sl2if = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_IVA,
};

/* l3_main_2 -> iva */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iva = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__kbd = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_kbd_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mailbox = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mailbox_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_addrs[] = {
	{
		.pa_start	= 0x40128000,
		.pa_end		= 0x401283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_dma_addrs[] = {
	{
		.pa_start	= 0x49028000,
		.pa_end		= 0x490283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp1_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp2 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp2_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp3_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcbsp4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcbsp4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcbsp4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcpdm = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcpdm_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ocmc_ram */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ocmc_ram = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ocmc_ram_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp_usb_phy */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp2scp_usb_phy = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp2scp_usb_phy_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu_private -> prcm_mpu */
static struct omap_hwmod_ocp_if omap44xx_mpu_private__prcm_mpu = {
	.master		= &omap44xx_mpu_private_hwmod,
	.slave		= &omap44xx_prcm_mpu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> cm_core_aon */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__cm_core_aon = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_cm_core_aon_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> cm_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__cm_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_cm_core_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> prm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__prm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_prm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> scrm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__scrm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_scrm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l3_main_2__sl2if = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_addrs[] = {
	{
		.pa_start	= 0x4012c000,
		.pa_end		= 0x4012c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_dma_addrs[] = {
	{
		.pa_start	= 0x4902c000,
		.pa_end		= 0x4902c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus2_addrs[] = {
	{
		.pa_start	= 0x48076000,
		.pa_end		= 0x480763ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> slimbus2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__slimbus2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_slimbus2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_slimbus2_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_core_addrs[] = {
	{
		.pa_start	= 0x4a0dd000,
		.pa_end		= 0x4a0dd03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_iva_addrs[] = {
	{
		.pa_start	= 0x4a0db000,
		.pa_end		= 0x4a0db03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_iva */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_iva = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_iva_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_iva_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_mpu_addrs[] = {
	{
		.pa_start	= 0x4a0d9000,
		.pa_end		= 0x4a0d903f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_mpu */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_mpu = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_mpu_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_mpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_spinlock_addrs[] = {
	{
		.pa_start	= 0x4a0f6000,
		.pa_end		= 0x4a0f6fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__spinlock = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_spinlock_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_spinlock_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__timer1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_timer1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer5 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer5_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer6 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer6_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer7 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer7_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer8 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer8_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer9 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer9_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer10 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer10_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer11 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer11_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_fs */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_cfg__usb_host_fs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_fs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_host_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_otg_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_otg_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_tll_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_tll_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__wd_timer2 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_wd_timer2_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_addrs[] = {
	{
		.pa_start	= 0x40130000,
		.pa_end		= 0x4013007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_dma_addrs[] = {
	{
		.pa_start	= 0x49030000,
		.pa_end		= 0x4903007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif2 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap44xx_hwmod_ocp_ifs[] __initdata = {
	&omap44xx_l3_main_1__dmm,
	&omap44xx_mpu__dmm,
	&omap44xx_iva__l3_instr,
	&omap44xx_l3_main_3__l3_instr,
	&omap44xx_ocp_wp_noc__l3_instr,
	&omap44xx_dsp__l3_main_1,
	&omap44xx_dss__l3_main_1,
	&omap44xx_l3_main_2__l3_main_1,
	&omap44xx_l4_cfg__l3_main_1,
	&omap44xx_mmc1__l3_main_1,
	&omap44xx_mmc2__l3_main_1,
	&omap44xx_mpu__l3_main_1,
	&omap44xx_debugss__l3_main_2,
	&omap44xx_dma_system__l3_main_2,
	&omap44xx_fdif__l3_main_2,
	&omap44xx_gpu__l3_main_2,
	&omap44xx_hsi__l3_main_2,
	&omap44xx_ipu__l3_main_2,
	&omap44xx_iss__l3_main_2,
	&omap44xx_iva__l3_main_2,
	&omap44xx_l3_main_1__l3_main_2,
	&omap44xx_l4_cfg__l3_main_2,
	/* &omap44xx_usb_host_fs__l3_main_2, */
	&omap44xx_usb_host_hs__l3_main_2,
	&omap44xx_usb_otg_hs__l3_main_2,
	&omap44xx_l3_main_1__l3_main_3,
	&omap44xx_l3_main_2__l3_main_3,
	&omap44xx_l4_cfg__l3_main_3,
	&omap44xx_aess__l4_abe,
	&omap44xx_dsp__l4_abe,
	&omap44xx_l3_main_1__l4_abe,
	&omap44xx_mpu__l4_abe,
	&omap44xx_l3_main_1__l4_cfg,
	&omap44xx_l3_main_2__l4_per,
	&omap44xx_l4_cfg__l4_wkup,
	&omap44xx_mpu__mpu_private,
	&omap44xx_l4_cfg__ocp_wp_noc,
	&omap44xx_l4_abe__aess,
	&omap44xx_l4_abe__aess_dma,
	&omap44xx_l3_main_2__c2c,
	&omap44xx_l4_wkup__counter_32k,
	&omap44xx_l4_cfg__ctrl_module_core,
	&omap44xx_l4_cfg__ctrl_module_pad_core,
	&omap44xx_l4_wkup__ctrl_module_wkup,
	&omap44xx_l4_wkup__ctrl_module_pad_wkup,
	&omap44xx_l3_instr__debugss,
	&omap44xx_l4_cfg__dma_system,
	&omap44xx_l4_abe__dmic,
	&omap44xx_dsp__iva,
	/* &omap44xx_dsp__sl2if, */
	&omap44xx_l4_cfg__dsp,
	&omap44xx_l3_main_2__dss,
	&omap44xx_l4_per__dss,
	&omap44xx_l3_main_2__dss_dispc,
	&omap44xx_l4_per__dss_dispc,
	&omap44xx_l3_main_2__dss_dsi1,
	&omap44xx_l4_per__dss_dsi1,
	&omap44xx_l3_main_2__dss_dsi2,
	&omap44xx_l4_per__dss_dsi2,
	&omap44xx_l3_main_2__dss_hdmi,
	&omap44xx_l4_per__dss_hdmi,
	&omap44xx_l3_main_2__dss_rfbi,
	&omap44xx_l4_per__dss_rfbi,
	&omap44xx_l3_main_2__dss_venc,
	&omap44xx_l4_per__dss_venc,
	&omap44xx_l4_per__elm,
	&omap44xx_l4_cfg__fdif,
	&omap44xx_l4_wkup__gpio1,
	&omap44xx_l4_per__gpio2,
	&omap44xx_l4_per__gpio3,
	&omap44xx_l4_per__gpio4,
	&omap44xx_l4_per__gpio5,
	&omap44xx_l4_per__gpio6,
	&omap44xx_l3_main_2__gpmc,
	&omap44xx_l3_main_2__gpu,
	&omap44xx_l4_per__hdq1w,
	&omap44xx_l4_cfg__hsi,
	&omap44xx_l4_per__i2c1,
	&omap44xx_l4_per__i2c2,
	&omap44xx_l4_per__i2c3,
	&omap44xx_l4_per__i2c4,
	&omap44xx_l3_main_2__ipu,
	&omap44xx_l3_main_2__iss,
	/* &omap44xx_iva__sl2if, */
	&omap44xx_l3_main_2__iva,
	&omap44xx_l4_wkup__kbd,
	&omap44xx_l4_cfg__mailbox,
	&omap44xx_l4_abe__mcasp,
	&omap44xx_l4_abe__mcasp_dma,
	&omap44xx_l4_abe__mcbsp1,
	&omap44xx_l4_abe__mcbsp2,
	&omap44xx_l4_abe__mcbsp3,
	&omap44xx_l4_per__mcbsp4,
	&omap44xx_l4_abe__mcpdm,
	&omap44xx_l4_per__mcspi1,
	&omap44xx_l4_per__mcspi2,
	&omap44xx_l4_per__mcspi3,
	&omap44xx_l4_per__mcspi4,
	&omap44xx_l4_per__mmc1,
	&omap44xx_l4_per__mmc2,
	&omap44xx_l4_per__mmc3,
	&omap44xx_l4_per__mmc4,
	&omap44xx_l4_per__mmc5,
	&omap44xx_l3_main_2__mmu_ipu,
	&omap44xx_l4_cfg__mmu_dsp,
	&omap44xx_l3_main_2__ocmc_ram,
	&omap44xx_l4_cfg__ocp2scp_usb_phy,
	&omap44xx_mpu_private__prcm_mpu,
	&omap44xx_l4_wkup__cm_core_aon,
	&omap44xx_l4_cfg__cm_core,
	&omap44xx_l4_wkup__prm,
	&omap44xx_l4_wkup__scrm,
	/* &omap44xx_l3_main_2__sl2if, */
	&omap44xx_l4_abe__slimbus1,
	&omap44xx_l4_abe__slimbus1_dma,
	&omap44xx_l4_per__slimbus2,
	&omap44xx_l4_cfg__smartreflex_core,
	&omap44xx_l4_cfg__smartreflex_iva,
	&omap44xx_l4_cfg__smartreflex_mpu,
	&omap44xx_l4_cfg__spinlock,
	&omap44xx_l4_wkup__timer1,
	&omap44xx_l4_per__timer2,
	&omap44xx_l4_per__timer3,
	&omap44xx_l4_per__timer4,
	&omap44xx_l4_abe__timer5,
	&omap44xx_l4_abe__timer6,
	&omap44xx_l4_abe__timer7,
	&omap44xx_l4_abe__timer8,
	&omap44xx_l4_per__timer9,
	&omap44xx_l4_per__timer10,
	&omap44xx_l4_per__timer11,
	&omap44xx_l4_per__uart1,
	&omap44xx_l4_per__uart2,
	&omap44xx_l4_per__uart3,
	&omap44xx_l4_per__uart4,
	/* &omap44xx_l4_cfg__usb_host_fs, */
	&omap44xx_l4_cfg__usb_host_hs,
	&omap44xx_l4_cfg__usb_otg_hs,
	&omap44xx_l4_cfg__usb_tll_hs,
	&omap44xx_l4_wkup__wd_timer2,
	&omap44xx_l4_abe__wd_timer3,
	&omap44xx_l4_abe__wd_timer3_dma,
	&omap44xx_mpu__emif1,
	&omap44xx_mpu__emif2,
	NULL,
};

int __init omap44xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap44xx_hwmod_ocp_ifs);
}

static struct omap_hwmod omap44xx_dss_dsi1_hwmod = {
	.name		= "dss_dsi1",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi1_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi1_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/* dss_dsi2 */
static struct omap_hwmod_irq_info omap44xx_dss_dsi2_irqs[] = {
	{ .irq = 84 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_dsi2_sdma_reqs[] = {
	{ .dma_req = 83 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_dsi2_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_dsi2_hwmod = {
	.name		= "dss_dsi2",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi2_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi2_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi2_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'hdmi' class
 * hdmi controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdmi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_hdmi_hwmod_class = {
	.name	= "hdmi",
	.sysc	= &omap44xx_hdmi_sysc,
};

/* dss_hdmi */
static struct omap_hwmod_irq_info omap44xx_dss_hdmi_irqs[] = {
	{ .irq = 101 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_hdmi_sdma_reqs[] = {
	{ .dma_req = 75 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_hdmi_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap44xx_hdmi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	/*
	 * HDMI audio requires to use no-idle mode. Hence,
	 * set idle mode by software.
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
	.mpu_irqs	= omap44xx_dss_hdmi_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_hdmi_sdma_reqs,
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap44xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap44xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_dma_info omap44xx_dss_rfbi_sdma_reqs[] = {
	{ .dma_req = 13 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_div_ck" },
};

static struct omap_hwmod omap44xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap44xx_rfbi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.sdma_reqs	= omap44xx_dss_rfbi_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'venc' class
 * video encoder
 */

static struct omap_hwmod_class omap44xx_venc_hwmod_class = {
	.name	= "venc",
};

/* dss_venc */
static struct omap_hwmod omap44xx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.class		= &omap44xx_venc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_tv_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'elm' class
 * bch error location module
 */

static struct omap_hwmod_class_sysconfig omap44xx_elm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_elm_hwmod_class = {
	.name	= "elm",
	.sysc	= &omap44xx_elm_sysc,
};

/* elm */
static struct omap_hwmod omap44xx_elm_hwmod = {
	.name		= "elm",
	.class		= &omap44xx_elm_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_ELM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'emif' class
 * external memory interface no1
 */

static struct omap_hwmod_class_sysconfig omap44xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap44xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap44xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap44xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap44xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'fdif' class
 * face detection hw accelerator module
 */

static struct omap_hwmod_class_sysconfig omap44xx_fdif_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * FDIF needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_fdif_hwmod_class = {
	.name	= "fdif",
	.sysc	= &omap44xx_fdif_sysc,
};

/* fdif */
static struct omap_hwmod omap44xx_fdif_hwmod = {
	.name		= "fdif",
	.class		= &omap44xx_fdif_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "fdif_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_FDIF_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpio_sysc = {
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

static struct omap_hwmod_class omap44xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap44xx_gpio_sysc,
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

static struct omap_hwmod omap44xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "l4_wkup_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_GPIO1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO3_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO4_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO5_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'gpmc' class
 * general purpose memory controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_gpmc_hwmod_class = {
	.name	= "gpmc",
	.sysc	= &omap44xx_gpmc_sysc,
};

/* gpmc */
static struct omap_hwmod omap44xx_gpmc_hwmod = {
	.name		= "gpmc",
	.class		= &omap44xx_gpmc_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	/*
	 * XXX HWMOD_INIT_NO_RESET should not be needed for this IP
	 * block.  It is not being added due to any known bugs with
	 * resetting the GPMC IP block, but rather because any timings
	 * set by the bootloader are not being correctly programmed by
	 * the kernel from the board file or DT data.
	 * HWMOD_INIT_NO_RESET should be removed ASAP.
	 */
	.flags		= HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_GPMC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpu' class
 * 2d/3d graphics accelerator
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpu_sysc = {
	.rev_offs	= 0x1fc00,
	.sysc_offs	= 0x1fc10,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_gpu_hwmod_class = {
	.name	= "gpu",
	.sysc	= &omap44xx_gpu_sysc,
};

/* gpu */
static struct omap_hwmod omap44xx_gpu_hwmod = {
	.name		= "gpu",
	.class		= &omap44xx_gpu_hwmod_class,
	.clkdm_name	= "l3_gfx_clkdm",
	.main_clk	= "sgx_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_GFX_GFX_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hdq1w' class
 * hdq / 1-wire serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdq1w_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0014,
	.syss_offs	= 0x0018,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hdq1w_hwmod_class = {
	.name	= "hdq1w",
	.sysc	= &omap44xx_hdq1w_sysc,
};

/* hdq1w */
static struct omap_hwmod omap44xx_hdq1w_hwmod = {
	.name		= "hdq1w",
	.class		= &omap44xx_hdq1w_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_INIT_NO_RESET, /* XXX temporary */
	.main_clk	= "func_12m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_HDQ1W_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hsi' class
 * mipi high-speed synchronous serial interface (multichannel and full-duplex
 * serial if)
 */

static struct omap_hwmod_class_sysconfig omap44xx_hsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hsi_hwmod_class = {
	.name	= "hsi",
	.sysc	= &omap44xx_hsi_sysc,
};

/* hsi */
static struct omap_hwmod omap44xx_hsi_hwmod = {
	.name		= "hsi",
	.class		= &omap44xx_hsi_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "hsi_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_HSI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_i2c_sysc = {
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

static struct omap_hwmod_class omap44xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap44xx_i2c_sysc,
	.rev	= OMAP_I2C_IP_VERSION_2,
	.reset	= &omap_i2c_reset,
};

static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap44xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap44xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap44xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap44xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'ipu' class
 * imaging processor unit
 */

static struct omap_hwmod_class omap44xx_ipu_hwmod_class = {
	.name	= "ipu",
};

/* ipu */
static struct omap_hwmod_rst_info omap44xx_ipu_resets[] = {
	{ .name = "cpu0", .rst_shift = 0 },
	{ .name = "cpu1", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_ipu_hwmod = {
	.name		= "ipu",
	.class		= &omap44xx_ipu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'iss' class
 * external images sensor pixel data processor
 */

static struct omap_hwmod_class_sysconfig omap44xx_iss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * ISS needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_iss_hwmod_class = {
	.name	= "iss",
	.sysc	= &omap44xx_iss_sysc,
};

/* iss */
static struct omap_hwmod_opt_clk iss_opt_clks[] = {
	{ .role = "ctrlclk", .clk = "iss_ctrlclk" },
};

static struct omap_hwmod omap44xx_iss_hwmod = {
	.name		= "iss",
	.class		= &omap44xx_iss_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_ISS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= iss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(iss_opt_clks),
};

/*
 * 'iva' class
 * multi-standard video encoder/decoder hardware accelerator
 */

static struct omap_hwmod_class omap44xx_iva_hwmod_class = {
	.name	= "iva",
};

/* iva */
static struct omap_hwmod_rst_info omap44xx_iva_resets[] = {
	{ .name = "seq0", .rst_shift = 0 },
	{ .name = "seq1", .rst_shift = 1 },
	{ .name = "logic", .rst_shift = 2 },
};

static struct omap_hwmod omap44xx_iva_hwmod = {
	.name		= "iva",
	.class		= &omap44xx_iva_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.rst_lines	= omap44xx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_iva_resets),
	.main_clk	= "dpll_iva_m5x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_IVAHD_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_IVAHD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap44xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap44xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap44xx_kbd_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_KEYBOARD_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_KEYBOARD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap44xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap44xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap44xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap44xx_mailbox_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcasp' class
 * multi-channel audio serial port controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_mcasp = {
	.sidle_shift	= 0,
};

static struct omap_hwmod_class_sysconfig omap44xx_mcasp_sysc = {
	.sysc_offs	= 0x0004,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_mcasp,
};

static struct omap_hwmod_class omap44xx_mcasp_hwmod_class = {
	.name	= "mcasp",
	.sysc	= &omap44xx_mcasp_sysc,
};

/* mcasp */
static struct omap_hwmod omap44xx_mcasp_hwmod = {
	.name		= "mcasp",
	.class		= &omap44xx_mcasp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcasp_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCASP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCASP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap44xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/* mcbsp4 */
static struct omap_hwmod_opt_clk mcbsp4_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp4_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "per_mcbsp4_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCBSP4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp4_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap44xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap44xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap44xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.
	 *
	 * Also, McPDM needs to be configured to NO_IDLE mode when it
	 * is in used otherwise vital clocks will be gated which
	 * results 'slow motion' audio playback.
	 */
	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_PDM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_PDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap44xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
static struct omap_hwmod_dma_info omap44xx_mcspi1_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 34 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 35 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 36 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 37 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx2", .dma_req = 38 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx2", .dma_req = 39 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx3", .dma_req = 40 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx3", .dma_req = 41 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap44xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi1_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
static struct omap_hwmod_dma_info omap44xx_mcspi2_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 42 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 43 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 44 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 45 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi2_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
static struct omap_hwmod_dma_info omap44xx_mcspi3_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 14 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 15 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 22 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 23 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
static struct omap_hwmod_dma_info omap44xx_mcspi4_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 69 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 70 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap44xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mmc_sysc = {
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

static struct omap_hwmod_class omap44xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap44xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_dma_info omap44xx_mmc1_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 60 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 61 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap44xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc1_sdma_reqs,
	.main_clk	= "hsmmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod_dma_info omap44xx_mmc2_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 46 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 47 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc2_sdma_reqs,
	.main_clk	= "hsmmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod_dma_info omap44xx_mmc3_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 76 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 77 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod_dma_info omap44xx_mmc4_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 56 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 57 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod_dma_info omap44xx_mmc5_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 58 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 59 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc5_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig mmu_sysc = {
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &mmu_sysc,
};

/* mmu ipu */

static struct omap_mmu_dev_attr mmu_ipu_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_ipu_addrs[] = {
	{
		.pa_start	= 0x55082000,
		.pa_end		= 0x550820ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__mmu_ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_mmu_ipu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_mmu_ipu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_ipu_dev_attr,
};

/* mmu dsp */

static struct omap_mmu_dev_attr mmu_dsp_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_dsp_addrs[] = {
	{
		.pa_start	= 0x4a066000,
		.pa_end		= 0x4a0660ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mmu_dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mmu_dsp_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_mmu_dsp_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_dsp_dev_attr,
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap44xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap44xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap44xx_mpu_hwmod_class,
	.clkdm_name	= "mpuss_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocmc_ram' class
 * top-level core on-chip ram
 */

static struct omap_hwmod_class omap44xx_ocmc_ram_hwmod_class = {
	.name	= "ocmc_ram",
};

/* ocmc_ram */
static struct omap_hwmod omap44xx_ocmc_ram_hwmod = {
	.name		= "ocmc_ram",
	.class		= &omap44xx_ocmc_ram_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_OCMC_RAM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap44xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap44xx_ocp2scp_sysc,
};

/* ocp2scp_usb_phy */
static struct omap_hwmod omap44xx_ocp2scp_usb_phy_hwmod = {
	.name		= "ocp2scp_usb_phy",
	.class		= &omap44xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	/*
	 * ocp2scp_usb_phy_phy_48m is provided by the OMAP4 PRCM IP
	 * block as an "optional clock," and normally should never be
	 * specified as the main_clk for an OMAP IP block.  However it
	 * turns out that this clock is actually the main clock for
	 * the ocp2scp_usb_phy IP block:
	 * http://lists.infradead.org/pipermail/linux-arm-kernel/2012-September/119943.html
	 * So listing ocp2scp_usb_phy_phy_48m as a main_clk here seems
	 * to be the best workaround.
	 */
	.main_clk	= "ocp2scp_usb_phy_phy_48m",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USBPHYOCP2SCP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'prcm' class
 * power and reset manager (part of the prcm infrastructure) + clock manager 2
 * + clock manager 1 (in always on power domain) + local prm in mpu
 */

static struct omap_hwmod_class omap44xx_prcm_hwmod_class = {
	.name	= "prcm",
};

/* prcm_mpu */
static struct omap_hwmod omap44xx_prcm_mpu_hwmod = {
	.name		= "prcm_mpu",
	.class		= &omap44xx_prcm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core_aon */
static struct omap_hwmod omap44xx_cm_core_aon_hwmod = {
	.name		= "cm_core_aon",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core */
static struct omap_hwmod omap44xx_cm_core_hwmod = {
	.name		= "cm_core",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* prm */
static struct omap_hwmod_rst_info omap44xx_prm_resets[] = {
	{ .name = "rst_global_warm_sw", .rst_shift = 0 },
	{ .name = "rst_global_cold_sw", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_prm_hwmod = {
	.name		= "prm",
	.class		= &omap44xx_prcm_hwmod_class,
	.rst_lines	= omap44xx_prm_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_prm_resets),
};

/*
 * 'scrm' class
 * system clock and reset manager
 */

static struct omap_hwmod_class omap44xx_scrm_hwmod_class = {
	.name	= "scrm",
};

/* scrm */
static struct omap_hwmod omap44xx_scrm_hwmod = {
	.name		= "scrm",
	.class		= &omap44xx_scrm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/*
 * 'sl2if' class
 * shared level 2 memory interface
 */

static struct omap_hwmod_class omap44xx_sl2if_hwmod_class = {
	.name	= "sl2if",
};

/* sl2if */
static struct omap_hwmod omap44xx_sl2if_hwmod = {
	.name		= "sl2if",
	.class		= &omap44xx_sl2if_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_SL2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'slimbus' class
 * bidirectional, multi-drop, multi-channel two-line serial interface between
 * the device and external components
 */

static struct omap_hwmod_class_sysconfig omap44xx_slimbus_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_slimbus_hwmod_class = {
	.name	= "slimbus",
	.sysc	= &omap44xx_slimbus_sysc,
};

/* slimbus1 */
static struct omap_hwmod_opt_clk slimbus1_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus1_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus1_fclk_0" },
	{ .role = "fclk_2", .clk = "slimbus1_fclk_2" },
	{ .role = "slimbus_clk", .clk = "slimbus1_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus1_hwmod = {
	.name		= "slimbus1",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_SLIMBUS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_SLIMBUS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus1_opt_clks),
};

/* slimbus2 */
static struct omap_hwmod_opt_clk slimbus2_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus2_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus2_fclk_0" },
	{ .role = "slimbus_clk", .clk = "slimbus2_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus2_hwmod = {
	.name		= "slimbus2",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_SLIMBUS2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus2_opt_clks),
};

/*
 * 'smartreflex' class
 * smartreflex module (monitor silicon performance and outputs a measure of
 * performance error)
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_smartreflex = {
	.sidle_shift	= 24,
	.enwkup_shift	= 26,
};

static struct omap_hwmod_class_sysconfig omap44xx_smartreflex_sysc = {
	.sysc_offs	= 0x0038,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_smartreflex,
};

static struct omap_hwmod_class omap44xx_smartreflex_hwmod_class = {
	.name	= "smartreflex",
	.sysc	= &omap44xx_smartreflex_sysc,
	.rev	= 2,
};

/* smartreflex_core */
static struct omap_smartreflex_dev_attr smartreflex_core_dev_attr = {
	.sensor_voltdm_name   = "core",
};

static struct omap_hwmod omap44xx_smartreflex_core_hwmod = {
	.name		= "smartreflex_core",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",

	.main_clk	= "smartreflex_core_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_CORE_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_core_dev_attr,
};

/* smartreflex_iva */
static struct omap_smartreflex_dev_attr smartreflex_iva_dev_attr = {
	.sensor_voltdm_name	= "iva",
};

static struct omap_hwmod omap44xx_smartreflex_iva_hwmod = {
	.name		= "smartreflex_iva",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_iva_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_IVA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_iva_dev_attr,
};

/* smartreflex_mpu */
static struct omap_smartreflex_dev_attr smartreflex_mpu_dev_attr = {
	.sensor_voltdm_name	= "mpu",
};

static struct omap_hwmod omap44xx_smartreflex_mpu_hwmod = {
	.name		= "smartreflex_mpu",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_mpu_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_MPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_mpu_dev_attr,
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap44xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap44xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap44xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap44xx_spinlock_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_HW_SEM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap44xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap44xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_sysc,
};

/* always-on timers dev attribute */
static struct omap_timer_capability_dev_attr capability_alwon_dev_attr = {
	.timer_capability	= OMAP_TIMER_ALWON,
};

/* pwm timers dev attribute */
static struct omap_timer_capability_dev_attr capability_pwm_dev_attr = {
	.timer_capability	= OMAP_TIMER_HAS_PWM,
};

/* timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ,
};

/* pwm timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_pwm_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ | OMAP_TIMER_HAS_PWM,
};

/* timer1 */
static struct omap_hwmod omap44xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "dmt1_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_alwon_dev_attr,
};

/* timer2 */
static struct omap_hwmod omap44xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm2_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap44xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm3_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap44xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm4_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap44xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer6 */
static struct omap_hwmod omap44xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer7 */
static struct omap_hwmod omap44xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer8 */
static struct omap_hwmod omap44xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_pwm_dev_attr,
};

/* timer9 */
static struct omap_hwmod omap44xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm9_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer10 */
static struct omap_hwmod omap44xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm10_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer11 */
static struct omap_hwmod omap44xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm11_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap44xx_uart_sysc = {
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

static struct omap_hwmod_class omap44xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap44xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap44xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap44xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap44xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap44xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_fs' class
 * full-speed usb host controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_usb_host_fs = {
	.midle_shift	= 4,
	.sidle_shift	= 2,
	.srst_shift	= 1,
};

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_fs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0210,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_usb_host_fs,
};

static struct omap_hwmod_class omap44xx_usb_host_fs_hwmod_class = {
	.name	= "usb_host_fs",
	.sysc	= &omap44xx_usb_host_fs_sysc,
};

/* usb_host_fs */
static struct omap_hwmod omap44xx_usb_host_fs_hwmod = {
	.name		= "usb_host_fs",
	.class		= &omap44xx_usb_host_fs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_fs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_FS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap44xx_usb_host_hs_sysc,
};

/* usb_host_hs */
static struct omap_hwmod omap44xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap44xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_hs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},

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
};

/*
 * 'usb_otg_hs' class
 * high-speed on-the-go universal serial bus (usb_otg_hs) controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_otg_hs_sysc = {
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_otg_hs_hwmod_class = {
	.name	= "usb_otg_hs",
	.sysc	= &omap44xx_usb_otg_hs_sysc,
};

/* usb_otg_hs */
static struct omap_hwmod_opt_clk usb_otg_hs_opt_clks[] = {
	{ .role = "xclk", .clk = "usb_otg_hs_xclk" },
};

static struct omap_hwmod omap44xx_usb_otg_hs_hwmod = {
	.name		= "usb_otg_hs",
	.class		= &omap44xx_usb_otg_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "usb_otg_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_OTG_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_hs_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_hs_opt_clks),
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap44xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap44xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap44xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_tll_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_TLL_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap44xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap44xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
	.reset		= &omap2_wd_timer_reset,
};

/* wd_timer2 */
static struct omap_hwmod omap44xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_WDT2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_WDT2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* wd_timer3 */
static struct omap_hwmod omap44xx_wd_timer3_hwmod = {
	.name		= "wd_timer3",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_WDT3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_WDT3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};


/*
 * interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__dmm = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_SDMA,
};

/* mpu -> dmm */
static struct omap_hwmod_ocp_if omap44xx_mpu__dmm = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* iva -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_instr = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_l3_main_3__l3_instr = {
	.master		= &omap44xx_l3_main_3_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ocp_wp_noc -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_ocp_wp_noc__l3_instr = {
	.master		= &omap44xx_ocp_wp_noc_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dsp__l3_main_1 = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dss -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dss__l3_main_1 = {
	.master		= &omap44xx_dss_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_1 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc1 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc1__l3_main_1 = {
	.master		= &omap44xx_mmc1_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc2__l3_main_1 = {
	.master		= &omap44xx_mmc2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__l3_main_1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* debugss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_debugss__l3_main_2 = {
	.master		= &omap44xx_debugss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "dbgclk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dma_system -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_dma_system__l3_main_2 = {
	.master		= &omap44xx_dma_system_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* fdif -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_fdif__l3_main_2 = {
	.master		= &omap44xx_fdif_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* gpu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_gpu__l3_main_2 = {
	.master		= &omap44xx_gpu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* hsi -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_hsi__l3_main_2 = {
	.master		= &omap44xx_hsi_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ipu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_ipu__l3_main_2 = {
	.master		= &omap44xx_ipu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iss__l3_main_2 = {
	.master		= &omap44xx_iss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_main_2 = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_2 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_2 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_fs -> l3_main_2 */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_usb_host_fs__l3_main_2 = {
	.master		= &omap44xx_usb_host_fs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_host_hs__l3_main_2 = {
	.master		= &omap44xx_usb_host_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_otg_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_otg_hs__l3_main_2 = {
	.master		= &omap44xx_usb_otg_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_3 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_3 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_3 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* aess -> l4_abe */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_aess__l4_abe = {
	.master		= &omap44xx_aess_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_dsp__l4_abe = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_abe = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_mpu__l4_abe = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_cfg = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_cfg_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l4_per = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l4_per_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l4_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l4_wkup = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l4_wkup_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap44xx_mpu__mpu_private = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_mpu_private_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp_wp_noc */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp_wp_noc = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp_wp_noc_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_aess_addrs[] = {
	{
		.name		= "dmem",
		.pa_start	= 0x40180000,
		.pa_end		= 0x4018ffff
	},
	{
		.name		= "cmem",
		.pa_start	= 0x401a0000,
		.pa_end		= 0x401a1fff
	},
	{
		.name		= "smem",
		.pa_start	= 0x401c0000,
		.pa_end		= 0x401c5fff
	},
	{
		.name		= "pmem",
		.pa_start	= 0x401e0000,
		.pa_end		= 0x401e1fff
	},
	{
		.name		= "mpu",
		.pa_start	= 0x401f1000,
		.pa_end		= 0x401f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_aess_dma_addrs[] = {
	{
		.name		= "dmem_dma",
		.pa_start	= 0x49080000,
		.pa_end		= 0x4908ffff
	},
	{
		.name		= "cmem_dma",
		.pa_start	= 0x490a0000,
		.pa_end		= 0x490a1fff
	},
	{
		.name		= "smem_dma",
		.pa_start	= 0x490c0000,
		.pa_end		= 0x490c5fff
	},
	{
		.name		= "pmem_dma",
		.pa_start	= 0x490e0000,
		.pa_end		= 0x490e1fff
	},
	{
		.name		= "dma",
		.pa_start	= 0x490f1000,
		.pa_end		= 0x490f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess (dma) */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l3_main_2 -> c2c */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__c2c = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_c2c_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__counter_32k = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_counter_32k_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_core_addrs[] = {
	{
		.pa_start	= 0x4a002000,
		.pa_end		= 0x4a0027ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_core_addrs[] = {
	{
		.pa_start	= 0x4a100000,
		.pa_end		= 0x4a1007ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_pad_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_pad_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_pad_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_wkup_addrs[] = {
	{
		.pa_start	= 0x4a30c000,
		.pa_end		= 0x4a30c7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_wkup_addrs[] = {
	{
		.pa_start	= 0x4a31e000,
		.pa_end		= 0x4a31e7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_pad_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_pad_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_pad_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_instr -> debugss */
static struct omap_hwmod_ocp_if omap44xx_l3_instr__debugss = {
	.master		= &omap44xx_l3_instr_hwmod,
	.slave		= &omap44xx_debugss_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dma_system = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dma_system_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__dmic = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_dmic_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> iva */
static struct omap_hwmod_ocp_if omap44xx_dsp__iva = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* dsp -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_dsp__sl2if = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dsp_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dma_addrs[] = {
	{
		.pa_start	= 0x58000000,
		.pa_end		= 0x5800007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_addrs[] = {
	{
		.pa_start	= 0x48040000,
		.pa_end		= 0x4804007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_dma_addrs[] = {
	{
		.pa_start	= 0x58001000,
		.pa_end		= 0x58001fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dispc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dispc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48041000,
		.pa_end		= 0x48041fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dispc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dispc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_dma_addrs[] = {
	{
		.pa_start	= 0x58004000,
		.pa_end		= 0x580041ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_addrs[] = {
	{
		.pa_start	= 0x48044000,
		.pa_end		= 0x480441ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_dma_addrs[] = {
	{
		.pa_start	= 0x58005000,
		.pa_end		= 0x580051ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi2 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi2_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_addrs[] = {
	{
		.pa_start	= 0x48045000,
		.pa_end		= 0x480451ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi2_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_dma_addrs[] = {
	{
		.pa_start	= 0x58006000,
		.pa_end		= 0x58006fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_hdmi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_hdmi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_addrs[] = {
	{
		.pa_start	= 0x48046000,
		.pa_end		= 0x48046fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_hdmi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_hdmi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_dma_addrs[] = {
	{
		.pa_start	= 0x58002000,
		.pa_end		= 0x580020ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_rfbi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_rfbi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48042000,
		.pa_end		= 0x480420ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_rfbi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_rfbi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_dma_addrs[] = {
	{
		.pa_start	= 0x58003000,
		.pa_end		= 0x580030ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_venc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_venc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48043000,
		.pa_end		= 0x480430ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_venc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_venc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_elm_addrs[] = {
	{
		.pa_start	= 0x48078000,
		.pa_end		= 0x48078fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> elm */
static struct omap_hwmod_ocp_if omap44xx_l4_per__elm = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_elm_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_elm_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_fdif_addrs[] = {
	{
		.pa_start	= 0x4a10a000,
		.pa_end		= 0x4a10a1ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> fdif */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__fdif = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_fdif_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_fdif_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__gpio1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_gpio1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio6 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio6_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> gpmc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpmc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpmc_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_gpu_addrs[] = {
	{
		.pa_start	= 0x56000000,
		.pa_end		= 0x5600ffff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> gpu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_gpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hdq1w_addrs[] = {
	{
		.pa_start	= 0x480b2000,
		.pa_end		= 0x480b201f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> hdq1w */
static struct omap_hwmod_ocp_if omap44xx_l4_per__hdq1w = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_hdq1w_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hdq1w_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hsi_addrs[] = {
	{
		.pa_start	= 0x4a058000,
		.pa_end		= 0x4a05bfff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> hsi */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__hsi = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_hsi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hsi_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ipu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_iss_addrs[] = {
	{
		.pa_start	= 0x52000000,
		.pa_end		= 0x520000ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> iss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_iss_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_iva__sl2if = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_IVA,
};

/* l3_main_2 -> iva */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iva = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__kbd = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_kbd_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mailbox = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mailbox_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_addrs[] = {
	{
		.pa_start	= 0x40128000,
		.pa_end		= 0x401283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_dma_addrs[] = {
	{
		.pa_start	= 0x49028000,
		.pa_end		= 0x490283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp1_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp2 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp2_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp3_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcbsp4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcbsp4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcbsp4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcpdm = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcpdm_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ocmc_ram */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ocmc_ram = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ocmc_ram_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp_usb_phy */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp2scp_usb_phy = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp2scp_usb_phy_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu_private -> prcm_mpu */
static struct omap_hwmod_ocp_if omap44xx_mpu_private__prcm_mpu = {
	.master		= &omap44xx_mpu_private_hwmod,
	.slave		= &omap44xx_prcm_mpu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> cm_core_aon */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__cm_core_aon = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_cm_core_aon_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> cm_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__cm_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_cm_core_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> prm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__prm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_prm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> scrm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__scrm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_scrm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l3_main_2__sl2if = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_addrs[] = {
	{
		.pa_start	= 0x4012c000,
		.pa_end		= 0x4012c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_dma_addrs[] = {
	{
		.pa_start	= 0x4902c000,
		.pa_end		= 0x4902c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus2_addrs[] = {
	{
		.pa_start	= 0x48076000,
		.pa_end		= 0x480763ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> slimbus2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__slimbus2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_slimbus2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_slimbus2_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_core_addrs[] = {
	{
		.pa_start	= 0x4a0dd000,
		.pa_end		= 0x4a0dd03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_iva_addrs[] = {
	{
		.pa_start	= 0x4a0db000,
		.pa_end		= 0x4a0db03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_iva */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_iva = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_iva_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_iva_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_mpu_addrs[] = {
	{
		.pa_start	= 0x4a0d9000,
		.pa_end		= 0x4a0d903f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_mpu */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_mpu = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_mpu_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_mpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_spinlock_addrs[] = {
	{
		.pa_start	= 0x4a0f6000,
		.pa_end		= 0x4a0f6fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__spinlock = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_spinlock_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_spinlock_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__timer1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_timer1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer5 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer5_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer6 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer6_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer7 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer7_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer8 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer8_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer9 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer9_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer10 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer10_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer11 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer11_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_fs */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_cfg__usb_host_fs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_fs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_host_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_otg_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_otg_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_tll_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_tll_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__wd_timer2 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_wd_timer2_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_addrs[] = {
	{
		.pa_start	= 0x40130000,
		.pa_end		= 0x4013007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_dma_addrs[] = {
	{
		.pa_start	= 0x49030000,
		.pa_end		= 0x4903007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif2 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap44xx_hwmod_ocp_ifs[] __initdata = {
	&omap44xx_l3_main_1__dmm,
	&omap44xx_mpu__dmm,
	&omap44xx_iva__l3_instr,
	&omap44xx_l3_main_3__l3_instr,
	&omap44xx_ocp_wp_noc__l3_instr,
	&omap44xx_dsp__l3_main_1,
	&omap44xx_dss__l3_main_1,
	&omap44xx_l3_main_2__l3_main_1,
	&omap44xx_l4_cfg__l3_main_1,
	&omap44xx_mmc1__l3_main_1,
	&omap44xx_mmc2__l3_main_1,
	&omap44xx_mpu__l3_main_1,
	&omap44xx_debugss__l3_main_2,
	&omap44xx_dma_system__l3_main_2,
	&omap44xx_fdif__l3_main_2,
	&omap44xx_gpu__l3_main_2,
	&omap44xx_hsi__l3_main_2,
	&omap44xx_ipu__l3_main_2,
	&omap44xx_iss__l3_main_2,
	&omap44xx_iva__l3_main_2,
	&omap44xx_l3_main_1__l3_main_2,
	&omap44xx_l4_cfg__l3_main_2,
	/* &omap44xx_usb_host_fs__l3_main_2, */
	&omap44xx_usb_host_hs__l3_main_2,
	&omap44xx_usb_otg_hs__l3_main_2,
	&omap44xx_l3_main_1__l3_main_3,
	&omap44xx_l3_main_2__l3_main_3,
	&omap44xx_l4_cfg__l3_main_3,
	&omap44xx_aess__l4_abe,
	&omap44xx_dsp__l4_abe,
	&omap44xx_l3_main_1__l4_abe,
	&omap44xx_mpu__l4_abe,
	&omap44xx_l3_main_1__l4_cfg,
	&omap44xx_l3_main_2__l4_per,
	&omap44xx_l4_cfg__l4_wkup,
	&omap44xx_mpu__mpu_private,
	&omap44xx_l4_cfg__ocp_wp_noc,
	&omap44xx_l4_abe__aess,
	&omap44xx_l4_abe__aess_dma,
	&omap44xx_l3_main_2__c2c,
	&omap44xx_l4_wkup__counter_32k,
	&omap44xx_l4_cfg__ctrl_module_core,
	&omap44xx_l4_cfg__ctrl_module_pad_core,
	&omap44xx_l4_wkup__ctrl_module_wkup,
	&omap44xx_l4_wkup__ctrl_module_pad_wkup,
	&omap44xx_l3_instr__debugss,
	&omap44xx_l4_cfg__dma_system,
	&omap44xx_l4_abe__dmic,
	&omap44xx_dsp__iva,
	/* &omap44xx_dsp__sl2if, */
	&omap44xx_l4_cfg__dsp,
	&omap44xx_l3_main_2__dss,
	&omap44xx_l4_per__dss,
	&omap44xx_l3_main_2__dss_dispc,
	&omap44xx_l4_per__dss_dispc,
	&omap44xx_l3_main_2__dss_dsi1,
	&omap44xx_l4_per__dss_dsi1,
	&omap44xx_l3_main_2__dss_dsi2,
	&omap44xx_l4_per__dss_dsi2,
	&omap44xx_l3_main_2__dss_hdmi,
	&omap44xx_l4_per__dss_hdmi,
	&omap44xx_l3_main_2__dss_rfbi,
	&omap44xx_l4_per__dss_rfbi,
	&omap44xx_l3_main_2__dss_venc,
	&omap44xx_l4_per__dss_venc,
	&omap44xx_l4_per__elm,
	&omap44xx_l4_cfg__fdif,
	&omap44xx_l4_wkup__gpio1,
	&omap44xx_l4_per__gpio2,
	&omap44xx_l4_per__gpio3,
	&omap44xx_l4_per__gpio4,
	&omap44xx_l4_per__gpio5,
	&omap44xx_l4_per__gpio6,
	&omap44xx_l3_main_2__gpmc,
	&omap44xx_l3_main_2__gpu,
	&omap44xx_l4_per__hdq1w,
	&omap44xx_l4_cfg__hsi,
	&omap44xx_l4_per__i2c1,
	&omap44xx_l4_per__i2c2,
	&omap44xx_l4_per__i2c3,
	&omap44xx_l4_per__i2c4,
	&omap44xx_l3_main_2__ipu,
	&omap44xx_l3_main_2__iss,
	/* &omap44xx_iva__sl2if, */
	&omap44xx_l3_main_2__iva,
	&omap44xx_l4_wkup__kbd,
	&omap44xx_l4_cfg__mailbox,
	&omap44xx_l4_abe__mcasp,
	&omap44xx_l4_abe__mcasp_dma,
	&omap44xx_l4_abe__mcbsp1,
	&omap44xx_l4_abe__mcbsp2,
	&omap44xx_l4_abe__mcbsp3,
	&omap44xx_l4_per__mcbsp4,
	&omap44xx_l4_abe__mcpdm,
	&omap44xx_l4_per__mcspi1,
	&omap44xx_l4_per__mcspi2,
	&omap44xx_l4_per__mcspi3,
	&omap44xx_l4_per__mcspi4,
	&omap44xx_l4_per__mmc1,
	&omap44xx_l4_per__mmc2,
	&omap44xx_l4_per__mmc3,
	&omap44xx_l4_per__mmc4,
	&omap44xx_l4_per__mmc5,
	&omap44xx_l3_main_2__mmu_ipu,
	&omap44xx_l4_cfg__mmu_dsp,
	&omap44xx_l3_main_2__ocmc_ram,
	&omap44xx_l4_cfg__ocp2scp_usb_phy,
	&omap44xx_mpu_private__prcm_mpu,
	&omap44xx_l4_wkup__cm_core_aon,
	&omap44xx_l4_cfg__cm_core,
	&omap44xx_l4_wkup__prm,
	&omap44xx_l4_wkup__scrm,
	/* &omap44xx_l3_main_2__sl2if, */
	&omap44xx_l4_abe__slimbus1,
	&omap44xx_l4_abe__slimbus1_dma,
	&omap44xx_l4_per__slimbus2,
	&omap44xx_l4_cfg__smartreflex_core,
	&omap44xx_l4_cfg__smartreflex_iva,
	&omap44xx_l4_cfg__smartreflex_mpu,
	&omap44xx_l4_cfg__spinlock,
	&omap44xx_l4_wkup__timer1,
	&omap44xx_l4_per__timer2,
	&omap44xx_l4_per__timer3,
	&omap44xx_l4_per__timer4,
	&omap44xx_l4_abe__timer5,
	&omap44xx_l4_abe__timer6,
	&omap44xx_l4_abe__timer7,
	&omap44xx_l4_abe__timer8,
	&omap44xx_l4_per__timer9,
	&omap44xx_l4_per__timer10,
	&omap44xx_l4_per__timer11,
	&omap44xx_l4_per__uart1,
	&omap44xx_l4_per__uart2,
	&omap44xx_l4_per__uart3,
	&omap44xx_l4_per__uart4,
	/* &omap44xx_l4_cfg__usb_host_fs, */
	&omap44xx_l4_cfg__usb_host_hs,
	&omap44xx_l4_cfg__usb_otg_hs,
	&omap44xx_l4_cfg__usb_tll_hs,
	&omap44xx_l4_wkup__wd_timer2,
	&omap44xx_l4_abe__wd_timer3,
	&omap44xx_l4_abe__wd_timer3_dma,
	&omap44xx_mpu__emif1,
	&omap44xx_mpu__emif2,
	NULL,
};

int __init omap44xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap44xx_hwmod_ocp_ifs);
}

static struct omap_hwmod omap44xx_dss_dsi2_hwmod = {
	.name		= "dss_dsi2",
	.class		= &omap44xx_dsi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.mpu_irqs	= omap44xx_dss_dsi2_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_dsi2_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_dsi2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi2_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'hdmi' class
 * hdmi controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdmi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_hdmi_hwmod_class = {
	.name	= "hdmi",
	.sysc	= &omap44xx_hdmi_sysc,
};

/* dss_hdmi */
static struct omap_hwmod_irq_info omap44xx_dss_hdmi_irqs[] = {
	{ .irq = 101 + OMAP44XX_IRQ_GIC_START },
	{ .irq = -1 }
};

static struct omap_hwmod_dma_info omap44xx_dss_hdmi_sdma_reqs[] = {
	{ .dma_req = 75 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_hdmi_opt_clks[] = {
	{ .role = "sys_clk", .clk = "dss_sys_clk" },
};

static struct omap_hwmod omap44xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap44xx_hdmi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	/*
	 * HDMI audio requires to use no-idle mode. Hence,
	 * set idle mode by software.
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
	.mpu_irqs	= omap44xx_dss_hdmi_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_hdmi_sdma_reqs,
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap44xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap44xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_dma_info omap44xx_dss_rfbi_sdma_reqs[] = {
	{ .dma_req = 13 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_div_ck" },
};

static struct omap_hwmod omap44xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap44xx_rfbi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.sdma_reqs	= omap44xx_dss_rfbi_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'venc' class
 * video encoder
 */

static struct omap_hwmod_class omap44xx_venc_hwmod_class = {
	.name	= "venc",
};

/* dss_venc */
static struct omap_hwmod omap44xx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.class		= &omap44xx_venc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_tv_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'elm' class
 * bch error location module
 */

static struct omap_hwmod_class_sysconfig omap44xx_elm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_elm_hwmod_class = {
	.name	= "elm",
	.sysc	= &omap44xx_elm_sysc,
};

/* elm */
static struct omap_hwmod omap44xx_elm_hwmod = {
	.name		= "elm",
	.class		= &omap44xx_elm_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_ELM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'emif' class
 * external memory interface no1
 */

static struct omap_hwmod_class_sysconfig omap44xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap44xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap44xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap44xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap44xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'fdif' class
 * face detection hw accelerator module
 */

static struct omap_hwmod_class_sysconfig omap44xx_fdif_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * FDIF needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_fdif_hwmod_class = {
	.name	= "fdif",
	.sysc	= &omap44xx_fdif_sysc,
};

/* fdif */
static struct omap_hwmod omap44xx_fdif_hwmod = {
	.name		= "fdif",
	.class		= &omap44xx_fdif_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "fdif_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_FDIF_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpio_sysc = {
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

static struct omap_hwmod_class omap44xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap44xx_gpio_sysc,
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

static struct omap_hwmod omap44xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "l4_wkup_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_GPIO1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO3_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO4_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO5_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'gpmc' class
 * general purpose memory controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_gpmc_hwmod_class = {
	.name	= "gpmc",
	.sysc	= &omap44xx_gpmc_sysc,
};

/* gpmc */
static struct omap_hwmod omap44xx_gpmc_hwmod = {
	.name		= "gpmc",
	.class		= &omap44xx_gpmc_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	/*
	 * XXX HWMOD_INIT_NO_RESET should not be needed for this IP
	 * block.  It is not being added due to any known bugs with
	 * resetting the GPMC IP block, but rather because any timings
	 * set by the bootloader are not being correctly programmed by
	 * the kernel from the board file or DT data.
	 * HWMOD_INIT_NO_RESET should be removed ASAP.
	 */
	.flags		= HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_GPMC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpu' class
 * 2d/3d graphics accelerator
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpu_sysc = {
	.rev_offs	= 0x1fc00,
	.sysc_offs	= 0x1fc10,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_gpu_hwmod_class = {
	.name	= "gpu",
	.sysc	= &omap44xx_gpu_sysc,
};

/* gpu */
static struct omap_hwmod omap44xx_gpu_hwmod = {
	.name		= "gpu",
	.class		= &omap44xx_gpu_hwmod_class,
	.clkdm_name	= "l3_gfx_clkdm",
	.main_clk	= "sgx_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_GFX_GFX_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hdq1w' class
 * hdq / 1-wire serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdq1w_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0014,
	.syss_offs	= 0x0018,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hdq1w_hwmod_class = {
	.name	= "hdq1w",
	.sysc	= &omap44xx_hdq1w_sysc,
};

/* hdq1w */
static struct omap_hwmod omap44xx_hdq1w_hwmod = {
	.name		= "hdq1w",
	.class		= &omap44xx_hdq1w_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_INIT_NO_RESET, /* XXX temporary */
	.main_clk	= "func_12m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_HDQ1W_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hsi' class
 * mipi high-speed synchronous serial interface (multichannel and full-duplex
 * serial if)
 */

static struct omap_hwmod_class_sysconfig omap44xx_hsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hsi_hwmod_class = {
	.name	= "hsi",
	.sysc	= &omap44xx_hsi_sysc,
};

/* hsi */
static struct omap_hwmod omap44xx_hsi_hwmod = {
	.name		= "hsi",
	.class		= &omap44xx_hsi_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "hsi_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_HSI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_i2c_sysc = {
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

static struct omap_hwmod_class omap44xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap44xx_i2c_sysc,
	.rev	= OMAP_I2C_IP_VERSION_2,
	.reset	= &omap_i2c_reset,
};

static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap44xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap44xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap44xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap44xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'ipu' class
 * imaging processor unit
 */

static struct omap_hwmod_class omap44xx_ipu_hwmod_class = {
	.name	= "ipu",
};

/* ipu */
static struct omap_hwmod_rst_info omap44xx_ipu_resets[] = {
	{ .name = "cpu0", .rst_shift = 0 },
	{ .name = "cpu1", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_ipu_hwmod = {
	.name		= "ipu",
	.class		= &omap44xx_ipu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'iss' class
 * external images sensor pixel data processor
 */

static struct omap_hwmod_class_sysconfig omap44xx_iss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * ISS needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_iss_hwmod_class = {
	.name	= "iss",
	.sysc	= &omap44xx_iss_sysc,
};

/* iss */
static struct omap_hwmod_opt_clk iss_opt_clks[] = {
	{ .role = "ctrlclk", .clk = "iss_ctrlclk" },
};

static struct omap_hwmod omap44xx_iss_hwmod = {
	.name		= "iss",
	.class		= &omap44xx_iss_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_ISS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= iss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(iss_opt_clks),
};

/*
 * 'iva' class
 * multi-standard video encoder/decoder hardware accelerator
 */

static struct omap_hwmod_class omap44xx_iva_hwmod_class = {
	.name	= "iva",
};

/* iva */
static struct omap_hwmod_rst_info omap44xx_iva_resets[] = {
	{ .name = "seq0", .rst_shift = 0 },
	{ .name = "seq1", .rst_shift = 1 },
	{ .name = "logic", .rst_shift = 2 },
};

static struct omap_hwmod omap44xx_iva_hwmod = {
	.name		= "iva",
	.class		= &omap44xx_iva_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.rst_lines	= omap44xx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_iva_resets),
	.main_clk	= "dpll_iva_m5x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_IVAHD_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_IVAHD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap44xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap44xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap44xx_kbd_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_KEYBOARD_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_KEYBOARD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap44xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap44xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap44xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap44xx_mailbox_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcasp' class
 * multi-channel audio serial port controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_mcasp = {
	.sidle_shift	= 0,
};

static struct omap_hwmod_class_sysconfig omap44xx_mcasp_sysc = {
	.sysc_offs	= 0x0004,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_mcasp,
};

static struct omap_hwmod_class omap44xx_mcasp_hwmod_class = {
	.name	= "mcasp",
	.sysc	= &omap44xx_mcasp_sysc,
};

/* mcasp */
static struct omap_hwmod omap44xx_mcasp_hwmod = {
	.name		= "mcasp",
	.class		= &omap44xx_mcasp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcasp_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCASP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCASP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap44xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/* mcbsp4 */
static struct omap_hwmod_opt_clk mcbsp4_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp4_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "per_mcbsp4_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCBSP4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp4_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap44xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap44xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap44xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.
	 *
	 * Also, McPDM needs to be configured to NO_IDLE mode when it
	 * is in used otherwise vital clocks will be gated which
	 * results 'slow motion' audio playback.
	 */
	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_PDM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_PDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap44xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
static struct omap_hwmod_dma_info omap44xx_mcspi1_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 34 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 35 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 36 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 37 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx2", .dma_req = 38 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx2", .dma_req = 39 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx3", .dma_req = 40 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx3", .dma_req = 41 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap44xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi1_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
static struct omap_hwmod_dma_info omap44xx_mcspi2_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 42 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 43 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 44 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 45 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi2_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
static struct omap_hwmod_dma_info omap44xx_mcspi3_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 14 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 15 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 22 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 23 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
static struct omap_hwmod_dma_info omap44xx_mcspi4_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 69 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 70 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap44xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mmc_sysc = {
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

static struct omap_hwmod_class omap44xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap44xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_dma_info omap44xx_mmc1_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 60 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 61 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap44xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc1_sdma_reqs,
	.main_clk	= "hsmmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod_dma_info omap44xx_mmc2_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 46 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 47 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc2_sdma_reqs,
	.main_clk	= "hsmmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod_dma_info omap44xx_mmc3_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 76 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 77 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod_dma_info omap44xx_mmc4_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 56 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 57 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod_dma_info omap44xx_mmc5_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 58 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 59 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc5_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig mmu_sysc = {
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &mmu_sysc,
};

/* mmu ipu */

static struct omap_mmu_dev_attr mmu_ipu_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_ipu_addrs[] = {
	{
		.pa_start	= 0x55082000,
		.pa_end		= 0x550820ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__mmu_ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_mmu_ipu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_mmu_ipu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_ipu_dev_attr,
};

/* mmu dsp */

static struct omap_mmu_dev_attr mmu_dsp_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_dsp_addrs[] = {
	{
		.pa_start	= 0x4a066000,
		.pa_end		= 0x4a0660ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mmu_dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mmu_dsp_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_mmu_dsp_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_dsp_dev_attr,
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap44xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap44xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap44xx_mpu_hwmod_class,
	.clkdm_name	= "mpuss_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocmc_ram' class
 * top-level core on-chip ram
 */

static struct omap_hwmod_class omap44xx_ocmc_ram_hwmod_class = {
	.name	= "ocmc_ram",
};

/* ocmc_ram */
static struct omap_hwmod omap44xx_ocmc_ram_hwmod = {
	.name		= "ocmc_ram",
	.class		= &omap44xx_ocmc_ram_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_OCMC_RAM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap44xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap44xx_ocp2scp_sysc,
};

/* ocp2scp_usb_phy */
static struct omap_hwmod omap44xx_ocp2scp_usb_phy_hwmod = {
	.name		= "ocp2scp_usb_phy",
	.class		= &omap44xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	/*
	 * ocp2scp_usb_phy_phy_48m is provided by the OMAP4 PRCM IP
	 * block as an "optional clock," and normally should never be
	 * specified as the main_clk for an OMAP IP block.  However it
	 * turns out that this clock is actually the main clock for
	 * the ocp2scp_usb_phy IP block:
	 * http://lists.infradead.org/pipermail/linux-arm-kernel/2012-September/119943.html
	 * So listing ocp2scp_usb_phy_phy_48m as a main_clk here seems
	 * to be the best workaround.
	 */
	.main_clk	= "ocp2scp_usb_phy_phy_48m",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USBPHYOCP2SCP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'prcm' class
 * power and reset manager (part of the prcm infrastructure) + clock manager 2
 * + clock manager 1 (in always on power domain) + local prm in mpu
 */

static struct omap_hwmod_class omap44xx_prcm_hwmod_class = {
	.name	= "prcm",
};

/* prcm_mpu */
static struct omap_hwmod omap44xx_prcm_mpu_hwmod = {
	.name		= "prcm_mpu",
	.class		= &omap44xx_prcm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core_aon */
static struct omap_hwmod omap44xx_cm_core_aon_hwmod = {
	.name		= "cm_core_aon",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core */
static struct omap_hwmod omap44xx_cm_core_hwmod = {
	.name		= "cm_core",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* prm */
static struct omap_hwmod_rst_info omap44xx_prm_resets[] = {
	{ .name = "rst_global_warm_sw", .rst_shift = 0 },
	{ .name = "rst_global_cold_sw", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_prm_hwmod = {
	.name		= "prm",
	.class		= &omap44xx_prcm_hwmod_class,
	.rst_lines	= omap44xx_prm_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_prm_resets),
};

/*
 * 'scrm' class
 * system clock and reset manager
 */

static struct omap_hwmod_class omap44xx_scrm_hwmod_class = {
	.name	= "scrm",
};

/* scrm */
static struct omap_hwmod omap44xx_scrm_hwmod = {
	.name		= "scrm",
	.class		= &omap44xx_scrm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/*
 * 'sl2if' class
 * shared level 2 memory interface
 */

static struct omap_hwmod_class omap44xx_sl2if_hwmod_class = {
	.name	= "sl2if",
};

/* sl2if */
static struct omap_hwmod omap44xx_sl2if_hwmod = {
	.name		= "sl2if",
	.class		= &omap44xx_sl2if_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_SL2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'slimbus' class
 * bidirectional, multi-drop, multi-channel two-line serial interface between
 * the device and external components
 */

static struct omap_hwmod_class_sysconfig omap44xx_slimbus_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_slimbus_hwmod_class = {
	.name	= "slimbus",
	.sysc	= &omap44xx_slimbus_sysc,
};

/* slimbus1 */
static struct omap_hwmod_opt_clk slimbus1_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus1_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus1_fclk_0" },
	{ .role = "fclk_2", .clk = "slimbus1_fclk_2" },
	{ .role = "slimbus_clk", .clk = "slimbus1_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus1_hwmod = {
	.name		= "slimbus1",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_SLIMBUS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_SLIMBUS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus1_opt_clks),
};

/* slimbus2 */
static struct omap_hwmod_opt_clk slimbus2_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus2_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus2_fclk_0" },
	{ .role = "slimbus_clk", .clk = "slimbus2_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus2_hwmod = {
	.name		= "slimbus2",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_SLIMBUS2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus2_opt_clks),
};

/*
 * 'smartreflex' class
 * smartreflex module (monitor silicon performance and outputs a measure of
 * performance error)
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_smartreflex = {
	.sidle_shift	= 24,
	.enwkup_shift	= 26,
};

static struct omap_hwmod_class_sysconfig omap44xx_smartreflex_sysc = {
	.sysc_offs	= 0x0038,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_smartreflex,
};

static struct omap_hwmod_class omap44xx_smartreflex_hwmod_class = {
	.name	= "smartreflex",
	.sysc	= &omap44xx_smartreflex_sysc,
	.rev	= 2,
};

/* smartreflex_core */
static struct omap_smartreflex_dev_attr smartreflex_core_dev_attr = {
	.sensor_voltdm_name   = "core",
};

static struct omap_hwmod omap44xx_smartreflex_core_hwmod = {
	.name		= "smartreflex_core",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",

	.main_clk	= "smartreflex_core_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_CORE_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_core_dev_attr,
};

/* smartreflex_iva */
static struct omap_smartreflex_dev_attr smartreflex_iva_dev_attr = {
	.sensor_voltdm_name	= "iva",
};

static struct omap_hwmod omap44xx_smartreflex_iva_hwmod = {
	.name		= "smartreflex_iva",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_iva_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_IVA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_iva_dev_attr,
};

/* smartreflex_mpu */
static struct omap_smartreflex_dev_attr smartreflex_mpu_dev_attr = {
	.sensor_voltdm_name	= "mpu",
};

static struct omap_hwmod omap44xx_smartreflex_mpu_hwmod = {
	.name		= "smartreflex_mpu",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_mpu_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_MPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_mpu_dev_attr,
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap44xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap44xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap44xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap44xx_spinlock_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_HW_SEM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap44xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap44xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_sysc,
};

/* always-on timers dev attribute */
static struct omap_timer_capability_dev_attr capability_alwon_dev_attr = {
	.timer_capability	= OMAP_TIMER_ALWON,
};

/* pwm timers dev attribute */
static struct omap_timer_capability_dev_attr capability_pwm_dev_attr = {
	.timer_capability	= OMAP_TIMER_HAS_PWM,
};

/* timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ,
};

/* pwm timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_pwm_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ | OMAP_TIMER_HAS_PWM,
};

/* timer1 */
static struct omap_hwmod omap44xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "dmt1_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_alwon_dev_attr,
};

/* timer2 */
static struct omap_hwmod omap44xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm2_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap44xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm3_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap44xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm4_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap44xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer6 */
static struct omap_hwmod omap44xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer7 */
static struct omap_hwmod omap44xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer8 */
static struct omap_hwmod omap44xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_pwm_dev_attr,
};

/* timer9 */
static struct omap_hwmod omap44xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm9_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer10 */
static struct omap_hwmod omap44xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm10_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer11 */
static struct omap_hwmod omap44xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm11_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap44xx_uart_sysc = {
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

static struct omap_hwmod_class omap44xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap44xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap44xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap44xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap44xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap44xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_fs' class
 * full-speed usb host controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_usb_host_fs = {
	.midle_shift	= 4,
	.sidle_shift	= 2,
	.srst_shift	= 1,
};

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_fs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0210,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_usb_host_fs,
};

static struct omap_hwmod_class omap44xx_usb_host_fs_hwmod_class = {
	.name	= "usb_host_fs",
	.sysc	= &omap44xx_usb_host_fs_sysc,
};

/* usb_host_fs */
static struct omap_hwmod omap44xx_usb_host_fs_hwmod = {
	.name		= "usb_host_fs",
	.class		= &omap44xx_usb_host_fs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_fs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_FS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap44xx_usb_host_hs_sysc,
};

/* usb_host_hs */
static struct omap_hwmod omap44xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap44xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_hs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},

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
};

/*
 * 'usb_otg_hs' class
 * high-speed on-the-go universal serial bus (usb_otg_hs) controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_otg_hs_sysc = {
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_otg_hs_hwmod_class = {
	.name	= "usb_otg_hs",
	.sysc	= &omap44xx_usb_otg_hs_sysc,
};

/* usb_otg_hs */
static struct omap_hwmod_opt_clk usb_otg_hs_opt_clks[] = {
	{ .role = "xclk", .clk = "usb_otg_hs_xclk" },
};

static struct omap_hwmod omap44xx_usb_otg_hs_hwmod = {
	.name		= "usb_otg_hs",
	.class		= &omap44xx_usb_otg_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "usb_otg_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_OTG_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_hs_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_hs_opt_clks),
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap44xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap44xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap44xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_tll_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_TLL_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap44xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap44xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
	.reset		= &omap2_wd_timer_reset,
};

/* wd_timer2 */
static struct omap_hwmod omap44xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_WDT2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_WDT2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* wd_timer3 */
static struct omap_hwmod omap44xx_wd_timer3_hwmod = {
	.name		= "wd_timer3",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_WDT3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_WDT3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};


/*
 * interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__dmm = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_SDMA,
};

/* mpu -> dmm */
static struct omap_hwmod_ocp_if omap44xx_mpu__dmm = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* iva -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_instr = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_l3_main_3__l3_instr = {
	.master		= &omap44xx_l3_main_3_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ocp_wp_noc -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_ocp_wp_noc__l3_instr = {
	.master		= &omap44xx_ocp_wp_noc_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dsp__l3_main_1 = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dss -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dss__l3_main_1 = {
	.master		= &omap44xx_dss_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_1 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc1 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc1__l3_main_1 = {
	.master		= &omap44xx_mmc1_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc2__l3_main_1 = {
	.master		= &omap44xx_mmc2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__l3_main_1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* debugss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_debugss__l3_main_2 = {
	.master		= &omap44xx_debugss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "dbgclk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dma_system -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_dma_system__l3_main_2 = {
	.master		= &omap44xx_dma_system_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* fdif -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_fdif__l3_main_2 = {
	.master		= &omap44xx_fdif_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* gpu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_gpu__l3_main_2 = {
	.master		= &omap44xx_gpu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* hsi -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_hsi__l3_main_2 = {
	.master		= &omap44xx_hsi_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ipu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_ipu__l3_main_2 = {
	.master		= &omap44xx_ipu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iss__l3_main_2 = {
	.master		= &omap44xx_iss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_main_2 = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_2 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_2 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_fs -> l3_main_2 */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_usb_host_fs__l3_main_2 = {
	.master		= &omap44xx_usb_host_fs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_host_hs__l3_main_2 = {
	.master		= &omap44xx_usb_host_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_otg_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_otg_hs__l3_main_2 = {
	.master		= &omap44xx_usb_otg_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_3 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_3 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_3 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* aess -> l4_abe */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_aess__l4_abe = {
	.master		= &omap44xx_aess_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_dsp__l4_abe = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_abe = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_mpu__l4_abe = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_cfg = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_cfg_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l4_per = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l4_per_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l4_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l4_wkup = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l4_wkup_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap44xx_mpu__mpu_private = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_mpu_private_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp_wp_noc */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp_wp_noc = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp_wp_noc_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_aess_addrs[] = {
	{
		.name		= "dmem",
		.pa_start	= 0x40180000,
		.pa_end		= 0x4018ffff
	},
	{
		.name		= "cmem",
		.pa_start	= 0x401a0000,
		.pa_end		= 0x401a1fff
	},
	{
		.name		= "smem",
		.pa_start	= 0x401c0000,
		.pa_end		= 0x401c5fff
	},
	{
		.name		= "pmem",
		.pa_start	= 0x401e0000,
		.pa_end		= 0x401e1fff
	},
	{
		.name		= "mpu",
		.pa_start	= 0x401f1000,
		.pa_end		= 0x401f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_aess_dma_addrs[] = {
	{
		.name		= "dmem_dma",
		.pa_start	= 0x49080000,
		.pa_end		= 0x4908ffff
	},
	{
		.name		= "cmem_dma",
		.pa_start	= 0x490a0000,
		.pa_end		= 0x490a1fff
	},
	{
		.name		= "smem_dma",
		.pa_start	= 0x490c0000,
		.pa_end		= 0x490c5fff
	},
	{
		.name		= "pmem_dma",
		.pa_start	= 0x490e0000,
		.pa_end		= 0x490e1fff
	},
	{
		.name		= "dma",
		.pa_start	= 0x490f1000,
		.pa_end		= 0x490f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess (dma) */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l3_main_2 -> c2c */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__c2c = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_c2c_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__counter_32k = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_counter_32k_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_core_addrs[] = {
	{
		.pa_start	= 0x4a002000,
		.pa_end		= 0x4a0027ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_core_addrs[] = {
	{
		.pa_start	= 0x4a100000,
		.pa_end		= 0x4a1007ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_pad_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_pad_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_pad_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_wkup_addrs[] = {
	{
		.pa_start	= 0x4a30c000,
		.pa_end		= 0x4a30c7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_wkup_addrs[] = {
	{
		.pa_start	= 0x4a31e000,
		.pa_end		= 0x4a31e7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_pad_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_pad_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_pad_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_instr -> debugss */
static struct omap_hwmod_ocp_if omap44xx_l3_instr__debugss = {
	.master		= &omap44xx_l3_instr_hwmod,
	.slave		= &omap44xx_debugss_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dma_system = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dma_system_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__dmic = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_dmic_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> iva */
static struct omap_hwmod_ocp_if omap44xx_dsp__iva = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* dsp -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_dsp__sl2if = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dsp_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dma_addrs[] = {
	{
		.pa_start	= 0x58000000,
		.pa_end		= 0x5800007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_addrs[] = {
	{
		.pa_start	= 0x48040000,
		.pa_end		= 0x4804007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_dma_addrs[] = {
	{
		.pa_start	= 0x58001000,
		.pa_end		= 0x58001fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dispc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dispc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48041000,
		.pa_end		= 0x48041fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dispc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dispc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_dma_addrs[] = {
	{
		.pa_start	= 0x58004000,
		.pa_end		= 0x580041ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_addrs[] = {
	{
		.pa_start	= 0x48044000,
		.pa_end		= 0x480441ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_dma_addrs[] = {
	{
		.pa_start	= 0x58005000,
		.pa_end		= 0x580051ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi2 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi2_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_addrs[] = {
	{
		.pa_start	= 0x48045000,
		.pa_end		= 0x480451ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi2_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_dma_addrs[] = {
	{
		.pa_start	= 0x58006000,
		.pa_end		= 0x58006fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_hdmi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_hdmi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_addrs[] = {
	{
		.pa_start	= 0x48046000,
		.pa_end		= 0x48046fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_hdmi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_hdmi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_dma_addrs[] = {
	{
		.pa_start	= 0x58002000,
		.pa_end		= 0x580020ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_rfbi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_rfbi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48042000,
		.pa_end		= 0x480420ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_rfbi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_rfbi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_dma_addrs[] = {
	{
		.pa_start	= 0x58003000,
		.pa_end		= 0x580030ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_venc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_venc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48043000,
		.pa_end		= 0x480430ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_venc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_venc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_elm_addrs[] = {
	{
		.pa_start	= 0x48078000,
		.pa_end		= 0x48078fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> elm */
static struct omap_hwmod_ocp_if omap44xx_l4_per__elm = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_elm_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_elm_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_fdif_addrs[] = {
	{
		.pa_start	= 0x4a10a000,
		.pa_end		= 0x4a10a1ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> fdif */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__fdif = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_fdif_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_fdif_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__gpio1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_gpio1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio6 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio6_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> gpmc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpmc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpmc_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_gpu_addrs[] = {
	{
		.pa_start	= 0x56000000,
		.pa_end		= 0x5600ffff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> gpu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_gpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hdq1w_addrs[] = {
	{
		.pa_start	= 0x480b2000,
		.pa_end		= 0x480b201f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> hdq1w */
static struct omap_hwmod_ocp_if omap44xx_l4_per__hdq1w = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_hdq1w_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hdq1w_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hsi_addrs[] = {
	{
		.pa_start	= 0x4a058000,
		.pa_end		= 0x4a05bfff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> hsi */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__hsi = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_hsi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hsi_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ipu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_iss_addrs[] = {
	{
		.pa_start	= 0x52000000,
		.pa_end		= 0x520000ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> iss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_iss_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_iva__sl2if = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_IVA,
};

/* l3_main_2 -> iva */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iva = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__kbd = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_kbd_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mailbox = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mailbox_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_addrs[] = {
	{
		.pa_start	= 0x40128000,
		.pa_end		= 0x401283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_dma_addrs[] = {
	{
		.pa_start	= 0x49028000,
		.pa_end		= 0x490283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp1_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp2 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp2_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp3_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcbsp4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcbsp4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcbsp4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcpdm = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcpdm_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ocmc_ram */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ocmc_ram = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ocmc_ram_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp_usb_phy */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp2scp_usb_phy = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp2scp_usb_phy_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu_private -> prcm_mpu */
static struct omap_hwmod_ocp_if omap44xx_mpu_private__prcm_mpu = {
	.master		= &omap44xx_mpu_private_hwmod,
	.slave		= &omap44xx_prcm_mpu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> cm_core_aon */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__cm_core_aon = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_cm_core_aon_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> cm_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__cm_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_cm_core_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> prm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__prm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_prm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> scrm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__scrm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_scrm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l3_main_2__sl2if = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_addrs[] = {
	{
		.pa_start	= 0x4012c000,
		.pa_end		= 0x4012c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_dma_addrs[] = {
	{
		.pa_start	= 0x4902c000,
		.pa_end		= 0x4902c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus2_addrs[] = {
	{
		.pa_start	= 0x48076000,
		.pa_end		= 0x480763ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> slimbus2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__slimbus2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_slimbus2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_slimbus2_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_core_addrs[] = {
	{
		.pa_start	= 0x4a0dd000,
		.pa_end		= 0x4a0dd03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_iva_addrs[] = {
	{
		.pa_start	= 0x4a0db000,
		.pa_end		= 0x4a0db03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_iva */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_iva = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_iva_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_iva_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_mpu_addrs[] = {
	{
		.pa_start	= 0x4a0d9000,
		.pa_end		= 0x4a0d903f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_mpu */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_mpu = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_mpu_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_mpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_spinlock_addrs[] = {
	{
		.pa_start	= 0x4a0f6000,
		.pa_end		= 0x4a0f6fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__spinlock = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_spinlock_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_spinlock_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__timer1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_timer1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer5 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer5_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer6 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer6_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer7 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer7_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer8 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer8_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer9 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer9_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer10 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer10_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer11 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer11_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_fs */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_cfg__usb_host_fs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_fs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_host_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_otg_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_otg_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_tll_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_tll_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__wd_timer2 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_wd_timer2_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_addrs[] = {
	{
		.pa_start	= 0x40130000,
		.pa_end		= 0x4013007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_dma_addrs[] = {
	{
		.pa_start	= 0x49030000,
		.pa_end		= 0x4903007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif2 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap44xx_hwmod_ocp_ifs[] __initdata = {
	&omap44xx_l3_main_1__dmm,
	&omap44xx_mpu__dmm,
	&omap44xx_iva__l3_instr,
	&omap44xx_l3_main_3__l3_instr,
	&omap44xx_ocp_wp_noc__l3_instr,
	&omap44xx_dsp__l3_main_1,
	&omap44xx_dss__l3_main_1,
	&omap44xx_l3_main_2__l3_main_1,
	&omap44xx_l4_cfg__l3_main_1,
	&omap44xx_mmc1__l3_main_1,
	&omap44xx_mmc2__l3_main_1,
	&omap44xx_mpu__l3_main_1,
	&omap44xx_debugss__l3_main_2,
	&omap44xx_dma_system__l3_main_2,
	&omap44xx_fdif__l3_main_2,
	&omap44xx_gpu__l3_main_2,
	&omap44xx_hsi__l3_main_2,
	&omap44xx_ipu__l3_main_2,
	&omap44xx_iss__l3_main_2,
	&omap44xx_iva__l3_main_2,
	&omap44xx_l3_main_1__l3_main_2,
	&omap44xx_l4_cfg__l3_main_2,
	/* &omap44xx_usb_host_fs__l3_main_2, */
	&omap44xx_usb_host_hs__l3_main_2,
	&omap44xx_usb_otg_hs__l3_main_2,
	&omap44xx_l3_main_1__l3_main_3,
	&omap44xx_l3_main_2__l3_main_3,
	&omap44xx_l4_cfg__l3_main_3,
	&omap44xx_aess__l4_abe,
	&omap44xx_dsp__l4_abe,
	&omap44xx_l3_main_1__l4_abe,
	&omap44xx_mpu__l4_abe,
	&omap44xx_l3_main_1__l4_cfg,
	&omap44xx_l3_main_2__l4_per,
	&omap44xx_l4_cfg__l4_wkup,
	&omap44xx_mpu__mpu_private,
	&omap44xx_l4_cfg__ocp_wp_noc,
	&omap44xx_l4_abe__aess,
	&omap44xx_l4_abe__aess_dma,
	&omap44xx_l3_main_2__c2c,
	&omap44xx_l4_wkup__counter_32k,
	&omap44xx_l4_cfg__ctrl_module_core,
	&omap44xx_l4_cfg__ctrl_module_pad_core,
	&omap44xx_l4_wkup__ctrl_module_wkup,
	&omap44xx_l4_wkup__ctrl_module_pad_wkup,
	&omap44xx_l3_instr__debugss,
	&omap44xx_l4_cfg__dma_system,
	&omap44xx_l4_abe__dmic,
	&omap44xx_dsp__iva,
	/* &omap44xx_dsp__sl2if, */
	&omap44xx_l4_cfg__dsp,
	&omap44xx_l3_main_2__dss,
	&omap44xx_l4_per__dss,
	&omap44xx_l3_main_2__dss_dispc,
	&omap44xx_l4_per__dss_dispc,
	&omap44xx_l3_main_2__dss_dsi1,
	&omap44xx_l4_per__dss_dsi1,
	&omap44xx_l3_main_2__dss_dsi2,
	&omap44xx_l4_per__dss_dsi2,
	&omap44xx_l3_main_2__dss_hdmi,
	&omap44xx_l4_per__dss_hdmi,
	&omap44xx_l3_main_2__dss_rfbi,
	&omap44xx_l4_per__dss_rfbi,
	&omap44xx_l3_main_2__dss_venc,
	&omap44xx_l4_per__dss_venc,
	&omap44xx_l4_per__elm,
	&omap44xx_l4_cfg__fdif,
	&omap44xx_l4_wkup__gpio1,
	&omap44xx_l4_per__gpio2,
	&omap44xx_l4_per__gpio3,
	&omap44xx_l4_per__gpio4,
	&omap44xx_l4_per__gpio5,
	&omap44xx_l4_per__gpio6,
	&omap44xx_l3_main_2__gpmc,
	&omap44xx_l3_main_2__gpu,
	&omap44xx_l4_per__hdq1w,
	&omap44xx_l4_cfg__hsi,
	&omap44xx_l4_per__i2c1,
	&omap44xx_l4_per__i2c2,
	&omap44xx_l4_per__i2c3,
	&omap44xx_l4_per__i2c4,
	&omap44xx_l3_main_2__ipu,
	&omap44xx_l3_main_2__iss,
	/* &omap44xx_iva__sl2if, */
	&omap44xx_l3_main_2__iva,
	&omap44xx_l4_wkup__kbd,
	&omap44xx_l4_cfg__mailbox,
	&omap44xx_l4_abe__mcasp,
	&omap44xx_l4_abe__mcasp_dma,
	&omap44xx_l4_abe__mcbsp1,
	&omap44xx_l4_abe__mcbsp2,
	&omap44xx_l4_abe__mcbsp3,
	&omap44xx_l4_per__mcbsp4,
	&omap44xx_l4_abe__mcpdm,
	&omap44xx_l4_per__mcspi1,
	&omap44xx_l4_per__mcspi2,
	&omap44xx_l4_per__mcspi3,
	&omap44xx_l4_per__mcspi4,
	&omap44xx_l4_per__mmc1,
	&omap44xx_l4_per__mmc2,
	&omap44xx_l4_per__mmc3,
	&omap44xx_l4_per__mmc4,
	&omap44xx_l4_per__mmc5,
	&omap44xx_l3_main_2__mmu_ipu,
	&omap44xx_l4_cfg__mmu_dsp,
	&omap44xx_l3_main_2__ocmc_ram,
	&omap44xx_l4_cfg__ocp2scp_usb_phy,
	&omap44xx_mpu_private__prcm_mpu,
	&omap44xx_l4_wkup__cm_core_aon,
	&omap44xx_l4_cfg__cm_core,
	&omap44xx_l4_wkup__prm,
	&omap44xx_l4_wkup__scrm,
	/* &omap44xx_l3_main_2__sl2if, */
	&omap44xx_l4_abe__slimbus1,
	&omap44xx_l4_abe__slimbus1_dma,
	&omap44xx_l4_per__slimbus2,
	&omap44xx_l4_cfg__smartreflex_core,
	&omap44xx_l4_cfg__smartreflex_iva,
	&omap44xx_l4_cfg__smartreflex_mpu,
	&omap44xx_l4_cfg__spinlock,
	&omap44xx_l4_wkup__timer1,
	&omap44xx_l4_per__timer2,
	&omap44xx_l4_per__timer3,
	&omap44xx_l4_per__timer4,
	&omap44xx_l4_abe__timer5,
	&omap44xx_l4_abe__timer6,
	&omap44xx_l4_abe__timer7,
	&omap44xx_l4_abe__timer8,
	&omap44xx_l4_per__timer9,
	&omap44xx_l4_per__timer10,
	&omap44xx_l4_per__timer11,
	&omap44xx_l4_per__uart1,
	&omap44xx_l4_per__uart2,
	&omap44xx_l4_per__uart3,
	&omap44xx_l4_per__uart4,
	/* &omap44xx_l4_cfg__usb_host_fs, */
	&omap44xx_l4_cfg__usb_host_hs,
	&omap44xx_l4_cfg__usb_otg_hs,
	&omap44xx_l4_cfg__usb_tll_hs,
	&omap44xx_l4_wkup__wd_timer2,
	&omap44xx_l4_abe__wd_timer3,
	&omap44xx_l4_abe__wd_timer3_dma,
	&omap44xx_mpu__emif1,
	&omap44xx_mpu__emif2,
	NULL,
};

int __init omap44xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap44xx_hwmod_ocp_ifs);
}

static struct omap_hwmod omap44xx_dss_hdmi_hwmod = {
	.name		= "dss_hdmi",
	.class		= &omap44xx_hdmi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	/*
	 * HDMI audio requires to use no-idle mode. Hence,
	 * set idle mode by software.
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
	.mpu_irqs	= omap44xx_dss_hdmi_irqs,
	.xlate_irq	= omap4_xlate_irq,
	.sdma_reqs	= omap44xx_dss_hdmi_sdma_reqs,
	.main_clk	= "dss_48mhz_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_hdmi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_hdmi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'rfbi' class
 * remote frame buffer interface
 */

static struct omap_hwmod_class_sysconfig omap44xx_rfbi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_rfbi_hwmod_class = {
	.name	= "rfbi",
	.sysc	= &omap44xx_rfbi_sysc,
};

/* dss_rfbi */
static struct omap_hwmod_dma_info omap44xx_dss_rfbi_sdma_reqs[] = {
	{ .dma_req = 13 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod_opt_clk dss_rfbi_opt_clks[] = {
	{ .role = "ick", .clk = "l3_div_ck" },
};

static struct omap_hwmod omap44xx_dss_rfbi_hwmod = {
	.name		= "dss_rfbi",
	.class		= &omap44xx_rfbi_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.sdma_reqs	= omap44xx_dss_rfbi_sdma_reqs,
	.main_clk	= "dss_dss_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'venc' class
 * video encoder
 */

static struct omap_hwmod_class omap44xx_venc_hwmod_class = {
	.name	= "venc",
};

/* dss_venc */
static struct omap_hwmod omap44xx_dss_venc_hwmod = {
	.name		= "dss_venc",
	.class		= &omap44xx_venc_hwmod_class,
	.clkdm_name	= "l3_dss_clkdm",
	.main_clk	= "dss_tv_clk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_DSS_DSS_CONTEXT_OFFSET,
		},
	},
	.parent_hwmod	= &omap44xx_dss_hwmod,
};

/*
 * 'elm' class
 * bch error location module
 */

static struct omap_hwmod_class_sysconfig omap44xx_elm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_elm_hwmod_class = {
	.name	= "elm",
	.sysc	= &omap44xx_elm_sysc,
};

/* elm */
static struct omap_hwmod omap44xx_elm_hwmod = {
	.name		= "elm",
	.class		= &omap44xx_elm_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_ELM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'emif' class
 * external memory interface no1
 */

static struct omap_hwmod_class_sysconfig omap44xx_emif_sysc = {
	.rev_offs	= 0x0000,
};

static struct omap_hwmod_class omap44xx_emif_hwmod_class = {
	.name	= "emif",
	.sysc	= &omap44xx_emif_sysc,
};

/* emif1 */
static struct omap_hwmod omap44xx_emif1_hwmod = {
	.name		= "emif1",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/* emif2 */
static struct omap_hwmod omap44xx_emif2_hwmod = {
	.name		= "emif2",
	.class		= &omap44xx_emif_hwmod_class,
	.clkdm_name	= "l3_emif_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "ddrphy_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MEMIF_EMIF_2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'fdif' class
 * face detection hw accelerator module
 */

static struct omap_hwmod_class_sysconfig omap44xx_fdif_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * FDIF needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_fdif_hwmod_class = {
	.name	= "fdif",
	.sysc	= &omap44xx_fdif_sysc,
};

/* fdif */
static struct omap_hwmod omap44xx_fdif_hwmod = {
	.name		= "fdif",
	.class		= &omap44xx_fdif_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "fdif_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_FDIF_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'gpio' class
 * general purpose io module
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpio_sysc = {
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

static struct omap_hwmod_class omap44xx_gpio_hwmod_class = {
	.name	= "gpio",
	.sysc	= &omap44xx_gpio_sysc,
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

static struct omap_hwmod omap44xx_gpio1_hwmod = {
	.name		= "gpio1",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "l4_wkup_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_GPIO1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_GPIO1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio2_hwmod = {
	.name		= "gpio2",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio3_hwmod = {
	.name		= "gpio3",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO3_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio4_hwmod = {
	.name		= "gpio4",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO4_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio5_hwmod = {
	.name		= "gpio5",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO5_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_gpio6_hwmod = {
	.name		= "gpio6",
	.class		= &omap44xx_gpio_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.main_clk	= "l4_div_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_GPIO6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.dev_attr	= &gpio_dev_attr,
};

/*
 * 'gpmc' class
 * general purpose memory controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpmc_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_gpmc_hwmod_class = {
	.name	= "gpmc",
	.sysc	= &omap44xx_gpmc_sysc,
};

/* gpmc */
static struct omap_hwmod omap44xx_gpmc_hwmod = {
	.name		= "gpmc",
	.class		= &omap44xx_gpmc_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	/*
	 * XXX HWMOD_INIT_NO_RESET should not be needed for this IP
	 * block.  It is not being added due to any known bugs with
	 * resetting the GPMC IP block, but rather because any timings
	 * set by the bootloader are not being correctly programmed by
	 * the kernel from the board file or DT data.
	 * HWMOD_INIT_NO_RESET should be removed ASAP.
	 */
	.flags		= HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET,
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_GPMC_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'gpu' class
 * 2d/3d graphics accelerator
 */

static struct omap_hwmod_class_sysconfig omap44xx_gpu_sysc = {
	.rev_offs	= 0x1fc00,
	.sysc_offs	= 0x1fc10,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_gpu_hwmod_class = {
	.name	= "gpu",
	.sysc	= &omap44xx_gpu_sysc,
};

/* gpu */
static struct omap_hwmod omap44xx_gpu_hwmod = {
	.name		= "gpu",
	.class		= &omap44xx_gpu_hwmod_class,
	.clkdm_name	= "l3_gfx_clkdm",
	.main_clk	= "sgx_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_GFX_GFX_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hdq1w' class
 * hdq / 1-wire serial interface controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_hdq1w_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0014,
	.syss_offs	= 0x0018,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hdq1w_hwmod_class = {
	.name	= "hdq1w",
	.sysc	= &omap44xx_hdq1w_sysc,
};

/* hdq1w */
static struct omap_hwmod omap44xx_hdq1w_hwmod = {
	.name		= "hdq1w",
	.class		= &omap44xx_hdq1w_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_INIT_NO_RESET, /* XXX temporary */
	.main_clk	= "func_12m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_HDQ1W_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'hsi' class
 * mipi high-speed synchronous serial interface (multichannel and full-duplex
 * serial if)
 */

static struct omap_hwmod_class_sysconfig omap44xx_hsi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_hsi_hwmod_class = {
	.name	= "hsi",
	.sysc	= &omap44xx_hsi_sysc,
};

/* hsi */
static struct omap_hwmod omap44xx_hsi_hwmod = {
	.name		= "hsi",
	.class		= &omap44xx_hsi_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "hsi_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_HSI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'i2c' class
 * multimaster high-speed i2c controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_i2c_sysc = {
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

static struct omap_hwmod_class omap44xx_i2c_hwmod_class = {
	.name	= "i2c",
	.sysc	= &omap44xx_i2c_sysc,
	.rev	= OMAP_I2C_IP_VERSION_2,
	.reset	= &omap_i2c_reset,
};

static struct omap_i2c_dev_attr i2c_dev_attr = {
	.flags	= OMAP_I2C_FLAG_BUS_SHIFT_NONE,
};

/* i2c1 */
static struct omap_hwmod omap44xx_i2c1_hwmod = {
	.name		= "i2c1",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c2 */
static struct omap_hwmod omap44xx_i2c2_hwmod = {
	.name		= "i2c2",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c3 */
static struct omap_hwmod omap44xx_i2c3_hwmod = {
	.name		= "i2c3",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/* i2c4 */
static struct omap_hwmod omap44xx_i2c4_hwmod = {
	.name		= "i2c4",
	.class		= &omap44xx_i2c_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "func_96m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_I2C4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &i2c_dev_attr,
};

/*
 * 'ipu' class
 * imaging processor unit
 */

static struct omap_hwmod_class omap44xx_ipu_hwmod_class = {
	.name	= "ipu",
};

/* ipu */
static struct omap_hwmod_rst_info omap44xx_ipu_resets[] = {
	{ .name = "cpu0", .rst_shift = 0 },
	{ .name = "cpu1", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_ipu_hwmod = {
	.name		= "ipu",
	.class		= &omap44xx_ipu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'iss' class
 * external images sensor pixel data processor
 */

static struct omap_hwmod_class_sysconfig omap44xx_iss_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	/*
	 * ISS needs 100 OCP clk cycles delay after a softreset before
	 * accessing sysconfig again.
	 * The lowest frequency at the moment for L3 bus is 100 MHz, so
	 * 1usec delay is needed. Add an x2 margin to be safe (2 usecs).
	 *
	 * TODO: Indicate errata when available.
	 */
	.srst_udelay	= 2,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_iss_hwmod_class = {
	.name	= "iss",
	.sysc	= &omap44xx_iss_sysc,
};

/* iss */
static struct omap_hwmod_opt_clk iss_opt_clks[] = {
	{ .role = "ctrlclk", .clk = "iss_ctrlclk" },
};

static struct omap_hwmod omap44xx_iss_hwmod = {
	.name		= "iss",
	.class		= &omap44xx_iss_hwmod_class,
	.clkdm_name	= "iss_clkdm",
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_CAM_ISS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= iss_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(iss_opt_clks),
};

/*
 * 'iva' class
 * multi-standard video encoder/decoder hardware accelerator
 */

static struct omap_hwmod_class omap44xx_iva_hwmod_class = {
	.name	= "iva",
};

/* iva */
static struct omap_hwmod_rst_info omap44xx_iva_resets[] = {
	{ .name = "seq0", .rst_shift = 0 },
	{ .name = "seq1", .rst_shift = 1 },
	{ .name = "logic", .rst_shift = 2 },
};

static struct omap_hwmod omap44xx_iva_hwmod = {
	.name		= "iva",
	.class		= &omap44xx_iva_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.rst_lines	= omap44xx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_iva_resets),
	.main_clk	= "dpll_iva_m5x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_IVAHD_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_IVAHD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'kbd' class
 * keyboard controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_kbd_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_kbd_hwmod_class = {
	.name	= "kbd",
	.sysc	= &omap44xx_kbd_sysc,
};

/* kbd */
static struct omap_hwmod omap44xx_kbd_hwmod = {
	.name		= "kbd",
	.class		= &omap44xx_kbd_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_KEYBOARD_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_KEYBOARD_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors using a
 * queued mailbox-interrupt mechanism.
 */

static struct omap_hwmod_class_sysconfig omap44xx_mailbox_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mailbox_hwmod_class = {
	.name	= "mailbox",
	.sysc	= &omap44xx_mailbox_sysc,
};

/* mailbox */
static struct omap_hwmod omap44xx_mailbox_hwmod = {
	.name		= "mailbox",
	.class		= &omap44xx_mailbox_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_MAILBOX_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'mcasp' class
 * multi-channel audio serial port controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_mcasp = {
	.sidle_shift	= 0,
};

static struct omap_hwmod_class_sysconfig omap44xx_mcasp_sysc = {
	.sysc_offs	= 0x0004,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_mcasp,
};

static struct omap_hwmod_class omap44xx_mcasp_hwmod_class = {
	.name	= "mcasp",
	.sysc	= &omap44xx_mcasp_sysc,
};

/* mcasp */
static struct omap_hwmod omap44xx_mcasp_hwmod = {
	.name		= "mcasp",
	.class		= &omap44xx_mcasp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcasp_abe_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCASP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCASP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcbsp_sysc = {
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mcbsp_hwmod_class = {
	.name	= "mcbsp",
	.sysc	= &omap44xx_mcbsp_sysc,
	.rev	= MCBSP_CONFIG_TYPE4,
};

/* mcbsp1 */
static struct omap_hwmod_opt_clk mcbsp1_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp1_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp1_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP1_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp2_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP2_CONTEXT_OFFSET,
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

static struct omap_hwmod omap44xx_mcbsp3_hwmod = {
	.name		= "mcbsp3",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "func_mcbsp3_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_MCBSP3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_MCBSP3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp3_opt_clks),
};

/* mcbsp4 */
static struct omap_hwmod_opt_clk mcbsp4_opt_clks[] = {
	{ .role = "pad_fck", .clk = "pad_clks_ck" },
	{ .role = "prcm_fck", .clk = "mcbsp4_sync_mux_ck" },
};

static struct omap_hwmod omap44xx_mcbsp4_hwmod = {
	.name		= "mcbsp4",
	.class		= &omap44xx_mcbsp_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "per_mcbsp4_gfclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCBSP4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= mcbsp4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp4_opt_clks),
};

/*
 * 'mcpdm' class
 * multi channel pdm controller (proprietary interface with phoenix power
 * ic)
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcpdm_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcpdm_hwmod_class = {
	.name	= "mcpdm",
	.sysc	= &omap44xx_mcpdm_sysc,
};

/* mcpdm */
static struct omap_hwmod omap44xx_mcpdm_hwmod = {
	.name		= "mcpdm",
	.class		= &omap44xx_mcpdm_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	/*
	 * It's suspected that the McPDM requires an off-chip main
	 * functional clock, controlled via I2C.  This IP block is
	 * currently reset very early during boot, before I2C is
	 * available, so it doesn't seem that we have any choice in
	 * the kernel other than to avoid resetting it.
	 *
	 * Also, McPDM needs to be configured to NO_IDLE mode when it
	 * is in used otherwise vital clocks will be gated which
	 * results 'slow motion' audio playback.
	 */
	.flags		= HWMOD_EXT_OPT_MAIN_CLK | HWMOD_SWSUP_SIDLE,
	.main_clk	= "pad_clks_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_PDM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_PDM_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mcspi' class
 * multichannel serial port interface (mcspi) / master/slave synchronous serial
 * bus
 */

static struct omap_hwmod_class_sysconfig omap44xx_mcspi_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_mcspi_hwmod_class = {
	.name	= "mcspi",
	.sysc	= &omap44xx_mcspi_sysc,
	.rev	= OMAP4_MCSPI_REV,
};

/* mcspi1 */
static struct omap_hwmod_dma_info omap44xx_mcspi1_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 34 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 35 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 36 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 37 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx2", .dma_req = 38 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx2", .dma_req = 39 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx3", .dma_req = 40 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx3", .dma_req = 41 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi1 dev_attr */
static struct omap2_mcspi_dev_attr mcspi1_dev_attr = {
	.num_chipselect	= 4,
};

static struct omap_hwmod omap44xx_mcspi1_hwmod = {
	.name		= "mcspi1",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi1_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi1_dev_attr,
};

/* mcspi2 */
static struct omap_hwmod_dma_info omap44xx_mcspi2_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 42 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 43 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 44 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 45 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi2 dev_attr */
static struct omap2_mcspi_dev_attr mcspi2_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi2_hwmod = {
	.name		= "mcspi2",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi2_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi2_dev_attr,
};

/* mcspi3 */
static struct omap_hwmod_dma_info omap44xx_mcspi3_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 14 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 15 + OMAP44XX_DMA_REQ_START },
	{ .name = "tx1", .dma_req = 22 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx1", .dma_req = 23 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi3 dev_attr */
static struct omap2_mcspi_dev_attr mcspi3_dev_attr = {
	.num_chipselect	= 2,
};

static struct omap_hwmod omap44xx_mcspi3_hwmod = {
	.name		= "mcspi3",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi3_dev_attr,
};

/* mcspi4 */
static struct omap_hwmod_dma_info omap44xx_mcspi4_sdma_reqs[] = {
	{ .name = "tx0", .dma_req = 69 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx0", .dma_req = 70 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mcspi4 dev_attr */
static struct omap2_mcspi_dev_attr mcspi4_dev_attr = {
	.num_chipselect	= 1,
};

static struct omap_hwmod omap44xx_mcspi4_hwmod = {
	.name		= "mcspi4",
	.class		= &omap44xx_mcspi_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mcspi4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MCSPI4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mcspi4_dev_attr,
};

/*
 * 'mmc' class
 * multimedia card high-speed/sd/sdio (mmc/sd/sdio) host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_mmc_sysc = {
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

static struct omap_hwmod_class omap44xx_mmc_hwmod_class = {
	.name	= "mmc",
	.sysc	= &omap44xx_mmc_sysc,
};

/* mmc1 */
static struct omap_hwmod_dma_info omap44xx_mmc1_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 60 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 61 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

/* mmc1 dev_attr */
static struct omap_hsmmc_dev_attr mmc1_dev_attr = {
	.flags	= OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
};

static struct omap_hwmod omap44xx_mmc1_hwmod = {
	.name		= "mmc1",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc1_sdma_reqs,
	.main_clk	= "hsmmc1_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &mmc1_dev_attr,
};

/* mmc2 */
static struct omap_hwmod_dma_info omap44xx_mmc2_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 46 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 47 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc2_hwmod = {
	.name		= "mmc2",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.sdma_reqs	= omap44xx_mmc2_sdma_reqs,
	.main_clk	= "hsmmc2_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_MMC2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc3 */
static struct omap_hwmod_dma_info omap44xx_mmc3_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 76 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 77 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc3_hwmod = {
	.name		= "mmc3",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc3_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc4 */
static struct omap_hwmod_dma_info omap44xx_mmc4_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 56 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 57 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc4_hwmod = {
	.name		= "mmc4",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc4_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* mmc5 */
static struct omap_hwmod_dma_info omap44xx_mmc5_sdma_reqs[] = {
	{ .name = "tx", .dma_req = 58 + OMAP44XX_DMA_REQ_START },
	{ .name = "rx", .dma_req = 59 + OMAP44XX_DMA_REQ_START },
	{ .dma_req = -1 }
};

static struct omap_hwmod omap44xx_mmc5_hwmod = {
	.name		= "mmc5",
	.class		= &omap44xx_mmc_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.sdma_reqs	= omap44xx_mmc5_sdma_reqs,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_MMCSD5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'mmu' class
 * The memory management unit performs virtual to physical address translation
 * for its requestors.
 */

static struct omap_hwmod_class_sysconfig mmu_sysc = {
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_mmu_hwmod_class = {
	.name = "mmu",
	.sysc = &mmu_sysc,
};

/* mmu ipu */

static struct omap_mmu_dev_attr mmu_ipu_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_ipu_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 2 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_ipu_addrs[] = {
	{
		.pa_start	= 0x55082000,
		.pa_end		= 0x550820ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l3_main_2 -> mmu_ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__mmu_ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_mmu_ipu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_mmu_ipu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_ipu_hwmod = {
	.name		= "mmu_ipu",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "ducati_clkdm",
	.rst_lines	= omap44xx_mmu_ipu_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_ipu_resets),
	.main_clk	= "ducati_clk_mux_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_DUCATI_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_DUCATI_DUCATI_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_ipu_dev_attr,
};

/* mmu dsp */

static struct omap_mmu_dev_attr mmu_dsp_dev_attr = {
	.nr_tlb_entries = 32,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod;
static struct omap_hwmod_rst_info omap44xx_mmu_dsp_resets[] = {
	{ .name = "mmu_cache", .rst_shift = 1 },
};

static struct omap_hwmod_addr_space omap44xx_mmu_dsp_addrs[] = {
	{
		.pa_start	= 0x4a066000,
		.pa_end		= 0x4a0660ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mmu_dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mmu_dsp_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_mmu_dsp_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod omap44xx_mmu_dsp_hwmod = {
	.name		= "mmu_dsp",
	.class		= &omap44xx_mmu_hwmod_class,
	.clkdm_name	= "tesla_clkdm",
	.rst_lines	= omap44xx_mmu_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_mmu_dsp_resets),
	.main_clk	= "dpll_iva_m4x2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_TESLA_TESLA_CLKCTRL_OFFSET,
			.rstctrl_offs = OMAP4_RM_TESLA_RSTCTRL_OFFSET,
			.context_offs = OMAP4_RM_TESLA_TESLA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.dev_attr	= &mmu_dsp_dev_attr,
};

/*
 * 'mpu' class
 * mpu sub-system
 */

static struct omap_hwmod_class omap44xx_mpu_hwmod_class = {
	.name	= "mpu",
};

/* mpu */
static struct omap_hwmod omap44xx_mpu_hwmod = {
	.name		= "mpu",
	.class		= &omap44xx_mpu_hwmod_class,
	.clkdm_name	= "mpuss_clkdm",
	.flags		= HWMOD_INIT_NO_IDLE,
	.main_clk	= "dpll_mpu_m2_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_MPU_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_MPU_MPU_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocmc_ram' class
 * top-level core on-chip ram
 */

static struct omap_hwmod_class omap44xx_ocmc_ram_hwmod_class = {
	.name	= "ocmc_ram",
};

/* ocmc_ram */
static struct omap_hwmod omap44xx_ocmc_ram_hwmod = {
	.name		= "ocmc_ram",
	.class		= &omap44xx_ocmc_ram_hwmod_class,
	.clkdm_name	= "l3_2_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3_2_OCMC_RAM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'ocp2scp' class
 * bridge to transform ocp interface protocol to scp (serial control port)
 * protocol
 */

static struct omap_hwmod_class_sysconfig omap44xx_ocp2scp_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_ocp2scp_hwmod_class = {
	.name	= "ocp2scp",
	.sysc	= &omap44xx_ocp2scp_sysc,
};

/* ocp2scp_usb_phy */
static struct omap_hwmod omap44xx_ocp2scp_usb_phy_hwmod = {
	.name		= "ocp2scp_usb_phy",
	.class		= &omap44xx_ocp2scp_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	/*
	 * ocp2scp_usb_phy_phy_48m is provided by the OMAP4 PRCM IP
	 * block as an "optional clock," and normally should never be
	 * specified as the main_clk for an OMAP IP block.  However it
	 * turns out that this clock is actually the main clock for
	 * the ocp2scp_usb_phy IP block:
	 * http://lists.infradead.org/pipermail/linux-arm-kernel/2012-September/119943.html
	 * So listing ocp2scp_usb_phy_phy_48m as a main_clk here seems
	 * to be the best workaround.
	 */
	.main_clk	= "ocp2scp_usb_phy_phy_48m",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USBPHYOCP2SCP_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'prcm' class
 * power and reset manager (part of the prcm infrastructure) + clock manager 2
 * + clock manager 1 (in always on power domain) + local prm in mpu
 */

static struct omap_hwmod_class omap44xx_prcm_hwmod_class = {
	.name	= "prcm",
};

/* prcm_mpu */
static struct omap_hwmod omap44xx_prcm_mpu_hwmod = {
	.name		= "prcm_mpu",
	.class		= &omap44xx_prcm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core_aon */
static struct omap_hwmod omap44xx_cm_core_aon_hwmod = {
	.name		= "cm_core_aon",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* cm_core */
static struct omap_hwmod omap44xx_cm_core_hwmod = {
	.name		= "cm_core",
	.class		= &omap44xx_prcm_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/* prm */
static struct omap_hwmod_rst_info omap44xx_prm_resets[] = {
	{ .name = "rst_global_warm_sw", .rst_shift = 0 },
	{ .name = "rst_global_cold_sw", .rst_shift = 1 },
};

static struct omap_hwmod omap44xx_prm_hwmod = {
	.name		= "prm",
	.class		= &omap44xx_prcm_hwmod_class,
	.rst_lines	= omap44xx_prm_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap44xx_prm_resets),
};

/*
 * 'scrm' class
 * system clock and reset manager
 */

static struct omap_hwmod_class omap44xx_scrm_hwmod_class = {
	.name	= "scrm",
};

/* scrm */
static struct omap_hwmod omap44xx_scrm_hwmod = {
	.name		= "scrm",
	.class		= &omap44xx_scrm_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.prcm = {
		.omap4 = {
			.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT,
		},
	},
};

/*
 * 'sl2if' class
 * shared level 2 memory interface
 */

static struct omap_hwmod_class omap44xx_sl2if_hwmod_class = {
	.name	= "sl2if",
};

/* sl2if */
static struct omap_hwmod omap44xx_sl2if_hwmod = {
	.name		= "sl2if",
	.class		= &omap44xx_sl2if_hwmod_class,
	.clkdm_name	= "ivahd_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_IVAHD_SL2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'slimbus' class
 * bidirectional, multi-drop, multi-channel two-line serial interface between
 * the device and external components
 */

static struct omap_hwmod_class_sysconfig omap44xx_slimbus_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_RESET_STATUS | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_slimbus_hwmod_class = {
	.name	= "slimbus",
	.sysc	= &omap44xx_slimbus_sysc,
};

/* slimbus1 */
static struct omap_hwmod_opt_clk slimbus1_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus1_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus1_fclk_0" },
	{ .role = "fclk_2", .clk = "slimbus1_fclk_2" },
	{ .role = "slimbus_clk", .clk = "slimbus1_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus1_hwmod = {
	.name		= "slimbus1",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_SLIMBUS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_SLIMBUS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus1_opt_clks),
};

/* slimbus2 */
static struct omap_hwmod_opt_clk slimbus2_opt_clks[] = {
	{ .role = "fclk_1", .clk = "slimbus2_fclk_1" },
	{ .role = "fclk_0", .clk = "slimbus2_fclk_0" },
	{ .role = "slimbus_clk", .clk = "slimbus2_slimbus_clk" },
};

static struct omap_hwmod omap44xx_slimbus2_hwmod = {
	.name		= "slimbus2",
	.class		= &omap44xx_slimbus_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_SLIMBUS2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.opt_clks	= slimbus2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(slimbus2_opt_clks),
};

/*
 * 'smartreflex' class
 * smartreflex module (monitor silicon performance and outputs a measure of
 * performance error)
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_smartreflex = {
	.sidle_shift	= 24,
	.enwkup_shift	= 26,
};

static struct omap_hwmod_class_sysconfig omap44xx_smartreflex_sysc = {
	.sysc_offs	= 0x0038,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_smartreflex,
};

static struct omap_hwmod_class omap44xx_smartreflex_hwmod_class = {
	.name	= "smartreflex",
	.sysc	= &omap44xx_smartreflex_sysc,
	.rev	= 2,
};

/* smartreflex_core */
static struct omap_smartreflex_dev_attr smartreflex_core_dev_attr = {
	.sensor_voltdm_name   = "core",
};

static struct omap_hwmod omap44xx_smartreflex_core_hwmod = {
	.name		= "smartreflex_core",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",

	.main_clk	= "smartreflex_core_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_CORE_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_core_dev_attr,
};

/* smartreflex_iva */
static struct omap_smartreflex_dev_attr smartreflex_iva_dev_attr = {
	.sensor_voltdm_name	= "iva",
};

static struct omap_hwmod omap44xx_smartreflex_iva_hwmod = {
	.name		= "smartreflex_iva",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_iva_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_IVA_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_iva_dev_attr,
};

/* smartreflex_mpu */
static struct omap_smartreflex_dev_attr smartreflex_mpu_dev_attr = {
	.sensor_voltdm_name	= "mpu",
};

static struct omap_hwmod omap44xx_smartreflex_mpu_hwmod = {
	.name		= "smartreflex_mpu",
	.class		= &omap44xx_smartreflex_hwmod_class,
	.clkdm_name	= "l4_ao_clkdm",
	.main_clk	= "smartreflex_mpu_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ALWON_SR_MPU_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &smartreflex_mpu_dev_attr,
};

/*
 * 'spinlock' class
 * spinlock provides hardware assistance for synchronizing the processes
 * running on multiple processors
 */

static struct omap_hwmod_class_sysconfig omap44xx_spinlock_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_spinlock_hwmod_class = {
	.name	= "spinlock",
	.sysc	= &omap44xx_spinlock_sysc,
};

/* spinlock */
static struct omap_hwmod omap44xx_spinlock_hwmod = {
	.name		= "spinlock",
	.class		= &omap44xx_spinlock_hwmod_class,
	.clkdm_name	= "l4_cfg_clkdm",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4CFG_HW_SEM_CONTEXT_OFFSET,
		},
	},
};

/*
 * 'timer' class
 * general purpose timer module with accurate 1ms tick
 * This class contains several variants: ['timer_1ms', 'timer']
 */

static struct omap_hwmod_class_sysconfig omap44xx_timer_1ms_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_EMUFREE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.clockact	= CLOCKACT_TEST_ICLK,
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_timer_1ms_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_1ms_sysc,
};

static struct omap_hwmod_class_sysconfig omap44xx_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_RESET_STATUS |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_timer_hwmod_class = {
	.name	= "timer",
	.sysc	= &omap44xx_timer_sysc,
};

/* always-on timers dev attribute */
static struct omap_timer_capability_dev_attr capability_alwon_dev_attr = {
	.timer_capability	= OMAP_TIMER_ALWON,
};

/* pwm timers dev attribute */
static struct omap_timer_capability_dev_attr capability_pwm_dev_attr = {
	.timer_capability	= OMAP_TIMER_HAS_PWM,
};

/* timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ,
};

/* pwm timers with DSP interrupt dev attribute */
static struct omap_timer_capability_dev_attr capability_dsp_pwm_dev_attr = {
	.timer_capability       = OMAP_TIMER_HAS_DSP_IRQ | OMAP_TIMER_HAS_PWM,
};

/* timer1 */
static struct omap_hwmod omap44xx_timer1_hwmod = {
	.name		= "timer1",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "dmt1_clk_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_TIMER1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_TIMER1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_alwon_dev_attr,
};

/* timer2 */
static struct omap_hwmod omap44xx_timer2_hwmod = {
	.name		= "timer2",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm2_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer3 */
static struct omap_hwmod omap44xx_timer3_hwmod = {
	.name		= "timer3",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm3_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer4 */
static struct omap_hwmod omap44xx_timer4_hwmod = {
	.name		= "timer4",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm4_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* timer5 */
static struct omap_hwmod omap44xx_timer5_hwmod = {
	.name		= "timer5",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer5_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER5_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER5_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer6 */
static struct omap_hwmod omap44xx_timer6_hwmod = {
	.name		= "timer6",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer6_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER6_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER6_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer7 */
static struct omap_hwmod omap44xx_timer7_hwmod = {
	.name		= "timer7",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer7_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER7_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER7_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_dev_attr,
};

/* timer8 */
static struct omap_hwmod omap44xx_timer8_hwmod = {
	.name		= "timer8",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "timer8_sync_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_TIMER8_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_TIMER8_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_dsp_pwm_dev_attr,
};

/* timer9 */
static struct omap_hwmod omap44xx_timer9_hwmod = {
	.name		= "timer9",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm9_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER9_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer10 */
static struct omap_hwmod omap44xx_timer10_hwmod = {
	.name		= "timer10",
	.class		= &omap44xx_timer_1ms_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
	.main_clk	= "cm2_dm10_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER10_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/* timer11 */
static struct omap_hwmod omap44xx_timer11_hwmod = {
	.name		= "timer11",
	.class		= &omap44xx_timer_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.main_clk	= "cm2_dm11_mux",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_DMTIMER11_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
	.dev_attr	= &capability_pwm_dev_attr,
};

/*
 * 'uart' class
 * universal asynchronous receiver/transmitter (uart)
 */

static struct omap_hwmod_class_sysconfig omap44xx_uart_sysc = {
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

static struct omap_hwmod_class omap44xx_uart_hwmod_class = {
	.name	= "uart",
	.sysc	= &omap44xx_uart_sysc,
};

/* uart1 */
static struct omap_hwmod omap44xx_uart1_hwmod = {
	.name		= "uart1",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART1_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart2 */
static struct omap_hwmod omap44xx_uart2_hwmod = {
	.name		= "uart2",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart3 */
static struct omap_hwmod omap44xx_uart3_hwmod = {
	.name		= "uart3",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* uart4 */
static struct omap_hwmod omap44xx_uart4_hwmod = {
	.name		= "uart4",
	.class		= &omap44xx_uart_hwmod_class,
	.clkdm_name	= "l4_per_clkdm",
	.flags		= DEBUG_OMAP4UART4_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.main_clk	= "func_48m_fclk",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L4PER_UART4_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_fs' class
 * full-speed usb host controller
 */

/* The IP is not compliant to type1 / type2 scheme */
static struct omap_hwmod_sysc_fields omap_hwmod_sysc_type_usb_host_fs = {
	.midle_shift	= 4,
	.sidle_shift	= 2,
	.srst_shift	= 1,
};

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_fs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0210,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type_usb_host_fs,
};

static struct omap_hwmod_class omap44xx_usb_host_fs_hwmod_class = {
	.name	= "usb_host_fs",
	.sysc	= &omap44xx_usb_host_fs_sysc,
};

/* usb_host_fs */
static struct omap_hwmod omap44xx_usb_host_fs_hwmod = {
	.name		= "usb_host_fs",
	.class		= &omap44xx_usb_host_fs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_fs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_FS_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_host_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART | MSTANDBY_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type2,
};

static struct omap_hwmod_class omap44xx_usb_host_hs_hwmod_class = {
	.name	= "usb_host_hs",
	.sysc	= &omap44xx_usb_host_hs_sysc,
};

/* usb_host_hs */
static struct omap_hwmod omap44xx_usb_host_hs_hwmod = {
	.name		= "usb_host_hs",
	.class		= &omap44xx_usb_host_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_host_hs_fck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_HOST_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},

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
};

/*
 * 'usb_otg_hs' class
 * high-speed on-the-go universal serial bus (usb_otg_hs) controller
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_otg_hs_sysc = {
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_MIDLEMODE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP | MSTANDBY_FORCE | MSTANDBY_NO |
			   MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_otg_hs_hwmod_class = {
	.name	= "usb_otg_hs",
	.sysc	= &omap44xx_usb_otg_hs_sysc,
};

/* usb_otg_hs */
static struct omap_hwmod_opt_clk usb_otg_hs_opt_clks[] = {
	{ .role = "xclk", .clk = "usb_otg_hs_xclk" },
};

static struct omap_hwmod omap44xx_usb_otg_hs_hwmod = {
	.name		= "usb_otg_hs",
	.class		= &omap44xx_usb_otg_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
	.main_clk	= "usb_otg_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_OTG_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
	.opt_clks	= usb_otg_hs_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(usb_otg_hs_opt_clks),
};

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */

static struct omap_hwmod_class_sysconfig omap44xx_usb_tll_hs_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_usb_tll_hs_hwmod_class = {
	.name	= "usb_tll_hs",
	.sysc	= &omap44xx_usb_tll_hs_sysc,
};

static struct omap_hwmod omap44xx_usb_tll_hs_hwmod = {
	.name		= "usb_tll_hs",
	.class		= &omap44xx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "l3_init_clkdm",
	.main_clk	= "usb_tll_hs_ick",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_L3INIT_USB_TLL_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_HWCTRL,
		},
	},
};

/*
 * 'wd_timer' class
 * 32-bit watchdog upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

static struct omap_hwmod_class_sysconfig omap44xx_wd_timer_sysc = {
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   SIDLE_SMART_WKUP),
	.sysc_fields	= &omap_hwmod_sysc_type1,
};

static struct omap_hwmod_class omap44xx_wd_timer_hwmod_class = {
	.name		= "wd_timer",
	.sysc		= &omap44xx_wd_timer_sysc,
	.pre_shutdown	= &omap2_wd_timer_disable,
	.reset		= &omap2_wd_timer_reset,
};

/* wd_timer2 */
static struct omap_hwmod omap44xx_wd_timer2_hwmod = {
	.name		= "wd_timer2",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "l4_wkup_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM_WKUP_WDT2_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_WKUP_WDT2_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};

/* wd_timer3 */
static struct omap_hwmod omap44xx_wd_timer3_hwmod = {
	.name		= "wd_timer3",
	.class		= &omap44xx_wd_timer_hwmod_class,
	.clkdm_name	= "abe_clkdm",
	.main_clk	= "sys_32k_ck",
	.prcm = {
		.omap4 = {
			.clkctrl_offs = OMAP4_CM1_ABE_WDT3_CLKCTRL_OFFSET,
			.context_offs = OMAP4_RM_ABE_WDT3_CONTEXT_OFFSET,
			.modulemode   = MODULEMODE_SWCTRL,
		},
	},
};


/*
 * interfaces
 */

/* l3_main_1 -> dmm */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__dmm = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_SDMA,
};

/* mpu -> dmm */
static struct omap_hwmod_ocp_if omap44xx_mpu__dmm = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_dmm_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* iva -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_instr = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_3 -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_l3_main_3__l3_instr = {
	.master		= &omap44xx_l3_main_3_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ocp_wp_noc -> l3_instr */
static struct omap_hwmod_ocp_if omap44xx_ocp_wp_noc__l3_instr = {
	.master		= &omap44xx_ocp_wp_noc_hwmod,
	.slave		= &omap44xx_l3_instr_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dsp__l3_main_1 = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dss -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_dss__l3_main_1 = {
	.master		= &omap44xx_dss_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_1 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc1 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc1__l3_main_1 = {
	.master		= &omap44xx_mmc1_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mmc2 -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mmc2__l3_main_1 = {
	.master		= &omap44xx_mmc2_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l3_main_1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__l3_main_1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l3_main_1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* debugss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_debugss__l3_main_2 = {
	.master		= &omap44xx_debugss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "dbgclk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dma_system -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_dma_system__l3_main_2 = {
	.master		= &omap44xx_dma_system_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* fdif -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_fdif__l3_main_2 = {
	.master		= &omap44xx_fdif_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* gpu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_gpu__l3_main_2 = {
	.master		= &omap44xx_gpu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* hsi -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_hsi__l3_main_2 = {
	.master		= &omap44xx_hsi_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* ipu -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_ipu__l3_main_2 = {
	.master		= &omap44xx_ipu_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iss -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iss__l3_main_2 = {
	.master		= &omap44xx_iss_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_iva__l3_main_2 = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_2 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_cfg -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_2 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_fs -> l3_main_2 */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_usb_host_fs__l3_main_2 = {
	.master		= &omap44xx_usb_host_fs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_host_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_host_hs__l3_main_2 = {
	.master		= &omap44xx_usb_host_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* usb_otg_hs -> l3_main_2 */
static struct omap_hwmod_ocp_if omap44xx_usb_otg_hs__l3_main_2 = {
	.master		= &omap44xx_usb_otg_hs_hwmod,
	.slave		= &omap44xx_l3_main_2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l3_main_3 = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l3_main_2 -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l3_main_3 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l3_main_3 */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l3_main_3 = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l3_main_3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* aess -> l4_abe */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_aess__l4_abe = {
	.master		= &omap44xx_aess_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_dsp__l4_abe = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_abe = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> l4_abe */
static struct omap_hwmod_ocp_if omap44xx_mpu__l4_abe = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_l4_abe_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_1 -> l4_cfg */
static struct omap_hwmod_ocp_if omap44xx_l3_main_1__l4_cfg = {
	.master		= &omap44xx_l3_main_1_hwmod,
	.slave		= &omap44xx_l4_cfg_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> l4_per */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__l4_per = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_l4_per_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> l4_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__l4_wkup = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_l4_wkup_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> mpu_private */
static struct omap_hwmod_ocp_if omap44xx_mpu__mpu_private = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_mpu_private_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp_wp_noc */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp_wp_noc = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp_wp_noc_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_aess_addrs[] = {
	{
		.name		= "dmem",
		.pa_start	= 0x40180000,
		.pa_end		= 0x4018ffff
	},
	{
		.name		= "cmem",
		.pa_start	= 0x401a0000,
		.pa_end		= 0x401a1fff
	},
	{
		.name		= "smem",
		.pa_start	= 0x401c0000,
		.pa_end		= 0x401c5fff
	},
	{
		.name		= "pmem",
		.pa_start	= 0x401e0000,
		.pa_end		= 0x401e1fff
	},
	{
		.name		= "mpu",
		.pa_start	= 0x401f1000,
		.pa_end		= 0x401f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_aess_dma_addrs[] = {
	{
		.name		= "dmem_dma",
		.pa_start	= 0x49080000,
		.pa_end		= 0x4908ffff
	},
	{
		.name		= "cmem_dma",
		.pa_start	= 0x490a0000,
		.pa_end		= 0x490a1fff
	},
	{
		.name		= "smem_dma",
		.pa_start	= 0x490c0000,
		.pa_end		= 0x490c5fff
	},
	{
		.name		= "pmem_dma",
		.pa_start	= 0x490e0000,
		.pa_end		= 0x490e1fff
	},
	{
		.name		= "dma",
		.pa_start	= 0x490f1000,
		.pa_end		= 0x490f13ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> aess (dma) */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_abe__aess_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_aess_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_aess_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l3_main_2 -> c2c */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__c2c = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_c2c_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> counter_32k */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__counter_32k = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_counter_32k_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_core_addrs[] = {
	{
		.pa_start	= 0x4a002000,
		.pa_end		= 0x4a0027ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_core_addrs[] = {
	{
		.pa_start	= 0x4a100000,
		.pa_end		= 0x4a1007ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> ctrl_module_pad_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ctrl_module_pad_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_ctrl_module_pad_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_wkup_addrs[] = {
	{
		.pa_start	= 0x4a30c000,
		.pa_end		= 0x4a30c7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_ctrl_module_pad_wkup_addrs[] = {
	{
		.pa_start	= 0x4a31e000,
		.pa_end		= 0x4a31e7ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_wkup -> ctrl_module_pad_wkup */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__ctrl_module_pad_wkup = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_ctrl_module_pad_wkup_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.addr		= omap44xx_ctrl_module_pad_wkup_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_instr -> debugss */
static struct omap_hwmod_ocp_if omap44xx_l3_instr__debugss = {
	.master		= &omap44xx_l3_instr_hwmod,
	.slave		= &omap44xx_debugss_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dma_system_addrs[] = {
	{
		.pa_start	= 0x4a056000,
		.pa_end		= 0x4a056fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> dma_system */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dma_system = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dma_system_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dma_system_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> dmic */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__dmic = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_dmic_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* dsp -> iva */
static struct omap_hwmod_ocp_if omap44xx_dsp__iva = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* dsp -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_dsp__sl2if = {
	.master		= &omap44xx_dsp_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_DSP,
};

/* l4_cfg -> dsp */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__dsp = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_dsp_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dma_addrs[] = {
	{
		.pa_start	= 0x58000000,
		.pa_end		= 0x5800007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_addrs[] = {
	{
		.pa_start	= 0x48040000,
		.pa_end		= 0x4804007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_dma_addrs[] = {
	{
		.pa_start	= 0x58001000,
		.pa_end		= 0x58001fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dispc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dispc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48041000,
		.pa_end		= 0x48041fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dispc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dispc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dispc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dispc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_dma_addrs[] = {
	{
		.pa_start	= 0x58004000,
		.pa_end		= 0x580041ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi1 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi1_addrs[] = {
	{
		.pa_start	= 0x48044000,
		.pa_end		= 0x480441ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi1_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_dma_addrs[] = {
	{
		.pa_start	= 0x58005000,
		.pa_end		= 0x580051ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_dsi2 = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_dsi2_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_dsi2_addrs[] = {
	{
		.pa_start	= 0x48045000,
		.pa_end		= 0x480451ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_dsi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_dsi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_dsi2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_dsi2_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_dma_addrs[] = {
	{
		.pa_start	= 0x58006000,
		.pa_end		= 0x58006fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_hdmi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_hdmi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_hdmi_addrs[] = {
	{
		.pa_start	= 0x48046000,
		.pa_end		= 0x48046fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_hdmi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_hdmi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_hdmi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_hdmi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_dma_addrs[] = {
	{
		.pa_start	= 0x58002000,
		.pa_end		= 0x580020ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_rfbi = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_rfbi_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48042000,
		.pa_end		= 0x480420ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_rfbi */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_rfbi = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_rfbi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_rfbi_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_dma_addrs[] = {
	{
		.pa_start	= 0x58003000,
		.pa_end		= 0x580030ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__dss_venc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_dss_venc_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48043000,
		.pa_end		= 0x480430ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> dss_venc */
static struct omap_hwmod_ocp_if omap44xx_l4_per__dss_venc = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_dss_venc_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_dss_venc_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_elm_addrs[] = {
	{
		.pa_start	= 0x48078000,
		.pa_end		= 0x48078fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> elm */
static struct omap_hwmod_ocp_if omap44xx_l4_per__elm = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_elm_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_elm_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_fdif_addrs[] = {
	{
		.pa_start	= 0x4a10a000,
		.pa_end		= 0x4a10a1ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> fdif */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__fdif = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_fdif_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_fdif_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> gpio1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__gpio1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_gpio1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> gpio6 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__gpio6 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_gpio6_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> gpmc */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpmc = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpmc_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_gpu_addrs[] = {
	{
		.pa_start	= 0x56000000,
		.pa_end		= 0x5600ffff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> gpu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__gpu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_gpu_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_gpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hdq1w_addrs[] = {
	{
		.pa_start	= 0x480b2000,
		.pa_end		= 0x480b201f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> hdq1w */
static struct omap_hwmod_ocp_if omap44xx_l4_per__hdq1w = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_hdq1w_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hdq1w_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_hsi_addrs[] = {
	{
		.pa_start	= 0x4a058000,
		.pa_end		= 0x4a05bfff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> hsi */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__hsi = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_hsi_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_hsi_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> i2c4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__i2c4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_i2c4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ipu */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ipu = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ipu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_iss_addrs[] = {
	{
		.pa_start	= 0x52000000,
		.pa_end		= 0x520000ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l3_main_2 -> iss */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iss = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iss_hwmod,
	.clk		= "l3_div_ck",
	.addr		= omap44xx_iss_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* iva -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_iva__sl2if = {
	.master		= &omap44xx_iva_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "dpll_iva_m5x2_ck",
	.user		= OCP_USER_IVA,
};

/* l3_main_2 -> iva */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__iva = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_iva_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU,
};

/* l4_wkup -> kbd */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__kbd = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_kbd_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> mailbox */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__mailbox = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_mailbox_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_addrs[] = {
	{
		.pa_start	= 0x40128000,
		.pa_end		= 0x401283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_mcasp_dma_addrs[] = {
	{
		.pa_start	= 0x49028000,
		.pa_end		= 0x490283ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> mcasp (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcasp_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcasp_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_mcasp_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* l4_abe -> mcbsp1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp1_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp2 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp2 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp2_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcbsp3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcbsp3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcbsp3_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcbsp4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcbsp4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcbsp4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> mcpdm */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__mcpdm = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_mcpdm_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mcspi4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mcspi4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mcspi4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> mmc5 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__mmc5 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_mmc5_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> ocmc_ram */
static struct omap_hwmod_ocp_if omap44xx_l3_main_2__ocmc_ram = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_ocmc_ram_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> ocp2scp_usb_phy */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__ocp2scp_usb_phy = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_ocp2scp_usb_phy_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu_private -> prcm_mpu */
static struct omap_hwmod_ocp_if omap44xx_mpu_private__prcm_mpu = {
	.master		= &omap44xx_mpu_private_hwmod,
	.slave		= &omap44xx_prcm_mpu_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> cm_core_aon */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__cm_core_aon = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_cm_core_aon_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> cm_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__cm_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_cm_core_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> prm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__prm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_prm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> scrm */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__scrm = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_scrm_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l3_main_2 -> sl2if */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l3_main_2__sl2if = {
	.master		= &omap44xx_l3_main_2_hwmod,
	.slave		= &omap44xx_sl2if_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_addrs[] = {
	{
		.pa_start	= 0x4012c000,
		.pa_end		= 0x4012c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_slimbus1_dma_addrs[] = {
	{
		.pa_start	= 0x4902c000,
		.pa_end		= 0x4902c3ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> slimbus1 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__slimbus1_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_slimbus1_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_slimbus1_dma_addrs,
	.user		= OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_slimbus2_addrs[] = {
	{
		.pa_start	= 0x48076000,
		.pa_end		= 0x480763ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_per -> slimbus2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__slimbus2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_slimbus2_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_slimbus2_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_core_addrs[] = {
	{
		.pa_start	= 0x4a0dd000,
		.pa_end		= 0x4a0dd03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_core */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_core = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_core_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_core_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_iva_addrs[] = {
	{
		.pa_start	= 0x4a0db000,
		.pa_end		= 0x4a0db03f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_iva */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_iva = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_iva_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_iva_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_smartreflex_mpu_addrs[] = {
	{
		.pa_start	= 0x4a0d9000,
		.pa_end		= 0x4a0d903f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> smartreflex_mpu */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__smartreflex_mpu = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_smartreflex_mpu_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_smartreflex_mpu_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_spinlock_addrs[] = {
	{
		.pa_start	= 0x4a0f6000,
		.pa_end		= 0x4a0f6fff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_cfg -> spinlock */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__spinlock = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_spinlock_hwmod,
	.clk		= "l4_div_ck",
	.addr		= omap44xx_spinlock_addrs,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> timer1 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__timer1 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_timer1_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer5 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer5 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer5_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer6 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer6 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer6_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer7 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer7 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer7_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_abe -> timer8 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__timer8 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_timer8_hwmod,
	.clk		= "ocp_abe_iclk",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer9 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer9 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer9_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer10 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer10 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer10_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> timer11 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__timer11 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_timer11_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart1 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart1 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart1_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart2 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart2 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart2_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart3 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart3 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart3_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_per -> uart4 */
static struct omap_hwmod_ocp_if omap44xx_l4_per__uart4 = {
	.master		= &omap44xx_l4_per_hwmod,
	.slave		= &omap44xx_uart4_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_fs */
static struct omap_hwmod_ocp_if __maybe_unused omap44xx_l4_cfg__usb_host_fs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_fs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_host_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_host_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_host_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_otg_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_otg_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_otg_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_cfg -> usb_tll_hs */
static struct omap_hwmod_ocp_if omap44xx_l4_cfg__usb_tll_hs = {
	.master		= &omap44xx_l4_cfg_hwmod,
	.slave		= &omap44xx_usb_tll_hs_hwmod,
	.clk		= "l4_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* l4_wkup -> wd_timer2 */
static struct omap_hwmod_ocp_if omap44xx_l4_wkup__wd_timer2 = {
	.master		= &omap44xx_l4_wkup_hwmod,
	.slave		= &omap44xx_wd_timer2_hwmod,
	.clk		= "l4_wkup_clk_mux_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_addrs[] = {
	{
		.pa_start	= 0x40130000,
		.pa_end		= 0x4013007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3 = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_addrs,
	.user		= OCP_USER_MPU,
};

static struct omap_hwmod_addr_space omap44xx_wd_timer3_dma_addrs[] = {
	{
		.pa_start	= 0x49030000,
		.pa_end		= 0x4903007f,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

/* l4_abe -> wd_timer3 (dma) */
static struct omap_hwmod_ocp_if omap44xx_l4_abe__wd_timer3_dma = {
	.master		= &omap44xx_l4_abe_hwmod,
	.slave		= &omap44xx_wd_timer3_hwmod,
	.clk		= "ocp_abe_iclk",
	.addr		= omap44xx_wd_timer3_dma_addrs,
	.user		= OCP_USER_SDMA,
};

/* mpu -> emif1 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif1 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif1_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

/* mpu -> emif2 */
static struct omap_hwmod_ocp_if omap44xx_mpu__emif2 = {
	.master		= &omap44xx_mpu_hwmod,
	.slave		= &omap44xx_emif2_hwmod,
	.clk		= "l3_div_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
};

static struct omap_hwmod_ocp_if *omap44xx_hwmod_ocp_ifs[] __initdata = {
	&omap44xx_l3_main_1__dmm,
	&omap44xx_mpu__dmm,
	&omap44xx_iva__l3_instr,
	&omap44xx_l3_main_3__l3_instr,
	&omap44xx_ocp_wp_noc__l3_instr,
	&omap44xx_dsp__l3_main_1,
	&omap44xx_dss__l3_main_1,
	&omap44xx_l3_main_2__l3_main_1,
	&omap44xx_l4_cfg__l3_main_1,
	&omap44xx_mmc1__l3_main_1,
	&omap44xx_mmc2__l3_main_1,
	&omap44xx_mpu__l3_main_1,
	&omap44xx_debugss__l3_main_2,
	&omap44xx_dma_system__l3_main_2,
	&omap44xx_fdif__l3_main_2,
	&omap44xx_gpu__l3_main_2,
	&omap44xx_hsi__l3_main_2,
	&omap44xx_ipu__l3_main_2,
	&omap44xx_iss__l3_main_2,
	&omap44xx_iva__l3_main_2,
	&omap44xx_l3_main_1__l3_main_2,
	&omap44xx_l4_cfg__l3_main_2,
	/* &omap44xx_usb_host_fs__l3_main_2, */
	&omap44xx_usb_host_hs__l3_main_2,
	&omap44xx_usb_otg_hs__l3_main_2,
	&omap44xx_l3_main_1__l3_main_3,
	&omap44xx_l3_main_2__l3_main_3,
	&omap44xx_l4_cfg__l3_main_3,
	&omap44xx_aess__l4_abe,
	&omap44xx_dsp__l4_abe,
	&omap44xx_l3_main_1__l4_abe,
	&omap44xx_mpu__l4_abe,
	&omap44xx_l3_main_1__l4_cfg,
	&omap44xx_l3_main_2__l4_per,
	&omap44xx_l4_cfg__l4_wkup,
	&omap44xx_mpu__mpu_private,
	&omap44xx_l4_cfg__ocp_wp_noc,
	&omap44xx_l4_abe__aess,
	&omap44xx_l4_abe__aess_dma,
	&omap44xx_l3_main_2__c2c,
	&omap44xx_l4_wkup__counter_32k,
	&omap44xx_l4_cfg__ctrl_module_core,
	&omap44xx_l4_cfg__ctrl_module_pad_core,
	&omap44xx_l4_wkup__ctrl_module_wkup,
	&omap44xx_l4_wkup__ctrl_module_pad_wkup,
	&omap44xx_l3_instr__debugss,
	&omap44xx_l4_cfg__dma_system,
	&omap44xx_l4_abe__dmic,
	&omap44xx_dsp__iva,
	/* &omap44xx_dsp__sl2if, */
	&omap44xx_l4_cfg__dsp,
	&omap44xx_l3_main_2__dss,
	&omap44xx_l4_per__dss,
	&omap44xx_l3_main_2__dss_dispc,
	&omap44xx_l4_per__dss_dispc,
	&omap44xx_l3_main_2__dss_dsi1,
	&omap44xx_l4_per__dss_dsi1,
	&omap44xx_l3_main_2__dss_dsi2,
	&omap44xx_l4_per__dss_dsi2,
	&omap44xx_l3_main_2__dss_hdmi,
	&omap44xx_l4_per__dss_hdmi,
	&omap44xx_l3_main_2__dss_rfbi,
	&omap44xx_l4_per__dss_rfbi,
	&omap44xx_l3_main_2__dss_venc,
	&omap44xx_l4_per__dss_venc,
	&omap44xx_l4_per__elm,
	&omap44xx_l4_cfg__fdif,
	&omap44xx_l4_wkup__gpio1,
	&omap44xx_l4_per__gpio2,
	&omap44xx_l4_per__gpio3,
	&omap44xx_l4_per__gpio4,
	&omap44xx_l4_per__gpio5,
	&omap44xx_l4_per__gpio6,
	&omap44xx_l3_main_2__gpmc,
	&omap44xx_l3_main_2__gpu,
	&omap44xx_l4_per__hdq1w,
	&omap44xx_l4_cfg__hsi,
	&omap44xx_l4_per__i2c1,
	&omap44xx_l4_per__i2c2,
	&omap44xx_l4_per__i2c3,
	&omap44xx_l4_per__i2c4,
	&omap44xx_l3_main_2__ipu,
	&omap44xx_l3_main_2__iss,
	/* &omap44xx_iva__sl2if, */
	&omap44xx_l3_main_2__iva,
	&omap44xx_l4_wkup__kbd,
	&omap44xx_l4_cfg__mailbox,
	&omap44xx_l4_abe__mcasp,
	&omap44xx_l4_abe__mcasp_dma,
	&omap44xx_l4_abe__mcbsp1,
	&omap44xx_l4_abe__mcbsp2,
	&omap44xx_l4_abe__mcbsp3,
	&omap44xx_l4_per__mcbsp4,
	&omap44xx_l4_abe__mcpdm,
	&omap44xx_l4_per__mcspi1,
	&omap44xx_l4_per__mcspi2,
	&omap44xx_l4_per__mcspi3,
	&omap44xx_l4_per__mcspi4,
	&omap44xx_l4_per__mmc1,
	&omap44xx_l4_per__mmc2,
	&omap44xx_l4_per__mmc3,
	&omap44xx_l4_per__mmc4,
	&omap44xx_l4_per__mmc5,
	&omap44xx_l3_main_2__mmu_ipu,
	&omap44xx_l4_cfg__mmu_dsp,
	&omap44xx_l3_main_2__ocmc_ram,
	&omap44xx_l4_cfg__ocp2scp_usb_phy,
	&omap44xx_mpu_private__prcm_mpu,
	&omap44xx_l4_wkup__cm_core_aon,
	&omap44xx_l4_cfg__cm_core,
	&omap44xx_l4_wkup__prm,
	&omap44xx_l4_wkup__scrm,
	/* &omap44xx_l3_main_2__sl2if, */
	&omap44xx_l4_abe__slimbus1,
	&omap44xx_l4_abe__slimbus1_dma,
	&omap44xx_l4_per__slimbus2,
	&omap44xx_l4_cfg__smartreflex_core,
	&omap44xx_l4_cfg__smartreflex_iva,
	&omap44xx_l4_cfg__smartreflex_mpu,
	&omap44xx_l4_cfg__spinlock,
	&omap44xx_l4_wkup__timer1,
	&omap44xx_l4_per__timer2,
	&omap44xx_l4_per__timer3,
	&omap44xx_l4_per__timer4,
	&omap44xx_l4_abe__timer5,
	&omap44xx_l4_abe__timer6,
	&omap44xx_l4_abe__timer7,
	&omap44xx_l4_abe__timer8,
	&omap44xx_l4_per__timer9,
	&omap44xx_l4_per__timer10,
	&omap44xx_l4_per__timer11,
	&omap44xx_l4_per__uart1,
	&omap44xx_l4_per__uart2,
	&omap44xx_l4_per__uart3,
	&omap44xx_l4_per__uart4,
	/* &omap44xx_l4_cfg__usb_host_fs, */
	&omap44xx_l4_cfg__usb_host_hs,
	&omap44xx_l4_cfg__usb_otg_hs,
	&omap44xx_l4_cfg__usb_tll_hs,
	&omap44xx_l4_wkup__wd_timer2,
	&omap44xx_l4_abe__wd_timer3,
	&omap44xx_l4_abe__wd_timer3_dma,
	&omap44xx_mpu__emif1,
	&omap44xx_mpu__emif2,
	NULL,
};

int __init omap44xx_hwmod_init(void)
{
	omap_hwmod_init();
	return omap_hwmod_register_links(omap44xx_hwmod_ocp_ifs);
}
