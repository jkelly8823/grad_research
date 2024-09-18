{
	int err = -ENOMEM;

	/* Already connected through? */
	if (vif->irq)
		return 0;

	err = xen_netbk_map_frontend_rings(vif, tx_ring_ref, rx_ring_ref);
	if (err < 0)
		goto err;

	err = bind_interdomain_evtchn_to_irqhandler(
		vif->domid, evtchn, xenvif_interrupt, 0,
		vif->dev->name, vif);
	if (err < 0)
		goto err_unmap;
	vif->irq = err;
	disable_irq(vif->irq);

	xenvif_get(vif);

	rtnl_lock();
	if (!vif->can_sg && vif->dev->mtu > ETH_DATA_LEN)
		dev_set_mtu(vif->dev, ETH_DATA_LEN);
	netdev_update_features(vif->dev);
	netif_carrier_on(vif->dev);
	if (netif_running(vif->dev))
		xenvif_up(vif);
	rtnl_unlock();

	return 0;
err_unmap:
	xen_netbk_unmap_frontend_rings(vif);
err:
	return err;
}

void xenvif_carrier_off(struct xenvif *vif)
{
	struct net_device *dev = vif->dev;

	rtnl_lock();
	netif_carrier_off(dev); /* discard queued packets */
	if (netif_running(dev))
		xenvif_down(vif);
	rtnl_unlock();
	xenvif_put(vif);
}

void xenvif_disconnect(struct xenvif *vif)
{
	if (netif_carrier_ok(vif->dev))
		xenvif_carrier_off(vif);

	atomic_dec(&vif->refcnt);
	wait_event(vif->waiting_to_free, atomic_read(&vif->refcnt) == 0);

	del_timer_sync(&vif->credit_timeout);

	if (vif->irq)
		unbind_from_irqhandler(vif->irq, vif);

	unregister_netdev(vif->dev);

	xen_netbk_unmap_frontend_rings(vif);

	free_netdev(vif->dev);
}