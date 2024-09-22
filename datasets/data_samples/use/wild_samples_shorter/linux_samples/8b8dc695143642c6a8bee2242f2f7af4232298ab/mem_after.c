	       (long int)((top_of_ram - total_ram) >> 20));

#ifdef CONFIG_ZONE_DMA
	max_zone_pfns[ZONE_DMA]	= min(max_low_pfn,
			((1UL << ARCH_ZONE_DMA_BITS) - 1) >> PAGE_SHIFT);
#endif
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
#ifdef CONFIG_HIGHMEM
	max_zone_pfns[ZONE_HIGHMEM] = max_pfn;