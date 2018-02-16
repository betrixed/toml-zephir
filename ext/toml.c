
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "toml.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *toml_arrayable_ce;
zend_class_entry *toml_box_ce;
zend_class_entry *toml_keytable_ce;
zend_class_entry *toml_lexer_ce;
zend_class_entry *toml_parser_ce;
zend_class_entry *toml_parttag_ce;
zend_class_entry *toml_tablelist_ce;
zend_class_entry *toml_token_ce;
zend_class_entry *toml_tokenlist_ce;
zend_class_entry *toml_tokenstream_ce;
zend_class_entry *toml_valuelist_ce;
zend_class_entry *toml_xarrayable_ce;

ZEND_DECLARE_MODULE_GLOBALS(toml)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(toml)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Toml_Arrayable);
	ZEPHIR_INIT(Toml_Box);
	ZEPHIR_INIT(Toml_KeyTable);
	ZEPHIR_INIT(Toml_Lexer);
	ZEPHIR_INIT(Toml_Parser);
	ZEPHIR_INIT(Toml_PartTag);
	ZEPHIR_INIT(Toml_TableList);
	ZEPHIR_INIT(Toml_Token);
	ZEPHIR_INIT(Toml_TokenList);
	ZEPHIR_INIT(Toml_TokenStream);
	ZEPHIR_INIT(Toml_ValueList);
	ZEPHIR_INIT(Toml_XArrayable);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(toml)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_toml_globals *toml_globals TSRMLS_DC)
{
	toml_globals->initialized = 0;

	/* Memory options */
	toml_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	toml_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	toml_globals->cache_enabled = 1;

	/* Recursive Lock */
	toml_globals->recursive_lock = 0;

	/* Static cache */
	memset(toml_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_toml_globals *toml_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(toml)
{

	zend_toml_globals *toml_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	toml_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(toml_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(toml_globals_ptr TSRMLS_CC);

	zephir_init_static_properties_Toml_Lexer(TSRMLS_C);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(toml)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(toml)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_TOML_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_TOML_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_TOML_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_TOML_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_TOML_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(toml)
{
	php_zephir_init_globals(toml_globals TSRMLS_CC);
	php_zephir_init_module_globals(toml_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(toml)
{

}


zend_function_entry php_toml_functions[] = {
ZEND_FE_END

};

zend_module_entry toml_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_TOML_EXTNAME,
	php_toml_functions,
	PHP_MINIT(toml),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(toml),
#else
	NULL,
#endif
	PHP_RINIT(toml),
	PHP_RSHUTDOWN(toml),
	PHP_MINFO(toml),
	PHP_TOML_VERSION,
	ZEND_MODULE_GLOBALS(toml),
	PHP_GINIT(toml),
	PHP_GSHUTDOWN(toml),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_TOML
ZEND_GET_MODULE(toml)
#endif
