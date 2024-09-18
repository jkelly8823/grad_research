/*
 * Copyright 2009-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include "internal/cryptlib.h"
#include <openssl/asn1t.h>
#include <openssl/pem.h>
#include <openssl/x509v3.h>
#include <openssl/err.h>
#include <openssl/cms.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include "internal/sizes.h"
#include "crypto/asn1.h"
#include "cms_local.h"

int CMS_RecipientInfo_set0_password(CMS_RecipientInfo *ri,
                                    unsigned char *pass, ossl_ssize_t passlen)
{
    CMS_PasswordRecipientInfo *pwri;
    if (ri->type != CMS_RECIPINFO_PASS) {
        ERR_raise(ERR_LIB_CMS, CMS_R_NOT_PWRI);
        return 0;
    }

    pwri = ri->d.pwri;
    pwri->pass = pass;
    if (pass && passlen < 0)
        passlen = strlen((char *)pass);
    pwri->passlen = passlen;
    return 1;
}
    if (EVP_EncryptInit_ex(ctx, kekciph, NULL, NULL, NULL) <= 0) {
        ERR_raise(ERR_LIB_CMS, ERR_R_EVP_LIB);
        goto err;
    }

    ivlen = EVP_CIPHER_CTX_get_iv_length(ctx);

    if (ivlen > 0) {
        if (RAND_bytes_ex(ossl_cms_ctx_get0_libctx(cms_ctx), iv, ivlen, 0) <= 0)
            goto err;
        if (EVP_EncryptInit_ex(ctx, NULL, NULL, NULL, iv) <= 0) {
            ERR_raise(ERR_LIB_CMS, ERR_R_EVP_LIB);
            goto err;
        }
        encalg->parameter = ASN1_TYPE_new();
        if (!encalg->parameter) {
            ERR_raise(ERR_LIB_CMS, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (EVP_CIPHER_param_to_asn1(ctx, encalg->parameter) <= 0) {
            ERR_raise(ERR_LIB_CMS, CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR);
            goto err;
        }
    }