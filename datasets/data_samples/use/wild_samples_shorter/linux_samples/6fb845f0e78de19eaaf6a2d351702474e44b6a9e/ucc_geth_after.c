	u16 i, j;
	u8 __iomem *bd;

	netdev_reset_queue(ugeth->ndev);

	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	for (i = 0; i < ugeth->ug_info->numQueuesTx; i++) {