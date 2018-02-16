
extern zend_class_entry *toml_parttag_ce;

ZEPHIR_INIT_CLASS(Toml_PartTag);

PHP_METHOD(Toml_PartTag, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parttag___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, objAOT)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_parttag_method_entry) {
	PHP_ME(Toml_PartTag, __construct, arginfo_toml_parttag___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
