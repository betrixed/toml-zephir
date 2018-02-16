
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/file.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "ext/date/php_date.h"


/**
* Transcribed from a version adapated from Yosymfony/Toml 
* 
* @author Michael Rynn
*/
/**
 * Parser for TOML strings (specification version 0.4.0).
 *
 * @author Victor Puertas <vpgugr@vpgugr.com>
 */
ZEPHIR_INIT_CLASS(Toml_Parser) {

	ZEPHIR_REGISTER_CLASS(Toml, Parser, toml, parser, toml_parser_method_entry, 0);

	zend_declare_property_null(toml_parser_ce, SL("_root"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_table"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_ts"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_xid"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_expStack"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_briefExpressions"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_fullExpressions"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_basicString"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_literalString"), ZEND_ACC_PUBLIC TSRMLS_CC);

	toml_parser_ce->create_object = zephir_init_properties_Toml_Parser;
	zephir_declare_class_constant_long(toml_parser_ce, SL("E_KEYS"), 1);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_VALUES"), 2);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_LITERAL"), 3);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_BASIC"), 4);

	return SUCCESS;

}

PHP_METHOD(Toml_Parser, setExpMap) {

	zval *xid_param = NULL, _0$$3, _1$$3, _2$$4, _3$$4, _4$$5, _5$$5, _6$$6, _7$$6, _8;
	zend_long xid, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &xid_param);

	if (UNEXPECTED(Z_TYPE_P(xid_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'xid' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	xid = Z_LVAL_P(xid_param);


	do {
		if (xid == 1) {
			zephir_read_property(&_0$$3, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_1$$3, this_ptr, SL("_briefExpressions"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_0$$3, "setexpmap", NULL, 0, &_1$$3);
			zephir_check_call_status();
			break;
		}
		if (xid == 2) {
			zephir_read_property(&_2$$4, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_3$$4, this_ptr, SL("_fullExpressions"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "setexpmap", NULL, 0, &_3$$4);
			zephir_check_call_status();
			break;
		}
		if (xid == 3) {
			zephir_read_property(&_4$$5, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_5$$5, this_ptr, SL("_literalString"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_4$$5, "setexpmap", NULL, 0, &_5$$5);
			zephir_check_call_status();
			break;
		}
		if (xid == 4) {
			zephir_read_property(&_6$$6, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
			zephir_read_property(&_7$$6, this_ptr, SL("_basicString"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(NULL, &_6$$6, "setexpmap", NULL, 0, &_7$$6);
			zephir_check_call_status();
			break;
		}
		RETURN_MM_NULL();
	} while(0);

	ZEPHIR_INIT_ZVAL_NREF(_8);
	ZVAL_LONG(&_8, xid);
	zephir_update_property_zval(this_ptr, SL("_xid"), &_8);
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the expression set to the previous on the
 * expression set stack (a stack of integers) 
 */
PHP_METHOD(Toml_Parser, popExpMap) {

	zval xid, _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&xid);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_expStack"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_MAKE_REF(&_0);
	ZEPHIR_CALL_FUNCTION(&xid, "array_pop", NULL, 13, &_0);
	ZEPHIR_UNREF(&_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpmap", NULL, 14, &xid);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Push a known expression set defined by a 
 * constant
 * @param int $value
 */
PHP_METHOD(Toml_Parser, pushExpMap) {

	zval *xid_param = NULL, _0;
	zend_long xid, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &xid_param);

	if (UNEXPECTED(Z_TYPE_P(xid_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'xid' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	xid = Z_LVAL_P(xid_param);


	zephir_read_property(&_0, this_ptr, SL("_xid"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_array_append(this_ptr, SL("_expStack"), &_0 TSRMLS_CC);
	ZVAL_LONG(&_0, xid);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpmap", NULL, 14, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Everything that must be setup before calling setInput
 */
PHP_METHOD(Toml_Parser, __construct) {

	zval ts, _0, _2, _3, _4, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18;
	zephir_fcall_cache_entry *_1 = NULL, *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, toml_keytable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", &_1, 3);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_root"), &_0);
	zephir_read_property(&_2, this_ptr, SL("_root"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_table"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, toml_keytable_ce);
	zephir_read_static_property_ce(&_6, toml_lexer_ce, SL("BriefList"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_4, toml_lexer_ce, "getexpmap", &_5, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", &_1, 3, &_4);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_briefExpressions"), &_3);
	ZEPHIR_INIT_VAR(&_7);
	object_init_ex(&_7, toml_keytable_ce);
	zephir_read_static_property_ce(&_9, toml_lexer_ce, SL("FullList"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_8, toml_lexer_ce, "getexpmap", &_5, 0, &_9);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_7, "__construct", &_1, 3, &_8);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_fullExpressions"), &_7);
	ZEPHIR_INIT_VAR(&_10);
	object_init_ex(&_10, toml_keytable_ce);
	zephir_read_static_property_ce(&_12, toml_lexer_ce, SL("BasicStringList"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_11, toml_lexer_ce, "getexpmap", &_5, 0, &_12);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_10, "__construct", &_1, 3, &_11);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_basicString"), &_10);
	ZEPHIR_INIT_VAR(&_13);
	object_init_ex(&_13, toml_keytable_ce);
	zephir_read_static_property_ce(&_15, toml_lexer_ce, SL("LiteralStringList"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_14, toml_lexer_ce, "getexpmap", &_5, 0, &_15);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_13, "__construct", &_1, 3, &_14);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_literalString"), &_13);
	ZEPHIR_INIT_VAR(&ts);
	object_init_ex(&ts, toml_tokenstream_ce);
	ZEPHIR_CALL_METHOD(NULL, &ts, "__construct", NULL, 2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_16);
	object_init_ex(&_16, toml_keytable_ce);
	zephir_read_static_property_ce(&_17, toml_lexer_ce, SL("Singles"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_16, "__construct", &_1, 3, &_17);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &ts, "setsingles", NULL, 5, &_16);
	zephir_check_call_status();
	ZVAL_LONG(&_18, 24);
	ZEPHIR_CALL_METHOD(NULL, &ts, "setunknownid", NULL, 6, &_18);
	zephir_check_call_status();
	ZVAL_LONG(&_18, 10);
	ZEPHIR_CALL_METHOD(NULL, &ts, "setnewlineid", NULL, 7, &_18);
	zephir_check_call_status();
	ZVAL_LONG(&_18, 4);
	ZEPHIR_CALL_METHOD(NULL, &ts, "seteosid", NULL, 8, &_18);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_ts"), &ts);
	ZVAL_LONG(&_18, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpmap", NULL, 14, &_18);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Reads string from specified file path and parses it as TOML.
 *
 * @param (string) File path
 *
 * @return (array) Toml::parse() result
 */
PHP_METHOD(Toml_Parser, parseFile) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, _0, toml, parser, _3, _4, _5, _6, _7, _1$$3;
	zval path, _2$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&toml);
	ZVAL_UNDEF(&parser);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path_param);

	if (UNEXPECTED(Z_TYPE_P(path_param) != IS_STRING && Z_TYPE_P(path_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'path' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(path_param) == IS_STRING)) {
		zephir_get_strval(&path, path_param);
	} else {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_EMPTY_STRING(&path);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "is_file", NULL, 15, &path);
	zephir_check_call_status();
	if (!zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, toml_xarrayable_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "File path not a file ", &path);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 16, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "toml/Parser.zep", 132 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&toml);
	zephir_file_get_contents(&toml, &path TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "H*");
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "EFBBBF");
	ZEPHIR_CALL_FUNCTION(&_5, "pack", NULL, 17, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SVS(&_6, "/^", &_5, "/");
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "");
	ZEPHIR_CALL_FUNCTION(&_7, "preg_replace", NULL, 18, &_6, &_3, &toml);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&toml, &_7);
	ZEPHIR_INIT_VAR(&parser);
	object_init_ex(&parser, toml_parser_ce);
	ZEPHIR_CALL_METHOD(NULL, &parser, "__construct", NULL, 19);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&parser, "parse", NULL, 20, &toml);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Toml_Parser, parse) {

	zval _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, _0, _1, _2, _3, _5, _6, _7, _8, _9, _10, _11;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_4);

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


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "//u");
	zephir_preg_match(&_1, &_2, &input, &_0, 0, 0 , 0  TSRMLS_CC);
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "The TOML input does not appear to be valid UTF-8.", "toml/Parser.zep", 152);
		return;
	}
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "\r\n");
	zephir_array_fast_append(&_4, &_5);
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "\r");
	zephir_array_fast_append(&_4, &_5);
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "\n");
	zephir_fast_str_replace(&_3, &_4, &_5, &input TSRMLS_CC);
	zephir_get_strval(&input, &_3);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "\t");
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, " ");
	zephir_fast_str_replace(&_6, &_7, &_8, &input TSRMLS_CC);
	zephir_get_strval(&input, &_6);
	zephir_read_property(&_9, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_9, "setinput", NULL, 0, &input);
	zephir_check_call_status();
	zephir_read_property(&_10, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "implementation", NULL, 21, &_10);
	zephir_check_call_status();
	zephir_read_property(&_11, this_ptr, SL("_root"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_11, "toarray", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Process all tokens until T_EOS
 * @param TokenStream $ts
 */
PHP_METHOD(Toml_Parser, implementation) {

	zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL, *_7 = NULL, *_10 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1, _2$$4, _4$$5, _6$$6, _8$$7, _9$$8, _11$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_11$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	zephir_read_property(&_0, this_ptr, SL("_root"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_table"), &_0);
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	while (1) {
		if (!(tokenId != 4)) {
			break;
		}
		do {
			if (tokenId == 23) {
				ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "parsecomment", &_3, 22, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_2$$4);
				break;
			}
			if (tokenId == 7 || tokenId == 18 || tokenId == 9 || tokenId == 5) {
				ZEPHIR_CALL_METHOD(&_4$$5, this_ptr, "parsekeyvalue", &_5, 23, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_4$$5);
				break;
			}
			if (tokenId == 12) {
				ZEPHIR_CALL_METHOD(&_6$$6, this_ptr, "parsetablepath", &_7, 24, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_6$$6);
				break;
			}
			if (tokenId == 11 || tokenId == 10) {
				ZEPHIR_CALL_METHOD(&_8$$7, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_8$$7);
				break;
			}
			ZEPHIR_CALL_METHOD(&_9$$8, ts, "gettoken", &_10, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$8);
			ZVAL_STRING(&_11$$8, "Expect Key = , [Path] or # Comment");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", &_12, 25, &_9$$8, &_11$$8);
			zephir_check_call_status();
			break;
		} while(0);

	}
	ZEPHIR_MM_RESTORE();

}

/** 
 * Skip comment, and return next none-comment token or NEWLINE or EOS
 *  
 */
PHP_METHOD(Toml_Parser, parseComment) {

	zend_bool _6$$4;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _3, _1$$3, _2$$3, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 23) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, tokenId);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_3, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_3);
	zephir_check_call_status();
	while (1) {
		if (!(1)) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_4$$4, ts, "movenextid", &_5, 0);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_4$$4);
		_6$$4 = (tokenId == 10);
		if (!(_6$$4)) {
			_6$$4 = (tokenId == 4);
		}
		if (_6$$4) {
			break;
		}
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_LONG(tokenId);

}

/**
 * Move off T_SPACE token to next
 * @param TokenStream $ts
 * @return int
 */
PHP_METHOD(Toml_Parser, skipSpace) {

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId == 11) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "movenextid", NULL, 0);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_1$$3);
	}
	RETURN_MM_LONG(tokenId);

}

PHP_METHOD(Toml_Parser, parseKeyValue) {

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zend_bool isFromInlineTable;
	zval *ts, ts_sub, *isFromInlineTable_param = NULL, keyName, value, _0, _1, _2, _6, _7, _11, _3$$4, _4$$5, _5$$5, _8$$6, _9$$7, _10$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &ts, &isFromInlineTable_param);

	if (!isFromInlineTable_param) {
		isFromInlineTable = 0;
	} else {
	if (UNEXPECTED(Z_TYPE_P(isFromInlineTable_param) != IS_TRUE && Z_TYPE_P(isFromInlineTable_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'isFromInlineTable' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	isFromInlineTable = (Z_TYPE_P(isFromInlineTable_param) == IS_TRUE);
	}


	ZEPHIR_CALL_METHOD(&keyName, this_ptr, "parsekeyname", NULL, 27, ts);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "offsetexists", NULL, 0, &keyName);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "erroruniquekey", NULL, 28, &keyName);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_2, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_2);
	if (tokenId == 11) {
		ZEPHIR_CALL_METHOD(&_3$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_3$$4);
	}
	if (tokenId != 1) {
		ZEPHIR_CALL_METHOD(&_4$$5, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_5$$5, 1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 26, &_4$$5, &_5$$5);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_6, 2);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, ts, "movenextid", NULL, 10);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_7);
	if (tokenId == 11) {
		ZEPHIR_CALL_METHOD(&_8$$6, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_8$$6);
	}
	if (tokenId == 12) {
		ZEPHIR_CALL_METHOD(&value, this_ptr, "parsearray", NULL, 29, ts);
		zephir_check_call_status();
		zephir_read_property(&_9$$7, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_9$$7, "offsetset", NULL, 0, &keyName, &value);
		zephir_check_call_status();
	} else if (tokenId == 14) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "parseinlinetable", NULL, 30, ts, &keyName);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&value, this_ptr, "parsesimplevalue", NULL, 31, ts);
		zephir_check_call_status();
		zephir_read_property(&_10$$9, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_10$$9, "offsetset", NULL, 0, &keyName, &value);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_11, ts, "movenextid", NULL, 10);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_11);
	if (!(isFromInlineTable)) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "finishline", NULL, 32, ts);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		RETURN_MM_LONG(tokenId);
	}

}

/**
 * Return a value
 */
PHP_METHOD(Toml_Parser, parseKeyName) {

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, value, _0, _1$$7, _2$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$7);
	ZVAL_UNDEF(&_2$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	do {
		if (tokenId == 18) {
			ZEPHIR_CALL_METHOD(&value, ts, "getvalue", NULL, 0);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 7) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsebasicstring", NULL, 33, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 9) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseliteralstring", NULL, 34, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 5) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseinteger", NULL, 35, ts);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_CALL_METHOD(&_1$$7, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$7);
		ZVAL_STRING(&_2$$7, "Improper key");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", NULL, 25, &_1$$7, &_2$$7);
		zephir_check_call_status();
		break;
	} while(0);

	RETURN_CCTOR(&value);

}

/**
 * @return object An object with two public properties: value and type.
 * Returned object must be cloned to keep values of returned instance.
 */
PHP_METHOD(Toml_Parser, parseSimpleValue) {

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, value, _0, _1$$11, _2$$11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$11);
	ZVAL_UNDEF(&_2$$11);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	do {
		if (tokenId == 2) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseboolean", NULL, 36, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 5) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseinteger", NULL, 35, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 22) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsefloat", NULL, 37, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 7) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsebasicstring", NULL, 33, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 6) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsemultilinebasicstring", NULL, 38, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 9) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseliteralstring", NULL, 34, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 8) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsemultilineliteralstring", NULL, 39, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 3) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsedatetime", NULL, 40, ts);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_CALL_METHOD(&_1$$11, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$11);
		ZVAL_STRING(&_2$$11, "Value expected: boolean, integer, string or datetime");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", NULL, 25, &_1$$11, &_2$$11);
		zephir_check_call_status();
		break;
	} while(0);

	RETURN_CCTOR(&value);

}

PHP_METHOD(Toml_Parser, parseBoolean) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, result, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(&_0, "true")) {
		ZEPHIR_INIT_VAR(&result);
		ZVAL_BOOL(&result, 1);
	} else {
		ZEPHIR_INIT_NVAR(&result);
		ZVAL_BOOL(&result, 0);
	}
	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Parser, parseInteger) {

	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, value, _0, _1, _2, _6, _7, _8, _9, _10, _3$$3, _4$$3, _11$$4, _12$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&value, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "/([^\\d]_[^\\d])|(_$)/");
	zephir_preg_match(&_1, &_2, &value, &_0, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(&_3$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "Invalid integer number: underscore must be surrounded by at least one digit");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 41, &_4$$3, &_3$$3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "_");
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "");
	zephir_fast_str_replace(&_6, &_7, &_8, &value TSRMLS_CC);
	ZEPHIR_CPY_WRT(&value, &_6);
	ZEPHIR_INIT_VAR(&_9);
	ZEPHIR_INIT_NVAR(&_6);
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "/^0\\d+/");
	zephir_preg_match(&_6, &_10, &value, &_9, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_6)) {
		ZEPHIR_CALL_METHOD(&_11$$4, ts, "gettoken", NULL, 11);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "Invalid integer number: leading zeros are not allowed.");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 41, &_12$$4, &_11$$4);
		zephir_check_call_status();
	}
	RETURN_MM_LONG(zephir_get_intval(&value));

}

PHP_METHOD(Toml_Parser, parseFloat) {

	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, value, _0, _1, _2, _6, _7, _8, _9, _10, _3$$3, _4$$3, _11$$4, _12$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&value, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "/([^\\d]_[^\\d])|_[eE]|[eE]_|(_$)/");
	zephir_preg_match(&_1, &_2, &value, &_0, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(&_3$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "Invalid float number: underscore must be surrounded by at least one digit");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 41, &_4$$3, &_3$$3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "_");
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "");
	zephir_fast_str_replace(&_6, &_7, &_8, &value TSRMLS_CC);
	ZEPHIR_CPY_WRT(&value, &_6);
	ZEPHIR_INIT_VAR(&_9);
	ZEPHIR_INIT_NVAR(&_6);
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "/^0\\d+/");
	zephir_preg_match(&_6, &_10, &value, &_9, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_6)) {
		ZEPHIR_CALL_METHOD(&_11$$4, ts, "gettoken", NULL, 11);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "Invalid float number: leading zeros are not allowed");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 41, &_12$$4, &_11$$4);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_FUNCTION("floatval", NULL, 42, &value);
	zephir_check_call_status();
	RETURN_MM();

}

/** In path parsing, we may want to keep quotes, because they can be used
 *  to enclose a '.' as a none separator. 
 * @param TokenStream $ts
 * @param type $stripQuote
 * @return string
 */
PHP_METHOD(Toml_Parser, parseBasicString) {

	zend_bool _5$$4, _6$$4;
	zval value, _12$$6, _15$$7;
	zephir_fcall_cache_entry *_9 = NULL, *_11 = NULL, *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, result, _1, _4, _2$$3, _3$$3, _16$$4, _17$$4, _7$$5, _8$$5, _10$$6, _13$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_15$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_1, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	if (tokenId != 7) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_3$$3, 7);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 26, &_2$$3, &_3$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_4, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_4);
	while (1) {
		if (!(tokenId != 7)) {
			break;
		}
		_5$$4 = (tokenId == 10);
		if (!(_5$$4)) {
			_5$$4 = (tokenId == 4);
		}
		_6$$4 = _5$$4;
		if (!(_6$$4)) {
			_6$$4 = (tokenId == 20);
		}
		if (_6$$4) {
			ZEPHIR_CALL_METHOD(&_7$$5, ts, "gettoken", NULL, 11);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_8$$5);
			ZVAL_STRING(&_8$$5, "This character is not valid");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", &_9, 25, &_7$$5, &_8$$5);
			zephir_check_call_status();
		} else if (tokenId == 19) {
			ZEPHIR_CALL_METHOD(&_10$$6, this_ptr, "parseescapedcharacter", &_11, 43, ts);
			zephir_check_call_status();
			zephir_get_strval(&_12$$6, &_10$$6);
			ZEPHIR_CPY_WRT(&value, &_12$$6);
		} else {
			ZEPHIR_CALL_METHOD(&_13$$7, ts, "getvalue", &_14, 0);
			zephir_check_call_status();
			zephir_get_strval(&_15$$7, &_13$$7);
			ZEPHIR_CPY_WRT(&value, &_15$$7);
		}
		ZEPHIR_INIT_LNVAR(_16$$4);
		ZEPHIR_CONCAT_VV(&_16$$4, &result, &value);
		ZEPHIR_CPY_WRT(&result, &_16$$4);
		ZEPHIR_CALL_METHOD(&_17$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_17$$4);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Parser, parseMultilineBasicString) {

	zval result, _13$$10, _15$$11;
	zend_bool doLoop = 0, _11$$8, _12$$8;
	zephir_fcall_cache_entry *_3 = NULL, *_7 = NULL, *_18 = NULL, *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _4, _5, _1$$3, _2$$3, _6$$4, _8$$7, _9$$7, _10$$9, _14$$10, _16$$11, _17$$12, _19$$12, _20$$12, _21$$13, _23$$13, _24$$13;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_23$$13);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_15$$11);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 6) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, 6);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_4, 4);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_5, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_5);
	if (tokenId == 10) {
		ZEPHIR_CALL_METHOD(&_6$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_6$$4);
	}
	doLoop = 1;
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (tokenId == 6) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", &_7, 0);
				zephir_check_call_status();
				doLoop = 0;
				break;
			}
			if (tokenId == 4) {
				ZEPHIR_CALL_METHOD(&_8$$7, ts, "gettoken", NULL, 11);
				zephir_check_call_status();
				ZVAL_LONG(&_9$$7, 6);
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_8$$7, &_9$$7);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 20) {
				do {
					ZEPHIR_CALL_METHOD(&_10$$9, ts, "movenextid", NULL, 10);
					zephir_check_call_status();
					tokenId = zephir_get_intval(&_10$$9);
					_11$$8 = (tokenId == 11);
					if (!(_11$$8)) {
						_11$$8 = (tokenId == 10);
					}
					_12$$8 = _11$$8;
					if (!(_12$$8)) {
						_12$$8 = (tokenId == 20);
					}
				} while (_12$$8);
				break;
			}
			if (tokenId == 11) {
				ZEPHIR_INIT_LNVAR(_13$$10);
				ZEPHIR_CONCAT_VS(&_13$$10, &result, " ");
				ZEPHIR_CPY_WRT(&result, &_13$$10);
				ZEPHIR_CALL_METHOD(&_14$$10, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_14$$10);
				break;
			}
			if (tokenId == 10) {
				ZEPHIR_INIT_LNVAR(_15$$11);
				ZEPHIR_CONCAT_VS(&_15$$11, &result, "\n");
				ZEPHIR_CPY_WRT(&result, &_15$$11);
				ZEPHIR_CALL_METHOD(&_16$$11, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_16$$11);
				break;
			}
			if (tokenId == 19) {
				ZEPHIR_CALL_METHOD(&_17$$12, this_ptr, "parseescapedcharacter", &_18, 43, ts);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_19$$12);
				ZEPHIR_CONCAT_VV(&_19$$12, &result, &_17$$12);
				zephir_get_strval(&result, &_19$$12);
				ZEPHIR_CALL_METHOD(&_20$$12, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_20$$12);
				break;
			}
			ZEPHIR_CALL_METHOD(&_21$$13, ts, "getvalue", &_22, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_23$$13);
			ZEPHIR_CONCAT_VV(&_23$$13, &result, &_21$$13);
			zephir_get_strval(&result, &_23$$13);
			ZEPHIR_CALL_METHOD(&_24$$13, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_24$$13);
			break;
		} while(0);

	}
	RETURN_CTOR(&result);

}

/**
 * 
 * @param TokenStream $ts
 * @param bool $stripQuote
 * @return string
 */
PHP_METHOD(Toml_Parser, parseLiteralString) {

	zend_bool _5$$4;
	zval result, _11$$4, _12$$4;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _3, _4, _1$$3, _2$$3, _9$$4, _13$$4, _6$$5, _7$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 9) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, 9);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_4);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	while (1) {
		if (!(tokenId != 9)) {
			break;
		}
		_5$$4 = (tokenId == 10);
		if (!(_5$$4)) {
			_5$$4 = (tokenId == 4);
		}
		if (_5$$4) {
			ZEPHIR_CALL_METHOD(&_6$$5, ts, "gettoken", NULL, 11);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$5);
			ZVAL_STRING(&_7$$5, "This character is not valid.");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", &_8, 25, &_6$$5, &_7$$5);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&_9$$4, ts, "getvalue", &_10, 0);
		zephir_check_call_status();
		zephir_get_strval(&_11$$4, &_9$$4);
		ZEPHIR_INIT_LNVAR(_12$$4);
		ZEPHIR_CONCAT_VV(&_12$$4, &result, &_11$$4);
		ZEPHIR_CPY_WRT(&result, &_12$$4);
		ZEPHIR_CALL_METHOD(&_13$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_13$$4);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	RETURN_CTOR(&result);

}

PHP_METHOD(Toml_Parser, parseMultilineLiteralString) {

	zval result, _12$$5, _13$$5;
	zephir_fcall_cache_entry *_3 = NULL, *_9 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _4, _5, _1$$3, _2$$3, _6$$4, _7$$7, _8$$7, _10$$5, _14$$5, _15$$8, _16$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 8) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, 8);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_4, 3);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_5, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_5);
	if (tokenId == 10) {
		ZEPHIR_CALL_METHOD(&_6$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_6$$4);
	}
	while (1) {
		if (!(1)) {
			break;
		}
		if (tokenId == 8) {
			break;
		}
		if (tokenId == 4) {
			ZEPHIR_CALL_METHOD(&_7$$7, ts, "gettoken", NULL, 11);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_8$$7);
			ZVAL_STRING(&_8$$7, "Expected token T_3_APOSTROPHE");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", &_9, 25, &_7$$7, &_8$$7);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&_10$$5, ts, "getvalue", &_11, 0);
		zephir_check_call_status();
		zephir_get_strval(&_12$$5, &_10$$5);
		ZEPHIR_INIT_LNVAR(_13$$5);
		ZEPHIR_CONCAT_VV(&_13$$5, &result, &_12$$5);
		ZEPHIR_CPY_WRT(&result, &_13$$5);
		ZEPHIR_CALL_METHOD(&_14$$5, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_14$$5);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	if (tokenId != 8) {
		ZEPHIR_CALL_METHOD(&_15$$8, ts, "gettoken", NULL, 11);
		zephir_check_call_status();
		ZVAL_LONG(&_16$$8, 8);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_15$$8, &_16$$8);
		zephir_check_call_status();
	}
	RETURN_CTOR(&result);

}

PHP_METHOD(Toml_Parser, parseEscapedCharacter) {

	zval value, _1, c1$$3, _5$$3, _7$$12;
	zend_long ZEPHIR_LAST_CALL_STATUS, ct = 0;
	zval *ts, ts_sub, _0, matches, _8, _9, _10, _11, _12, _2$$3, _3$$3, _4$$3, _6$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&c1$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$12);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	zephir_get_strval(&_1, &_0);
	ZEPHIR_CPY_WRT(&value, &_1);
	ct = zephir_fast_strlen_ev(&value);
	if (ct == 2) {
		ZVAL_LONG(&_2$$3, 1);
		ZVAL_LONG(&_3$$3, 1);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_substr(&_4$$3, &value, 1 , 1 , 0);
		zephir_get_strval(&_5$$3, &_4$$3);
		ZEPHIR_CPY_WRT(&c1$$3, &_5$$3);
		do {
			if (ZEPHIR_IS_STRING(&c1$$3, "n")) {
				RETURN_MM_STRING("\n");
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "t")) {
				RETURN_MM_STRING("\t");
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "r")) {
				RETURN_MM_STRING("\r");
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "b")) {
				RETURN_MM_STRING("\\b");
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "f")) {
				ZVAL_LONG(&_6$$8, 12);
				ZEPHIR_RETURN_CALL_FUNCTION("chr", NULL, 44, &_6$$8);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "\\")) {
				RETURN_MM_STRING("\\");
			}
			if (ZEPHIR_IS_STRING(&c1$$3, "\"")) {
				RETURN_MM_STRING("\"");
			}
			break;
		} while(0);

	}
	if (ct == 6) {
		ZEPHIR_INIT_VAR(&_7$$12);
		ZEPHIR_CONCAT_SVS(&_7$$12, "\"", &value, "\"");
		zephir_json_decode(return_value, &_7$$12, 0 );
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_8);
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "/\\\\U([0-9a-fA-F]{4})([0-9a-fA-F]{4})/");
	zephir_preg_match(&_8, &_9, &value, &matches, 0, 0 , 0  TSRMLS_CC);
	zephir_array_fetch_long(&_10, &matches, 1, PH_NOISY | PH_READONLY, "toml/Parser.zep", 625 TSRMLS_CC);
	zephir_array_fetch_long(&_11, &matches, 2, PH_NOISY | PH_READONLY, "toml/Parser.zep", 625 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_12);
	ZEPHIR_CONCAT_SVSVS(&_12, "\"\\u", &_10, "\\u", &_11, "\"");
	zephir_json_decode(return_value, &_12, 0 );
	RETURN_MM();

}

PHP_METHOD(Toml_Parser, parseDatetime) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, date;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&date);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&date, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	object_init_ex(return_value, php_date_get_date_ce());
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 0, &date);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Recursive call of itself.
 * @param \Tomlmfony\Toml\TokenStream $ts
 * @return array
 */
PHP_METHOD(Toml_Parser, parseArray) {

	zend_bool _5, _21$$6, _28$$6;
	zephir_fcall_cache_entry *_3 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_12 = NULL, *_17 = NULL, *_19 = NULL, *_27 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0, rct = 0;
	zval *ts, ts_sub, value, result, e, _0, _4, _1$$3, _2$$3, _6$$4, _7$$5, _11$$9, _13$$6, _20$$6, _14$$10, _15$$10, _16$$10, _18$$10, _22$$11, _23$$12, _24$$13, _25$$14, _26$$14, _29$$15, _30$$16, _31$$17, _32$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_24$$13);
	ZVAL_UNDEF(&_25$$14);
	ZVAL_UNDEF(&_26$$14);
	ZVAL_UNDEF(&_29$$15);
	ZVAL_UNDEF(&_30$$16);
	ZVAL_UNDEF(&_31$$17);
	ZVAL_UNDEF(&_32$$17);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 12) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, 12);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&result);
	object_init_ex(&result, toml_valuelist_ce);
	ZEPHIR_CALL_METHOD(NULL, &result, "__construct", NULL, 45);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_4);
	while (1) {
		_5 = tokenId == 11;
		if (!(_5)) {
			_5 = tokenId == 10;
		}
		if (!(_5)) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_6$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_6$$4);
	}
	if (tokenId == 23) {
		ZEPHIR_CALL_METHOD(&_7$$5, this_ptr, "parsecommentsandspace", &_8, 46, ts);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_7$$5);
	}
	rct = 0;
	while (1) {
		if (!(tokenId != 13)) {
			break;
		}
		if (tokenId == 12) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsearray", &_9, 29, ts);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsesimplevalue", &_10, 31, ts);
			zephir_check_call_status();
		}

		/* try_start_1: */

			ZVAL_LONG(&_11$$9, rct);
			ZEPHIR_CALL_METHOD(NULL, &result, "offsetset", &_12, 47, &_11$$9, &value);
			zephir_check_call_status_or_jump(try_end_1);
			rct = (rct + 1);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_NVAR(&_13$$6);
			ZVAL_OBJ(&_13$$6, EG(exception));
			Z_ADDREF_P(&_13$$6);
			if (zephir_instance_of_ev(&_13$$6, toml_xarrayable_ce TSRMLS_CC)) {
				zend_clear_exception(TSRMLS_C);
				ZEPHIR_CPY_WRT(&e, &_13$$6);
				ZEPHIR_INIT_NVAR(&_14$$10);
				object_init_ex(&_14$$10, toml_xarrayable_ce);
				ZEPHIR_CALL_METHOD(&_15$$10, &e, "getmessage", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_16$$10, ts, "getline", &_17, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_18$$10);
				ZEPHIR_CONCAT_VSV(&_18$$10, &_15$$10, " at line ", &_16$$10);
				ZEPHIR_CALL_METHOD(NULL, &_14$$10, "__construct", &_19, 16, &_18$$10);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_14$$10, "toml/Parser.zep", 673 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&_20$$6, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_20$$6);
		while (1) {
			_21$$6 = tokenId == 11;
			if (!(_21$$6)) {
				_21$$6 = tokenId == 10;
			}
			if (!(_21$$6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&_22$$11, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_22$$11);
		}
		if (tokenId == 23) {
			ZEPHIR_CALL_METHOD(&_23$$12, this_ptr, "parsecommentsandspace", &_8, 46, ts);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_23$$12);
		}
		if (tokenId == 16) {
			ZEPHIR_CALL_METHOD(&_24$$13, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_24$$13);
		} else if (tokenId != 13) {
			ZEPHIR_CALL_METHOD(&_25$$14, ts, "gettoken", NULL, 11);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_26$$14);
			ZVAL_STRING(&_26$$14, "Expect '.' or ']' after array item");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", &_27, 25, &_25$$14, &_26$$14);
			zephir_check_call_status();
		}
		while (1) {
			_28$$6 = tokenId == 11;
			if (!(_28$$6)) {
				_28$$6 = tokenId == 10;
			}
			if (!(_28$$6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&_29$$15, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_29$$15);
		}
		if (tokenId == 23) {
			ZEPHIR_CALL_METHOD(&_30$$16, this_ptr, "parsecommentsandspace", &_8, 46, ts);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_30$$16);
		}
	}
	if (tokenId != 13) {
		ZEPHIR_CALL_METHOD(&_31$$17, ts, "gettoken", NULL, 11);
		zephir_check_call_status();
		ZVAL_LONG(&_32$$17, 13);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_31$$17, &_32$$17);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&result);

}

/**
 * Used by parseInlineTable, to push a new Table as a value
 *  and set current work table to it.
 * @param string $keyName
 */
PHP_METHOD(Toml_Parser, pushWorkTable) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *keyName, keyName_sub, work, pushed, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&keyName_sub);
	ZVAL_UNDEF(&work);
	ZVAL_UNDEF(&pushed);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keyName);



	ZEPHIR_OBS_VAR(&work);
	zephir_read_property(&work, this_ptr, SL("_table"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, &work, "offsetexists", NULL, 0, keyName);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&pushed);
		object_init_ex(&pushed, toml_keytable_ce);
		ZEPHIR_CALL_METHOD(NULL, &pushed, "__construct", NULL, 3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &work, "offsetset", NULL, 0, keyName, &pushed);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("_table"), &pushed);
	}
	ZEPHIR_CALL_METHOD(&_1, &work, "offsetget", NULL, 0, keyName);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_table"), &_1);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Parser, parseInlineTable) {

	zephir_fcall_cache_entry *_3 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, *keyName, keyName_sub, priorTable, _0, _4, _5, _1$$3, _2$$3, _6$$4, _7$$5, _8$$5, _10$$6, _11$$7, _13$$7, _14$$7, _12$$8, _15$$9, _16$$10, _17$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&keyName_sub);
	ZVAL_UNDEF(&priorTable);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$10);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &ts, &keyName);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId != 14) {
		ZEPHIR_CALL_METHOD(&_1$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_2$$3, 14);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZVAL_LONG(&_4, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpmap", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&priorTable);
	zephir_read_property(&priorTable, this_ptr, SL("_table"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushworktable", NULL, 48, keyName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_5);
	if (tokenId == 11) {
		ZEPHIR_CALL_METHOD(&_6$$4, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_6$$4);
	}
	if (tokenId != 15) {
		ZVAL_BOOL(&_8$$5, 1);
		ZEPHIR_CALL_METHOD(&_7$$5, this_ptr, "parsekeyvalue", &_9, 23, ts, &_8$$5);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_7$$5);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_10$$6, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_10$$6);
		}
	}
	while (1) {
		if (!(tokenId == 16)) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_11$$7, ts, "movenextid", NULL, 10);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_11$$7);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_12$$8, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_12$$8);
		}
		ZVAL_BOOL(&_14$$7, 1);
		ZEPHIR_CALL_METHOD(&_13$$7, this_ptr, "parsekeyvalue", &_9, 23, ts, &_14$$7);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_13$$7);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_15$$9, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_15$$9);
		}
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpmap", NULL, 0);
	zephir_check_call_status();
	if (tokenId != 15) {
		ZEPHIR_CALL_METHOD(&_16$$10, ts, "gettoken", NULL, 11);
		zephir_check_call_status();
		ZVAL_LONG(&_17$$10, 15);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_3, 26, &_16$$10, &_17$$10);
		zephir_check_call_status();
	}
	zephir_update_property_zval(this_ptr, SL("_table"), &priorTable);
	ZEPHIR_MM_RESTORE();

}

/**
 * Nothing more of interest on the line,
 * anything besides a comment is an error
 * Used by parseObjectPath and parseKeyValue
 */
PHP_METHOD(Toml_Parser, finishLine) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, tokenId, _1$$5, _2$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&tokenId);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&tokenId, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 11)) {
		ZEPHIR_CALL_METHOD(&tokenId, ts, "movenextid", NULL, 0);
		zephir_check_call_status();
	}
	if (ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 23)) {
		ZEPHIR_CALL_METHOD(&tokenId, this_ptr, "parsecomment", NULL, 22, ts);
		zephir_check_call_status();
	}
	_0 = !ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 10);
	if (_0) {
		_0 = !ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 4);
	}
	if (_0) {
		ZEPHIR_CALL_METHOD(&_1$$5, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$5);
		ZVAL_STRING(&_2$$5, "Expected T_NEWLINE or T_EOS.");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", NULL, 25, &_1$$5, &_2$$5);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&tokenId);

}

PHP_METHOD(Toml_Parser, tablePathError) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *msg_param = NULL, _0, _1, _2, _3;
	zval msg, errMsg;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&errMsg);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &msg_param);

	if (UNEXPECTED(Z_TYPE_P(msg_param) != IS_STRING && Z_TYPE_P(msg_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'msg' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(msg_param) == IS_STRING)) {
		zephir_get_strval(&msg, msg_param);
	} else {
		ZEPHIR_INIT_VAR(&msg);
		ZVAL_EMPTY_STRING(&msg);
	}


	zephir_read_property(&_0, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CONCAT_VSV(&_2, &msg, " at line ", &_1);
	zephir_get_strval(&errMsg, &_2);
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, toml_xarrayable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 16, &errMsg);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "toml/Parser.zep", 809 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * From array of Table/TableList generate its key path
 * using the object tags
 * @param array of parts
 * @return string
 */
PHP_METHOD(Toml_Parser, getPathName) {

	zend_string *_2;
	zend_ulong _1;
	zval result, bit, _8$$4, _11$$8;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool withIndex;
	zval *parts_param = NULL, *withIndex_param = NULL, idx, p, tag, *_0, _3$$3, _4$$4, _5$$4, _6$$5, _7$$5, _9$$6, _10$$6;
	zval parts;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&idx);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&tag);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&bit);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_11$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &parts_param, &withIndex_param);

	ZEPHIR_OBS_COPY_OR_DUP(&parts, parts_param);
	if (!withIndex_param) {
		withIndex = 1;
	} else {
	if (UNEXPECTED(Z_TYPE_P(withIndex_param) != IS_TRUE && Z_TYPE_P(withIndex_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'withIndex' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	withIndex = (Z_TYPE_P(withIndex_param) == IS_TRUE);
	}


	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	zephir_is_iterable(&parts, 0, "toml/Parser.zep", 841);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&parts), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&idx);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&idx, _2);
		} else {
			ZVAL_LONG(&idx, _1);
		}
		ZEPHIR_INIT_NVAR(&p);
		ZVAL_COPY(&p, _0);
		ZEPHIR_CALL_METHOD(&tag, &p, "gettag", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3$$3, &tag, SL("objAOT"), PH_NOISY_CC | PH_READONLY);
		if (zephir_is_true(&_3$$3)) {
			zephir_read_property(&_4$$4, &tag, SL("partKey"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_LNVAR(_5$$4);
			ZEPHIR_CONCAT_SV(&_5$$4, "[", &_4$$4);
			zephir_get_strval(&bit, &_5$$4);
			if (withIndex) {
				ZEPHIR_CALL_METHOD(&_6$$5, &p, "getendindex", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_7$$5);
				ZEPHIR_CONCAT_VSV(&_7$$5, &bit, "/", &_6$$5);
				zephir_get_strval(&bit, &_7$$5);
			}
			ZEPHIR_INIT_LNVAR(_8$$4);
			ZEPHIR_CONCAT_VS(&_8$$4, &bit, "]");
			ZEPHIR_CPY_WRT(&bit, &_8$$4);
		} else {
			zephir_read_property(&_9$$6, &tag, SL("partKey"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_LNVAR(_10$$6);
			ZEPHIR_CONCAT_SVS(&_10$$6, "{", &_9$$6, "}");
			zephir_get_strval(&bit, &_10$$6);
		}
		if (ZEPHIR_IS_LONG(&idx, 0)) {
			ZEPHIR_CPY_WRT(&result, &bit);
		} else {
			ZEPHIR_INIT_LNVAR(_11$$8);
			ZEPHIR_CONCAT_VV(&_11$$8, &result, &bit);
			ZEPHIR_CPY_WRT(&result, &_11$$8);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&p);
	ZEPHIR_INIT_NVAR(&idx);
	RETURN_CTOR(&result);

}

/**
 * Convert the path string, into the array with the path of
 * Table and TableList objects indicated.
 * @param TokenStream $ts
 */
PHP_METHOD(Toml_Parser, parseObjectPath) {

	zval parts;
	zend_bool isAOT = 0, hitNew = 0, doLoop = 0, preMade = 0, _12$$14, _19$$19, _28$$25;
	zephir_fcall_cache_entry *_3 = NULL, *_18 = NULL, *_23 = NULL, *_24 = NULL, *_25 = NULL, *_26 = NULL, *_27 = NULL, *_30 = NULL, *_34 = NULL, *_35 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pathLine = 0, partsCt = 0, i = 0, firstNew = 0, dotCount = 0, AOTLength = 0, tokenId = 0;
	zval *ts, ts_sub, __$true, __$false, pobj, testObj, tag, partKey, path, _0, _1, _4, _2$$3, _5$$5, _6$$6, _7$$7, _8$$9, _9$$12, _10$$11, _11$$13, _15$$14, _13$$15, _14$$16, _16$$18, _17$$17, _21$$19, _37$$19, _20$$20, _22$$21, _36$$25, _29$$26, _31$$26, _32$$26, _33$$26, _38$$29, _39$$30, _40$$31, _41$$33, _42$$33, _43$$33, _44$$33, _45$$33, _46$$34, _47$$36, _48$$36, _49$$36, _50$$36, _51$$36;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&pobj);
	ZVAL_UNDEF(&testObj);
	ZVAL_UNDEF(&tag);
	ZVAL_UNDEF(&partKey);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_9$$12);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$13);
	ZVAL_UNDEF(&_15$$14);
	ZVAL_UNDEF(&_13$$15);
	ZVAL_UNDEF(&_14$$16);
	ZVAL_UNDEF(&_16$$18);
	ZVAL_UNDEF(&_17$$17);
	ZVAL_UNDEF(&_21$$19);
	ZVAL_UNDEF(&_37$$19);
	ZVAL_UNDEF(&_20$$20);
	ZVAL_UNDEF(&_22$$21);
	ZVAL_UNDEF(&_36$$25);
	ZVAL_UNDEF(&_29$$26);
	ZVAL_UNDEF(&_31$$26);
	ZVAL_UNDEF(&_32$$26);
	ZVAL_UNDEF(&_33$$26);
	ZVAL_UNDEF(&_38$$29);
	ZVAL_UNDEF(&_39$$30);
	ZVAL_UNDEF(&_40$$31);
	ZVAL_UNDEF(&_41$$33);
	ZVAL_UNDEF(&_42$$33);
	ZVAL_UNDEF(&_43$$33);
	ZVAL_UNDEF(&_44$$33);
	ZVAL_UNDEF(&_45$$33);
	ZVAL_UNDEF(&_46$$34);
	ZVAL_UNDEF(&_47$$36);
	ZVAL_UNDEF(&_48$$36);
	ZVAL_UNDEF(&_49$$36);
	ZVAL_UNDEF(&_50$$36);
	ZVAL_UNDEF(&_51$$36);
	ZVAL_UNDEF(&parts);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	isAOT = 0;
	hitNew = 0;
	partsCt = 0;
	AOTLength = 0;
	dotCount = 0;
	firstNew = -1;
	ZEPHIR_OBS_VAR(&pobj);
	zephir_read_property(&pobj, this_ptr, SL("_root"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&testObj);
	ZVAL_NULL(&testObj);
	ZEPHIR_CALL_METHOD(&_0, ts, "getline", NULL, 0);
	zephir_check_call_status();
	pathLine = zephir_get_intval(&_0);
	ZEPHIR_CALL_METHOD(&_1, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	if (tokenId != 12) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Path start [ expected");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_2$$3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_4, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_4);
	doLoop = 1;
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (tokenId == 23) {
				ZEPHIR_INIT_NVAR(&_5$$5);
				ZVAL_STRING(&_5$$5, "Unexpected '#' in path");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_5$$5);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 1) {
				ZEPHIR_INIT_NVAR(&_6$$6);
				ZVAL_STRING(&_6$$6, "Unexpected '=' in path");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_6$$6);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 11) {
				ZEPHIR_CALL_METHOD(&_7$$7, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_7$$7);
				break;
			}
			if (tokenId == 4) {
				doLoop = 0;
				break;
			}
			if (tokenId == 10) {
				ZEPHIR_INIT_NVAR(&_8$$9);
				ZVAL_STRING(&_8$$9, "New line in unfinished path");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_8$$9);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 13) {
				if (isAOT) {
					if (AOTLength == 0) {
						ZEPHIR_INIT_NVAR(&_9$$12);
						ZVAL_STRING(&_9$$12, "AOT Segment cannot be empty");
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_9$$12);
						zephir_check_call_status();
					}
					isAOT = 0;
					AOTLength = 0;
					ZEPHIR_CALL_METHOD(&_10$$11, ts, "movenextid", NULL, 10);
					zephir_check_call_status();
					tokenId = zephir_get_intval(&_10$$11);
				} else {
					ZEPHIR_CALL_METHOD(&_11$$13, ts, "movenextid", NULL, 10);
					zephir_check_call_status();
					tokenId = zephir_get_intval(&_11$$13);
					doLoop = 0;
				}
				break;
			}
			if (tokenId == 12) {
				_12$$14 = dotCount < 1;
				if (_12$$14) {
					_12$$14 = zephir_fast_count_int(&parts TSRMLS_CC) > 0;
				}
				if (_12$$14) {
					ZEPHIR_INIT_NVAR(&_13$$15);
					ZVAL_STRING(&_13$$15, "Expected a '.' after path key");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_13$$15);
					zephir_check_call_status();
				}
				if (isAOT) {
					ZEPHIR_INIT_NVAR(&_14$$16);
					ZVAL_STRING(&_14$$16, "Too many consecutive [ in path");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_14$$16);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_15$$14, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_15$$14);
				isAOT = 1;
				break;
			}
			if (tokenId == 17) {
				if (dotCount == 1) {
					ZEPHIR_INIT_NVAR(&_16$$18);
					ZVAL_STRING(&_16$$18, "Found '..' in path");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_16$$18);
					zephir_check_call_status();
				}
				dotCount = (dotCount + 1);
				ZEPHIR_CALL_METHOD(&_17$$17, ts, "movenextid", NULL, 10);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_17$$17);
				break;
			}
			ZEPHIR_CALL_METHOD(&partKey, this_ptr, "parsekeyname", &_18, 27, ts);
			zephir_check_call_status();
			_19$$19 = dotCount < 1;
			if (_19$$19) {
				_19$$19 = zephir_fast_count_int(&parts TSRMLS_CC) > 0;
			}
			if (_19$$19) {
				ZEPHIR_INIT_NVAR(&_20$$20);
				ZVAL_STRING(&_20$$20, "Expected a '.' after path key");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_20$$20);
				zephir_check_call_status();
			}
			dotCount = 0;
			ZEPHIR_CALL_METHOD(&_21$$19, &pobj, "offsetexists", NULL, 0, &partKey);
			zephir_check_call_status();
			if (zephir_is_true(&_21$$19)) {
				ZEPHIR_CALL_METHOD(&testObj, &pobj, "offsetget", NULL, 0, &partKey);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&testObj);
				ZVAL_NULL(&testObj);
			}
			if (ZEPHIR_IS_EMPTY(&testObj)) {
				if (!(hitNew)) {
					hitNew = 1;
					firstNew = partsCt;
				}
				ZEPHIR_INIT_NVAR(&tag);
				object_init_ex(&tag, toml_parttag_ce);
				if (isAOT) {
					ZVAL_BOOL(&_22$$21, 1);
				} else {
					ZVAL_BOOL(&_22$$21, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, &tag, "__construct", &_23, 50, &partKey, &_22$$21);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&testObj);
				if (isAOT) {
					AOTLength = (AOTLength + 1);
					object_init_ex(&testObj, toml_tablelist_ce);
					ZEPHIR_CALL_METHOD(NULL, &testObj, "__construct", &_24, 51);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &pobj, "offsetset", NULL, 0, &partKey, &testObj);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&pobj, &testObj, "getendtable", &_25, 52);
					zephir_check_call_status();
				} else {
					object_init_ex(&testObj, toml_keytable_ce);
					ZEPHIR_CALL_METHOD(NULL, &testObj, "__construct", &_26, 3);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &pobj, "offsetset", NULL, 0, &partKey, &testObj);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&pobj, &testObj);
				}
				ZEPHIR_CALL_METHOD(NULL, &testObj, "settag", &_27, 53, &tag);
				zephir_check_call_status();
			} else {
				_28$$25 = Z_TYPE_P(&testObj) == IS_OBJECT;
				if (_28$$25) {
					_28$$25 = zephir_instance_of_ev(&testObj, toml_arrayable_ce TSRMLS_CC);
				}
				preMade = _28$$25;
				if (!(preMade)) {
					ZEPHIR_CALL_METHOD(&_29$$26, this_ptr, "getpathname", &_30, 54, &parts);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&path);
					ZEPHIR_CONCAT_VSV(&path, &_29$$26, ".", &partKey);
					ZEPHIR_INIT_NVAR(&_31$$26);
					object_init_ex(&_31$$26, toml_xarrayable_ce);
					ZEPHIR_SINIT_NVAR(_32$$26);
					ZVAL_LONG(&_32$$26, pathLine);
					ZEPHIR_INIT_LNVAR(_33$$26);
					ZEPHIR_CONCAT_SVSV(&_33$$26, "Duplicate key path: ", &path, " line ", &_32$$26);
					ZEPHIR_CALL_METHOD(NULL, &_31$$26, "__construct", &_34, 16, &_33$$26);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_31$$26, "toml/Parser.zep", 967 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_35, 55);
				zephir_check_call_status();
				if (isAOT) {
					zephir_update_property_zval(&tag, SL("isAOT"), &__$true);
				} else {
					zephir_update_property_zval(&tag, SL("isAOT"), &__$false);
				}
				zephir_read_property(&_36$$25, &tag, SL("objAOT"), PH_NOISY_CC | PH_READONLY);
				if (zephir_is_true(&_36$$25)) {
					AOTLength = (AOTLength + 1);
					ZEPHIR_CALL_METHOD(&pobj, &testObj, "getendtable", &_25, 52);
					zephir_check_call_status();
				} else {
					ZEPHIR_CPY_WRT(&pobj, &testObj);
				}
			}
			zephir_array_append(&parts, &testObj, PH_SEPARATE, "toml/Parser.zep", 979);
			partsCt = (partsCt + 1);
			ZEPHIR_CALL_METHOD(&_37$$19, ts, "movenextid", NULL, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_37$$19);
			break;
		} while(0);

	}
	if (partsCt == 0) {
		ZEPHIR_INIT_VAR(&_38$$29);
		ZVAL_STRING(&_38$$29, "Table path cannot be empty");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 49, &_38$$29);
		zephir_check_call_status();
	}
	if (!(hitNew)) {
		ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_35, 55);
		zephir_check_call_status();
		zephir_read_property(&_39$$30, &tag, SL("objAOT"), PH_NOISY_CC | PH_READONLY);
		if (zephir_is_true(&_39$$30)) {
			zephir_read_property(&_40$$31, &tag, SL("isAOT"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_40$$31)) {
				ZEPHIR_CALL_METHOD(&pobj, &testObj, "newtable", NULL, 56);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_VAR(&_41$$33);
				object_init_ex(&_41$$33, toml_xarrayable_ce);
				ZVAL_BOOL(&_43$$33, 0);
				ZEPHIR_CALL_METHOD(&_42$$33, this_ptr, "getpathname", &_30, 54, &parts, &_43$$33);
				zephir_check_call_status();
				ZEPHIR_SINIT_VAR(_44$$33);
				ZVAL_LONG(&_44$$33, pathLine);
				ZEPHIR_INIT_VAR(&_45$$33);
				ZEPHIR_CONCAT_SVSV(&_45$$33, "Table path mismatch with ", &_42$$33, " line ", &_44$$33);
				ZEPHIR_CALL_METHOD(NULL, &_41$$33, "__construct", &_34, 16, &_45$$33);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_41$$33, "toml/Parser.zep", 996 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_read_property(&_46$$34, &tag, SL("implicit"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_46$$34)) {
				if (0) {
					zephir_update_property_zval(&tag, SL("implicit"), &__$true);
				} else {
					zephir_update_property_zval(&tag, SL("implicit"), &__$false);
				}
			} else {
				ZEPHIR_INIT_VAR(&_47$$36);
				object_init_ex(&_47$$36, toml_xarrayable_ce);
				ZVAL_BOOL(&_49$$36, 0);
				ZEPHIR_CALL_METHOD(&_48$$36, this_ptr, "getpathname", &_30, 54, &parts, &_49$$36);
				zephir_check_call_status();
				ZEPHIR_SINIT_VAR(_50$$36);
				ZVAL_LONG(&_50$$36, pathLine);
				ZEPHIR_INIT_VAR(&_51$$36);
				ZEPHIR_CONCAT_SVSV(&_51$$36, "Duplicate key path: [", &_48$$36, "] line ", &_50$$36);
				ZEPHIR_CALL_METHOD(NULL, &_47$$36, "__construct", &_34, 16, &_51$$36);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_47$$36, "toml/Parser.zep", 1005 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	} else {
		partsCt = (partsCt - 1);
		i = firstNew;
		while (1) {
			if (!(i < partsCt)) {
				break;
			}
			ZEPHIR_OBS_NVAR(&testObj);
			zephir_array_fetch_long(&testObj, &parts, i, PH_NOISY, "toml/Parser.zep", 1016 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_35, 55);
			zephir_check_call_status();
			if (1) {
				zephir_update_property_zval(&tag, SL("implicit"), &__$true);
			} else {
				zephir_update_property_zval(&tag, SL("implicit"), &__$false);
			}
			i = (i + 1);
		}
	}
	zephir_update_property_zval(this_ptr, SL("_table"), &pobj);
	ZEPHIR_MM_RESTORE();

}

/**
 * @param TokenStream $ts
 * For mixed AOT and table paths, some rules to be followed, or else.
 * For existing paths, a new AOT-T is created if end of path is AOT
 * New path dynamic AOT segments always create an initial AOT-T
 * Existing AOT segments ended with a Table Path are unaltered.
 * 
 * Traverse the path parts and adjust workArray
 * 
 * Would be nice to have a token that says "I am relative" to last path,
 * //TODO: Try relative paths and replacement. Means more tokens to LEXER
 * If first character is a "plus" + , it extends and replaces last path
 * If first character is a "minus" - , it extends last path without replacement
 * 
 */
PHP_METHOD(Toml_Parser, parseTablePath) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "parseobjectpath", NULL, 57, ts);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "finishline", NULL, 32, ts);
	zephir_check_call_status();
	RETURN_MM();

}

/** 
 * 
 */
PHP_METHOD(Toml_Parser, throwTokenError) {

	zephir_fcall_cache_entry *_0 = NULL;
	zend_long expectedId, ZEPHIR_LAST_CALL_STATUS;
	zval *token, token_sub, *expectedId_param = NULL, tokenName, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&token_sub);
	ZVAL_UNDEF(&tokenName);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &token, &expectedId_param);

	if (UNEXPECTED(Z_TYPE_P(expectedId_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'expectedId' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	expectedId = Z_LVAL_P(expectedId_param);


	ZVAL_LONG(&_1, expectedId);
	ZEPHIR_CALL_CE_STATIC(&tokenName, toml_lexer_ce, "tokenname", &_0, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CONCAT_SV(&_2, "Expected ", &tokenName);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "unexpectedtokenerror", NULL, 25, token, &_2);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the next tokenId, after skipping any comments and space
 * @param TokenStream $ts
 */
PHP_METHOD(Toml_Parser, parseCommentsAndSpace) {

	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1$$3, _3$$4, _5$$5, _6$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	if (tokenId == 23) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "parsecomment", &_2, 22, ts);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_1$$3);
	}
	while (1) {
		if (!(tokenId == 10)) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_3$$4, ts, "movenextid", &_4, 0);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_3$$4);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_5$$5, ts, "movenextid", &_4, 10);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_5$$5);
		}
		if (tokenId == 23) {
			ZEPHIR_CALL_METHOD(&_6$$6, this_ptr, "parsecomment", &_2, 22, ts);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_6$$6);
		}
	}
	RETURN_MM_LONG(tokenId);

}

PHP_METHOD(Toml_Parser, errorUniqueKey) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *keyName_param = NULL, _0, _1;
	zval keyName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keyName_param);

	if (UNEXPECTED(Z_TYPE_P(keyName_param) != IS_STRING && Z_TYPE_P(keyName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'keyName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(keyName_param) == IS_STRING)) {
		zephir_get_strval(&keyName, keyName_param);
	} else {
		ZEPHIR_INIT_VAR(&keyName);
		ZVAL_EMPTY_STRING(&keyName);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "The key { %s } has already been defined previously.");
	ZEPHIR_CALL_FUNCTION(&_1, "sprintf", NULL, 58, &_0, &keyName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 41, &_1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Parser, unexpectedTokenError) {

	zend_long ZEPHIR_LAST_CALL_STATUS, line = 0;
	zephir_fcall_cache_entry *_1 = NULL;
	zval expectedMsg, name, value, msg, _3, _9, _10$$3, _11$$4, _12$$5;
	zval *token, token_sub, *expectedMsg_param = NULL, _0, _2, _4, _5, _6, _7, _8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&token_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&expectedMsg);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &token, &expectedMsg_param);

	if (!expectedMsg_param) {
		ZEPHIR_INIT_VAR(&expectedMsg);
		ZVAL_STRING(&expectedMsg, "");
	} else {
		zephir_get_strval(&expectedMsg, expectedMsg_param);
	}


	zephir_read_property(&_2, token, SL("id"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_0, toml_lexer_ce, "tokenname", &_1, 0, &_2);
	zephir_check_call_status();
	zephir_get_strval(&_3, &_0);
	ZEPHIR_CPY_WRT(&name, &_3);
	zephir_read_property(&_4, token, SL("line"), PH_NOISY_CC | PH_READONLY);
	line = zephir_get_numberval(&_4);
	zephir_read_property(&_5, token, SL("value"), PH_NOISY_CC | PH_READONLY);
	zephir_get_strval(&value, &_5);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "Syntax error: unexpected token %s at line %s");
	ZVAL_LONG(&_7, line);
	ZEPHIR_CALL_FUNCTION(&_8, "sprintf", NULL, 58, &_6, &name, &_7);
	zephir_check_call_status();
	zephir_get_strval(&_9, &_8);
	ZEPHIR_CPY_WRT(&msg, &_9);
	zephir_read_property(&_7, token, SL("isSingle"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_7))) {
		ZEPHIR_INIT_VAR(&_10$$3);
		ZEPHIR_CONCAT_VSVS(&_10$$3, &msg, " value { '", &value, "' }. ");
		ZEPHIR_CPY_WRT(&msg, &_10$$3);
	} else {
		ZEPHIR_INIT_VAR(&_11$$4);
		ZEPHIR_CONCAT_VS(&_11$$4, &msg, ".");
		ZEPHIR_CPY_WRT(&msg, &_11$$4);
	}
	if (!(ZEPHIR_IS_EMPTY(&expectedMsg))) {
		ZEPHIR_INIT_VAR(&_12$$5);
		ZEPHIR_CONCAT_VSV(&_12$$5, &msg, " ", &expectedMsg);
		ZEPHIR_CPY_WRT(&msg, &_12$$5);
	}
	ZEPHIR_INIT_NVAR(&_6);
	object_init_ex(&_6, toml_xarrayable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_6, "__construct", NULL, 16, &msg);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_6, "toml/Parser.zep", 1113 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Toml_Parser, syntaxError) {

	zend_long ZEPHIR_LAST_CALL_STATUS, line = 0;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *msg_param = NULL, *token = NULL, token_sub, __$null, _13, _0$$3, _2$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3;
	zval msg, name, value, tokenMsg, _3$$3, _9$$3, _12$$3, _10$$4, _11$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&tokenMsg);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&token_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &msg_param, &token);

	if (UNEXPECTED(Z_TYPE_P(msg_param) != IS_STRING && Z_TYPE_P(msg_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'msg' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(msg_param) == IS_STRING)) {
		zephir_get_strval(&msg, msg_param);
	} else {
		ZEPHIR_INIT_VAR(&msg);
		ZVAL_EMPTY_STRING(&msg);
	}
	if (!token) {
		token = &token_sub;
		token = &__$null;
	}


	if (!(ZEPHIR_IS_EMPTY(token))) {
		zephir_read_property(&_2$$3, token, SL("id"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_0$$3, toml_lexer_ce, "tokenname", &_1, 0, &_2$$3);
		zephir_check_call_status();
		zephir_get_strval(&_3$$3, &_0$$3);
		ZEPHIR_CPY_WRT(&name, &_3$$3);
		zephir_read_property(&_4$$3, token, SL("line"), PH_NOISY_CC | PH_READONLY);
		line = zephir_get_numberval(&_4$$3);
		zephir_read_property(&_5$$3, token, SL("value"), PH_NOISY_CC | PH_READONLY);
		zephir_get_strval(&value, &_5$$3);
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, " Token: %s line: %s");
		ZVAL_LONG(&_7$$3, line);
		ZEPHIR_CALL_FUNCTION(&_8$$3, "sprintf", NULL, 58, &_6$$3, &name, &_7$$3);
		zephir_check_call_status();
		zephir_get_strval(&_9$$3, &_8$$3);
		ZEPHIR_CPY_WRT(&tokenMsg, &_9$$3);
		zephir_read_property(&_7$$3, token, SL("isSingle"), PH_NOISY_CC | PH_READONLY);
		if (!(zephir_is_true(&_7$$3))) {
			ZEPHIR_INIT_VAR(&_10$$4);
			ZEPHIR_CONCAT_VSVS(&_10$$4, &tokenMsg, " value { '", &value, "' }.");
			ZEPHIR_CPY_WRT(&tokenMsg, &_10$$4);
		} else {
			ZEPHIR_INIT_VAR(&_11$$5);
			ZEPHIR_CONCAT_VS(&_11$$5, &tokenMsg, ".");
			ZEPHIR_CPY_WRT(&tokenMsg, &_11$$5);
		}
		ZEPHIR_INIT_VAR(&_12$$3);
		ZEPHIR_CONCAT_VV(&_12$$3, &msg, &tokenMsg);
		ZEPHIR_CPY_WRT(&msg, &_12$$3);
	}
	ZEPHIR_INIT_VAR(&_13);
	object_init_ex(&_13, toml_xarrayable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_13, "__construct", NULL, 16, &msg);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_13, "toml/Parser.zep", 1133 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

zend_object *zephir_init_properties_Toml_Parser(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("_expStack"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("_expStack"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

