{
	ext4_group_t group, ngroups = EXT4_SB(sb)->s_groups_count;
	struct ext4_group_desc *gdp = NULL;

	if (!ext4_has_group_desc_csum(sb))
		return ngroups;

	for (group = 0; group < ngroups; group++) {
		gdp = ext4_get_group_desc(sb, group, NULL);
		if (!gdp)
			continue;

		if (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED))
			continue;
		if (group != 0)
			break;
		ext4_error(sb, "Inode table for bg 0 marked as "
			   "needing zeroing");
		if (sb_rdonly(sb))
			return ngroups;
	}