
extern zend_class_entry *yosy_keytable_ce;

ZEPHIR_INIT_CLASS(Yosy_KeyTable);

PHP_METHOD(Yosy_KeyTable, __construct);
PHP_METHOD(Yosy_KeyTable, offsetSet);
PHP_METHOD(Yosy_KeyTable, offsetExists);
PHP_METHOD(Yosy_KeyTable, offsetGet);
PHP_METHOD(Yosy_KeyTable, offsetUnset);
PHP_METHOD(Yosy_KeyTable, count);
PHP_METHOD(Yosy_KeyTable, get);
PHP_METHOD(Yosy_KeyTable, toArray);
PHP_METHOD(Yosy_KeyTable, treeIterateValues);
PHP_METHOD(Yosy_KeyTable, merge);
PHP_METHOD(Yosy_KeyTable, _merge);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, seed, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_get, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_toarray, 0, 0, 0)
	ZEND_ARG_INFO(0, recurse)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_treeiteratevalues, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable_merge, 0, 0, 1)
	ZEND_ARG_INFO(0, kt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_keytable__merge, 0, 0, 1)
	ZEND_ARG_INFO(0, kt)
	ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_keytable_method_entry) {
	PHP_ME(Yosy_KeyTable, __construct, arginfo_yosy_keytable___construct, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_ME(Yosy_KeyTable, offsetSet, arginfo_yosy_keytable_offsetset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, offsetExists, arginfo_yosy_keytable_offsetexists, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, offsetGet, arginfo_yosy_keytable_offsetget, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, offsetUnset, arginfo_yosy_keytable_offsetunset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, count, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, get, arginfo_yosy_keytable_get, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, toArray, arginfo_yosy_keytable_toarray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, treeIterateValues, arginfo_yosy_keytable_treeiteratevalues, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, merge, arginfo_yosy_keytable_merge, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_KeyTable, _merge, arginfo_yosy_keytable__merge, ZEND_ACC_PROTECTED|ZEND_ACC_FINAL)
	PHP_FE_END
};
