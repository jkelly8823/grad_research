	/* host flags */
	SIL24_COMMON_FLAGS	= ATA_FLAG_SATA | ATA_FLAG_PIO_DMA |
				  ATA_FLAG_NCQ | ATA_FLAG_ACPI_SATA |
				  ATA_FLAG_AN | ATA_FLAG_PMP,
	SIL24_FLAG_PCIX_IRQ_WOC	= (1 << 24), /* IRQ loss errata on PCI-X */

	IRQ_STAT_4PORTS		= 0xf,
};