				r = &dev->resource[idx];
				if (!r->start)
					continue;
				pci_claim_bridge_resource(dev, idx);
			}
		}
		pcibios_allocate_bus_resources(&bus->children);
	}