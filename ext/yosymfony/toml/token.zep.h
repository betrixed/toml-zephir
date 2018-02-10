
extern zend_class_entry *yosymfony_toml_token_ce;

ZEPHIR_INIT_CLASS(Yosymfony_Toml_Token);

PHP_METHOD(Yosymfony_Toml_Token, getValue);
PHP_METHOD(Yosymfony_Toml_Token, getId);
PHP_METHOD(Yosymfony_Toml_Token, getLine);
PHP_METHOD(Yosymfony_Toml_Token, __construct);
PHP_METHOD(Yosymfony_Toml_Token, set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosymfony_toml_token_set, 0, 0, 3)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, isSingle)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosymfony_toml_token_method_entry) {
	PHP_ME(Yosymfony_Toml_Token, getValue, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosymfony_Toml_Token, getId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosymfony_Toml_Token, getLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosymfony_Toml_Token, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yosymfony_Toml_Token, set, arginfo_yosymfony_toml_token_set, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
