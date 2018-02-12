
extern zend_class_entry *toml_table_ce;

ZEPHIR_INIT_CLASS(Toml_Table);

PHP_METHOD(Toml_Table, mergeArray);
PHP_METHOD(Toml_Table, __construct);
PHP_METHOD(Toml_Table, offsetSet);
PHP_METHOD(Toml_Table, offsetExists);
PHP_METHOD(Toml_Table, offsetGet);
PHP_METHOD(Toml_Table, offsetUnset);
PHP_METHOD(Toml_Table, count);
PHP_METHOD(Toml_Table, path);
PHP_METHOD(Toml_Table, get);
PHP_METHOD(Toml_Table, toArray);
PHP_METHOD(Toml_Table, treeIterateValues);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_mergearray, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, kv, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, aval, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_path, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_get, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_toarray, 0, 0, 0)
	ZEND_ARG_INFO(0, recurse)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_table_treeiteratevalues, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_table_method_entry) {
	PHP_ME(Toml_Table, mergeArray, arginfo_toml_table_mergearray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, __construct, arginfo_toml_table___construct, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_ME(Toml_Table, offsetSet, arginfo_toml_table_offsetset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, offsetExists, arginfo_toml_table_offsetexists, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, offsetGet, arginfo_toml_table_offsetget, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, offsetUnset, arginfo_toml_table_offsetunset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, count, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, path, arginfo_toml_table_path, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, get, arginfo_toml_table_get, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, toArray, arginfo_toml_table_toarray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Table, treeIterateValues, arginfo_toml_table_treeiteratevalues, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_FE_END
};
