	spin_lock_irqsave(&lp->lock, flags);

	len = (*lp->write)(lp->fd, skb, lp);

	if (len == skb->len) {
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
static const struct ethtool_ops uml_net_ethtool_ops = {
	.get_drvinfo	= uml_net_get_drvinfo,
	.get_link	= ethtool_op_get_link,
};

static void uml_net_user_timer_expire(unsigned long _conn)
{