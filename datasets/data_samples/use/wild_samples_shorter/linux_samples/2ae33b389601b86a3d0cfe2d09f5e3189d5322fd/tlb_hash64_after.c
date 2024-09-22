	if (!is_kernel_addr(addr)) {
		ssize = user_segment_size(addr);
		vsid = get_vsid(mm->context.id, addr, ssize);
	} else {
		vsid = get_kernel_vsid(addr, mmu_kernel_ssize);
		ssize = mmu_kernel_ssize;
	}
	WARN_ON(vsid == 0);
	vpn = hpt_vpn(addr, vsid, ssize);
	rpte = __real_pte(__pte(pte), ptep);

	/*