ctnetlink_nfqueue_parse(const struct nlattr *attr, struct nf_conn *ct)
{
	struct nlattr *cda[CTA_MAX+1];
	int ret;

	nla_parse_nested(cda, CTA_MAX, attr, ct_nla_policy);

	spin_lock_bh(&nf_conntrack_lock);
	ret = ctnetlink_nfqueue_parse_ct((const struct nlattr **)cda, ct);
	spin_unlock_bh(&nf_conntrack_lock);

	return ret;
}

static struct nfq_ct_hook ctnetlink_nfqueue_hook = {
	.build_size	= ctnetlink_nfqueue_build_size,