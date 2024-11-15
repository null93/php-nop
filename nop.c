/* nop extension for PHP */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_nop.h"
#include "nop_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_BEGIN_MODULE_GLOBALS(nop)
    char *functions;
ZEND_END_MODULE_GLOBALS(nop)

ZEND_DECLARE_MODULE_GLOBALS(nop)

#ifdef ZTS
#define NOP_G(v) ZEND_TSRMG(nop_globals_id, zend_nop_globals *, v)
#else
#define NOP_G(v) (nop_globals.v)
#endif

static void php_nop_init_globals(zend_nop_globals *nop_globals)
{
    nop_globals->functions = NULL;
}

PHP_FUNCTION(no_operation)
{
	// Do nothing
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(nop)
{
#if defined(ZTS) && defined(COMPILE_DL_NOP)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("nop.functions", "", PHP_INI_ALL, OnUpdateString, functions, zend_nop_globals, nop_globals)
PHP_INI_END()

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(nop)
{
    ZEND_INIT_MODULE_GLOBALS(nop, php_nop_init_globals, NULL);
	REGISTER_INI_ENTRIES();

	char *functions = NOP_G(functions);
	if (functions != NULL) {
		char *token;
		char *rest = functions;
		while ((token = strtok_r(rest, ",", &rest))) {
			zend_function *original;
			original = zend_hash_str_find_ptr(CG(function_table), token, strlen(token));

			if (original != NULL) {
				original->internal_function.handler = PHP_FN(no_operation);
			}
		}
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(nop)
{
    UNREGISTER_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(nop)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "nop support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ nop_module_entry */
zend_module_entry nop_module_entry = {
	STANDARD_MODULE_HEADER,
	"nop",					/* Extension name */
	ext_functions,			/* zend_function_entry */
	PHP_MINIT(nop),			/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(nop),	    /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(nop),			/* PHP_RINIT - Request initialization */
	NULL,					/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(nop),			/* PHP_MINFO - Module info */
	PHP_NOP_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_NOP
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(nop)
#endif
