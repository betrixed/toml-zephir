
extern zend_class_entry *yosy_valuelist_ce;

ZEPHIR_INIT_CLASS(Yosy_ValueList);

PHP_METHOD(Yosy_ValueList, getType);
PHP_METHOD(Yosy_ValueList, __construct);
PHP_METHOD(Yosy_ValueList, offsetSet);
PHP_METHOD(Yosy_ValueList, offsetExists);
PHP_METHOD(Yosy_ValueList, offsetGet);
PHP_METHOD(Yosy_ValueList, offsetUnset);
PHP_METHOD(Yosy_ValueList, count);
PHP_METHOD(Yosy_ValueList, get);
PHP_METHOD(Yosy_ValueList, toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_get, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, defaultValue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_valuelist_toarray, 0, 0, 0)
	ZEND_ARG_INFO(0, recurse)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_valuelist_method_entry) {
	PHP_ME(Yosy_ValueList, getType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_ValueList, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_ME(Yosy_ValueList, offsetSet, arginfo_yosy_valuelist_offsetset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, offsetExists, arginfo_yosy_valuelist_offsetexists, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, offsetGet, arginfo_yosy_valuelist_offsetget, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, offsetUnset, arginfo_yosy_valuelist_offsetunset, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, count, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, get, arginfo_yosy_valuelist_get, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Yosy_ValueList, toArray, arginfo_yosy_valuelist_toarray, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_FE_END
};
