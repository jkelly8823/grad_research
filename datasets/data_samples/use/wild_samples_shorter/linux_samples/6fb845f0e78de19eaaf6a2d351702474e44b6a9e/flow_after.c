		UAPI_DEF_IS_OBJ_SUPPORTED(flow_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE(
		UVERBS_OBJECT_FLOW,
		&mlx5_ib_fs),
	UAPI_DEF_CHAIN_OBJ_TREE(UVERBS_OBJECT_FLOW_ACTION,
				&mlx5_ib_flow_actions),
	{},
};