	if (err)
		return err;

	if (!tb[NL80211_REKEY_DATA_REPLAY_CTR] || !tb[NL80211_REKEY_DATA_KEK] ||
	    !tb[NL80211_REKEY_DATA_KCK])
		return -EINVAL;
	if (nla_len(tb[NL80211_REKEY_DATA_REPLAY_CTR]) != NL80211_REPLAY_CTR_LEN)
		return -ERANGE;
	if (nla_len(tb[NL80211_REKEY_DATA_KEK]) != NL80211_KEK_LEN)
		return -ERANGE;