
extern zend_class_entry *toml_box_ce;

ZEPHIR_INIT_CLASS(Toml_Box);

PHP_METHOD(Toml_Box, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_box___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, me)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_box_method_entry) {
	PHP_ME(Toml_Box, __construct, arginfo_toml_box___construct, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_FE_END
};
