	{ "SAMSUNG MZMPC128HBFU-000MV", "CXM14M1Q", ATA_HORKAGE_NOLPM, },
	{ "SAMSUNG SSD PM830 mSATA *",  "CXM13D1Q", ATA_HORKAGE_NOLPM, },
	{ "SAMSUNG MZ7TD256HAFV-000L9", NULL,       ATA_HORKAGE_NOLPM, },

	/* devices that don't properly handle queued TRIM commands */
	{ "Micron_M500IT_*",		"MU01",	ATA_HORKAGE_NO_NCQ_TRIM |
						ATA_HORKAGE_ZERO_AFTER_TRIM, },