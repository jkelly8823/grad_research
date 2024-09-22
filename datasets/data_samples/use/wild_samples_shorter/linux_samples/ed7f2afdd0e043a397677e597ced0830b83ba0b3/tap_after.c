	struct sk_buff *skb;
	int err, depth;

	if (unlikely(xdp->data_end - xdp->data < ETH_HLEN)) {
		err = -EINVAL;
		goto err;
	}

	if (q->flags & IFF_VNET_HDR)
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);

	skb = build_skb(xdp->data_hard_start, buflen);