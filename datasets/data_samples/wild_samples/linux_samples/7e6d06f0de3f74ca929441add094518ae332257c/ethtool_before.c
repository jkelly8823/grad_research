{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending > EFX_MAX_DMAQ_SIZE ||
	    ring->tx_pending > EFX_MAX_DMAQ_SIZE)
		return -EINVAL;

	if (ring->rx_pending < EFX_MIN_RING_SIZE ||
	    ring->tx_pending < EFX_MIN_RING_SIZE) {
		netif_err(efx, drv, efx->net_dev,
			  "TX and RX queues cannot be smaller than %ld\n",
			  EFX_MIN_RING_SIZE);
		return -EINVAL;
	}

	return efx_realloc_channels(efx, ring->rx_pending, ring->tx_pending);
}