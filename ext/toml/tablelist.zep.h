
extern zend_class_entry *toml_tablelist_ce;

ZEPHIR_INIT_CLASS(Toml_TableList);

PHP_METHOD(Toml_TableList, __construct);
PHP_METHOD(Toml_TableList, getTag);
PHP_METHOD(Toml_TableList, setTag);
PHP_METHOD(Toml_TableList, getEndIndex);
PHP_METHOD(Toml_TableList, getEndTable);
PHP_METHOD(Toml_TableList, getTables);
PHP_METHOD(Toml_TableList, newTable);
PHP_METHOD(Toml_TableList, addTables);
PHP_METHOD(Toml_TableList, offsetSet);
PHP_METHOD(Toml_TableList, offsetExists);
PHP_METHOD(Toml_TableList, offsetGet);
PHP_METHOD(Toml_TableList, offsetUnset);
PHP_METHOD(Toml_TableList, count);
PHP_METHOD(Toml_TableList, toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, list, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_settag, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_addtables, 0, 0, 1)
	ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tablelist_toarray, 0, 0, 0)
	ZEND_ARG_INFO(0, recurse)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_tablelist_method_entry) {
	PHP_ME(Toml_TableList, __construct, arginfo_toml_tablelist___construct, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_ME(Toml_TableList, getTag, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, setTag, arginfo_toml_tablelist_settag, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, getEndIndex, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, getEndTable, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, getTables, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, newTable, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, addTables, arginfo_toml_tablelist_addtables, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, offsetSet, arginfo_toml_tablelist_offsetset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, offsetExists, arginfo_toml_tablelist_offsetexists, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, offsetGet, arginfo_toml_tablelist_offsetget, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, offsetUnset, arginfo_toml_tablelist_offsetunset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, count, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_TableList, toArray, arginfo_toml_tablelist_toarray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_FE_END
};
