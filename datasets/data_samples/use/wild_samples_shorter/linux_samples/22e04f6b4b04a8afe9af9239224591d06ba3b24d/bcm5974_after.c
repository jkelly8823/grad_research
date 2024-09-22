#define USB_DEVICE_ID_APPLE_WELLSPRING7A_ISO	0x025a
#define USB_DEVICE_ID_APPLE_WELLSPRING7A_JIS	0x025b
/* MacbookAir6,2 (unibody, June 2013) */
#define USB_DEVICE_ID_APPLE_WELLSPRING8_ANSI	0x0290
#define USB_DEVICE_ID_APPLE_WELLSPRING8_ISO	0x0291
#define USB_DEVICE_ID_APPLE_WELLSPRING8_JIS	0x0292

#define BCM5974_DEVICE(prod) {					\
	.match_flags = (USB_DEVICE_ID_MATCH_DEVICE |		\
			USB_DEVICE_ID_MATCH_INT_CLASS |		\