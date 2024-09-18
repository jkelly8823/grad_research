		     addr += cb->cb->length, len -= cb->cb->length, cb++) {
			if (direction == DMA_DEV_TO_MEM)
				cb->cb->dst = addr;
			else
				cb->cb->src = addr;
			cb->cb->length = min(len, max_len);
		}
	}
}

static int bcm2835_dma_abort(void __iomem *chan_base)
{
	unsigned long cs;
	long int timeout = 10000;

	cs = readl(chan_base + BCM2835_DMA_CS);
	if (!(cs & BCM2835_DMA_ACTIVE))
		return 0;

	/* Write 0 to the active bit - Pause the DMA */
	writel(0, chan_base + BCM2835_DMA_CS);

	/* Wait for any current AXI transfer to complete */
	while ((cs & BCM2835_DMA_ISPAUSED) && --timeout) {
		cpu_relax();
		cs = readl(chan_base + BCM2835_DMA_CS);
	}
	if (c->irq_flags & IRQF_SHARED) {
		/* check if the interrupt is enabled */
		flags = readl(c->chan_base + BCM2835_DMA_CS);
		/* if not set then we are not the reason for the irq */
		if (!(flags & BCM2835_DMA_INT))
			return IRQ_NONE;
	}

	spin_lock_irqsave(&c->vc.lock, flags);

	/* Acknowledge interrupt */
	writel(BCM2835_DMA_INT, c->chan_base + BCM2835_DMA_CS);

	d = c->desc;

	if (d) {
		if (d->cyclic) {
			/* call the cyclic callback */
			vchan_cyclic_callback(&d->vd);

			/* Keep the DMA engine running */
			writel(BCM2835_DMA_ACTIVE,
			       c->chan_base + BCM2835_DMA_CS);
		} else {
			vchan_cookie_complete(&c->desc->vd);
			bcm2835_dma_start_desc(c);
		}
	}

	spin_unlock_irqrestore(&c->vc.lock, flags);

	return IRQ_HANDLED;
}
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	struct bcm2835_dmadev *d = to_bcm2835_dma_dev(c->vc.chan.device);
	unsigned long flags;
	int timeout = 10000;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after bcm_dma_abort() returns (even if it does, it will see
	 * c->desc is NULL and exit.)
	 */
	if (c->desc) {
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = NULL;
		bcm2835_dma_abort(c->chan_base);

		/* Wait for stopping */
		while (--timeout) {
			if (!(readl(c->chan_base + BCM2835_DMA_CS) &
						BCM2835_DMA_ACTIVE))
				break;

			cpu_relax();
		}

		if (!timeout)
			dev_err(d->ddev.dev, "DMA transfer could not be terminated\n");
	}
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	struct bcm2835_dmadev *d = to_bcm2835_dma_dev(c->vc.chan.device);
	unsigned long flags;
	int timeout = 10000;
	LIST_HEAD(head);

	spin_lock_irqsave(&c->vc.lock, flags);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after bcm_dma_abort() returns (even if it does, it will see
	 * c->desc is NULL and exit.)
	 */
	if (c->desc) {
		vchan_terminate_vdesc(&c->desc->vd);
		c->desc = NULL;
		bcm2835_dma_abort(c->chan_base);

		/* Wait for stopping */
		while (--timeout) {
			if (!(readl(c->chan_base + BCM2835_DMA_CS) &
						BCM2835_DMA_ACTIVE))
				break;

			cpu_relax();
		}

		if (!timeout)
			dev_err(d->ddev.dev, "DMA transfer could not be terminated\n");
	}