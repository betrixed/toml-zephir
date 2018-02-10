
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "yosymfony.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *yosymfony_toml_lexer_ce;
zend_class_entry *yosymfony_toml_token_ce;

ZEND_DECLARE_MODULE_GLOBALS(yosymfony)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(yosymfony)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Yosymfony_Toml_Lexer);
	ZEPHIR_INIT(Yosymfony_Toml_Token);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(yosymfony)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_yosymfony_globals *yosymfony_globals TSRMLS_DC)
{
	yosymfony_globals->initialized = 0;

	/* Memory options */
	yosymfony_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	yosymfony_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	yosymfony_globals->cache_enabled = 1;

	/* Recursive Lock */
	yosymfony_globals->recursive_lock = 0;

	/* Static cache */
	memset(yosymfony_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_yosymfony_globals *yosymfony_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(yosymfony)
{

	zend_yosymfony_globals *yosymfony_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	yosymfony_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(yosymfony_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(yosymfony_globals_ptr TSRMLS_CC);

	zephir_init_static_properties_Yosymfony_Toml_Lexer(TSRMLS_C);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(yosymfony)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(yosymfony)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_YOSYMFONY_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_YOSYMFONY_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_YOSYMFONY_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_YOSYMFONY_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_YOSYMFONY_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(yosymfony)
{
	php_zephir_init_globals(yosymfony_globals TSRMLS_CC);
	php_zephir_init_module_globals(yosymfony_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(yosymfony)
{

}


zend_function_entry php_yosymfony_functions[] = {
ZEND_FE_END

};

zend_module_entry yosymfony_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_YOSYMFONY_EXTNAME,
	php_yosymfony_functions,
	PHP_MINIT(yosymfony),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(yosymfony),
#else
	NULL,
#endif
	PHP_RINIT(yosymfony),
	PHP_RSHUTDOWN(yosymfony),
	PHP_MINFO(yosymfony),
	PHP_YOSYMFONY_VERSION,
	ZEND_MODULE_GLOBALS(yosymfony),
	PHP_GINIT(yosymfony),
	PHP_GSHUTDOWN(yosymfony),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_YOSYMFONY
ZEND_GET_MODULE(yosymfony)
#endif
