
U_CFUNC PHP_FUNCTION(intlcal_get_now)
{
	UErrorCode	status			= U_ZERO_ERROR;
	intl_error_reset(NULL TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR,