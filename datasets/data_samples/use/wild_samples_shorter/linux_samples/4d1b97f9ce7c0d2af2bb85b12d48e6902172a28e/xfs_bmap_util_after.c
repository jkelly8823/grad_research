xfs_alloc_file_space(
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
{
	xfs_mount_t		*mp = ip->i_mount;
	xfs_off_t		count;
	xfs_filblks_t		allocated_fsb;
			goto error;

		error = xfs_bmapi_write(tp, ip, startoffset_fsb,
				allocatesize_fsb, XFS_BMAPI_PREALLOC, 0, imapp,
				&nimaps);
		if (error)
			goto error;

		/*