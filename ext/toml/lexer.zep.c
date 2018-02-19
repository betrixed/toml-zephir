
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
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Toml_Lexer) {

	ZEPHIR_REGISTER_CLASS(Toml, Lexer, toml, lexer, toml_lexer_method_entry, 0);

	zend_declare_property_null(toml_lexer_ce, SL("_nameList"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("Singles"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("_AllRegExp"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("_AllSingles"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

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

	zephir_declare_class_constant_string(toml_lexer_ce, SL("USE_VERSION"), "Zephir");

	return SUCCESS;

}

PHP_METHOD(Toml_Lexer, getTomlVersion) {

	zval *this_ptr = getThis();


	RETURN_STRING("0.4");

}

PHP_METHOD(Toml_Lexer, getUseVersion) {

	zval *this_ptr = getThis();


	RETURN_STRING("Zephir");

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
	zephir_array_fetch_long(&_2, &_1, tokenId, PH_NOISY | PH_READONLY, "toml/Lexer.zep", 116 TSRMLS_CC);
	RETURN_CTORW(&_2);

}

PHP_METHOD(Toml_Lexer, getExpSet) {

	zephir_fcall_cache_entry *_2 = NULL, *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *idList_param = NULL, all, result, id, *_0, _1$$3;
	zval idList;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&idList);
	ZVAL_UNDEF(&all);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &idList_param);

	ZEPHIR_OBS_COPY_OR_DUP(&idList, idList_param);


	ZEPHIR_CALL_SELF(&all, "getallregex", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	object_init_ex(&result, toml_keytable_ce);
	ZEPHIR_CALL_METHOD(NULL, &result, "__construct", NULL, 2);
	zephir_check_call_status();
	zephir_is_iterable(&idList, 0, "toml/Lexer.zep", 130);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&idList), _0)
	{
		ZEPHIR_INIT_NVAR(&id);
		ZVAL_COPY(&id, _0);
		ZEPHIR_CALL_METHOD(&_1$$3, &all, "offsetget", &_2, 3, &id);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &result, "offsetset", &_3, 4, &id, &_1$$3);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&id);
	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Lexer, getAllSingles) {

	zval _0, _15, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$3, _10$$3, _11$$3, _12$$3, _13$$3, _14$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);

	ZEPHIR_MM_GROW();

	zephir_read_static_property_ce(&_0, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, toml_keytable_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 2);
		zephir_check_call_status();
		zend_update_static_property(toml_lexer_ce, ZEND_STRL("_AllSingles"), &_1$$3);
		zephir_read_static_property_ce(&_2$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "=");
		ZVAL_LONG(&_3$$3, 1);
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "offsetset", NULL, 0, &_1$$3, &_3$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_3$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "[");
		ZVAL_LONG(&_4$$3, 12);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "offsetset", NULL, 0, &_1$$3, &_4$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_4$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "]");
		ZVAL_LONG(&_5$$3, 13);
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "offsetset", NULL, 0, &_1$$3, &_5$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_5$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, ".");
		ZVAL_LONG(&_6$$3, 17);
		ZEPHIR_CALL_METHOD(NULL, &_5$$3, "offsetset", NULL, 0, &_1$$3, &_6$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_6$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, ",");
		ZVAL_LONG(&_7$$3, 16);
		ZEPHIR_CALL_METHOD(NULL, &_6$$3, "offsetset", NULL, 0, &_1$$3, &_7$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_7$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "\"");
		ZVAL_LONG(&_8$$3, 7);
		ZEPHIR_CALL_METHOD(NULL, &_7$$3, "offsetset", NULL, 0, &_1$$3, &_8$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_8$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, ".");
		ZVAL_LONG(&_9$$3, 17);
		ZEPHIR_CALL_METHOD(NULL, &_8$$3, "offsetset", NULL, 0, &_1$$3, &_9$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_9$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "{");
		ZVAL_LONG(&_10$$3, 14);
		ZEPHIR_CALL_METHOD(NULL, &_9$$3, "offsetset", NULL, 0, &_1$$3, &_10$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_10$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "}");
		ZVAL_LONG(&_11$$3, 15);
		ZEPHIR_CALL_METHOD(NULL, &_10$$3, "offsetset", NULL, 0, &_1$$3, &_11$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_11$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "'");
		ZVAL_LONG(&_12$$3, 9);
		ZEPHIR_CALL_METHOD(NULL, &_11$$3, "offsetset", NULL, 0, &_1$$3, &_12$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_12$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "#");
		ZVAL_LONG(&_13$$3, 23);
		ZEPHIR_CALL_METHOD(NULL, &_12$$3, "offsetset", NULL, 0, &_1$$3, &_13$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_13$$3, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "\\");
		ZVAL_LONG(&_14$$3, 20);
		ZEPHIR_CALL_METHOD(NULL, &_13$$3, "offsetset", NULL, 0, &_1$$3, &_14$$3);
		zephir_check_call_status();
	}
	zephir_read_static_property_ce(&_15, toml_lexer_ce, SL("_AllSingles"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTOR(&_15);

}

PHP_METHOD(Toml_Lexer, getAllRegex) {

	zval _0, _23, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$3, _10$$3, _11$$3, _12$$3, _13$$3, _14$$3, _15$$3, _16$$3, _17$$3, _18$$3, _19$$3, _20$$3, _21$$3, _22$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_18$$3);
	ZVAL_UNDEF(&_19$$3);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_22$$3);

	ZEPHIR_MM_GROW();

	zephir_read_static_property_ce(&_0, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, toml_keytable_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 2);
		zephir_check_call_status();
		zend_update_static_property(toml_lexer_ce, ZEND_STRL("_AllRegExp"), &_1$$3);
		zephir_read_static_property_ce(&_2$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_3$$3, 1);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(=)/");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "offsetset", NULL, 0, &_3$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_3$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_4$$3, 2);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(true|false)/");
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "offsetset", NULL, 0, &_4$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_4$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_5$$3, 3);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "offsetset", NULL, 0, &_5$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_5$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_6$$3, 22);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/");
		ZEPHIR_CALL_METHOD(NULL, &_5$$3, "offsetset", NULL, 0, &_6$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_6$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_7$$3, 5);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^([+-]?(\\d_?)+)/");
		ZEPHIR_CALL_METHOD(NULL, &_6$$3, "offsetset", NULL, 0, &_7$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_7$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_8$$3, 6);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\"\"\")/");
		ZEPHIR_CALL_METHOD(NULL, &_7$$3, "offsetset", NULL, 0, &_8$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_8$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_9$$3, 7);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\")/");
		ZEPHIR_CALL_METHOD(NULL, &_8$$3, "offsetset", NULL, 0, &_9$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_9$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_10$$3, 8);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\'\\'\\')/");
		ZEPHIR_CALL_METHOD(NULL, &_9$$3, "offsetset", NULL, 0, &_10$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_10$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_11$$3, 9);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\')/");
		ZEPHIR_CALL_METHOD(NULL, &_10$$3, "offsetset", NULL, 0, &_11$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_11$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_12$$3, 23);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(#)/");
		ZEPHIR_CALL_METHOD(NULL, &_11$$3, "offsetset", NULL, 0, &_12$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_12$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_13$$3, 11);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\s+)/");
		ZEPHIR_CALL_METHOD(NULL, &_12$$3, "offsetset", NULL, 0, &_13$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_13$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_14$$3, 12);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\[)/");
		ZEPHIR_CALL_METHOD(NULL, &_13$$3, "offsetset", NULL, 0, &_14$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_14$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_15$$3, 13);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\])/");
		ZEPHIR_CALL_METHOD(NULL, &_14$$3, "offsetset", NULL, 0, &_15$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_15$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_16$$3, 14);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\{)/");
		ZEPHIR_CALL_METHOD(NULL, &_15$$3, "offsetset", NULL, 0, &_16$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_16$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_17$$3, 15);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\})/");
		ZEPHIR_CALL_METHOD(NULL, &_16$$3, "offsetset", NULL, 0, &_17$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_17$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_18$$3, 16);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(,)/");
		ZEPHIR_CALL_METHOD(NULL, &_17$$3, "offsetset", NULL, 0, &_18$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_18$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_19$$3, 17);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\.)/");
		ZEPHIR_CALL_METHOD(NULL, &_18$$3, "offsetset", NULL, 0, &_19$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_19$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_20$$3, 18);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^([-A-Z_a-z0-9]+)/");
		ZEPHIR_CALL_METHOD(NULL, &_19$$3, "offsetset", NULL, 0, &_20$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_20$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_21$$3, 19);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\\\(b|t|n|f|r|\"|\\\\|u[0-9AaBbCcDdEeFf]{4,4}|U[0-9AaBbCcDdEeFf]{8,8}))/");
		ZEPHIR_CALL_METHOD(NULL, &_20$$3, "offsetset", NULL, 0, &_21$$3, &_1$$3);
		zephir_check_call_status();
		zephir_read_static_property_ce(&_21$$3, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
		ZVAL_LONG(&_22$$3, 21);
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^([\\x{20}-\\x{21}\\x{23}-\\x{26}\\x{28}-\\x{5A}\\x{5E}-\\x{10FFFF}]+)/u");
		ZEPHIR_CALL_METHOD(NULL, &_21$$3, "offsetset", NULL, 0, &_22$$3, &_1$$3);
		zephir_check_call_status();
	}
	zephir_read_static_property_ce(&_23, toml_lexer_ce, SL("_AllRegExp"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTOR(&_23);

}

PHP_METHOD(Toml_Lexer, tokenize) {

	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, stream, list, _0, _1, _2, _3, _8, _9, _5$$3, _7$$3;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&stream);
	ZVAL_UNDEF(&list);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &input_param);

	zephir_get_strval(&input, input_param);


	ZEPHIR_INIT_VAR(&stream);
	object_init_ex(&stream, toml_tokenstream_ce);
	ZEPHIR_CALL_METHOD(NULL, &stream, "__construct", NULL, 5);
	zephir_check_call_status();
	ZEPHIR_CALL_SELF(&_0, "getallregex", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setexplist", NULL, 6, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_SELF(&_1, "getallsingles", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setsingles", NULL, 7, &_1);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 24);
	ZEPHIR_CALL_METHOD(NULL, &stream, "setunknownid", NULL, 8, &_2);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 10);
	ZEPHIR_CALL_METHOD(NULL, &stream, "setnewlineid", NULL, 9, &_2);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 4);
	ZEPHIR_CALL_METHOD(NULL, &stream, "seteosid", NULL, 10, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &stream, "setinput", NULL, 11, &input);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&list);
	array_init(&list);
	while (1) {
		ZEPHIR_CALL_METHOD(&_3, &stream, "movenextid", &_4, 12);
		zephir_check_call_status();
		if (!(!ZEPHIR_IS_LONG_IDENTICAL(&_3, 4))) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_5$$3, &stream, "gettoken", &_6, 13);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_clone(&_7$$3, &_5$$3 TSRMLS_CC) == FAILURE) {
			RETURN_MM();
		}
		zephir_array_append(&list, &_7$$3, PH_SEPARATE, "toml/Lexer.zep", 195);
	}
	ZEPHIR_CALL_METHOD(&_8, &stream, "gettoken", &_6, 13);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_9);
	if (zephir_clone(&_9, &_8 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_array_append(&list, &_9, PH_SEPARATE, "toml/Lexer.zep", 197);
	object_init_ex(return_value, toml_tokenlist_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 14, &list);
	zephir_check_call_status();
	RETURN_MM();

}

void zephir_init_static_properties_Toml_Lexer(TSRMLS_D) {

	zval _1;
	zval _0, _2, _3, _4, _5, _6;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
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
	zephir_create_array(&_5, 11, 0 TSRMLS_CC);
	add_assoc_long_ex(&_5, SL("="), 1);
	add_assoc_long_ex(&_5, SL("["), 12);
	add_assoc_long_ex(&_5, SL("]"), 13);
	add_assoc_long_ex(&_5, SL("."), 17);
	add_assoc_long_ex(&_5, SL(","), 16);
	add_assoc_long_ex(&_5, SL("{"), 14);
	add_assoc_long_ex(&_5, SL("}"), 15);
	add_assoc_long_ex(&_5, SL("\""), 7);
	add_assoc_long_ex(&_5, SL("'"), 9);
	add_assoc_long_ex(&_5, SL("#"), 23);
	add_assoc_long_ex(&_5, SL("\\"), 20);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("Singles"), &_5);
	ZEPHIR_INIT_VAR(&_6);
	zephir_create_array(&_6, 25, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BAD");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EQUAL");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BOOLEAN");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DATE_TIME");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EOS");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_INTEGER");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_QUOTATION_MARK");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_QUOTATION_MARK");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_APOSTROPHE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_APOSTROPHE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_NEWLINE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_SPACE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_SQUARE_BRACE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_SQUARE_BRACE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_CURLY_BRACE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_CURLY_BRACE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_COMMA");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DOT");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_UNQUOTED_KEY");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPED_CHARACTER");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPE");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BASIC_UNESCAPED");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_FLOAT");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_HASH");
	zephir_array_fast_append(&_6, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_CHAR");
	zephir_array_fast_append(&_6, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("_nameList"), &_6);
	ZEPHIR_MM_RESTORE();

}

