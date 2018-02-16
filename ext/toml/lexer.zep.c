
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"


ZEPHIR_INIT_CLASS(Toml_Lexer) {

	ZEPHIR_REGISTER_CLASS(Toml, Lexer, toml, lexer, toml_lexer_method_entry, 0);

	zend_declare_property_null(toml_lexer_ce, SL("_nameList"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("Singles"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("Regex"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("BriefList"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("FullList"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("BasicStringList"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("LiteralStringList"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BAD"), 0);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_EQUAL"), 1);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BOOLEAN"), 2);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_DATE_TIME"), 3);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_EOS"), 4);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_INTEGER"), 5);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_3_QUOTATION_MARK"), 6);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_QUOTATION_MARK"), 7);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_3_APOSTROPHE"), 8);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_APOSTROPHE"), 9);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_NEWLINE"), 10);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_SPACE"), 11);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LEFT_SQUARE_BRACE"), 12);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_RIGHT_SQUARE_BRACE"), 13);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LEFT_CURLY_BRACE"), 14);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_RIGHT_CURLY_BRACE"), 15);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_COMMA"), 16);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_DOT"), 17);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_UNQUOTED_KEY"), 18);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_ESCAPED_CHARACTER"), 19);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_ESCAPE"), 20);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BASIC_UNESCAPED"), 21);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_FLOAT"), 22);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_HASH"), 23);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_CHAR"), 24);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LAST_TOKEN"), 24);

	zephir_declare_class_constant_string(toml_lexer_ce, SL("TOML_VERSION"), "0.4");

	return SUCCESS;

}

PHP_METHOD(Toml_Lexer, tomlVersion) {

	zval *this_ptr = getThis();


	RETURN_STRING("0.4");

}

PHP_METHOD(Toml_Lexer, tokenName) {

	zend_bool _0;
	zval *tokenId_param = NULL, _1, _2;
	zend_long tokenId;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	zephir_fetch_params(0, 1, 0, &tokenId_param);

	tokenId = zephir_get_intval(tokenId_param);


	_0 = tokenId > 24;
	if (!(_0)) {
		_0 = tokenId < 0;
	}
	if (_0) {
		tokenId = 0;
	}
	zephir_read_static_property_ce(&_1, toml_lexer_ce, SL("_nameList"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_2, &_1, tokenId, PH_NOISY | PH_READONLY, "toml/Lexer.zep", 132 TSRMLS_CC);
	RETURN_CTORW(&_2);

}

PHP_METHOD(Toml_Lexer, getExpSet) {

	zval *idList_param = NULL, result, id, *_0, _1$$3, _2$$3;
	zval idList;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&idList);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &idList_param);

	ZEPHIR_OBS_COPY_OR_DUP(&idList, idList_param);


	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	zephir_is_iterable(&idList, 0, "toml/Lexer.zep", 141);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&idList), _0)
	{
		ZEPHIR_INIT_NVAR(&id);
		ZVAL_COPY(&id, _0);
		zephir_read_static_property_ce(&_1$$3, toml_lexer_ce, SL("Regex"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_2$$3, &_1$$3, &id, PH_NOISY | PH_READONLY, "toml/Lexer.zep", 139 TSRMLS_CC);
		zephir_array_update_zval(&result, &id, &_2$$3, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&id);
	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Lexer, tokenize) {

	zephir_fcall_cache_entry *_2 = NULL, *_7 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, stream, list, _0, _1, _3, _4, _5, _6, _11, _12, _8$$3, _10$$3;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&stream);
	ZVAL_UNDEF(&list);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_10$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &input_param);

	zephir_get_strval(&input, input_param);


	ZEPHIR_INIT_VAR(&stream);
	object_init_ex(&stream, toml_tokenstream_ce);
	ZEPHIR_CALL_METHOD(NULL, &stream, "__construct", NULL, 2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, toml_keytable_ce);
	zephir_read_static_property_ce(&_1, toml_lexer_ce, SL("Regex"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", &_2, 3, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setexplist", NULL, 4, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, toml_keytable_ce);
	zephir_read_static_property_ce(&_4, toml_lexer_ce, SL("Singles"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", &_2, 3, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setsingles", NULL, 5, &_3);
	zephir_check_call_status();
	ZVAL_LONG(&_5, 24);
	ZEPHIR_CALL_METHOD(NULL, &stream, "setunknownid", NULL, 6, &_5);
	zephir_check_call_status();
	ZVAL_LONG(&_5, 10);
	ZEPHIR_CALL_METHOD(NULL, &stream, "setnewlineid", NULL, 7, &_5);
	zephir_check_call_status();
	ZVAL_LONG(&_5, 4);
	ZEPHIR_CALL_METHOD(NULL, &stream, "seteosid", NULL, 8, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setinput", NULL, 9, &input);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&list);
	array_init(&list);
	while (1) {
		ZEPHIR_CALL_METHOD(&_6, &stream, "movenextid", &_7, 10);
		zephir_check_call_status();
		if (!(!ZEPHIR_IS_LONG_IDENTICAL(&_6, 4))) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_8$$3, &stream, "gettoken", &_9, 11);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_10$$3);
		if (zephir_clone(&_10$$3, &_8$$3 TSRMLS_CC) == FAILURE) {
			RETURN_MM();
		}
		zephir_array_append(&list, &_10$$3, PH_SEPARATE, "toml/Lexer.zep", 161);
	}
	ZEPHIR_CALL_METHOD(&_11, &stream, "gettoken", &_9, 11);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	if (zephir_clone(&_12, &_11 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_array_append(&list, &_12, PH_SEPARATE, "toml/Lexer.zep", 163);
	object_init_ex(return_value, toml_tokenlist_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 12, &list);
	zephir_check_call_status();
	RETURN_MM();

}

void zephir_init_static_properties_Toml_Lexer(TSRMLS_D) {

	zval _1;
	zval _0, _2, _3, _4, _5, _6, _7;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, 21);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 19);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 8);
	zephir_array_fast_append(&_0, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("LiteralStringList"), &_0);
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 4, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 11);
	zephir_array_fast_append(&_2, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 21);
	zephir_array_fast_append(&_2, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 19);
	zephir_array_fast_append(&_2, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 6);
	zephir_array_fast_append(&_2, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("BasicStringList"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 9, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 11);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 2);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 3);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 22);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 5);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 6);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 8);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 18);
	zephir_array_fast_append(&_3, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 19);
	zephir_array_fast_append(&_3, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("FullList"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 11);
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 18);
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 5);
	zephir_array_fast_append(&_4, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("BriefList"), &_4);
	ZEPHIR_INIT_VAR(&_5);
	zephir_create_array(&_5, 20, 0 TSRMLS_CC);
	add_index_stringl(&_5, 1, SL("/^(=)/"));
	add_index_stringl(&_5, 2, SL("/^(true|false)/"));
	add_index_stringl(&_5, 3, SL("/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/"));
	add_index_stringl(&_5, 22, SL("/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/"));
	add_index_stringl(&_5, 5, SL("/^([+-]?(\\d_?)+)/"));
	add_index_stringl(&_5, 6, SL("/^(\"\"\")/"));
	add_index_stringl(&_5, 7, SL("/^(\")/"));
	add_index_stringl(&_5, 8, SL("/^(\'\'\')/"));
	add_index_stringl(&_5, 9, SL("/^(\')/"));
	add_index_stringl(&_5, 23, SL("/^(#)/"));
	add_index_stringl(&_5, 11, SL("/^(\\s+)/"));
	add_index_stringl(&_5, 12, SL("/^(\\[)/"));
	add_index_stringl(&_5, 13, SL("/^(\\])/"));
	add_index_stringl(&_5, 14, SL("/^(\\{)/"));
	add_index_stringl(&_5, 15, SL("/^(\\})/"));
	add_index_stringl(&_5, 16, SL("/^(,)/"));
	add_index_stringl(&_5, 17, SL("/^(\\.)/"));
	add_index_stringl(&_5, 18, SL("/^([-A-Z_a-z0-9]+)/"));
	add_index_stringl(&_5, 19, SL("/^(\\\\(b|t|n|f|r|\"|\\\\|u[0-9AaBbCcDdEeFf]{4,4}|U[0-9AaBbCcDdEeFf]{8,8}))/"));
	add_index_stringl(&_5, 21, SL("/^([\\x{20}-\\x{21}\\x{23}-\\x{26}\\x{28}-\\x{5A}\\x{5E}-\\x{10FFFF}]+)/u"));
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("Regex"), &_5);
	ZEPHIR_INIT_VAR(&_6);
	zephir_create_array(&_6, 11, 0 TSRMLS_CC);
	add_assoc_long_ex(&_6, SL("="), 1);
	add_assoc_long_ex(&_6, SL("["), 12);
	add_assoc_long_ex(&_6, SL("]"), 13);
	add_assoc_long_ex(&_6, SL("."), 17);
	add_assoc_long_ex(&_6, SL(","), 16);
	add_assoc_long_ex(&_6, SL("{"), 14);
	add_assoc_long_ex(&_6, SL("}"), 15);
	add_assoc_long_ex(&_6, SL("\""), 7);
	add_assoc_long_ex(&_6, SL("'"), 9);
	add_assoc_long_ex(&_6, SL("#"), 23);
	add_assoc_long_ex(&_6, SL("\\"), 20);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("Singles"), &_6);
	ZEPHIR_INIT_VAR(&_7);
	zephir_create_array(&_7, 25, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BAD");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EQUAL");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BOOLEAN");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DATE_TIME");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EOS");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_INTEGER");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_QUOTATION_MARK");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_QUOTATION_MARK");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_APOSTROPHE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_APOSTROPHE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_NEWLINE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_SPACE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_SQUARE_BRACE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_SQUARE_BRACE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_CURLY_BRACE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_CURLY_BRACE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_COMMA");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DOT");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_UNQUOTED_KEY");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPED_CHARACTER");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPE");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BASIC_UNESCAPED");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_FLOAT");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_HASH");
	zephir_array_fast_append(&_7, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_CHAR");
	zephir_array_fast_append(&_7, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("_nameList"), &_7);
	ZEPHIR_MM_RESTORE();

}

