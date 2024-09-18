struct wcn36xx_vif {
	struct list_head list;
	u8 dtim_period;
	enum ani_ed_type encrypt_type;
	bool is_joining;
	bool sta_assoc;
	struct wcn36xx_hal_mac_ssid ssid;
	enum wcn36xx_hal_bss_type bss_type;

	/* Power management */
	enum wcn36xx_power_state pw_state;

	u8 bss_index;
	/* Returned from WCN36XX_HAL_ADD_STA_SELF_RSP */
	u8 self_sta_index;
	u8 self_dpu_desc_index;
	u8 self_ucast_dpu_sign;

#if IS_ENABLED(CONFIG_IPV6)
	/* IPv6 addresses for WoWLAN */
	struct in6_addr target_ipv6_addrs[WCN36XX_HAL_IPV6_OFFLOAD_ADDR_MAX];
	unsigned long tentative_addrs[BITS_TO_LONGS(WCN36XX_HAL_IPV6_OFFLOAD_ADDR_MAX)];
	int num_target_ipv6_addrs;
#endif
	/* WoWLAN GTK rekey data */
	struct {
		u8 kck[NL80211_KCK_LEN], kek[NL80211_KEK_LEN];
		__le64 replay_ctr;
		bool valid;
	} rekey_data;

	struct list_head sta_list;

	int bmps_fail_ct;
};

/**
 * struct wcn36xx_sta - holds STA related fields
 *
 * @tid: traffic ID that is used during AMPDU and in TX BD.
 * @sta_index: STA index is returned from HW after config_sta call and is
 * used in both SMD channel and TX BD.
 * @dpu_desc_index: DPU descriptor index is returned from HW after config_sta
 * call and is used in TX BD.
 * @bss_sta_index: STA index is returned from HW after config_bss call and is
 * used in both SMD channel and TX BD. See table bellow when it is used.
 * @bss_dpu_desc_index: DPU descriptor index is returned from HW after
 * config_bss call and is used in TX BD.
 * ______________________________________________
 * |		  |	STA	|	AP	|
 * |______________|_____________|_______________|
 * |    TX BD     |bss_sta_index|   sta_index   |
 * |______________|_____________|_______________|
 * |all SMD calls |bss_sta_index|   sta_index	|
 * |______________|_____________|_______________|
 * |smd_delete_sta|  sta_index  |   sta_index	|
 * |______________|_____________|_______________|
 */
struct wcn36xx_sta {
	struct list_head list;
	struct wcn36xx_vif *vif;
	u16 aid;
	u16 tid;
	u8 sta_index;
	u8 dpu_desc_index;
	u8 ucast_dpu_sign;
	u8 bss_sta_index;
	u8 bss_dpu_desc_index;
	bool is_data_encrypted;
	/* Rates */
	struct wcn36xx_hal_supported_rates_v1 supported_rates;

	spinlock_t ampdu_lock;		/* protects next two fields */
	enum wcn36xx_ampdu_state ampdu_state[16];
	int non_agg_frame_ct;
};
struct wcn36xx_dxe_ch;
struct wcn36xx {
	struct ieee80211_hw	*hw;
	struct device		*dev;
	struct list_head	vif_list;

	const char		*nv_file;
	const struct firmware	*nv;

	u8			fw_revision;
	u8			fw_version;
	u8			fw_minor;
	u8			fw_major;
	u32			fw_feat_caps[WCN36XX_HAL_CAPS_SIZE];
	bool			is_pronto;

	/* extra byte for the NULL termination */
	u8			crm_version[WCN36XX_HAL_VERSION_LENGTH + 1];
	u8			wlan_version[WCN36XX_HAL_VERSION_LENGTH + 1];

	bool		first_boot;

	/* IRQs */
	int			tx_irq;
	int			rx_irq;
	void __iomem		*ccu_base;
	void __iomem		*dxe_base;

	struct rpmsg_endpoint	*smd_channel;

	struct qcom_smem_state  *tx_enable_state;
	unsigned		tx_enable_state_bit;
	struct qcom_smem_state	*tx_rings_empty_state;
	unsigned		tx_rings_empty_state_bit;

	/* prevents concurrent FW reconfiguration */
	struct mutex		conf_mutex;

	/*
	 * smd_buf must be protected with smd_mutex to garantee
	 * that all messages are sent one after another
	 */
	u8			*hal_buf;
	size_t			hal_rsp_len;
	struct mutex		hal_mutex;
	struct completion	hal_rsp_compl;
	struct workqueue_struct	*hal_ind_wq;
	struct work_struct	hal_ind_work;
	spinlock_t		hal_ind_lock;
	struct list_head	hal_ind_queue;

	struct cfg80211_scan_request *scan_req;
	bool			sw_scan;
	u8			sw_scan_opchannel;
	u8			sw_scan_channel;
	struct ieee80211_vif	*sw_scan_vif;
	struct mutex		scan_lock;
	bool			scan_aborted;

	/* DXE channels */
	struct wcn36xx_dxe_ch	dxe_tx_l_ch;	/* TX low */
	struct wcn36xx_dxe_ch	dxe_tx_h_ch;	/* TX high */
	struct wcn36xx_dxe_ch	dxe_rx_l_ch;	/* RX low */
	struct wcn36xx_dxe_ch	dxe_rx_h_ch;	/* RX high */

	/* For synchronization of DXE resources from BH, IRQ and WQ contexts */
	spinlock_t	dxe_lock;
	bool                    queues_stopped;

	/* Memory pools */
	struct wcn36xx_dxe_mem_pool mgmt_mem_pool;
	struct wcn36xx_dxe_mem_pool data_mem_pool;

	struct sk_buff		*tx_ack_skb;
	struct timer_list	tx_ack_timer;

	/* For A-MSDU re-aggregation */
	struct sk_buff_head amsdu;

	/* RF module */
	unsigned		rf_id;

#ifdef CONFIG_WCN36XX_DEBUGFS
	/* Debug file system entry */
	struct wcn36xx_dfs_entry    dfs;
#endif /* CONFIG_WCN36XX_DEBUGFS */
};

static inline bool wcn36xx_is_fw_version(struct wcn36xx *wcn,
					 u8 major,
					 u8 minor,
					 u8 version,
					 u8 revision)
{
	return (wcn->fw_major == major &&
		wcn->fw_minor == minor &&
		wcn->fw_version == version &&
		wcn->fw_revision == revision);
}
void wcn36xx_set_default_rates(struct wcn36xx_hal_supported_rates *rates);
void wcn36xx_set_default_rates_v1(struct wcn36xx_hal_supported_rates_v1 *rates);

static inline
struct ieee80211_sta *wcn36xx_priv_to_sta(struct wcn36xx_sta *sta_priv)
{
	return container_of((void *)sta_priv, struct ieee80211_sta, drv_priv);
}

static inline
struct wcn36xx_vif *wcn36xx_vif_to_priv(struct ieee80211_vif *vif)
{
	return (struct wcn36xx_vif *) vif->drv_priv;
}

static inline
struct ieee80211_vif *wcn36xx_priv_to_vif(struct wcn36xx_vif *vif_priv)
{
	return container_of((void *) vif_priv, struct ieee80211_vif, drv_priv);
}

static inline
struct wcn36xx_sta *wcn36xx_sta_to_priv(struct ieee80211_sta *sta)
{
	return (struct wcn36xx_sta *)sta->drv_priv;
}

#endif	/* _WCN36XX_H_ */
	struct {
		u8 kck[NL80211_KCK_LEN], kek[NL80211_KEK_LEN];
		__le64 replay_ctr;
		bool valid;
	} rekey_data;

	struct list_head sta_list;

	int bmps_fail_ct;
};

/**
 * struct wcn36xx_sta - holds STA related fields
 *
 * @tid: traffic ID that is used during AMPDU and in TX BD.
 * @sta_index: STA index is returned from HW after config_sta call and is
 * used in both SMD channel and TX BD.
 * @dpu_desc_index: DPU descriptor index is returned from HW after config_sta
 * call and is used in TX BD.
 * @bss_sta_index: STA index is returned from HW after config_bss call and is
 * used in both SMD channel and TX BD. See table bellow when it is used.
 * @bss_dpu_desc_index: DPU descriptor index is returned from HW after
 * config_bss call and is used in TX BD.
 * ______________________________________________
 * |		  |	STA	|	AP	|
 * |______________|_____________|_______________|
 * |    TX BD     |bss_sta_index|   sta_index   |
 * |______________|_____________|_______________|
 * |all SMD calls |bss_sta_index|   sta_index	|
 * |______________|_____________|_______________|
 * |smd_delete_sta|  sta_index  |   sta_index	|
 * |______________|_____________|_______________|
 */
struct wcn36xx_sta {
	struct list_head list;
	struct wcn36xx_vif *vif;
	u16 aid;
	u16 tid;
	u8 sta_index;
	u8 dpu_desc_index;
	u8 ucast_dpu_sign;
	u8 bss_sta_index;
	u8 bss_dpu_desc_index;
	bool is_data_encrypted;
	/* Rates */
	struct wcn36xx_hal_supported_rates_v1 supported_rates;

	spinlock_t ampdu_lock;		/* protects next two fields */
	enum wcn36xx_ampdu_state ampdu_state[16];
	int non_agg_frame_ct;
};
struct wcn36xx_dxe_ch;
struct wcn36xx {
	struct ieee80211_hw	*hw;
	struct device		*dev;
	struct list_head	vif_list;

	const char		*nv_file;
	const struct firmware	*nv;

	u8			fw_revision;
	u8			fw_version;
	u8			fw_minor;
	u8			fw_major;
	u32			fw_feat_caps[WCN36XX_HAL_CAPS_SIZE];
	bool			is_pronto;

	/* extra byte for the NULL termination */
	u8			crm_version[WCN36XX_HAL_VERSION_LENGTH + 1];
	u8			wlan_version[WCN36XX_HAL_VERSION_LENGTH + 1];

	bool		first_boot;

	/* IRQs */
	int			tx_irq;
	int			rx_irq;
	void __iomem		*ccu_base;
	void __iomem		*dxe_base;

	struct rpmsg_endpoint	*smd_channel;

	struct qcom_smem_state  *tx_enable_state;
	unsigned		tx_enable_state_bit;
	struct qcom_smem_state	*tx_rings_empty_state;
	unsigned		tx_rings_empty_state_bit;

	/* prevents concurrent FW reconfiguration */
	struct mutex		conf_mutex;

	/*
	 * smd_buf must be protected with smd_mutex to garantee
	 * that all messages are sent one after another
	 */
	u8			*hal_buf;
	size_t			hal_rsp_len;
	struct mutex		hal_mutex;
	struct completion	hal_rsp_compl;
	struct workqueue_struct	*hal_ind_wq;
	struct work_struct	hal_ind_work;
	spinlock_t		hal_ind_lock;
	struct list_head	hal_ind_queue;

	struct cfg80211_scan_request *scan_req;
	bool			sw_scan;
	u8			sw_scan_opchannel;
	u8			sw_scan_channel;
	struct ieee80211_vif	*sw_scan_vif;
	struct mutex		scan_lock;
	bool			scan_aborted;

	/* DXE channels */
	struct wcn36xx_dxe_ch	dxe_tx_l_ch;	/* TX low */
	struct wcn36xx_dxe_ch	dxe_tx_h_ch;	/* TX high */
	struct wcn36xx_dxe_ch	dxe_rx_l_ch;	/* RX low */
	struct wcn36xx_dxe_ch	dxe_rx_h_ch;	/* RX high */

	/* For synchronization of DXE resources from BH, IRQ and WQ contexts */
	spinlock_t	dxe_lock;
	bool                    queues_stopped;

	/* Memory pools */
	struct wcn36xx_dxe_mem_pool mgmt_mem_pool;
	struct wcn36xx_dxe_mem_pool data_mem_pool;

	struct sk_buff		*tx_ack_skb;
	struct timer_list	tx_ack_timer;

	/* For A-MSDU re-aggregation */
	struct sk_buff_head amsdu;

	/* RF module */
	unsigned		rf_id;

#ifdef CONFIG_WCN36XX_DEBUGFS
	/* Debug file system entry */
	struct wcn36xx_dfs_entry    dfs;
#endif /* CONFIG_WCN36XX_DEBUGFS */
};

static inline bool wcn36xx_is_fw_version(struct wcn36xx *wcn,
					 u8 major,
					 u8 minor,
					 u8 version,
					 u8 revision)
{
	return (wcn->fw_major == major &&
		wcn->fw_minor == minor &&
		wcn->fw_version == version &&
		wcn->fw_revision == revision);
}
void wcn36xx_set_default_rates(struct wcn36xx_hal_supported_rates *rates);
void wcn36xx_set_default_rates_v1(struct wcn36xx_hal_supported_rates_v1 *rates);

static inline
struct ieee80211_sta *wcn36xx_priv_to_sta(struct wcn36xx_sta *sta_priv)
{
	return container_of((void *)sta_priv, struct ieee80211_sta, drv_priv);
}

static inline
struct wcn36xx_vif *wcn36xx_vif_to_priv(struct ieee80211_vif *vif)
{
	return (struct wcn36xx_vif *) vif->drv_priv;
}

static inline
struct ieee80211_vif *wcn36xx_priv_to_vif(struct wcn36xx_vif *vif_priv)
{
	return container_of((void *) vif_priv, struct ieee80211_vif, drv_priv);
}

static inline
struct wcn36xx_sta *wcn36xx_sta_to_priv(struct ieee80211_sta *sta)
{
	return (struct wcn36xx_sta *)sta->drv_priv;
}

#endif	/* _WCN36XX_H_ */
struct wcn36xx {
	struct ieee80211_hw	*hw;
	struct device		*dev;
	struct list_head	vif_list;

	const char		*nv_file;
	const struct firmware	*nv;

	u8			fw_revision;
	u8			fw_version;
	u8			fw_minor;
	u8			fw_major;
	u32			fw_feat_caps[WCN36XX_HAL_CAPS_SIZE];
	bool			is_pronto;

	/* extra byte for the NULL termination */
	u8			crm_version[WCN36XX_HAL_VERSION_LENGTH + 1];
	u8			wlan_version[WCN36XX_HAL_VERSION_LENGTH + 1];

	bool		first_boot;

	/* IRQs */
	int			tx_irq;
	int			rx_irq;
	void __iomem		*ccu_base;
	void __iomem		*dxe_base;

	struct rpmsg_endpoint	*smd_channel;

	struct qcom_smem_state  *tx_enable_state;
	unsigned		tx_enable_state_bit;
	struct qcom_smem_state	*tx_rings_empty_state;
	unsigned		tx_rings_empty_state_bit;

	/* prevents concurrent FW reconfiguration */
	struct mutex		conf_mutex;

	/*
	 * smd_buf must be protected with smd_mutex to garantee
	 * that all messages are sent one after another
	 */
	u8			*hal_buf;
	size_t			hal_rsp_len;
	struct mutex		hal_mutex;
	struct completion	hal_rsp_compl;
	struct workqueue_struct	*hal_ind_wq;
	struct work_struct	hal_ind_work;
	spinlock_t		hal_ind_lock;
	struct list_head	hal_ind_queue;

	struct cfg80211_scan_request *scan_req;
	bool			sw_scan;
	u8			sw_scan_opchannel;
	u8			sw_scan_channel;
	struct ieee80211_vif	*sw_scan_vif;
	struct mutex		scan_lock;
	bool			scan_aborted;

	/* DXE channels */
	struct wcn36xx_dxe_ch	dxe_tx_l_ch;	/* TX low */
	struct wcn36xx_dxe_ch	dxe_tx_h_ch;	/* TX high */
	struct wcn36xx_dxe_ch	dxe_rx_l_ch;	/* RX low */
	struct wcn36xx_dxe_ch	dxe_rx_h_ch;	/* RX high */

	/* For synchronization of DXE resources from BH, IRQ and WQ contexts */
	spinlock_t	dxe_lock;
	bool                    queues_stopped;

	/* Memory pools */
	struct wcn36xx_dxe_mem_pool mgmt_mem_pool;
	struct wcn36xx_dxe_mem_pool data_mem_pool;

	struct sk_buff		*tx_ack_skb;
	struct timer_list	tx_ack_timer;

	/* For A-MSDU re-aggregation */
	struct sk_buff_head amsdu;

	/* RF module */
	unsigned		rf_id;

#ifdef CONFIG_WCN36XX_DEBUGFS
	/* Debug file system entry */
	struct wcn36xx_dfs_entry    dfs;
#endif /* CONFIG_WCN36XX_DEBUGFS */
};

static inline bool wcn36xx_is_fw_version(struct wcn36xx *wcn,
					 u8 major,
					 u8 minor,
					 u8 version,
					 u8 revision)
{
	return (wcn->fw_major == major &&
		wcn->fw_minor == minor &&
		wcn->fw_version == version &&
		wcn->fw_revision == revision);
}