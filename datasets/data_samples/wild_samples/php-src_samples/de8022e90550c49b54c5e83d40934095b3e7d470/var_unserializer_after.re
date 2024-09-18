	if (!var_hash) {
		var_hash = emalloc(sizeof(var_entries));
		var_hash->used_slots = 0;
		var_hash->next = 0;

		if (!(*var_hashx)->first)
			(*var_hashx)->first = var_hash;
		else
			prev->next = var_hash;
	}

	var_hash->data[var_hash->used_slots++] = *rval;
}

PHPAPI void var_push_dtor(php_unserialize_data_t *var_hashx, zval **rval)
{
	var_entries *var_hash = (*var_hashx)->first_dtor, *prev = NULL;
#if 0
	fprintf(stderr, "var_push_dtor(%ld): %d\n", var_hash?var_hash->used_slots:-1L, Z_TYPE_PP(rval));
#endif
		
	while (var_hash && var_hash->used_slots == VAR_ENTRIES_MAX) {
		prev = var_hash;
		var_hash = var_hash->next;
	}