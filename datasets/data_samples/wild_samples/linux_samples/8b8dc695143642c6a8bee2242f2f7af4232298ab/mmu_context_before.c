{
	unsigned long max;

	if (mmu_has_feature(MMU_FTR_68_BIT_VA))
		max = MAX_USER_CONTEXT;
	else
		max = MAX_USER_CONTEXT_65BIT_VA;

	return alloc_context_id(MIN_USER_CONTEXT, max);
}
EXPORT_SYMBOL_GPL(hash__alloc_context_id);

void slb_setup_new_exec(void);

static int hash__init_new_context(struct mm_struct *mm)
{
	int index;

	index = hash__alloc_context_id();
	if (index < 0)
		return index;

	mm->context.hash_context = kmalloc(sizeof(struct hash_mm_context),
					   GFP_KERNEL);
	if (!mm->context.hash_context) {
		ida_free(&mmu_context_ida, index);
		return -ENOMEM;
	}

	/*
	 * The old code would re-promote on fork, we don't do that when using
	 * slices as it could cause problem promoting slices that have been
	 * forced down to 4K.
	 *
	 * For book3s we have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details for newly allocated mm's (which will
	 * have id == 0) and don't alter context slice inherited via fork (which
	 * will have id != 0).
	 *
	 * We should not be calling init_new_context() on init_mm. Hence a
	 * check against 0 is OK.
	 */
	if (mm->context.id == 0) {
		memset(mm->context.hash_context, 0, sizeof(struct hash_mm_context));
		slice_init_new_context_exec(mm);
	} else {
		/* This is fork. Copy hash_context details from current->mm */
		memcpy(mm->context.hash_context, current->mm->context.hash_context, sizeof(struct hash_mm_context));
#ifdef CONFIG_PPC_SUBPAGE_PROT
		/* inherit subpage prot detalis if we have one. */
		if (current->mm->context.hash_context->spt) {
			mm->context.hash_context->spt = kmalloc(sizeof(struct subpage_prot_table),
								GFP_KERNEL);
			if (!mm->context.hash_context->spt) {
				ida_free(&mmu_context_ida, index);
				kfree(mm->context.hash_context);
				return -ENOMEM;
			}
		}
#endif

	}

	pkey_mm_init(mm);
	return index;
}

void hash__setup_new_exec(void)
{
	slice_setup_new_exec();

	slb_setup_new_exec();
}

static int radix__init_new_context(struct mm_struct *mm)
{
	unsigned long rts_field;
	int index, max_id;

	max_id = (1 << mmu_pid_bits) - 1;
	index = alloc_context_id(mmu_base_pid, max_id);
	if (index < 0)
		return index;

	/*
	 * set the process table entry,
	 */
	rts_field = radix__get_tree_size();
	process_tb[index].prtb0 = cpu_to_be64(rts_field | __pa(mm->pgd) | RADIX_PGD_INDEX_SIZE);

	/*
	 * Order the above store with subsequent update of the PID
	 * register (at which point HW can start loading/caching
	 * the entry) and the corresponding load by the MMU from
	 * the L2 cache.
	 */
	asm volatile("ptesync;isync" : : : "memory");

	mm->context.npu_context = NULL;
	mm->context.hash_context = NULL;

	return index;
}

int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	int index;

	if (radix_enabled())
		index = radix__init_new_context(mm);
	else
		index = hash__init_new_context(mm);

	if (index < 0)
		return index;

	mm->context.id = index;

	mm->context.pte_frag = NULL;
	mm->context.pmd_frag = NULL;
#ifdef CONFIG_SPAPR_TCE_IOMMU
	mm_iommu_init(mm);
#endif
	atomic_set(&mm->context.active_cpus, 0);
	atomic_set(&mm->context.copros, 0);

	return 0;
}

void __destroy_context(int context_id)
{
	ida_free(&mmu_context_ida, context_id);
}
EXPORT_SYMBOL_GPL(__destroy_context);

static void destroy_contexts(mm_context_t *ctx)
{
	int index, context_id;

	for (index = 0; index < ARRAY_SIZE(ctx->extended_id); index++) {
		context_id = ctx->extended_id[index];
		if (context_id)
			ida_free(&mmu_context_ida, context_id);
	}
	kfree(ctx->hash_context);
}

static void pmd_frag_destroy(void *pmd_frag)
{
	int count;
	struct page *page;

	page = virt_to_page(pmd_frag);
	/* drop all the pending references */
	count = ((unsigned long)pmd_frag & ~PAGE_MASK) >> PMD_FRAG_SIZE_SHIFT;
	/* We allow PTE_FRAG_NR fragments from a PTE page */
	if (atomic_sub_and_test(PMD_FRAG_NR - count, &page->pt_frag_refcount)) {
		pgtable_pmd_page_dtor(page);
		__free_page(page);
	}
}

static void destroy_pagetable_cache(struct mm_struct *mm)
{
	void *frag;

	frag = mm->context.pte_frag;
	if (frag)
		pte_frag_destroy(frag);

	frag = mm->context.pmd_frag;
	if (frag)
		pmd_frag_destroy(frag);
	return;
}

void destroy_context(struct mm_struct *mm)
{
#ifdef CONFIG_SPAPR_TCE_IOMMU
	WARN_ON_ONCE(!list_empty(&mm->context.iommu_group_mem_list));
#endif
	if (radix_enabled())
		WARN_ON(process_tb[mm->context.id].prtb0 != 0);
	else
		subpage_prot_free(mm);
	destroy_contexts(&mm->context);
	mm->context.id = MMU_NO_CONTEXT;
}

void arch_exit_mmap(struct mm_struct *mm)
{
	destroy_pagetable_cache(mm);

	if (radix_enabled()) {
		/*
		 * Radix doesn't have a valid bit in the process table
		 * entries. However we know that at least P9 implementation
		 * will avoid caching an entry with an invalid RTS field,
		 * and 0 is invalid. So this will do.
		 *
		 * This runs before the "fullmm" tlb flush in exit_mmap,
		 * which does a RIC=2 tlbie to clear the process table
		 * entry. See the "fullmm" comments in tlb-radix.c.
		 *
		 * No barrier required here after the store because
		 * this process will do the invalidate, which starts with
		 * ptesync.
		 */
		process_tb[mm->context.id].prtb0 = 0;
	}
}

#ifdef CONFIG_PPC_RADIX_MMU
void radix__switch_mmu_context(struct mm_struct *prev, struct mm_struct *next)
{
	mtspr(SPRN_PID, next->context.id);
	isync();
}
#endif
		if (current->mm->context.hash_context->spt) {
			mm->context.hash_context->spt = kmalloc(sizeof(struct subpage_prot_table),
								GFP_KERNEL);
			if (!mm->context.hash_context->spt) {
				ida_free(&mmu_context_ida, index);
				kfree(mm->context.hash_context);
				return -ENOMEM;
			}