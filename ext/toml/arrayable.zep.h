
extern zend_class_entry *toml_arrayable_ce;

ZEPHIR_INIT_CLASS(Toml_Arrayable);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_arrayable_settag, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_arrayable_method_entry) {
	PHP_ABSTRACT_ME(Toml_Arrayable, toArray, NULL)
	PHP_ABSTRACT_ME(Toml_Arrayable, getTag, NULL)
	PHP_ABSTRACT_ME(Toml_Arrayable, setTag, arginfo_toml_arrayable_settag)
	PHP_FE_END
};
