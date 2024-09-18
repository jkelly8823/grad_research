{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct nlattr *tb[NUM_NL80211_REKEY_DATA];
	struct cfg80211_gtk_rekey_data rekey_data;
	int err;

	if (!info->attrs[NL80211_ATTR_REKEY_DATA])
		return -EINVAL;

	err = nla_parse_nested(tb, MAX_NL80211_REKEY_DATA,
			       info->attrs[NL80211_ATTR_REKEY_DATA],
			       nl80211_rekey_policy, info->extack);
	if (err)
		return err;

	if (!tb[NL80211_REKEY_DATA_REPLAY_CTR] || !tb[NL80211_REKEY_DATA_KEK] ||
	    !tb[NL80211_REKEY_DATA_KCK])
		return -EINVAL;
	if (nla_len(tb[NL80211_REKEY_DATA_REPLAY_CTR]) != NL80211_REPLAY_CTR_LEN)
		return -ERANGE;
	if (nla_len(tb[NL80211_REKEY_DATA_KEK]) != NL80211_KEK_LEN)
		return -ERANGE;
	if (nla_len(tb[NL80211_REKEY_DATA_KCK]) != NL80211_KCK_LEN)
		return -ERANGE;

	rekey_data.kek = nla_data(tb[NL80211_REKEY_DATA_KEK]);
	rekey_data.kck = nla_data(tb[NL80211_REKEY_DATA_KCK]);
	rekey_data.replay_ctr = nla_data(tb[NL80211_REKEY_DATA_REPLAY_CTR]);

	wdev_lock(wdev);
	if (!wdev->current_bss) {
		err = -ENOTCONN;
		goto out;
	}