	int (*get_lpage_level)(void);
	bool (*rdtscp_supported)(void);
	bool (*invpcid_supported)(void);
	void (*adjust_tsc_offset_guest)(struct kvm_vcpu *vcpu, s64 adjustment);

	void (*set_tdp_cr3)(struct kvm_vcpu *vcpu, unsigned long cr3);

	void (*set_supported_cpuid)(u32 func, struct kvm_cpuid_entry2 *entry);

	void (*write_tsc_offset)(struct kvm_vcpu *vcpu, u64 offset);

	u64 (*read_l1_tsc)(struct kvm_vcpu *vcpu, u64 host_tsc);

	void (*get_exit_info)(struct kvm_vcpu *vcpu, u64 *info1, u64 *info2);

	int (*check_intercept)(struct kvm_vcpu *vcpu,
			       struct x86_instruction_info *info,