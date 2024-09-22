/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2018 - 2020 Intel Corporation
 *
 * Portions of this file are derived from the ipw3945 project.
 *
 * Contact Information:
 *  Intel Linux Wireless <linuxwifi@intel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#ifndef __iwl_debug_h__
#define __iwl_debug_h__
#endif
}

struct device;
void __iwl_err(struct device *dev, bool rfkill_prefix, bool only_trace,
		const char *fmt, ...) __printf(4, 5);
void __iwl_warn(struct device *dev, const char *fmt, ...) __printf(2, 3);
void __iwl_info(struct device *dev, const char *fmt, ...) __printf(2, 3);
void __iwl_crit(struct device *dev, const char *fmt, ...) __printf(2, 3);

#define CHECK_FOR_NEWLINE(f) BUILD_BUG_ON(f[sizeof(f) - 2] != '\n')

/* No matter what is m (priv, bus, trans), this will work */
#define IWL_ERR_DEV(d, f, a...)						\
	do {								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_err((d), false, false, f, ## a);			\
	} while (0)
#define IWL_ERR(m, f, a...)						\
	IWL_ERR_DEV((m)->dev, f, ## a)
#define IWL_WARN(m, f, a...)						\
	do {								\
		CHECK_FOR_NEWLINE(f);					\
		__iwl_warn((m)->dev, f, ## a);				\