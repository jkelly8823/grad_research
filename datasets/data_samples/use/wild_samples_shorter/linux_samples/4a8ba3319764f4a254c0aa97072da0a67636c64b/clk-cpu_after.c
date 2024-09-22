{
	const struct rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	unsigned long alt_prate, alt_div;
	unsigned long flags;

	alt_prate = clk_get_rate(cpuclk->alt_parent);

	spin_lock_irqsave(cpuclk->lock, flags);

	/*
	 * If the old parent clock speed is less than the clock speed
	 * of the alternate parent, then it should be ensured that at no point
			cpuclk->reg_base + reg_data->core_reg);
	}

	spin_unlock_irqrestore(cpuclk->lock, flags);
	return 0;
}

static int rockchip_cpuclk_post_rate_change(struct rockchip_cpuclk *cpuclk,
{
	const struct rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	const struct rockchip_cpuclk_rate_table *rate;
	unsigned long flags;

	rate = rockchip_get_cpuclk_settings(cpuclk, ndata->new_rate);
	if (!rate) {
		pr_err("%s: Invalid rate : %lu for cpuclk\n",
		return -EINVAL;
	}

	spin_lock_irqsave(cpuclk->lock, flags);

	if (ndata->old_rate < ndata->new_rate)
		rockchip_cpuclk_set_dividers(cpuclk, rate);

	if (ndata->old_rate > ndata->new_rate)
		rockchip_cpuclk_set_dividers(cpuclk, rate);

	spin_unlock_irqrestore(cpuclk->lock, flags);
	return 0;
}

/*