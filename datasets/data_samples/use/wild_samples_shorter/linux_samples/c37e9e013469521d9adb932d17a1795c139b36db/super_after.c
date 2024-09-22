	} else {
		sbi->s_inode_size = le16_to_cpu(es->s_inode_size);
		sbi->s_first_ino = le32_to_cpu(es->s_first_ino);
		if (sbi->s_first_ino < EXT4_GOOD_OLD_FIRST_INO) {
			ext4_msg(sb, KERN_ERR, "invalid first ino: %u",
				 sbi->s_first_ino);
			goto failed_mount;
		}
		if ((sbi->s_inode_size < EXT4_GOOD_OLD_INODE_SIZE) ||
		    (!is_power_of_2(sbi->s_inode_size)) ||
		    (sbi->s_inode_size > blocksize)) {
			ext4_msg(sb, KERN_ERR,