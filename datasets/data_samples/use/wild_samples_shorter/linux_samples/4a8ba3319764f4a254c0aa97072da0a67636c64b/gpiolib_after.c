		base = gpiochip_find_base(chip->ngpio);
		if (base < 0) {
			status = base;
			spin_unlock_irqrestore(&gpio_lock, flags);
			goto err_free_descs;
		}
		chip->base = base;
	}

	status = gpiochip_add_to_list(chip);
	if (status) {
		spin_unlock_irqrestore(&gpio_lock, flags);
		goto err_free_descs;
	}

	for (id = 0; id < chip->ngpio; id++) {
		struct gpio_desc *desc = &descs[id];

		desc->chip = chip;

		/* REVISIT: most hardware initializes GPIOs as inputs (often
		 * with pullups enabled) so power usage is minimized. Linux
		 * code should set the gpio direction first thing; but until
		 * it does, and in case chip->get_direction is not set, we may
		 * expose the wrong direction in sysfs.
		 */
		desc->flags = !chip->direction_input ? (1 << FLAG_IS_OUT) : 0;
	}

	chip->desc = descs;

	of_gpiochip_add(chip);
	acpi_gpiochip_add(chip);

	status = gpiochip_export(chip);
	if (status)
		goto err_remove_chip;

	pr_debug("%s: registered GPIOs %d to %d on device: %s\n", __func__,
		chip->base, chip->base + chip->ngpio - 1,
		chip->label ? : "generic");

	return 0;

err_remove_chip:
	acpi_gpiochip_remove(chip);
	of_gpiochip_remove(chip);
	spin_lock_irqsave(&gpio_lock, flags);
	list_del(&chip->list);
	spin_unlock_irqrestore(&gpio_lock, flags);
	chip->desc = NULL;
err_free_descs:
	kfree(descs);

	/* failures here can mean systems won't boot... */
	pr_err("%s: GPIOs %d..%d (%s) failed to register\n", __func__,
		chip->base, chip->base + chip->ngpio - 1,
	unsigned long	flags;
	unsigned	id;

	gpiochip_unexport(chip);

	gpiochip_irqchip_remove(chip);

	acpi_gpiochip_remove(chip);
	gpiochip_remove_pin_ranges(chip);
	of_gpiochip_remove(chip);

	spin_lock_irqsave(&gpio_lock, flags);
	for (id = 0; id < chip->ngpio; id++) {
		if (test_bit(FLAG_REQUESTED, &chip->desc[id].flags))
			dev_crit(chip->dev, "REMOVING GPIOCHIP WITH GPIOS STILL REQUESTED\n");
	}

	list_del(&chip->list);
	spin_unlock_irqrestore(&gpio_lock, flags);

	kfree(chip->desc);
	chip->desc = NULL;
}