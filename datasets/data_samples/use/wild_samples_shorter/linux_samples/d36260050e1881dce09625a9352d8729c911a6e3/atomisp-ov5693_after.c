	if (data_length == OV5693_8BIT)
		*val = (u8)data[0];
	else if (data_length == OV5693_16BIT)
		*val = be16_to_cpu(*(__be16 *)&data[0]);
	else
		*val = be32_to_cpu(*(__be32 *)&data[0]);

	return 0;
}

	struct i2c_msg msg;
	const int num_msg = 1;
	int ret;
	__be16 val;

	val = cpu_to_be16(data);
	msg.addr = VCM_ADDR;
	msg.flags = 0;
	msg.len = OV5693_16BIT;
	msg.buf = (void *)&val;

	ret = i2c_transfer(client->adapter, &msg, 1);

	return ret == num_msg ? 0 : -EIO;
{
	int ret;
	unsigned char data[4] = {0};
	__be16 *wreg = (void *)data;
	const u16 len = data_length + sizeof(u16); /* 16-bit address + data */

	if (data_length != OV5693_8BIT && data_length != OV5693_16BIT) {
		dev_err(&client->dev,
		data[2] = (u8)(val);
	} else {
		/* OV5693_16BIT */
		__be16 *wdata = (void *)&data[2];

		*wdata = cpu_to_be16(val);
	}

	ret = ov5693_i2c_write(client, len, data);
				    struct ov5693_write_ctrl *ctrl)
{
	u16 size;
	__be16 *reg = (void *)&ctrl->buffer.addr;

	if (ctrl->index == 0)
		return 0;

	size = sizeof(u16) + ctrl->index; /* 16-bit address + data */

	*reg = cpu_to_be16(ctrl->buffer.addr);
	ctrl->index = 0;

	return ov5693_i2c_write(client, size, (u8 *)reg);
}

static int __ov5693_buf_reg_array(struct i2c_client *client,
				  struct ov5693_write_ctrl *ctrl,
				  const struct ov5693_reg *next)
{
	int size;
	__be16 *data16;

	switch (next->type) {
	case OV5693_8BIT:
		size = 1;
		break;
	case OV5693_16BIT:
		size = 2;

		data16 = (void *)&ctrl->buffer.data[ctrl->index];
		*data16 = cpu_to_be16((u16)next->val);
		break;
	default:
		return -EINVAL;
	return ret;
}

static int ad5823_t_focus_abs(struct v4l2_subdev *sd, s32 value)
{
	value = min(value, AD5823_MAX_FOCUS_POS);
	return ad5823_t_focus_vcm(sd, value);
}
	.g_volatile_ctrl = ov5693_g_volatile_ctrl
};

static const struct v4l2_ctrl_config ov5693_controls[] = {
	{
	 .ops = &ctrl_ops,
	 .id = V4L2_CID_EXPOSURE_ABSOLUTE,
	 .type = V4L2_CTRL_TYPE_INTEGER,