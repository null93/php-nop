/* nop extension for PHP */

#ifndef PHP_NOP_H
# define PHP_NOP_H

extern zend_module_entry nop_module_entry;
# define phpext_nop_ptr &nop_module_entry

# define PHP_NOP_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_NOP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_NOP_H */
