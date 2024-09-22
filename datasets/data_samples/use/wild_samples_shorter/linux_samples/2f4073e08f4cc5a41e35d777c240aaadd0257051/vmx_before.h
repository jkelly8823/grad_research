#define EXIT_REASON_UMWAIT              67
#define EXIT_REASON_TPAUSE              68
#define EXIT_REASON_BUS_LOCK            74

#define VMX_EXIT_REASONS \
	{ EXIT_REASON_EXCEPTION_NMI,         "EXCEPTION_NMI" }, \
	{ EXIT_REASON_EXTERNAL_INTERRUPT,    "EXTERNAL_INTERRUPT" }, \
	{ EXIT_REASON_XRSTORS,               "XRSTORS" }, \
	{ EXIT_REASON_UMWAIT,                "UMWAIT" }, \
	{ EXIT_REASON_TPAUSE,                "TPAUSE" }, \
	{ EXIT_REASON_BUS_LOCK,              "BUS_LOCK" }

#define VMX_EXIT_REASON_FLAGS \
	{ VMX_EXIT_REASONS_FAILED_VMENTRY,	"FAILED_VMENTRY" }
