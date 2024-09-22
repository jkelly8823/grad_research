// Software required to flush link stack on context switch
#define SEC_FTR_FLUSH_LINK_STACK	0x0000000000001000ull


// Features enabled by default
#define SEC_FTR_DEFAULT \
	(SEC_FTR_L1D_FLUSH_HV | \
	 SEC_FTR_L1D_FLUSH_PR | \
	 SEC_FTR_BNDS_CHK_SPEC_BAR | \
	 SEC_FTR_FAVOUR_SECURITY)

#endif /* _ASM_POWERPC_SECURITY_FEATURES_H */