	load_sp0(t, &current->thread);
	set_tss_desc(cpu, t);
	load_TR_desc();
	load_mm_ldt(&init_mm);

	clear_all_debug_regs();
	dbg_restore_debug_regs();

	load_sp0(t, thread);
	set_tss_desc(cpu, t);
	load_TR_desc();
	load_mm_ldt(&init_mm);

	t->x86_tss.io_bitmap_base = offsetof(struct tss_struct, io_bitmap);

#ifdef CONFIG_DOUBLEFAULT