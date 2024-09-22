{
	u32 func_id = smccc_get_function(vcpu);
	u32 val = PSCI_RET_NOT_SUPPORTED;

	switch (func_id) {
	case ARM_SMCCC_VERSION_FUNC_ID:
		val = ARM_SMCCC_VERSION_1_1;
		break;
	case ARM_SMCCC_ARCH_FEATURES_FUNC_ID:
		/* Nothing supported yet */
		break;
	default:
		return kvm_psci_call(vcpu);
	}