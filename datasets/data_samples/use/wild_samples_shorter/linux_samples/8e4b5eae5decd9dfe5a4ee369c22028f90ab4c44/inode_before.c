		goto bad_inode;
	raw_inode = ext4_raw_inode(&iloc);

	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) {
		ei->i_extra_isize = le16_to_cpu(raw_inode->i_extra_isize);
		if (EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize >
			EXT4_INODE_SIZE(inode->i_sb) ||