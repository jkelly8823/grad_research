	const u32 pattern = 0xdeadbeef;
	int ret;

	kctl = snd_ctl_find_id(card, &control->id);
	if (kctl == NULL)
		return -ENOENT;

	index_offset = snd_ctl_get_ioff(kctl, &control->id);
	vd = &kctl->vd[index_offset];
	if (!(vd->access & SNDRV_CTL_ELEM_ACCESS_READ) || kctl->get == NULL)
		return -EPERM;

	snd_ctl_build_ioff(&control->id, kctl, index_offset);

#ifdef CONFIG_SND_CTL_DEBUG
	info.id = control->id;
	ret = __snd_ctl_elem_info(card, kctl, &info, NULL);
	if (ret < 0)
		return ret;
#endif

	if (!snd_ctl_skip_validation(&info))
		fill_remaining_elem_value(control, &info, pattern);
		ret = kctl->get(kctl, control);
	snd_power_unref(card);
	if (ret < 0)
		return ret;
	if (!snd_ctl_skip_validation(&info) &&
	    sanity_check_elem_value(card, control, &info, pattern) < 0) {
		dev_err(card->dev,
			"control %i:%i:%i:%s:%i: access overflow\n",
			control->id.iface, control->id.device,
			control->id.subdevice, control->id.name,
			control->id.index);
		return -EINVAL;
	}
	return ret;
}

static int snd_ctl_elem_read_user(struct snd_card *card,
	if (IS_ERR(control))
		return PTR_ERR(control);

	down_read(&card->controls_rwsem);
	result = snd_ctl_elem_read(card, control);
	up_read(&card->controls_rwsem);
	if (result < 0)
		goto error;

	if (copy_to_user(_control, control, sizeof(*control)))