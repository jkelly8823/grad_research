
static unsigned long randomize_stack_top(unsigned long stack_top)
{
	unsigned long random_variable = 0;

	if ((current->flags & PF_RANDOMIZE) &&
		!(current->personality & ADDR_NO_RANDOMIZE)) {
		random_variable = (unsigned long) get_random_int();
		random_variable &= STACK_RND_MASK;
		random_variable <<= PAGE_SHIFT;
	}
#ifdef CONFIG_STACK_GROWSUP
	return PAGE_ALIGN(stack_top) + random_variable;