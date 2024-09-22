	size_t x_start = 0, x_end = 0;
	resource_size_t end;
	void __iomem *io;
	ssize_t done;

	if (pci_resource_start(pdev, bar))
		end = pci_resource_len(pdev, bar);

	count = min(count, (size_t)(end - pos));

	if (bar == PCI_ROM_RESOURCE) {
		/*
		 * The ROM can fill less space than the BAR, so we start the
		 * excluded range at the end of the actual ROM.  This makes
		 * filling large ROM BARs much faster.
		 */
		io = pci_map_rom(pdev, &x_start);
		if (!io)
			return -ENOMEM;
		x_end = end;
	} else {
		int ret = vfio_pci_setup_barmap(vdev, bar);
		if (ret)
			return ret;

		io = vdev->barmap[bar];
	}


	if (bar == PCI_ROM_RESOURCE)
		pci_unmap_rom(pdev, io);

	return done;
}
