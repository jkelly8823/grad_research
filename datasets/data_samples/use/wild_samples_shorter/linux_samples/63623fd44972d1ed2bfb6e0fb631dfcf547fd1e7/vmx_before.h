	/* L2 must run next, and mustn't decide to exit to L1. */
	bool nested_run_pending;

	struct loaded_vmcs vmcs02;

	/*
	 * Guest pages referred to in the vmcs02 with host-physical