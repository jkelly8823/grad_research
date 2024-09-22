{
	struct clk_frac_pll *pll = to_clk_frac_pll(hw);
	u32 val, divfi, divff;
	u64 temp64;
	int ret;

	parent_rate *= 8;
	rate *= 2;
	divfi = rate / parent_rate;
	temp64 = parent_rate * divfi;
	temp64 = rate - temp64;
	temp64 *= PLL_FRAC_DENOM;
	do_div(temp64, parent_rate);
	divff = temp64;
