/* Generated by re2c 0.13.5 on Mon Apr 12 10:11:22 2010 */
#line 1 "ext/standard/var_unserializer.re"
/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
	var_hash->data[var_hash->used_slots++] = *rval;
}

static inline void var_push_dtor(php_unserialize_data_t *var_hashx, zval **rval)
{
	var_entries *var_hash = var_hashx->first_dtor, *prev = NULL;

	while (var_hash && var_hash->used_slots == VAR_ENTRIES_MAX) {