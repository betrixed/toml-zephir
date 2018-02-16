
extern zend_class_entry *toml_lexer_ce;

ZEPHIR_INIT_CLASS(Toml_Lexer);

PHP_METHOD(Toml_Lexer, tomlVersion);
PHP_METHOD(Toml_Lexer, tokenName);
PHP_METHOD(Toml_Lexer, getExpSet);
PHP_METHOD(Toml_Lexer, tokenize);
void zephir_init_static_properties_Toml_Lexer(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_lexer_tokenname, 0, 0, 1)
	ZEND_ARG_INFO(0, tokenId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_lexer_getexpset, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, idList, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_lexer_tokenize, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_lexer_method_entry) {
	PHP_ME(Toml_Lexer, tomlVersion, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Lexer, tokenName, arginfo_toml_lexer_tokenname, ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Lexer, getExpSet, arginfo_toml_lexer_getexpset, ZEND_ACC_STATIC|ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Lexer, tokenize, arginfo_toml_lexer_tokenize, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
