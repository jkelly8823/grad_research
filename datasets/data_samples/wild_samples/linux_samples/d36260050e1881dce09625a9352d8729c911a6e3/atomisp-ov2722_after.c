	if (err != 2) {
		if (err >= 0)
			err = -EIO;
		dev_err(&client->dev,
			"read from offset 0x%x error %d", reg, err);
		return err;
	}

	*val = 0;
	/* high byte comes first */
	if (data_length == OV2722_8BIT)
		*val = (u8)data[0];
	else if (data_length == OV2722_16BIT)
		*val = be16_to_cpu(*(__be16 *)&data[0]);
	else
		*val = be32_to_cpu(*(__be32 *)&data[0]);

	return 0;
}

static int ov2722_i2c_write(struct i2c_client *client, u16 len, u8 *data)
{
	struct i2c_msg msg;
	const int num_msg = 1;
	int ret;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = len;
	msg.buf = data;
	ret = i2c_transfer(client->adapter, &msg, 1);

	return ret == num_msg ? 0 : -EIO;
}

static int ov2722_write_reg(struct i2c_client *client, u16 data_length,
							u16 reg, u16 val)
{
	int ret;
	unsigned char data[4] = {0};
	__be16 *wreg = (__be16 *)data;
	const u16 len = data_length + sizeof(u16); /* 16-bit address + data */

	if (data_length != OV2722_8BIT && data_length != OV2722_16BIT) {
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		return -EINVAL;
	}
{
	int ret;
	unsigned char data[4] = {0};
	__be16 *wreg = (__be16 *)data;
	const u16 len = data_length + sizeof(u16); /* 16-bit address + data */

	if (data_length != OV2722_8BIT && data_length != OV2722_16BIT) {
		dev_err(&client->dev,
			"%s error, invalid data_length\n", __func__);
		return -EINVAL;
	}
	} else {
		/* OV2722_16BIT */
		__be16 *wdata = (__be16 *)&data[2];

		*wdata = cpu_to_be16(val);
	}
{
	u16 size;
	__be16 *data16 = (void *)&ctrl->buffer.addr;

	if (ctrl->index == 0)
		return 0;

	size = sizeof(u16) + ctrl->index; /* 16-bit address + data */
	*data16 = cpu_to_be16(ctrl->buffer.addr);
	ctrl->index = 0;

	return ov2722_i2c_write(client, size, (u8 *)&ctrl->buffer);
}
{
	int size;
	__be16 *data16;

	switch (next->type) {
	case OV2722_8BIT:
		size = 1;
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		break;
	case OV2722_16BIT:
		size = 2;
		data16 = (void *)&ctrl->buffer.data[ctrl->index];
		*data16 = cpu_to_be16((u16)next->val);
		break;
	default:
		return -EINVAL;
	}

	/* When first item is added, we need to store its starting address */
	if (ctrl->index == 0)
		ctrl->buffer.addr = next->reg;

	ctrl->index += size;

	/*
	 * Buffer cannot guarantee free space for u32? Better flush it to avoid
	 * possible lack of memory for next item.
	 */
	if (ctrl->index + sizeof(u16) >= OV2722_MAX_WRITE_BUF_SIZE)
		return __ov2722_flush_reg_array(client, ctrl);

	return 0;
}
	switch (next->type) {
	case OV2722_8BIT:
		size = 1;
		ctrl->buffer.data[ctrl->index] = (u8)next->val;
		break;
	case OV2722_16BIT:
		size = 2;
		data16 = (void *)&ctrl->buffer.data[ctrl->index];
		*data16 = cpu_to_be16((u16)next->val);
		break;
	default:
		return -EINVAL;
	}

	/* When first item is added, we need to store its starting address */
	if (ctrl->index == 0)
		ctrl->buffer.addr = next->reg;

	ctrl->index += size;

	/*
	 * Buffer cannot guarantee free space for u32? Better flush it to avoid
	 * possible lack of memory for next item.
	 */
	if (ctrl->index + sizeof(u16) >= OV2722_MAX_WRITE_BUF_SIZE)
		return __ov2722_flush_reg_array(client, ctrl);

	return 0;
}

static int __ov2722_write_reg_is_consecutive(struct i2c_client *client,
					     struct ov2722_write_ctrl *ctrl,
					     const struct ov2722_reg *next)
{
	if (ctrl->index == 0)
		return 1;

	return ctrl->buffer.addr + ctrl->index == next->reg;
}

static int ov2722_write_reg_array(struct i2c_client *client,
				  const struct ov2722_reg *reglist)
{
	const struct ov2722_reg *next = reglist;
	struct ov2722_write_ctrl ctrl;
	int err;

	ctrl.index = 0;
	for (; next->type != OV2722_TOK_TERM; next++) {
		switch (next->type & OV2722_TOK_MASK) {
		case OV2722_TOK_DELAY:
			err = __ov2722_flush_reg_array(client, &ctrl);
			if (err)
				return err;
			msleep(next->val);
			break;
		default:
			/*
			 * If next address is not consecutive, data needs to be
			 * flushed before proceed.
			 */
			if (!__ov2722_write_reg_is_consecutive(client, &ctrl,
								next)) {
				err = __ov2722_flush_reg_array(client, &ctrl);
				if (err)
					return err;
			}
			err = __ov2722_buf_reg_array(client, &ctrl, next);
			if (err) {
				dev_err(&client->dev, "%s: write error, aborted\n",
					 __func__);
				return err;
			}
			break;
		}
static const struct v4l2_ctrl_ops ctrl_ops = {
	.g_volatile_ctrl = ov2722_g_volatile_ctrl
};

static const struct v4l2_ctrl_config ov2722_controls[] = {
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_EXPOSURE_ABSOLUTE,
	 .type = V4L2_CTRL_TYPE_INTEGER,
	 .name = "exposure",
	 .min = 0x0,
	 .max = 0xffff,
	 .step = 0x01,
	 .def = 0x00,
	 .flags = 0,
	 },
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_FOCAL_ABSOLUTE,
	 .type = V4L2_CTRL_TYPE_INTEGER,
	 .name = "focal length",
	 .min = OV2722_FOCAL_LENGTH_DEFAULT,
	 .max = OV2722_FOCAL_LENGTH_DEFAULT,
	 .step = 0x01,
	 .def = OV2722_FOCAL_LENGTH_DEFAULT,
	 .flags = 0,
	 },
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_FNUMBER_ABSOLUTE,
	 .type = V4L2_CTRL_TYPE_INTEGER,
	 .name = "f-number",
	 .min = OV2722_F_NUMBER_DEFAULT,
	 .max = OV2722_F_NUMBER_DEFAULT,
	 .step = 0x01,
	 .def = OV2722_F_NUMBER_DEFAULT,
	 .flags = 0,
	 },
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_FNUMBER_RANGE,
	 .type = V4L2_CTRL_TYPE_INTEGER,
	 .name = "f-number range",
	 .min = OV2722_F_NUMBER_RANGE,
	 .max = OV2722_F_NUMBER_RANGE,
	 .step = 0x01,
	 .def = OV2722_F_NUMBER_RANGE,
	 .flags = 0,
	 },
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_LINK_FREQ,
	 .name = "Link Frequency",
	 .type = V4L2_CTRL_TYPE_INTEGER,
	 .min = 1,
	 .max = 1500000 * 1000,
	 .step = 1,
	 .def = 1,
	 .flags = V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_READ_ONLY,
	 },
};

static int ov2722_init(struct v4l2_subdev *sd)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);

	mutex_lock(&dev->input_lock);

	/* restore settings */
	ov2722_res = ov2722_res_preview;
	N_RES = N_RES_PREVIEW;

	mutex_unlock(&dev->input_lock);

	return 0;
}

static int power_ctrl(struct v4l2_subdev *sd, bool flag)
{
	int ret = -1;
	struct ov2722_device *dev = to_ov2722_sensor(sd);

	if (!dev || !dev->platform_data)
		return -ENODEV;

	if (flag) {
		ret = dev->platform_data->v1p8_ctrl(sd, 1);
		if (ret == 0) {
			ret = dev->platform_data->v2p8_ctrl(sd, 1);
			if (ret)
				dev->platform_data->v1p8_ctrl(sd, 0);
		}
	} else {
		ret = dev->platform_data->v1p8_ctrl(sd, 0);
		ret |= dev->platform_data->v2p8_ctrl(sd, 0);
	}

	return ret;
}

static int gpio_ctrl(struct v4l2_subdev *sd, bool flag)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	int ret = -1;

	if (!dev || !dev->platform_data)
		return -ENODEV;

	/* Note: the GPIO order is asymmetric: always RESET#
	 * before PWDN# when turning it on or off.
	 */
	ret = dev->platform_data->gpio0_ctrl(sd, flag);
	/*
	 *ov2722 PWDN# active high when pull down,opposite to the convention
	 */
	ret |= dev->platform_data->gpio1_ctrl(sd, !flag);
	return ret;
}

static int power_up(struct v4l2_subdev *sd)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	if (!dev->platform_data) {
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		return -ENODEV;
	}

	/* power control */
	ret = power_ctrl(sd, 1);
	if (ret)
		goto fail_power;

	/* according to DS, at least 5ms is needed between DOVDD and PWDN */
	usleep_range(5000, 6000);

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 1);
	if (ret) {
		ret = gpio_ctrl(sd, 0);
		if (ret)
			goto fail_power;
	}

	/* flis clock control */
	ret = dev->platform_data->flisclk_ctrl(sd, 1);
	if (ret)
		goto fail_clk;

	/* according to DS, 20ms is needed between PWDN and i2c access */
	msleep(20);

	return 0;

fail_clk:
	gpio_ctrl(sd, 0);
fail_power:
	power_ctrl(sd, 0);
	dev_err(&client->dev, "sensor power-up failed\n");

	return ret;
}

static int power_down(struct v4l2_subdev *sd)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	if (!dev->platform_data) {
		dev_err(&client->dev,
			"no camera_sensor_platform_data");
		return -ENODEV;
	}

	ret = dev->platform_data->flisclk_ctrl(sd, 0);
	if (ret)
		dev_err(&client->dev, "flisclk failed\n");

	/* gpio ctrl */
	ret = gpio_ctrl(sd, 0);
	if (ret) {
		ret = gpio_ctrl(sd, 0);
		if (ret)
			dev_err(&client->dev, "gpio failed 2\n");
	}

	/* power control */
	ret = power_ctrl(sd, 0);
	if (ret)
		dev_err(&client->dev, "vprog failed.\n");

	return ret;
}

static int ov2722_s_power(struct v4l2_subdev *sd, int on)
{
	int ret;
	if (on == 0)
		return power_down(sd);
	else {
		ret = power_up(sd);
		if (!ret)
			return ov2722_init(sd);
	}
	return ret;
}

/*
 * distance - calculate the distance
 * @res: resolution
 * @w: width
 * @h: height
 *
 * Get the gap between resolution and w/h.
 * res->width/height smaller than w/h wouldn't be considered.
 * Returns the value of gap or -1 if fail.
 */
#define LARGEST_ALLOWED_RATIO_MISMATCH 800
static int distance(struct ov2722_resolution *res, u32 w, u32 h)
{
	unsigned int w_ratio = (res->width << 13) / w;
	unsigned int h_ratio;
	int match;

	if (h == 0)
		return -1;
	h_ratio = (res->height << 13) / h;
	if (h_ratio == 0)
		return -1;
	match   = abs(((w_ratio << 13) / h_ratio) - 8192);

	if ((w_ratio < 8192) || (h_ratio < 8192) ||
	    (match > LARGEST_ALLOWED_RATIO_MISMATCH))
		return -1;

	return w_ratio + h_ratio;
}

/* Return the nearest higher resolution index */
static int nearest_resolution_index(int w, int h)
{
	int i;
	int idx = -1;
	int dist;
	int min_dist = INT_MAX;
	struct ov2722_resolution *tmp_res = NULL;

	for (i = 0; i < N_RES; i++) {
		tmp_res = &ov2722_res[i];
		dist = distance(tmp_res, w, h);
		if (dist == -1)
			continue;
		if (dist < min_dist) {
			min_dist = dist;
			idx = i;
		}
	}

	return idx;
}

static int get_resolution_index(int w, int h)
{
	int i;

	for (i = 0; i < N_RES; i++) {
		if (w != ov2722_res[i].width)
			continue;
		if (h != ov2722_res[i].height)
			continue;

		return i;
	}

	return -1;
}

/* TODO: remove it. */
static int startup(struct v4l2_subdev *sd)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	ret = ov2722_write_reg(client, OV2722_8BIT,
					OV2722_SW_RESET, 0x01);
	if (ret) {
		dev_err(&client->dev, "ov2722 reset err.\n");
		return ret;
	}

	ret = ov2722_write_reg_array(client, ov2722_res[dev->fmt_idx].regs);
	if (ret) {
		dev_err(&client->dev, "ov2722 write register err.\n");
		return ret;
	}

	return ret;
}

static int ov2722_set_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct camera_mipi_info *ov2722_info = NULL;
	int ret = 0;
	int idx;
	if (format->pad)
		return -EINVAL;
	if (!fmt)
		return -EINVAL;
	ov2722_info = v4l2_get_subdev_hostdata(sd);
	if (!ov2722_info)
		return -EINVAL;

	mutex_lock(&dev->input_lock);
	idx = nearest_resolution_index(fmt->width, fmt->height);
	if (idx == -1) {
		/* return the largest resolution */
		fmt->width = ov2722_res[N_RES - 1].width;
		fmt->height = ov2722_res[N_RES - 1].height;
	} else {
		fmt->width = ov2722_res[idx].width;
		fmt->height = ov2722_res[idx].height;
	}
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		cfg->try_fmt = *fmt;
		mutex_unlock(&dev->input_lock);
		return 0;
	}

	dev->fmt_idx = get_resolution_index(fmt->width, fmt->height);
	if (dev->fmt_idx == -1) {
		dev_err(&client->dev, "get resolution fail\n");
		mutex_unlock(&dev->input_lock);
		return -EINVAL;
	}

	dev->pixels_per_line = ov2722_res[dev->fmt_idx].pixels_per_line;
	dev->lines_per_frame = ov2722_res[dev->fmt_idx].lines_per_frame;

	ret = startup(sd);
	if (ret) {
		int i = 0;
		dev_err(&client->dev, "ov2722 startup err, retry to power up\n");
		for (i = 0; i < OV2722_POWER_UP_RETRY_NUM; i++) {
			dev_err(&client->dev,
				"ov2722 retry to power up %d/%d times, result: ",
				i + 1, OV2722_POWER_UP_RETRY_NUM);
			power_down(sd);
			ret = power_up(sd);
			if (ret) {
				dev_err(&client->dev, "power up failed, continue\n");
				continue;
			}
			ret = startup(sd);
			if (ret) {
				dev_err(&client->dev, " startup FAILED!\n");
			} else {
				dev_err(&client->dev, " startup SUCCESS!\n");
				break;
			}
		}
		if (ret) {
			dev_err(&client->dev, "ov2722 startup err\n");
			goto err;
		}
	}

	ret = ov2722_get_intg_factor(client, ov2722_info,
					&ov2722_res[dev->fmt_idx]);
	if (ret)
		dev_err(&client->dev, "failed to get integration_factor\n");

err:
	mutex_unlock(&dev->input_lock);
	return ret;
}
static int ov2722_get_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct ov2722_device *dev = to_ov2722_sensor(sd);

	if (format->pad)
		return -EINVAL;
	if (!fmt)
		return -EINVAL;

	fmt->width = ov2722_res[dev->fmt_idx].width;
	fmt->height = ov2722_res[dev->fmt_idx].height;
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	return 0;
}

static int ov2722_detect(struct i2c_client *client)
{
	struct i2c_adapter *adapter = client->adapter;
	u16 high, low;
	int ret;
	u16 id;
	u8 revision;

	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		return -ENODEV;

	ret = ov2722_read_reg(client, OV2722_8BIT,
					OV2722_SC_CMMN_CHIP_ID_H, &high);
	if (ret) {
		dev_err(&client->dev, "sensor_id_high = 0x%x\n", high);
		return -ENODEV;
	}
	ret = ov2722_read_reg(client, OV2722_8BIT,
					OV2722_SC_CMMN_CHIP_ID_L, &low);
	id = (high << 8) | low;

	if ((id != OV2722_ID) && (id != OV2720_ID)) {
		dev_err(&client->dev, "sensor ID error\n");
		return -ENODEV;
	}

	ret = ov2722_read_reg(client, OV2722_8BIT,
					OV2722_SC_CMMN_SUB_ID, &high);
	revision = (u8) high & 0x0f;

	dev_dbg(&client->dev, "sensor_revision = 0x%x\n", revision);
	dev_dbg(&client->dev, "detect ov2722 success\n");
	return 0;
}

static int ov2722_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	mutex_lock(&dev->input_lock);

	ret = ov2722_write_reg(client, OV2722_8BIT, OV2722_SW_STREAM,
				enable ? OV2722_START_STREAMING :
				OV2722_STOP_STREAMING);

	mutex_unlock(&dev->input_lock);
	return ret;
}

static int ov2722_s_config(struct v4l2_subdev *sd,
			   int irq, void *platform_data)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	if (!platform_data)
		return -ENODEV;

	dev->platform_data =
		(struct camera_sensor_platform_data *)platform_data;

	mutex_lock(&dev->input_lock);

	/* power off the module, then power on it in future
	 * as first power on by board may not fulfill the
	 * power on sequqence needed by the module
	 */
	ret = power_down(sd);
	if (ret) {
		dev_err(&client->dev, "ov2722 power-off err.\n");
		goto fail_power_off;
	}

	ret = power_up(sd);
	if (ret) {
		dev_err(&client->dev, "ov2722 power-up err.\n");
		goto fail_power_on;
	}

	ret = dev->platform_data->csi_cfg(sd, 1);
	if (ret)
		goto fail_csi_cfg;

	/* config & detect sensor */
	ret = ov2722_detect(client);
	if (ret) {
		dev_err(&client->dev, "ov2722_detect err s_config.\n");
		goto fail_csi_cfg;
	}

	/* turn off sensor, after probed */
	ret = power_down(sd);
	if (ret) {
		dev_err(&client->dev, "ov2722 power-off err.\n");
		goto fail_csi_cfg;
	}
	mutex_unlock(&dev->input_lock);

	return 0;

fail_csi_cfg:
	dev->platform_data->csi_cfg(sd, 0);
fail_power_on:
	power_down(sd);
	dev_err(&client->dev, "sensor power-gating failed\n");
fail_power_off:
	mutex_unlock(&dev->input_lock);
	return ret;
}

static int ov2722_g_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *interval)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);

	interval->interval.numerator = 1;
	interval->interval.denominator = ov2722_res[dev->fmt_idx].fps;

	return 0;
}

static int ov2722_enum_mbus_code(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->index >= MAX_FMTS)
		return -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	return 0;
}

static int ov2722_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	int index = fse->index;

	if (index >= N_RES)
		return -EINVAL;

	fse->min_width = ov2722_res[index].width;
	fse->min_height = ov2722_res[index].height;
	fse->max_width = ov2722_res[index].width;
	fse->max_height = ov2722_res[index].height;

	return 0;

}


static int ov2722_g_skip_frames(struct v4l2_subdev *sd, u32 *frames)
{
	struct ov2722_device *dev = to_ov2722_sensor(sd);

	mutex_lock(&dev->input_lock);
	*frames = ov2722_res[dev->fmt_idx].skip_frames;
	mutex_unlock(&dev->input_lock);

	return 0;
}

static const struct v4l2_subdev_sensor_ops ov2722_sensor_ops = {
	.g_skip_frames	= ov2722_g_skip_frames,
};

static const struct v4l2_subdev_video_ops ov2722_video_ops = {
	.s_stream = ov2722_s_stream,
	.g_frame_interval = ov2722_g_frame_interval,
};

static const struct v4l2_subdev_core_ops ov2722_core_ops = {
	.s_power = ov2722_s_power,
	.ioctl = ov2722_ioctl,
};

static const struct v4l2_subdev_pad_ops ov2722_pad_ops = {
	.enum_mbus_code = ov2722_enum_mbus_code,
	.enum_frame_size = ov2722_enum_frame_size,
	.get_fmt = ov2722_get_fmt,
	.set_fmt = ov2722_set_fmt,
};

static const struct v4l2_subdev_ops ov2722_ops = {
	.core = &ov2722_core_ops,
	.video = &ov2722_video_ops,
	.pad = &ov2722_pad_ops,
	.sensor = &ov2722_sensor_ops,
};

static int ov2722_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ov2722_device *dev = to_ov2722_sensor(sd);
	dev_dbg(&client->dev, "ov2722_remove...\n");

	dev->platform_data->csi_cfg(sd, 0);
	v4l2_ctrl_handler_free(&dev->ctrl_handler);
	v4l2_device_unregister_subdev(sd);

	atomisp_gmin_remove_subdev(sd);

	media_entity_cleanup(&dev->sd.entity);
	kfree(dev);

	return 0;
}

static int __ov2722_init_ctrl_handler(struct ov2722_device *dev)
{
	struct v4l2_ctrl_handler *hdl;
	unsigned int i;
	hdl = &dev->ctrl_handler;
	v4l2_ctrl_handler_init(&dev->ctrl_handler, ARRAY_SIZE(ov2722_controls));
	for (i = 0; i < ARRAY_SIZE(ov2722_controls); i++)
		v4l2_ctrl_new_custom(&dev->ctrl_handler, &ov2722_controls[i],
				     NULL);

	dev->link_freq = v4l2_ctrl_find(&dev->ctrl_handler, V4L2_CID_LINK_FREQ);

	if (dev->ctrl_handler.error || !dev->link_freq)
		return dev->ctrl_handler.error;

	dev->sd.ctrl_handler = hdl;

	return 0;
}

static int ov2722_probe(struct i2c_client *client)
{
	struct ov2722_device *dev;
	void *ovpdev;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	mutex_init(&dev->input_lock);

	dev->fmt_idx = 0;
	v4l2_i2c_subdev_init(&(dev->sd), client, &ov2722_ops);

	ovpdev = gmin_camera_platform_data(&dev->sd,
					   ATOMISP_INPUT_FORMAT_RAW_10,
					   atomisp_bayer_order_grbg);

	ret = ov2722_s_config(&dev->sd, client->irq, ovpdev);
	if (ret)
		goto out_free;

	ret = __ov2722_init_ctrl_handler(dev);
	if (ret)
		goto out_ctrl_handler_free;

	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->format.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	if (ret)
		ov2722_remove(client);

	return atomisp_register_i2c_module(&dev->sd, ovpdev, RAW_CAMERA);

out_ctrl_handler_free:
	v4l2_ctrl_handler_free(&dev->ctrl_handler);

out_free:
	v4l2_device_unregister_subdev(&dev->sd);
	kfree(dev);
	return ret;
}

static const struct acpi_device_id ov2722_acpi_match[] = {
	{ "INT33FB" },
	{},
};
MODULE_DEVICE_TABLE(acpi, ov2722_acpi_match);

static struct i2c_driver ov2722_driver = {
	.driver = {
		.name = "ov2722",
		.acpi_match_table = ov2722_acpi_match,
	},
	.probe_new = ov2722_probe,
	.remove = ov2722_remove,
};
module_i2c_driver(ov2722_driver);

MODULE_AUTHOR("Wei Liu <wei.liu@intel.com>");
MODULE_DESCRIPTION("A low-level driver for OmniVision 2722 sensors");
MODULE_LICENSE("GPL");