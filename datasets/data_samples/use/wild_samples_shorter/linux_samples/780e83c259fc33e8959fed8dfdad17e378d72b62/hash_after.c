u32 xenvif_set_hash_mapping(struct xenvif *vif, u32 gref, u32 len,
			    u32 off)
{
	u32 *mapping = vif->hash.mapping;
	struct gnttab_copy copy_op = {
		.source.u.ref = gref,
		.source.domid = vif->domid,
		.dest.domid = DOMID_SELF,
		.len = len * sizeof(*mapping),
		.flags = GNTCOPY_source_gref
	};

	if ((off + len < off) || (off + len > vif->hash.size) ||
	    len > XEN_PAGE_SIZE / sizeof(*mapping))
		return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	copy_op.dest.u.gmfn = virt_to_gfn(mapping + off);
	copy_op.dest.offset = xen_offset_in_page(mapping + off);

	while (len-- != 0)
		if (mapping[off++] >= vif->num_queues)
			return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
