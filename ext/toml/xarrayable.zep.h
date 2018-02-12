
extern zend_class_entry *toml_xarrayable_ce;

ZEPHIR_INIT_CLASS(Toml_XArrayable);

PHP_METHOD(Toml_XArrayable, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_xarrayable___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_xarrayable_method_entry) {
	PHP_ME(Toml_XArrayable, __construct, arginfo_toml_xarrayable___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
