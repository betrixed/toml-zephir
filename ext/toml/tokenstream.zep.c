
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Toml_TokenStream) {

	ZEPHIR_REGISTER_CLASS(Toml, TokenStream, toml, tokenstream, toml_tokenstream_method_entry, 0);

	zend_declare_property_null(toml_tokenstream_ce, SL("_lines"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_lineCount"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_curLine"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_id"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_value"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_lineNo"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_tokenLine"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_isSingle"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_offset"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_regex"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_singles"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_unknownId"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_newLineId"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_eosId"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenstream_ce, SL("_token"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Toml_TokenStream, __construct) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, toml_token_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 63);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_token"), &_0);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_TokenStream, setEOSId) {

	zval *id_param = NULL, _0;
	zend_long id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &id_param);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	id = Z_LVAL_P(id_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, id);
	zephir_update_property_zval(this_ptr, SL("_eosId"), &_0);

}

PHP_METHOD(Toml_TokenStream, setNewLineId) {

	zval *id_param = NULL, _0;
	zend_long id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &id_param);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	id = Z_LVAL_P(id_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, id);
	zephir_update_property_zval(this_ptr, SL("_newLineId"), &_0);

}

PHP_METHOD(Toml_TokenStream, setUnknownId) {

	zval *id_param = NULL, _0;
	zend_long id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &id_param);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	id = Z_LVAL_P(id_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, id);
	zephir_update_property_zval(this_ptr, SL("_unknownId"), &_0);

}

/**
 * Return current expression set object
 */
PHP_METHOD(Toml_TokenStream, getExpSet) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_regex");

}

/**
 * Argument is reference to associative array[int] of string regular expressions
 * @param array $ref
 */
PHP_METHOD(Toml_TokenStream, setExpSet) {

	zval *obj, obj_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&obj_sub);

	zephir_fetch_params(0, 1, 0, &obj);



	zephir_update_property_zval(this_ptr, SL("_regex"), obj);

}

/** 
 * For lookup of tokenId of single character string
 * Argument is reference to associative array[string] of int 
 * @param array $ref
 */
PHP_METHOD(Toml_TokenStream, setSingles) {

	zval *ref, ref_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ref_sub);

	zephir_fetch_params(0, 1, 0, &ref);



	zephir_update_property_zval(this_ptr, SL("_singles"), ref);

}

PHP_METHOD(Toml_TokenStream, setInput) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, boxme, _0;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&boxme);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &input_param);

	if (UNEXPECTED(Z_TYPE_P(input_param) != IS_STRING && Z_TYPE_P(input_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'input' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(input_param) == IS_STRING)) {
		zephir_get_strval(&input, input_param);
	} else {
		ZEPHIR_INIT_VAR(&input);
		ZVAL_EMPTY_STRING(&input);
	}


	ZEPHIR_INIT_VAR(&boxme);
	object_init_ex(&boxme, toml_box_ce);
	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_explode_str(&_0, SL("\n"), &input, LONG_MAX TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, &boxme, "__construct", NULL, 64, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setlines", NULL, 0, &boxme);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_TokenStream, getLine) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_tokenLine");

}

PHP_METHOD(Toml_TokenStream, hasPendingTokens) {

	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);


	zephir_read_property(&_0, this_ptr, SL("_id"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(!ZEPHIR_IS_EQUAL(&_0, &_1));

}

/**
 * Get all token details of parse step
 * @return \Yosy\Token
 */
PHP_METHOD(Toml_TokenStream, getToken) {

	zval token, _0, _1, _2, _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&token);
	zephir_read_property(&token, this_ptr, SL("_token"), PH_NOISY_CC);
	zephir_read_property(&_0, this_ptr, SL("_value"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("_id"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("_tokenLine"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_3, this_ptr, SL("_isSingle"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &token, "set", NULL, 0, &_0, &_1, &_2, &_3);
	zephir_check_call_status();
	RETURN_CCTOR(&token);

}

/**
 * Return the current token value, do next parse step
 * @return string
 */
PHP_METHOD(Toml_TokenStream, getValue) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_value");

}

/**
 * Fetch the internal token id without advancing parse
 */
PHP_METHOD(Toml_TokenStream, getTokenId) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_id");

}

/** 
 * This sets the parse state to before the first line.
 * To get the first token, call moveNextId
 */
PHP_METHOD(Toml_TokenStream, setLines) {

	zval *boxed, boxed_sub, ct, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&boxed_sub);
	ZVAL_UNDEF(&ct);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &boxed);



	zephir_read_property(&_0, boxed, SL("_me"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&ct);
	ZVAL_LONG(&ct, zephir_fast_count_int(&_0 TSRMLS_CC));
	zephir_update_property_zval(this_ptr, SL("_lines"), boxed);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, 0);
	zephir_update_property_zval(this_ptr, SL("_lineNo"), &_1);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, 0);
	zephir_update_property_zval(this_ptr, SL("_offset"), &_1);
	zephir_update_property_zval(this_ptr, SL("_lineCount"), &ct);
	ZEPHIR_INIT_VAR(&_2);
	if (ZEPHIR_GT_LONG(&ct, 0)) {
		zephir_read_property(&_1, boxed, SL("_me"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_NVAR(&_2);
		zephir_array_fetch_long(&_2, &_1, 0, PH_NOISY, "toml/TokenStream.zep", 119 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_NULL(&_2);
	}
	zephir_update_property_zval(this_ptr, SL("_curLine"), &_2);
	ZEPHIR_MM_RESTORE();

}

/** Return the single character at the front of the parse. 
 *  Does not alter this objects internal state values,
 *  except for properties of Token, which must be treated as read-only. 
 *  Maybe can use this to 'predict' the next expression set to use.
 *  Return "value" and single character TokenId in the Token.
 *  Cannot return tokenId for multi-character regular expressions,
 *  which is the whole idea.
 */
PHP_METHOD(Toml_TokenStream, peekToken) {

	zend_long ZEPHIR_LAST_CALL_STATUS, nextLine = 0;
	zval __$true, __$false, test, token, uni, _6, _7, _8, _0$$3, _1$$3, _2$$4, _3$$4, _4$$5, _5$$5, _9$$6, _10$$7, _11$$7, _12$$7;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&uni);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_12$$7);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&test);
	zephir_read_property(&test, this_ptr, SL("_curLine"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(&token);
	zephir_read_property(&token, this_ptr, SL("_token"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(&test)) {
		ZEPHIR_OBS_VAR(&_0$$3);
		zephir_read_property(&_0$$3, this_ptr, SL("_lineNo"), PH_NOISY_CC);
		nextLine = (zephir_get_intval(&_0$$3) + 1);
		ZEPHIR_INIT_ZVAL_NREF(_1$$3);
		ZVAL_LONG(&_1$$3, nextLine);
		zephir_update_property_zval(&token, SL("line"), &_1$$3);
		if (1) {
			zephir_update_property_zval(&token, SL("isSingle"), &__$true);
		} else {
			zephir_update_property_zval(&token, SL("isSingle"), &__$false);
		}
		zephir_read_property(&_1$$3, this_ptr, SL("_lineCount"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_GT_LONG(&_1$$3, nextLine)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_INIT_NVAR(&_2$$4);
			ZVAL_STRING(&_2$$4, "");
			zephir_update_property_zval(&token, SL("value"), &_2$$4);
			zephir_read_property(&_3$$4, this_ptr, SL("_newLineId"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(&token, SL("id"), &_3$$4);
		} else {
			ZEPHIR_INIT_VAR(&_4$$5);
			ZEPHIR_INIT_NVAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "");
			zephir_update_property_zval(&token, SL("value"), &_4$$5);
			zephir_read_property(&_5$$5, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(&token, SL("id"), &_5$$5);
		}
		RETURN_CCTOR(&token);
	}
	ZVAL_LONG(&_6, 0);
	ZVAL_LONG(&_7, 1);
	ZEPHIR_CALL_FUNCTION(&uni, "mb_substr", NULL, 65, &test, &_6, &_7);
	zephir_check_call_status();
	zephir_update_property_zval(&token, SL("value"), &uni);
	zephir_read_property(&_6, this_ptr, SL("_tokenLine"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(&token, SL("line"), &_6);
	zephir_read_property(&_7, this_ptr, SL("_singles"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_8, &_7, "offsetexists", NULL, 0, &uni);
	zephir_check_call_status();
	if (!(zephir_is_true(&_8))) {
		zephir_read_property(&_9$$6, this_ptr, SL("_unknownId"), PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval(&token, SL("id"), &_9$$6);
		if (0) {
			zephir_update_property_zval(&token, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(&token, SL("_isSingle"), &__$false);
		}
	} else {
		zephir_read_property(&_10$$7, this_ptr, SL("_singles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_11$$7, &_10$$7, "offsetget", NULL, 0, &uni);
		zephir_check_call_status();
		ZEPHIR_INIT_ZVAL_NREF(_12$$7);
		ZVAL_LONG(&_12$$7, zephir_get_intval(&_11$$7));
		zephir_update_property_zval(&token, SL("id"), &_12$$7);
		if (1) {
			zephir_update_property_zval(&token, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(&token, SL("_isSingle"), &__$false);
		}
	}
	RETURN_CCTOR(&token);

}

/**
 * If a peekNextChar has been done, this uses internal Token values to 
 * advance the parse (namely the string length of the value),
 * on the current line. It is important that token values have not been altered,
 * and parse position has not been altered prior to calling this method.
 * 
 * A call to getToken, will still return same values as the Token;
 */
PHP_METHOD(Toml_TokenStream, acceptToken) {

	zend_long takeoff = 0, nextLine$$4 = 0;
	zval token, _0, _1, _2, _3, _4, _16, _17, _18, _19, _20, _21, _22, _23, _5$$3, _6$$3, _7$$4, _8$$4, _9$$4, _10$$4, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&token);
	zephir_read_property(&token, this_ptr, SL("_token"), PH_NOISY_CC);
	zephir_read_property(&_0, &token, SL("id"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, &token, SL("id"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_3, this_ptr, SL("_newLineId"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_4, this_ptr, SL("_offset"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_INIT_NVAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "");
		zephir_update_property_zval(this_ptr, SL("_value"), &_5$$3);
		zephir_read_property(&_6$$3, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval(this_ptr, SL("_id"), &_6$$3);
		RETURN_MM_NULL();
	} else if (ZEPHIR_IS_IDENTICAL(&_2, &_3)) {
		ZEPHIR_OBS_VAR(&_7$$4);
		zephir_read_property(&_7$$4, this_ptr, SL("_lineNo"), PH_NOISY_CC);
		nextLine$$4 = (zephir_get_intval(&_7$$4) + 1);
		zephir_read_property(&_8$$4, this_ptr, SL("_lines"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_9$$4, &_8$$4, SL("_me"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_10$$4, &_9$$4, nextLine$$4, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 187 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("_curLine"), &_10$$4);
		ZEPHIR_INIT_ZVAL_NREF(_11$$4);
		ZVAL_LONG(&_11$$4, 0);
		zephir_update_property_zval(this_ptr, SL("_offset"), &_11$$4);
		ZEPHIR_INIT_VAR(&_12$$4);
		ZEPHIR_INIT_NVAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "");
		zephir_update_property_zval(this_ptr, SL("_value"), &_12$$4);
		zephir_read_property(&_11$$4, this_ptr, SL("_newLineId"), PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval(this_ptr, SL("_id"), &_11$$4);
		ZEPHIR_INIT_ZVAL_NREF(_13$$4);
		ZVAL_LONG(&_13$$4, nextLine$$4);
		zephir_update_property_zval(this_ptr, SL("_lineNo"), &_13$$4);
		RETURN_MM_NULL();
	} else if (ZEPHIR_IS_LONG_IDENTICAL(&_4, 0)) {
		zephir_read_property(&_14$$5, this_ptr, SL("_lineNo"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_ZVAL_NREF(_15$$5);
		ZVAL_LONG(&_15$$5, (zephir_get_numberval(&_14$$5) + 1));
		zephir_update_property_zval(this_ptr, SL("_tokenLine"), &_15$$5);
	}
	zephir_read_property(&_16, &token, SL("value"), PH_NOISY_CC | PH_READONLY);
	takeoff = zephir_fast_strlen_ev(&_16);
	zephir_read_property(&_17, this_ptr, SL("_curLine"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_18, takeoff);
	ZEPHIR_INIT_VAR(&_19);
	zephir_substr(&_19, &_17, zephir_get_intval(&_18), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_update_property_zval(this_ptr, SL("_curLine"), &_19);
	zephir_read_property(&_20, this_ptr, SL("_offset"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_ZVAL_NREF(_21);
	ZVAL_LONG(&_21, (zephir_get_numberval(&_20) + takeoff));
	zephir_update_property_zval(this_ptr, SL("_offset"), &_21);
	zephir_read_property(&_21, &token, SL("id"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_id"), &_21);
	zephir_read_property(&_22, &token, SL("isSingle"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_isSingle"), &_22);
	zephir_read_property(&_23, &token, SL("value"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_value"), &_23);
	RETURN_MM_NULL();

}

/**
 * Try regular expression, and return capture, if any.
 * Assumes previous peekToken returned a known token.
 * Leaves tokenId as unknownId.
 * 
 * @param string $pattern 
 * @return boolean , true if match found
 * Pattern must be such that preg_match can return match
 *  array with 2 items.
 *  If returns true, then getValue() returns the capture.
 */
PHP_METHOD(Toml_TokenStream, moveRegex) {

	zend_long takeOff = 0;
	zval *pattern_param = NULL, __$true, __$false, test, matches, _0, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3;
	zval pattern;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &pattern_param);

	if (UNEXPECTED(Z_TYPE_P(pattern_param) != IS_STRING && Z_TYPE_P(pattern_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'pattern' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(pattern_param) == IS_STRING)) {
		zephir_get_strval(&pattern, pattern_param);
	} else {
		ZEPHIR_INIT_VAR(&pattern);
		ZVAL_EMPTY_STRING(&pattern);
	}


	ZEPHIR_OBS_VAR(&test);
	zephir_read_property(&test, this_ptr, SL("_curLine"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&matches);
	ZVAL_NULL(&matches);
	ZEPHIR_INIT_VAR(&_0);
	zephir_preg_match(&_0, &pattern, &test, &matches, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_0)) {
		zephir_array_fetch_long(&_1$$3, &matches, 1, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 225 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("_value"), &_1$$3);
		if (0) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
		zephir_read_property(&_2$$3, this_ptr, SL("_unknownId"), PH_NOISY_CC | PH_READONLY);
		zephir_update_property_zval(this_ptr, SL("_id"), &_2$$3);
		zephir_array_fetch_long(&_3$$3, &matches, 0, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 228 TSRMLS_CC);
		takeOff = zephir_fast_strlen_ev(&_3$$3);
		zephir_read_property(&_4$$3, this_ptr, SL("_offset"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_ZVAL_NREF(_5$$3);
		ZVAL_LONG(&_5$$3, (zephir_get_numberval(&_4$$3) + takeOff));
		zephir_update_property_zval(this_ptr, SL("_offset"), &_5$$3);
		ZVAL_LONG(&_5$$3, takeOff);
		ZEPHIR_INIT_VAR(&_6$$3);
		zephir_substr(&_6$$3, &test, zephir_get_intval(&_5$$3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_update_property_zval(this_ptr, SL("_curLine"), &_6$$3);
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/** 
 * Advance the parse then return the internal token id.
 */
PHP_METHOD(Toml_TokenStream, moveNextId) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_regex"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "parsenextid", NULL, 66, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Set up the internal current token values, from the current parse
 * position in the line, and move the parse position to the next. Return
 * a token id.
 * Returned token id may be a NEWLINE or EOS, before the
 * $patterns are checked. If neither NEWLINE, EOS, or any of the 
 * $patterns match, the next unicode character is checked against the
 * assigned Singles table, and its token id is returned, or else
 * the character value is assigned the UnknownId
 * @param \Yosy\KeyTable $patterns
 * @return int
 */
PHP_METHOD(Toml_TokenStream, parseNextId) {

	zend_string *_18;
	zend_ulong _17;
	zend_long ZEPHIR_LAST_CALL_STATUS, takeoff = 0, nextLine = 0, tid = 0;
	zval *patterns, patterns_sub, __$true, __$false, __$null, id, pattern, uni, test, _0, _1, _14, _15, *_16, _25, _26, _27, _28, _32, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _7$$4, _8$$4, _9$$4, _10$$5, _11$$5, _12$$6, _13$$6, matches$$7, _19$$7, _20$$8, _21$$8, _22$$8, _23$$8, _24$$8, _29$$9, _30$$10, _31$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&patterns_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&uni);
	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&matches$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_31$$10);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &patterns);



	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_curLine"), PH_NOISY_CC);
	zephir_read_property(&_1, this_ptr, SL("_offset"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		zephir_read_property(&_2$$3, this_ptr, SL("_lineNo"), PH_NOISY_CC | PH_READONLY);
		nextLine = (zephir_get_numberval(&_2$$3) + 1);
		zephir_read_property(&_3$$3, this_ptr, SL("_lineCount"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_GT_LONG(&_3$$3, nextLine)) {
			zephir_read_property(&_4$$4, this_ptr, SL("_lines"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_5$$4, &_4$$4, SL("_me"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_long(&_6$$4, &_5$$4, nextLine, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 270 TSRMLS_CC);
			zephir_update_property_zval(this_ptr, SL("_curLine"), &_6$$4);
			ZEPHIR_INIT_ZVAL_NREF(_7$$4);
			ZVAL_LONG(&_7$$4, 0);
			zephir_update_property_zval(this_ptr, SL("_offset"), &_7$$4);
			ZEPHIR_INIT_VAR(&_8$$4);
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZVAL_STRING(&_8$$4, "\n");
			zephir_update_property_zval(this_ptr, SL("_value"), &_8$$4);
			zephir_read_property(&_7$$4, this_ptr, SL("_newLineId"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(this_ptr, SL("_id"), &_7$$4);
			ZEPHIR_INIT_ZVAL_NREF(_9$$4);
			ZVAL_LONG(&_9$$4, nextLine);
			zephir_update_property_zval(this_ptr, SL("_lineNo"), &_9$$4);
		} else {
			ZEPHIR_INIT_VAR(&_10$$5);
			ZEPHIR_INIT_NVAR(&_10$$5);
			ZVAL_STRING(&_10$$5, "");
			zephir_update_property_zval(this_ptr, SL("_value"), &_10$$5);
			zephir_read_property(&_11$$5, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(this_ptr, SL("_id"), &_11$$5);
		}
		if (1) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
		RETURN_MM_MEMBER(getThis(), "_id");
	} else if (ZEPHIR_IS_LONG(&_1, 0)) {
		zephir_read_property(&_12$$6, this_ptr, SL("_lineNo"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_ZVAL_NREF(_13$$6);
		ZVAL_LONG(&_13$$6, (zephir_get_numberval(&_12$$6) + 1));
		zephir_update_property_zval(this_ptr, SL("_tokenLine"), &_13$$6);
	}
	ZEPHIR_OBS_VAR(&test);
	zephir_read_property(&test, this_ptr, SL("_curLine"), PH_NOISY_CC);
	zephir_update_property_zval(this_ptr, SL("_curLine"), &__$null);
	zephir_read_property(&_14, this_ptr, SL("_regex"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_15, &_14, SL("_store"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_15, 0, "toml/TokenStream.zep", 310);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_15), _17, _18, _16)
	{
		ZEPHIR_INIT_NVAR(&id);
		if (_18 != NULL) { 
			ZVAL_STR_COPY(&id, _18);
		} else {
			ZVAL_LONG(&id, _17);
		}
		ZEPHIR_INIT_NVAR(&pattern);
		ZVAL_COPY(&pattern, _16);
		ZEPHIR_INIT_NVAR(&matches$$7);
		ZVAL_NULL(&matches$$7);
		ZEPHIR_INIT_NVAR(&_19$$7);
		zephir_preg_match(&_19$$7, &pattern, &test, &matches$$7, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(&_19$$7)) {
			zephir_array_fetch_long(&_20$$8, &matches$$7, 1, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 293 TSRMLS_CC);
			zephir_update_property_zval(this_ptr, SL("_value"), &_20$$8);
			zephir_update_property_zval(this_ptr, SL("_id"), &id);
			if (0) {
				zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
			} else {
				zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
			}
			zephir_read_property(&_21$$8, this_ptr, SL("_tokenLine"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(this_ptr, SL("_line"), &_21$$8);
			zephir_array_fetch_long(&_22$$8, &matches$$7, 0, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 298 TSRMLS_CC);
			takeoff = zephir_fast_strlen_ev(&_22$$8);
			ZEPHIR_INIT_ZVAL_NREF(_23$$8);
			ZVAL_LONG(&_23$$8, takeoff);
			zephir_update_property_zval(this_ptr, SL("_offset"), &_23$$8);
			ZVAL_LONG(&_23$$8, takeoff);
			ZEPHIR_INIT_NVAR(&_24$$8);
			zephir_substr(&_24$$8, &test, zephir_get_intval(&_23$$8), 0, ZEPHIR_SUBSTR_NO_LENGTH);
			zephir_update_property_zval(this_ptr, SL("_curLine"), &_24$$8);
			RETURN_MM_MEMBER(getThis(), "_id");
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&pattern);
	ZEPHIR_INIT_NVAR(&id);
	ZVAL_LONG(&_25, 0);
	ZVAL_LONG(&_26, 1);
	ZEPHIR_CALL_FUNCTION(&uni, "mb_substr", NULL, 65, &test, &_25, &_26);
	zephir_check_call_status();
	takeoff = zephir_fast_strlen_ev(&uni);
	ZEPHIR_INIT_ZVAL_NREF(_25);
	ZVAL_LONG(&_25, takeoff);
	zephir_update_property_zval(this_ptr, SL("_offset"), &_25);
	ZVAL_LONG(&_25, takeoff);
	ZEPHIR_INIT_VAR(&_27);
	zephir_substr(&_27, &test, zephir_get_intval(&_25), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_update_property_zval(this_ptr, SL("_curLine"), &_27);
	zephir_update_property_zval(this_ptr, SL("_value"), &uni);
	zephir_read_property(&_26, this_ptr, SL("_singles"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_28, &_26, "offsetexists", NULL, 0, &uni);
	zephir_check_call_status();
	if (!(zephir_is_true(&_28))) {
		ZEPHIR_OBS_VAR(&_29$$9);
		zephir_read_property(&_29$$9, this_ptr, SL("_unknownId"), PH_NOISY_CC);
		tid = zephir_get_intval(&_29$$9);
		if (0) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
	} else {
		zephir_read_property(&_30$$10, this_ptr, SL("_singles"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_31$$10, &_30$$10, "offsetget", NULL, 0, &uni);
		zephir_check_call_status();
		tid = zephir_get_intval(&_31$$10);
		if (1) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
	}
	ZEPHIR_INIT_ZVAL_NREF(_32);
	ZVAL_LONG(&_32, tid);
	zephir_update_property_zval(this_ptr, SL("_id"), &_32);
	RETURN_MM_LONG(tid);

}

