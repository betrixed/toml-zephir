
extern zend_class_entry *toml_arrayable_ce;

ZEPHIR_INIT_CLASS(Toml_Arrayable);

PHP_METHOD(Toml_Arrayable, setTag);
PHP_METHOD(Toml_Arrayable, getTag);
PHP_METHOD(Toml_Arrayable, toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_arrayable_settag, 0, 0, 1)
	ZEND_ARG_INFO(0, any)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_arrayable_method_entry) {
	PHP_ME(Toml_Arrayable, setTag, arginfo_toml_arrayable_settag, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Arrayable, getTag, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_ME(Toml_Arrayable, toArray, NULL, ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
