{
	union split_pud res, *orig = (union split_pud *)pudp;

#ifdef CONFIG_PAGE_TABLE_ISOLATION
	pti_set_user_pgtbl(&pudp->p4d.pgd, __pgd(0));
#endif

	/* xchg acts as a barrier before setting of the high bits */
	res.pud_low = xchg(&orig->pud_low, 0);
	res.pud_high = orig->pud_high;
	orig->pud_high = 0;

	return res.pud;
}
#else
#define native_pudp_get_and_clear(xp) native_local_pudp_get_and_clear(xp)
#endif

/* Encode and de-code a swap entry */
#define SWP_TYPE_BITS		5

#define SWP_OFFSET_FIRST_BIT	(_PAGE_BIT_PROTNONE + 1)

/* We always extract/encode the offset by shifting it all the way up, and then down again */
#define SWP_OFFSET_SHIFT	(SWP_OFFSET_FIRST_BIT + SWP_TYPE_BITS)

#define MAX_SWAPFILES_CHECK() BUILD_BUG_ON(MAX_SWAPFILES_SHIFT > 5)
#define __swp_type(x)			(((x).val) & 0x1f)
#define __swp_offset(x)			((x).val >> 5)
#define __swp_entry(type, offset)	((swp_entry_t){(type) | (offset) << 5})

/*
 * Normally, __swp_entry() converts from arch-independent swp_entry_t to
 * arch-dependent swp_entry_t, and __swp_entry_to_pte() just stores the result
 * to pte. But here we have 32bit swp_entry_t and 64bit pte, and need to use the
 * whole 64 bits. Thus, we shift the "real" arch-dependent conversion to
 * __swp_entry_to_pte() through the following helper macro based on 64bit
 * __swp_entry().
 */
#define __swp_pteval_entry(type, offset) ((pteval_t) { \
	(~(pteval_t)(offset) << SWP_OFFSET_SHIFT >> SWP_TYPE_BITS) \
	| ((pteval_t)(type) << (64 - SWP_TYPE_BITS)) })

#define __swp_entry_to_pte(x)	((pte_t){ .pte = \
		__swp_pteval_entry(__swp_type(x), __swp_offset(x)) })
/*
 * Analogically, __pte_to_swp_entry() doesn't just extract the arch-dependent
 * swp_entry_t, but also has to convert it from 64bit to the 32bit
 * intermediate representation, using the following macros based on 64bit
 * __swp_type() and __swp_offset().
 */
#define __pteval_swp_type(x) ((unsigned long)((x).pte >> (64 - SWP_TYPE_BITS)))
#define __pteval_swp_offset(x) ((unsigned long)(~((x).pte) << SWP_TYPE_BITS >> SWP_OFFSET_SHIFT))

#define __pte_to_swp_entry(pte)	(__swp_entry(__pteval_swp_type(pte), \
					     __pteval_swp_offset(pte)))

#define gup_get_pte gup_get_pte
/*
 * WARNING: only to be used in the get_user_pages_fast() implementation.
 *
 * With get_user_pages_fast(), we walk down the pagetables without taking
 * any locks.  For this we would like to load the pointers atomically,
 * but that is not possible (without expensive cmpxchg8b) on PAE.  What
 * we do have is the guarantee that a PTE will only either go from not
 * present to present, or present to not present or both -- it will not
 * switch to a completely different present page without a TLB flush in
 * between; something that we are blocking by holding interrupts off.
 *
 * Setting ptes from not present to present goes:
 *
 *   ptep->pte_high = h;
 *   smp_wmb();
 *   ptep->pte_low = l;
 *
 * And present to not present goes:
 *
 *   ptep->pte_low = 0;
 *   smp_wmb();
 *   ptep->pte_high = 0;
 *
 * We must ensure here that the load of pte_low sees 'l' iff pte_high
 * sees 'h'. We load pte_high *after* loading pte_low, which ensures we
 * don't see an older value of pte_high.  *Then* we recheck pte_low,
 * which ensures that we haven't picked up a changed pte high. We might
 * have gotten rubbish values from pte_low and pte_high, but we are
 * guaranteed that pte_low will not have the present bit set *unless*
 * it is 'l'. Because get_user_pages_fast() only operates on present ptes
 * we're safe.
 */
static inline pte_t gup_get_pte(pte_t *ptep)
{
	pte_t pte;

	do {
		pte.pte_low = ptep->pte_low;
		smp_rmb();
		pte.pte_high = ptep->pte_high;
		smp_rmb();
	} while (unlikely(pte.pte_low != ptep->pte_low));

	return pte;
}

#include <asm/pgtable-invert.h>

#endif /* _ASM_X86_PGTABLE_3LEVEL_H */
	do {
		pte.pte_low = ptep->pte_low;
		smp_rmb();
		pte.pte_high = ptep->pte_high;
		smp_rmb();
	} while (unlikely(pte.pte_low != ptep->pte_low));

	return pte;
}

#include <asm/pgtable-invert.h>

#endif /* _ASM_X86_PGTABLE_3LEVEL_H */