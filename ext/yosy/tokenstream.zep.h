
extern zend_class_entry *yosy_tokenstream_ce;

ZEPHIR_INIT_CLASS(Yosy_TokenStream);

PHP_METHOD(Yosy_TokenStream, __construct);
PHP_METHOD(Yosy_TokenStream, setEOSId);
PHP_METHOD(Yosy_TokenStream, setNewLineId);
PHP_METHOD(Yosy_TokenStream, setUnknownId);
PHP_METHOD(Yosy_TokenStream, setExpList);
PHP_METHOD(Yosy_TokenStream, setSingles);
PHP_METHOD(Yosy_TokenStream, setInput);
PHP_METHOD(Yosy_TokenStream, hasPendingTokens);
PHP_METHOD(Yosy_TokenStream, getToken);
PHP_METHOD(Yosy_TokenStream, getValue);
PHP_METHOD(Yosy_TokenStream, getTokenId);
PHP_METHOD(Yosy_TokenStream, setLines);
PHP_METHOD(Yosy_TokenStream, moveNextId);
PHP_METHOD(Yosy_TokenStream, parseNextId);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_seteosid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setnewlineid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setunknownid, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setexplist, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setsingles, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setinput, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_setlines, 0, 0, 1)
	ZEND_ARG_INFO(0, lines)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_tokenstream_parsenextid, 0, 0, 1)
	ZEND_ARG_INFO(0, patterns)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_tokenstream_method_entry) {
	PHP_ME(Yosy_TokenStream, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yosy_TokenStream, setEOSId, arginfo_yosy_tokenstream_seteosid, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setNewLineId, arginfo_yosy_tokenstream_setnewlineid, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setUnknownId, arginfo_yosy_tokenstream_setunknownid, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setExpList, arginfo_yosy_tokenstream_setexplist, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setSingles, arginfo_yosy_tokenstream_setsingles, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setInput, arginfo_yosy_tokenstream_setinput, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, hasPendingTokens, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, getToken, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, getValue, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, getTokenId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, setLines, arginfo_yosy_tokenstream_setlines, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, moveNextId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_TokenStream, parseNextId, arginfo_yosy_tokenstream_parsenextid, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
