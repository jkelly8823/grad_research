// SPDX-License-Identifier: GPL-2.0-or-later
/* System trusted keyring for trusted public keys
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/uidgid.h>
#include <linux/verification.h>
#include <keys/asymmetric-type.h>
#include <keys/system_keyring.h>
#include <crypto/pkcs7.h>
#include "common.h"

static struct key *builtin_trusted_keys;
#ifdef CONFIG_SECONDARY_TRUSTED_KEYRING
static struct key *secondary_trusted_keys;
#endif
#ifdef CONFIG_INTEGRITY_PLATFORM_KEYRING
static struct key *platform_trusted_keys;
#endif

extern __initconst const u8 system_certificate_list[];
extern __initconst const unsigned long system_certificate_list_size;

/**
 * restrict_link_to_builtin_trusted - Restrict keyring addition by built in CA
 *
 * Restrict the addition of keys into a keyring based on the key-to-be-added
 * being vouched for by a key in the built in system keyring.
 */
int restrict_link_by_builtin_trusted(struct key *dest_keyring,
				     const struct key_type *type,
				     const union key_payload *payload,
				     struct key *restriction_key)
{
	return restrict_link_by_signature(dest_keyring, type, payload,
					  builtin_trusted_keys);
}
{
	pr_notice("Initialise system trusted keyrings\n");

	builtin_trusted_keys =
		keyring_alloc(".builtin_trusted_keys",
			      GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			      ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
			      KEY_USR_VIEW | KEY_USR_READ | KEY_USR_SEARCH),
			      KEY_ALLOC_NOT_IN_QUOTA,
			      NULL, NULL);
	if (IS_ERR(builtin_trusted_keys))
		panic("Can't allocate builtin trusted keyring\n");

#ifdef CONFIG_SECONDARY_TRUSTED_KEYRING
	secondary_trusted_keys =
		keyring_alloc(".secondary_trusted_keys",
			      GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			      ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
			       KEY_USR_VIEW | KEY_USR_READ | KEY_USR_SEARCH |
			       KEY_USR_WRITE),
			      KEY_ALLOC_NOT_IN_QUOTA,
			      get_builtin_and_secondary_restriction(),
			      NULL);
	if (IS_ERR(secondary_trusted_keys))
		panic("Can't allocate secondary trusted keyring\n");

	if (key_link(secondary_trusted_keys, builtin_trusted_keys) < 0)
		panic("Can't link trusted keyrings\n");
#endif

	return 0;
}

/*
 * Must be initialised before we try and load the keys into the keyring.
 */
device_initcall(system_trusted_keyring_init);

/*
 * Load the compiled-in list of X.509 certificates.
 */
static __init int load_system_certificate_list(void)
{
	pr_notice("Loading compiled-in X.509 certificates\n");

	return load_certificate_list(system_certificate_list, system_certificate_list_size,
				     builtin_trusted_keys);
}
		if (!trusted_keys) {
			ret = -ENOKEY;
			pr_devel("PKCS#7 platform keyring is not available\n");
			goto error;
		}

		ret = is_key_on_revocation_list(pkcs7);
		if (ret != -ENOKEY) {
			pr_devel("PKCS#7 platform key is on revocation list\n");
			goto error;
		}
	}
	ret = pkcs7_validate_trust(pkcs7, trusted_keys);
	if (ret < 0) {
		if (ret == -ENOKEY)
			pr_devel("PKCS#7 signature not signed with a trusted key\n");
		goto error;
	}

	if (view_content) {
		size_t asn1hdrlen;

		ret = pkcs7_get_content_data(pkcs7, &data, &len, &asn1hdrlen);
		if (ret < 0) {
			if (ret == -ENODATA)
				pr_devel("PKCS#7 message does not contain data\n");
			goto error;
		}

		ret = view_content(ctx, data, len, asn1hdrlen);
	}

error:
	pr_devel("<==%s() = %d\n", __func__, ret);
	return ret;
}

/**
 * verify_pkcs7_signature - Verify a PKCS#7-based signature on system data.
 * @data: The data to be verified (NULL if expecting internal data).
 * @len: Size of @data.
 * @raw_pkcs7: The PKCS#7 message that is the signature.
 * @pkcs7_len: The size of @raw_pkcs7.
 * @trusted_keys: Trusted keys to use (NULL for builtin trusted keys only,
 *					(void *)1UL for all trusted keys).
 * @usage: The use to which the key is being put.
 * @view_content: Callback to gain access to content.
 * @ctx: Context for callback.
 */
int verify_pkcs7_signature(const void *data, size_t len,
			   const void *raw_pkcs7, size_t pkcs7_len,
			   struct key *trusted_keys,
			   enum key_being_used_for usage,
			   int (*view_content)(void *ctx,
					       const void *data, size_t len,
					       size_t asn1hdrlen),
			   void *ctx)
{
	struct pkcs7_message *pkcs7;
	int ret;

	pkcs7 = pkcs7_parse_message(raw_pkcs7, pkcs7_len);
	if (IS_ERR(pkcs7))
		return PTR_ERR(pkcs7);

	ret = verify_pkcs7_message_sig(data, len, pkcs7, trusted_keys, usage,
				       view_content, ctx);

	pkcs7_free_message(pkcs7);
	pr_devel("<==%s() = %d\n", __func__, ret);
	return ret;
}
EXPORT_SYMBOL_GPL(verify_pkcs7_signature);

#endif /* CONFIG_SYSTEM_DATA_VERIFICATION */

#ifdef CONFIG_INTEGRITY_PLATFORM_KEYRING
void __init set_platform_trusted_keys(struct key *keyring)
{
	platform_trusted_keys = keyring;
}
#endif