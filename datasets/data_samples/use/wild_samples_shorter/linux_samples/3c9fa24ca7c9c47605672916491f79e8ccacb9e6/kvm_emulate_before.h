	 *  @addr:  [IN ] Linear address from which to read.
	 *  @val:   [OUT] Value read from memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to read from memory.
	 */
	int (*read_std)(struct x86_emulate_ctxt *ctxt,
			unsigned long addr, void *val,
			unsigned int bytes,
			struct x86_exception *fault);

	/*
	 * read_phys: Read bytes of standard (non-emulated/special) memory.
	 *            Used for descriptor reading.
	 *  @addr:  [IN ] Linear address to which to write.
	 *  @val:   [OUT] Value write to memory, zero-extended to 'u_long'.
	 *  @bytes: [IN ] Number of bytes to write to memory.
	 */
	int (*write_std)(struct x86_emulate_ctxt *ctxt,
			 unsigned long addr, void *val, unsigned int bytes,
			 struct x86_exception *fault);
	/*
	 * fetch: Read bytes of standard (non-emulated/special) memory.
	 *        Used for instruction fetch.
	 *  @addr:  [IN ] Linear address from which to read.