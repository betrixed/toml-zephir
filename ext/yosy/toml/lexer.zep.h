
extern zend_class_entry *yosy_toml_lexer_ce;

ZEPHIR_INIT_CLASS(Yosy_Toml_Lexer);

PHP_METHOD(Yosy_Toml_Lexer, tomlVersion);
PHP_METHOD(Yosy_Toml_Lexer, tokenName);
void zephir_init_static_properties_Yosy_Toml_Lexer(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_toml_lexer_tokenname, 0, 0, 1)
	ZEND_ARG_INFO(0, tokenId)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_toml_lexer_method_entry) {
	PHP_ME(Yosy_Toml_Lexer, tomlVersion, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_Toml_Lexer, tokenName, arginfo_yosy_toml_lexer_tokenname, ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
