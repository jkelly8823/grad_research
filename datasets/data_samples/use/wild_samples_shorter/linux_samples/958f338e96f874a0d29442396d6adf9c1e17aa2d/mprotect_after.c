	return pages;
}

static int prot_none_pte_entry(pte_t *pte, unsigned long addr,
			       unsigned long next, struct mm_walk *walk)
{
	return pfn_modify_allowed(pte_pfn(*pte), *(pgprot_t *)(walk->private)) ?
		0 : -EACCES;
}

static int prot_none_hugetlb_entry(pte_t *pte, unsigned long hmask,
				   unsigned long addr, unsigned long next,
				   struct mm_walk *walk)
{
	return pfn_modify_allowed(pte_pfn(*pte), *(pgprot_t *)(walk->private)) ?
		0 : -EACCES;
}

static int prot_none_test(unsigned long addr, unsigned long next,
			  struct mm_walk *walk)
{
	return 0;
}

static int prot_none_walk(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end, unsigned long newflags)
{
	pgprot_t new_pgprot = vm_get_page_prot(newflags);
	struct mm_walk prot_none_walk = {
		.pte_entry = prot_none_pte_entry,
		.hugetlb_entry = prot_none_hugetlb_entry,
		.test_walk = prot_none_test,
		.mm = current->mm,
		.private = &new_pgprot,
	};

	return walk_page_range(start, end, &prot_none_walk);
}

int
mprotect_fixup(struct vm_area_struct *vma, struct vm_area_struct **pprev,
	unsigned long start, unsigned long end, unsigned long newflags)
{
		return 0;
	}

	/*
	 * Do PROT_NONE PFN permission checks here when we can still
	 * bail out without undoing a lot of state. This is a rather
	 * uncommon case, so doesn't need to be very optimized.
	 */
	if (arch_has_pfn_modify_check() &&
	    (vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) &&
	    (newflags & (VM_READ|VM_WRITE|VM_EXEC)) == 0) {
		error = prot_none_walk(vma, start, end, newflags);
		if (error)
			return error;
	}

	/*
	 * If we make a private mapping writable we increase our commit;
	 * but (without finer accounting) cannot reduce our commit if we
	 * make it unwritable again. hugetlb mapping were accounted for