
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_YOSY_H
#define PHP_YOSY_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_YOSY_NAME        "toml"
#define PHP_YOSY_VERSION     "0.0.1"
#define PHP_YOSY_EXTNAME     "yosy"
#define PHP_YOSY_AUTHOR      "Michael Rynn"
#define PHP_YOSY_ZEPVERSION  "0.10.7-8059e66568"
#define PHP_YOSY_DESCRIPTION "A toml parser, adapted from Yosymfony/Toml"



ZEND_BEGIN_MODULE_GLOBALS(yosy)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(yosy)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(yosy)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(yosy, v)
#else
	#define ZEPHIR_GLOBAL(v) (yosy_globals.v)
#endif

#ifdef ZTS
	void ***tsrm_ls;
	#define ZEPHIR_VGLOBAL ((zend_yosy_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(yosy_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(yosy_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def yosy_globals
#define zend_zephir_globals_def zend_yosy_globals

extern zend_module_entry yosy_module_entry;
#define phpext_yosy_ptr &yosy_module_entry

#endif
