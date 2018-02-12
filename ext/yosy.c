
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "yosy.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *yosy_arrayable_ce;
zend_class_entry *yosy_token_ce;
zend_class_entry *yosy_toml_lexer_ce;
zend_class_entry *yosy_valuelist_ce;
zend_class_entry *yosy_xarrayable_ce;

ZEND_DECLARE_MODULE_GLOBALS(yosy)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(yosy)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Yosy_Arrayable);
	ZEPHIR_INIT(Yosy_Token);
	ZEPHIR_INIT(Yosy_Toml_Lexer);
	ZEPHIR_INIT(Yosy_ValueList);
	ZEPHIR_INIT(Yosy_XArrayable);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(yosy)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_yosy_globals *yosy_globals TSRMLS_DC)
{
	yosy_globals->initialized = 0;

	/* Memory options */
	yosy_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	yosy_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	yosy_globals->cache_enabled = 1;

	/* Recursive Lock */
	yosy_globals->recursive_lock = 0;

	/* Static cache */
	memset(yosy_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_yosy_globals *yosy_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(yosy)
{

	zend_yosy_globals *yosy_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	yosy_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(yosy_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(yosy_globals_ptr TSRMLS_CC);

	zephir_init_static_properties_Yosy_Toml_Lexer(TSRMLS_C);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(yosy)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(yosy)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_YOSY_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_YOSY_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_YOSY_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_YOSY_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_YOSY_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(yosy)
{
	php_zephir_init_globals(yosy_globals TSRMLS_CC);
	php_zephir_init_module_globals(yosy_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(yosy)
{

}


zend_function_entry php_yosy_functions[] = {
ZEND_FE_END

};

zend_module_entry yosy_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_YOSY_EXTNAME,
	php_yosy_functions,
	PHP_MINIT(yosy),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(yosy),
#else
	NULL,
#endif
	PHP_RINIT(yosy),
	PHP_RSHUTDOWN(yosy),
	PHP_MINFO(yosy),
	PHP_YOSY_VERSION,
	ZEND_MODULE_GLOBALS(yosy),
	PHP_GINIT(yosy),
	PHP_GSHUTDOWN(yosy),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_YOSY
ZEND_GET_MODULE(yosy)
#endif
