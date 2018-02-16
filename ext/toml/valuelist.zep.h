
extern zend_class_entry *toml_valuelist_ce;

ZEPHIR_INIT_CLASS(Toml_ValueList);

PHP_METHOD(Toml_ValueList, getType);
PHP_METHOD(Toml_ValueList, __construct);
PHP_METHOD(Toml_ValueList, getTag);
PHP_METHOD(Toml_ValueList, setTag);
PHP_METHOD(Toml_ValueList, offsetSet);
PHP_METHOD(Toml_ValueList, offsetExists);
PHP_METHOD(Toml_ValueList, offsetGet);
PHP_METHOD(Toml_ValueList, offsetUnset);
PHP_METHOD(Toml_ValueList, count);
PHP_METHOD(Toml_ValueList, get);
PHP_METHOD(Toml_ValueList, toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_settag, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_get, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_valuelist_toarray, 0, 0, 0)
	ZEND_ARG_INFO(0, recurse)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_valuelist_method_entry) {
	PHP_ME(Toml_ValueList, getType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_ValueList, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_ME(Toml_ValueList, getTag, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, setTag, arginfo_toml_valuelist_settag, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, offsetSet, arginfo_toml_valuelist_offsetset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, offsetExists, arginfo_toml_valuelist_offsetexists, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, offsetGet, arginfo_toml_valuelist_offsetget, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, offsetUnset, arginfo_toml_valuelist_offsetunset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, count, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, get, arginfo_toml_valuelist_get, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_ValueList, toArray, arginfo_toml_valuelist_toarray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_FE_END
};
