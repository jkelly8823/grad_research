struct fw_rx_desc_base {
	u8 info0;
} __packed;

#define FW_RX_DESC_FLAGS_FIRST_MSDU (1 << 0)
#define FW_RX_DESC_FLAGS_LAST_MSDU  (1 << 1)
#define FW_RX_DESC_C3_FAILED        (1 << 2)
#define FW_RX_DESC_C4_FAILED        (1 << 3)
#define FW_RX_DESC_IPV6             (1 << 4)
#define FW_RX_DESC_TCP              (1 << 5)
#define FW_RX_DESC_UDP              (1 << 6)

struct fw_rx_desc_hl {
	union {
		struct {
		u8 discard:1,
		   forward:1,
		   any_err:1,
		   dup_err:1,
		   reserved:1,
		   inspect:1,
		   extension:2;
		} bits;
		u8 info0;
	} u;

	u8 version;
	u8 len;
	u8 flags;
} __packed;

#endif /* _RX_DESC_H_ */