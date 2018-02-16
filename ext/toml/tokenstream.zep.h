
extern zend_class_entry *toml_tokenstream_ce;

ZEPHIR_INIT_CLASS(Toml_TokenStream);

PHP_METHOD(Toml_TokenStream, __construct);
PHP_METHOD(Toml_TokenStream, setEOSId);
PHP_METHOD(Toml_TokenStream, setNewLineId);
PHP_METHOD(Toml_TokenStream, setUnknownId);
PHP_METHOD(Toml_TokenStream, setExpList);
PHP_METHOD(Toml_TokenStream, setSingles);
PHP_METHOD(Toml_TokenStream, setInput);
PHP_METHOD(Toml_TokenStream, getLine);
PHP_METHOD(Toml_TokenStream, hasPendingTokens);
PHP_METHOD(Toml_TokenStream, getToken);
PHP_METHOD(Toml_TokenStream, getValue);
PHP_METHOD(Toml_TokenStream, getTokenId);
PHP_METHOD(Toml_TokenStream, setLines);
PHP_METHOD(Toml_TokenStream, moveNextId);
PHP_METHOD(Toml_TokenStream, parseNextId);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_seteosid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setnewlineid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setunknownid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setexplist, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setsingles, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setinput, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_setlines, 0, 0, 1)
	ZEND_ARG_INFO(0, boxed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_tokenstream_parsenextid, 0, 0, 1)
	ZEND_ARG_INFO(0, patterns)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_tokenstream_method_entry) {
	PHP_ME(Toml_TokenStream, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Toml_TokenStream, setEOSId, arginfo_toml_tokenstream_seteosid, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setNewLineId, arginfo_toml_tokenstream_setnewlineid, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setUnknownId, arginfo_toml_tokenstream_setunknownid, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setExpList, arginfo_toml_tokenstream_setexplist, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setSingles, arginfo_toml_tokenstream_setsingles, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setInput, arginfo_toml_tokenstream_setinput, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, getLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, hasPendingTokens, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, getToken, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, getValue, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, getTokenId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, setLines, arginfo_toml_tokenstream_setlines, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, moveNextId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_TokenStream, parseNextId, arginfo_toml_tokenstream_parsenextid, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
