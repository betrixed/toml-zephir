
extern zend_class_entry *toml_parser_ce;

ZEPHIR_INIT_CLASS(Toml_Parser);

PHP_METHOD(Toml_Parser, popExpSet);
PHP_METHOD(Toml_Parser, pushExpSet);
PHP_METHOD(Toml_Parser, getExpSet);
PHP_METHOD(Toml_Parser, setExpSet);
PHP_METHOD(Toml_Parser, __construct);
PHP_METHOD(Toml_Parser, parseFile);
PHP_METHOD(Toml_Parser, prepareInput);
PHP_METHOD(Toml_Parser, parse);
PHP_METHOD(Toml_Parser, getRoot);
PHP_METHOD(Toml_Parser, implementation);
PHP_METHOD(Toml_Parser, parseComment);
PHP_METHOD(Toml_Parser, skipSpace);
PHP_METHOD(Toml_Parser, parseKeyValue);
PHP_METHOD(Toml_Parser, parseKeyName);
PHP_METHOD(Toml_Parser, parseSimpleValue);
PHP_METHOD(Toml_Parser, parseBoolean);
PHP_METHOD(Toml_Parser, parseInteger);
PHP_METHOD(Toml_Parser, parseFloat);
PHP_METHOD(Toml_Parser, parseBasicString);
PHP_METHOD(Toml_Parser, parseMultilineBasicString);
PHP_METHOD(Toml_Parser, parseLiteralString);
PHP_METHOD(Toml_Parser, parseMultilineLiteralString);
PHP_METHOD(Toml_Parser, parseEscapedCharacter);
PHP_METHOD(Toml_Parser, parseDatetime);
PHP_METHOD(Toml_Parser, parseArray);
PHP_METHOD(Toml_Parser, pushWorkTable);
PHP_METHOD(Toml_Parser, parseInlineTable);
PHP_METHOD(Toml_Parser, finishLine);
PHP_METHOD(Toml_Parser, tablePathError);
PHP_METHOD(Toml_Parser, getPathName);
PHP_METHOD(Toml_Parser, parseObjectPath);
PHP_METHOD(Toml_Parser, parseTablePath);
PHP_METHOD(Toml_Parser, throwTokenError);
PHP_METHOD(Toml_Parser, parseCommentsAndSpace);
PHP_METHOD(Toml_Parser, errorUniqueKey);
PHP_METHOD(Toml_Parser, unexpectedTokenError);
PHP_METHOD(Toml_Parser, syntaxError);

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_pushexpset, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_getexpset, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_setexpset, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsefile, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_prepareinput, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parse, 0, 0, 1)
	ZEND_ARG_INFO(0, input)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_implementation, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsecomment, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_skipspace, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsekeyvalue, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
	ZEND_ARG_INFO(0, isFromInlineTable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsekeyname, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsesimplevalue, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseboolean, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseinteger, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsefloat, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsebasicstring, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsemultilinebasicstring, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseliteralstring, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsemultilineliteralstring, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseescapedcharacter, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsedatetime, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsearray, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_pushworktable, 0, 0, 1)
	ZEND_ARG_INFO(0, keyName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseinlinetable, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
	ZEND_ARG_INFO(0, keyName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_finishline, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_tablepatherror, 0, 0, 1)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_getpathname, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, parts, 0)
	ZEND_ARG_INFO(0, withIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parseobjectpath, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsetablepath, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_throwtokenerror, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, token, Toml\\Token, 0)
	ZEND_ARG_INFO(0, expectedId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_parsecommentsandspace, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ts, Toml\\TokenStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_erroruniquekey, 0, 0, 1)
	ZEND_ARG_INFO(0, keyName)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_unexpectedtokenerror, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, token, Toml\\Token, 0)
	ZEND_ARG_INFO(0, expectedMsg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_toml_parser_syntaxerror, 0, 0, 1)
	ZEND_ARG_INFO(0, msg)
	ZEND_ARG_OBJ_INFO(0, token, Toml\\Token, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(toml_parser_method_entry) {
	PHP_ME(Toml_Parser, popExpSet, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Parser, pushExpSet, arginfo_toml_parser_pushexpset, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Parser, getExpSet, arginfo_toml_parser_getexpset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Toml_Parser, setExpSet, arginfo_toml_parser_setexpset, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Toml_Parser, parseFile, arginfo_toml_parser_parsefile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Toml_Parser, prepareInput, arginfo_toml_parser_prepareinput, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parse, arginfo_toml_parser_parse, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Parser, getRoot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Toml_Parser, implementation, arginfo_toml_parser_implementation, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseComment, arginfo_toml_parser_parsecomment, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, skipSpace, arginfo_toml_parser_skipspace, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseKeyValue, arginfo_toml_parser_parsekeyvalue, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseKeyName, arginfo_toml_parser_parsekeyname, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseSimpleValue, arginfo_toml_parser_parsesimplevalue, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseBoolean, arginfo_toml_parser_parseboolean, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseInteger, arginfo_toml_parser_parseinteger, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseFloat, arginfo_toml_parser_parsefloat, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseBasicString, arginfo_toml_parser_parsebasicstring, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseMultilineBasicString, arginfo_toml_parser_parsemultilinebasicstring, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseLiteralString, arginfo_toml_parser_parseliteralstring, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseMultilineLiteralString, arginfo_toml_parser_parsemultilineliteralstring, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseEscapedCharacter, arginfo_toml_parser_parseescapedcharacter, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseDatetime, arginfo_toml_parser_parsedatetime, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseArray, arginfo_toml_parser_parsearray, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, pushWorkTable, arginfo_toml_parser_pushworktable, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseInlineTable, arginfo_toml_parser_parseinlinetable, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, finishLine, arginfo_toml_parser_finishline, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, tablePathError, arginfo_toml_parser_tablepatherror, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, getPathName, arginfo_toml_parser_getpathname, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseObjectPath, arginfo_toml_parser_parseobjectpath, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseTablePath, arginfo_toml_parser_parsetablepath, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, throwTokenError, arginfo_toml_parser_throwtokenerror, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, parseCommentsAndSpace, arginfo_toml_parser_parsecommentsandspace, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, errorUniqueKey, arginfo_toml_parser_erroruniquekey, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, unexpectedTokenError, arginfo_toml_parser_unexpectedtokenerror, ZEND_ACC_PRIVATE)
	PHP_ME(Toml_Parser, syntaxError, arginfo_toml_parser_syntaxerror, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
