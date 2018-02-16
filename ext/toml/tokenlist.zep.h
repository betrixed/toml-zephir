
extern zend_class_entry *toml_tokenlist_ce;

ZEPHIR_INIT_CLASS(Toml_TokenList);

PHP_METHOD(Toml_TokenList, __construct);
PHP_METHOD(Toml_TokenList, getOffset);
PHP_METHOD(Toml_TokenList, setOffset);
PHP_METHOD(Toml_TokenList, isNextSequence);
PHP_METHOD(Toml_TokenList, moveNextId);
PHP_METHOD(Toml_TokenList, getToken);
PHP_METHOD(Toml_TokenList, getTokenId);
PHP_METHOD(Toml_TokenList, getValue);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenlist___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenlist_setoffset, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenlist_isnextsequence, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, tokenIds, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_tokenlist_method_entry) {
	PHP_ME(Toml_TokenList, __construct, arginfo_toml_tokenlist___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Toml_TokenList, getOffset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, setOffset, arginfo_toml_tokenlist_setoffset, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, isNextSequence, arginfo_toml_tokenlist_isnextsequence, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, moveNextId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, getToken, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, getTokenId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenList, getValue, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
