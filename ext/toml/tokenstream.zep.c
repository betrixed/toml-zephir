
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

	zend_declare_property_null(toml_tokenstream_ce, SL("_matches"), ZEND_ACC_PROTECTED TSRMLS_CC);

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
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 12);
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
 * Argument is reference to associative array[int] of string regular expressions
 * @param array $ref
 */
PHP_METHOD(Toml_TokenStream, setExpList) {

	zval *ref, ref_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ref_sub);

	zephir_fetch_params(0, 1, 0, &ref);



	zephir_update_property_zval(this_ptr, SL("_regex"), ref);

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
	ZEPHIR_CALL_METHOD(NULL, &boxme, "__construct", NULL, 13, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setlines", NULL, 0, &boxme);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

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

	zval *lines, lines_sub, _0, _1, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&lines_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &lines);



	zephir_update_property_zval(this_ptr, SL("_lines"), lines);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval(this_ptr, SL("_lineNo"), &_0);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval(this_ptr, SL("_offset"), &_0);
	zephir_read_property(&_0, lines, SL("_me"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, zephir_fast_count_int(&_0 TSRMLS_CC));
	zephir_update_property_zval(this_ptr, SL("_lineCount"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	zephir_read_property(&_1, this_ptr, SL("_lineCount"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_GT_LONG(&_1, 0)) {
		zephir_read_property(&_3, lines, SL("_me"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_NVAR(&_2);
		zephir_array_fetch_long(&_2, &_3, 0, PH_NOISY, "toml/TokenStream.zep", 105 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_NULL(&_2);
	}
	zephir_update_property_zval(this_ptr, SL("_curLine"), &_2);
	ZEPHIR_MM_RESTORE();

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
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "parsenextid", NULL, 14, &_0);
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

	zend_string *_17;
	zend_ulong _16;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *patterns, patterns_sub, __$true, __$false, id, pattern, takeoff, matches, nextLine, tid, uni, _0, _1, _13, _14, *_15, _25, _26, _27, _28, _29, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _7$$4, _8$$4, _9$$5, _10$$5, _11$$6, _12$$6, _18$$7, _19$$7, _20$$8, _21$$8, _22$$8, _23$$8, _24$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&patterns_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&takeoff);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&nextLine);
	ZVAL_UNDEF(&tid);
	ZVAL_UNDEF(&uni);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &patterns);



	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_curLine"), PH_NOISY_CC);
	zephir_read_property(&_1, this_ptr, SL("_offset"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		zephir_read_property(&_2$$3, this_ptr, SL("_lineNo"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&nextLine);
		ZVAL_LONG(&nextLine, (zephir_get_numberval(&_2$$3) + 1));
		zephir_read_property(&_3$$3, this_ptr, SL("_lineCount"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_LT(&nextLine, &_3$$3)) {
			zephir_read_property(&_4$$4, this_ptr, SL("_lines"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_5$$4, &_4$$4, SL("_me"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_6$$4, &_5$$4, &nextLine, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 138 TSRMLS_CC);
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
			zephir_update_property_zval(this_ptr, SL("_lineNo"), &nextLine);
		} else {
			ZEPHIR_INIT_VAR(&_9$$5);
			ZEPHIR_INIT_NVAR(&_9$$5);
			ZVAL_STRING(&_9$$5, "");
			zephir_update_property_zval(this_ptr, SL("_value"), &_9$$5);
			zephir_read_property(&_10$$5, this_ptr, SL("_eosId"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(this_ptr, SL("_id"), &_10$$5);
		}
		if (1) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
		RETURN_MM_MEMBER(getThis(), "_id");
	} else if (ZEPHIR_IS_LONG(&_1, 0)) {
		zephir_read_property(&_11$$6, this_ptr, SL("_lineNo"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_ZVAL_NREF(_12$$6);
		ZVAL_LONG(&_12$$6, (zephir_get_numberval(&_11$$6) + 1));
		zephir_update_property_zval(this_ptr, SL("_tokenLine"), &_12$$6);
	}
	zephir_read_property(&_13, this_ptr, SL("_regex"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_14, &_13, SL("_store"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_14, 0, "toml/TokenStream.zep", 171);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_14), _16, _17, _15)
	{
		ZEPHIR_INIT_NVAR(&id);
		if (_17 != NULL) { 
			ZVAL_STR_COPY(&id, _17);
		} else {
			ZVAL_LONG(&id, _16);
		}
		ZEPHIR_INIT_NVAR(&pattern);
		ZVAL_COPY(&pattern, _15);
		ZEPHIR_INIT_NVAR(&_18$$7);
		zephir_read_property(&_19$$7, this_ptr, SL("_curLine"), PH_NOISY_CC | PH_READONLY);
		zephir_preg_match(&_18$$7, &pattern, &_19$$7, &matches, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(&_18$$7)) {
			zephir_array_fetch_long(&_20$$8, &matches, 1, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 157 TSRMLS_CC);
			zephir_update_property_zval(this_ptr, SL("_value"), &_20$$8);
			zephir_update_property_zval(this_ptr, SL("_id"), &id);
			if (0) {
				zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
			} else {
				zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
			}
			zephir_read_property(&_21$$8, this_ptr, SL("_tokenLine"), PH_NOISY_CC | PH_READONLY);
			zephir_update_property_zval(this_ptr, SL("_line"), &_21$$8);
			zephir_array_fetch_long(&_22$$8, &matches, 1, PH_NOISY | PH_READONLY, "toml/TokenStream.zep", 162 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&takeoff);
			ZVAL_LONG(&takeoff, zephir_fast_strlen_ev(&_22$$8));
			zephir_update_property_zval(this_ptr, SL("_offset"), &takeoff);
			zephir_read_property(&_23$$8, this_ptr, SL("_curLine"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_NVAR(&_24$$8);
			zephir_substr(&_24$$8, &_23$$8, zephir_get_intval(&takeoff), 0, ZEPHIR_SUBSTR_NO_LENGTH);
			zephir_update_property_zval(this_ptr, SL("_curLine"), &_24$$8);
			RETURN_MM_MEMBER(getThis(), "_id");
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&pattern);
	ZEPHIR_INIT_NVAR(&id);
	zephir_read_property(&_25, this_ptr, SL("_curLine"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_26, 0);
	ZVAL_LONG(&_27, 1);
	ZEPHIR_CALL_FUNCTION(&uni, "mb_substr", NULL, 15, &_25, &_26, &_27);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&takeoff);
	ZVAL_LONG(&takeoff, zephir_fast_strlen_ev(&uni));
	zephir_update_property_zval(this_ptr, SL("_offset"), &takeoff);
	zephir_read_property(&_26, this_ptr, SL("_curLine"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_28);
	zephir_substr(&_28, &_26, zephir_get_intval(&takeoff), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_update_property_zval(this_ptr, SL("_curLine"), &_28);
	zephir_update_property_zval(this_ptr, SL("_value"), &uni);
	ZEPHIR_OBS_VAR(&tid);
	zephir_read_property(&_27, this_ptr, SL("_singles"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_29, &_27, SL("_store"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&tid, &_29, &uni, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(&tid);
		zephir_read_property(&tid, this_ptr, SL("_unknownId"), PH_NOISY_CC);
		if (0) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
	} else {
		if (1) {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
		}
	}
	zephir_update_property_zval(this_ptr, SL("_id"), &tid);
	RETURN_CCTOR(&tid);

}

