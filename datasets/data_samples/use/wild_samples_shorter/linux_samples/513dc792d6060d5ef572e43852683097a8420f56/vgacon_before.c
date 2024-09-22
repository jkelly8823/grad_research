static int vgacon_resize(struct vc_data *c, unsigned int width,
			 unsigned int height, unsigned int user)
{
	if (width % 2 || width > screen_info.orig_video_cols ||
	    height > (screen_info.orig_video_lines * vga_default_font_height)/
	    c->vc_font.height)
		/* let svgatextmode tinker with video timings and