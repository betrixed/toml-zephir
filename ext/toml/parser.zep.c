
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "ext/spl/spl_fixedarray.h"
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

	zend_declare_property_long(toml_parser_ce, SL("_expSetId"), -1, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_expStack"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_stackTop"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_keyRegex"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_valRegex"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_regEString"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_regLString"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_parser_ce, SL("_regMLString"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_KEY"), 0);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_SCALER"), 1);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_LSTRING"), 2);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_MLSTRING"), 3);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_BSTRING"), 4);

	zephir_declare_class_constant_long(toml_parser_ce, SL("E_ALL"), 5);

	zephir_declare_class_constant_string(toml_parser_ce, SL("IM_SPACE"), "/(\\s+)/");

	return SUCCESS;

}

/**
 * Set the expression set to the previous on the
 * expression set stack (a stack of integers) 
 */
PHP_METHOD(Toml_Parser, popExpSet) {

	zval stack, _0, _1$$3, _2$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS, value = 0, top = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&stack);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&stack);
	zephir_read_property(&stack, this_ptr, SL("_expStack"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_stackTop"), PH_NOISY_CC);
	top = zephir_get_intval(&_0);
	if (top > 0) {
		top = (top - 1);
		ZVAL_LONG(&_2$$3, top);
		ZEPHIR_CALL_METHOD(&_1$$3, &stack, "offsetget", NULL, 0, &_2$$3);
		zephir_check_call_status();
		value = zephir_get_intval(&_1$$3);
		ZVAL_LONG(&_2$$3, value);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpset", NULL, 15, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_ZVAL_NREF(_2$$3);
		ZVAL_LONG(&_2$$3, top);
		zephir_update_property_zval(this_ptr, SL("_stackTop"), &_2$$3);
		RETURN_MM_NULL();
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "popExpSet on empty stack", "toml/Parser.zep", 63);
	return;

}

/**
 * Push a known expression set defined by a 
 * constant
 * @param int $value
 */
PHP_METHOD(Toml_Parser, pushExpSet) {

	zval *value_param = NULL, stack, _0, _1, _3, _4, _2$$3;
	zend_long value, ZEPHIR_LAST_CALL_STATUS, ct = 0, top = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&stack);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	if (UNEXPECTED(Z_TYPE_P(value_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'value' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	value = Z_LVAL_P(value_param);


	ZEPHIR_OBS_VAR(&stack);
	zephir_read_property(&stack, this_ptr, SL("_expStack"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_stackTop"), PH_NOISY_CC);
	top = zephir_get_intval(&_0);
	ZEPHIR_CALL_METHOD(&_1, &stack, "count", NULL, 0);
	zephir_check_call_status();
	ct = zephir_get_intval(&_1);
	if (ct <= top) {
		ZVAL_LONG(&_2$$3, (top + 16));
		ZEPHIR_CALL_METHOD(NULL, &stack, "setsize", NULL, 0, &_2$$3);
		zephir_check_call_status();
	}
	zephir_read_property(&_3, this_ptr, SL("_expSetId"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_4, top);
	ZEPHIR_CALL_METHOD(NULL, &stack, "offsetset", NULL, 0, &_4, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_ZVAL_NREF(_4);
	ZVAL_LONG(&_4, (top + 1));
	zephir_update_property_zval(this_ptr, SL("_stackTop"), &_4);
	ZVAL_LONG(&_4, value);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpset", NULL, 15, &_4);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Parser, getExpSet) {

	zephir_fcall_cache_entry *_0 = NULL, *_6 = NULL;
	zval *value_param = NULL, result, _1$$4, _2$$6, _3$$8, _4$$10, _5$$12;
	zend_long value, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$8);
	ZVAL_UNDEF(&_4$$10);
	ZVAL_UNDEF(&_5$$12);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	if (UNEXPECTED(Z_TYPE_P(value_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'value' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	value = Z_LVAL_P(value_param);


	do {
		if (value == 0) {
			ZEPHIR_OBS_VAR(&result);
			zephir_read_static_property_ce(&result, toml_parser_ce, SL("_keyRegex"), PH_NOISY_CC);
			if (ZEPHIR_IS_EMPTY(&result)) {
				zephir_read_static_property_ce(&_1$$4, toml_lexer_ce, SL("KeyList"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getexpset", &_0, 0, &_1$$4);
				zephir_check_call_status();
				zend_update_static_property(toml_parser_ce, ZEND_STRL("_keyRegex"), &result);
			}
			break;
		}
		if (value == 4) {
			ZEPHIR_OBS_NVAR(&result);
			zephir_read_static_property_ce(&result, toml_parser_ce, SL("_regEString"), PH_NOISY_CC);
			if (ZEPHIR_IS_EMPTY(&result)) {
				zephir_read_static_property_ce(&_2$$6, toml_lexer_ce, SL("BasicString"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getexpset", &_0, 0, &_2$$6);
				zephir_check_call_status();
				zend_update_static_property(toml_parser_ce, ZEND_STRL("_regEString"), &result);
			}
			break;
		}
		if (value == 2) {
			ZEPHIR_OBS_NVAR(&result);
			zephir_read_static_property_ce(&result, toml_parser_ce, SL("_regLString"), PH_NOISY_CC);
			if (ZEPHIR_IS_EMPTY(&result)) {
				zephir_read_static_property_ce(&_3$$8, toml_lexer_ce, SL("LiteralString"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getexpset", &_0, 0, &_3$$8);
				zephir_check_call_status();
				zend_update_static_property(toml_parser_ce, ZEND_STRL("_regLString"), &result);
			}
			break;
		}
		if (value == 1) {
			ZEPHIR_OBS_NVAR(&result);
			zephir_read_static_property_ce(&result, toml_parser_ce, SL("_valRegex"), PH_NOISY_CC);
			if (ZEPHIR_IS_EMPTY(&result)) {
				zephir_read_static_property_ce(&_4$$10, toml_lexer_ce, SL("ScalerList"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getexpset", &_0, 0, &_4$$10);
				zephir_check_call_status();
				zend_update_static_property(toml_parser_ce, ZEND_STRL("_valRegex"), &result);
			}
			break;
		}
		if (value == 3) {
			ZEPHIR_OBS_NVAR(&result);
			zephir_read_static_property_ce(&result, toml_parser_ce, SL("_regMLString"), PH_NOISY_CC);
			if (ZEPHIR_IS_EMPTY(&result)) {
				zephir_read_static_property_ce(&_5$$12, toml_lexer_ce, SL("LiteralMLString"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getexpset", &_0, 0, &_5$$12);
				zephir_check_call_status();
				zend_update_static_property(toml_parser_ce, ZEND_STRL("_regMLString"), &result);
			}
			break;
		}
		if (value == 5) {
			ZEPHIR_CALL_CE_STATIC(&result, toml_lexer_ce, "getallregex", &_6, 0);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "Not a defined table constant for getExpSet", "toml/Parser.zep", 132);
		return;
	} while(0);

	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Parser, setExpSet) {

	zval _2$$8;
	zval *value_param = NULL, obj, _3, _0$$8, _1$$8;
	zend_long value, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&obj);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$8);
	ZVAL_UNDEF(&_1$$8);
	ZVAL_UNDEF(&_2$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	if (UNEXPECTED(Z_TYPE_P(value_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'value' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	value = Z_LVAL_P(value_param);


	do {
		if (value == 0) {
			ZEPHIR_OBS_VAR(&obj);
			zephir_read_static_property_ce(&obj, toml_parser_ce, SL("_keyRegex"), PH_NOISY_CC);
			break;
		}
		if (value == 1) {
			ZEPHIR_OBS_NVAR(&obj);
			zephir_read_static_property_ce(&obj, toml_parser_ce, SL("_valRegex"), PH_NOISY_CC);
			break;
		}
		if (value == 2) {
			ZEPHIR_OBS_NVAR(&obj);
			zephir_read_static_property_ce(&obj, toml_parser_ce, SL("_regLString"), PH_NOISY_CC);
			break;
		}
		if (value == 4) {
			ZEPHIR_OBS_NVAR(&obj);
			zephir_read_static_property_ce(&obj, toml_parser_ce, SL("_regEString"), PH_NOISY_CC);
			break;
		}
		if (value == 3) {
			ZEPHIR_OBS_NVAR(&obj);
			zephir_read_static_property_ce(&obj, toml_parser_ce, SL("_regMLString"), PH_NOISY_CC);
			break;
		}
		ZEPHIR_INIT_VAR(&_0$$8);
		object_init_ex(&_0$$8, toml_xarrayable_ce);
		ZEPHIR_SINIT_VAR(_1$$8);
		ZVAL_LONG(&_1$$8, value);
		ZEPHIR_INIT_VAR(&_2$$8);
		ZEPHIR_CONCAT_SV(&_2$$8, "Invalid expression set constant ", &_1$$8);
		ZEPHIR_CALL_METHOD(NULL, &_0$$8, "__construct", NULL, 16, &_2$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$8, "toml/Parser.zep", 156 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_INIT_ZVAL_NREF(_3);
	ZVAL_LONG(&_3, value);
	zephir_update_property_zval(this_ptr, SL("_expSetId"), &_3);
	zephir_read_property(&_3, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_3, "setexpset", NULL, 0, &obj);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Setup class constants
 */
PHP_METHOD(Toml_Parser, __construct) {

	zval ts, _0, _1, _2, _3, _4;
	zephir_fcall_cache_entry *_5 = NULL, *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, toml_keytable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 2);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_root"), &_0);
	zephir_read_property(&_1, this_ptr, SL("_root"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("_table"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, spl_ce_SplFixedArray);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 17);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_expStack"), &_2);
	ZEPHIR_INIT_ZVAL_NREF(_3);
	ZVAL_LONG(&_3, 0);
	zephir_update_property_zval(this_ptr, SL("_stackTop"), &_3);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getexpset", &_5, 0, &_3);
	zephir_check_call_status();
	zend_update_static_property(toml_parser_ce, ZEND_STRL("_keyRegex"), &_4);
	ZVAL_LONG(&_3, 1);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getexpset", &_5, 0, &_3);
	zephir_check_call_status();
	zend_update_static_property(toml_parser_ce, ZEND_STRL("_valRegex"), &_4);
	ZVAL_LONG(&_3, 4);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getexpset", &_5, 0, &_3);
	zephir_check_call_status();
	zend_update_static_property(toml_parser_ce, ZEND_STRL("_regEString"), &_4);
	ZVAL_LONG(&_3, 2);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getexpset", &_5, 0, &_3);
	zephir_check_call_status();
	zend_update_static_property(toml_parser_ce, ZEND_STRL("_regLString"), &_4);
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getexpset", &_5, 0, &_3);
	zephir_check_call_status();
	zend_update_static_property(toml_parser_ce, ZEND_STRL("_regMLString"), &_4);
	ZEPHIR_INIT_VAR(&ts);
	object_init_ex(&ts, toml_tokenstream_ce);
	ZEPHIR_CALL_METHOD(NULL, &ts, "__construct", NULL, 5);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_4, toml_lexer_ce, "getallsingles", &_6, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &ts, "setsingles", NULL, 7, &_4);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 25);
	ZEPHIR_CALL_METHOD(NULL, &ts, "setunknownid", NULL, 8, &_3);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 10);
	ZEPHIR_CALL_METHOD(NULL, &ts, "setnewlineid", NULL, 9, &_3);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 4);
	ZEPHIR_CALL_METHOD(NULL, &ts, "seteosid", NULL, 10, &_3);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_ts"), &ts);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setexpset", NULL, 15, &_3);
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


	ZEPHIR_CALL_FUNCTION(&_0, "is_file", NULL, 18, &path);
	zephir_check_call_status();
	if (!zephir_is_true(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, toml_xarrayable_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SV(&_2$$3, "File path not a file ", &path);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 16, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "toml/Parser.zep", 199 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&toml);
	zephir_file_get_contents(&toml, &path TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "H*");
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "EFBBBF");
	ZEPHIR_CALL_FUNCTION(&_5, "pack", NULL, 19, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_SVS(&_6, "/^", &_5, "/");
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "");
	ZEPHIR_CALL_FUNCTION(&_7, "preg_replace", NULL, 20, &_6, &_3, &toml);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&toml, &_7);
	ZEPHIR_INIT_VAR(&parser);
	object_init_ex(&parser, toml_parser_ce);
	ZEPHIR_CALL_METHOD(NULL, &parser, "__construct", NULL, 21);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&parser, "parse", NULL, 22, &toml);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Toml_Parser, prepareInput) {

	zval _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input, input_sub, _0, _1, _2, iclean, _4, _5, _6, _7, _8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&iclean);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &input);



	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "//u");
	zephir_preg_match(&_1, &_2, input, &_0, 0, 0 , 0  TSRMLS_CC);
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "The TOML input does not appear to be valid UTF-8.", "toml/Parser.zep", 215);
		return;
	}
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "\r\n");
	zephir_array_fast_append(&_3, &_4);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "\r");
	zephir_array_fast_append(&_3, &_4);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "\n");
	ZEPHIR_INIT_VAR(&iclean);
	zephir_fast_str_replace(&iclean, &_3, &_4, input TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "\t");
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, " ");
	zephir_fast_str_replace(&_5, &_6, &_7, &iclean TSRMLS_CC);
	ZEPHIR_CPY_WRT(&iclean, &_5);
	zephir_read_property(&_8, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_8, "setinput", NULL, 0, &iclean);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Toml_Parser, parse) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, _0, _1;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

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


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "prepareinput", NULL, 23, &input);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("_ts"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "implementation", NULL, 24, &_0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("_root"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "toarray", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Toml_Parser, getRoot) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_root");

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
				ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "parsecomment", &_3, 25, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_2$$4);
				break;
			}
			if (tokenId == 7 || tokenId == 18 || tokenId == 9 || tokenId == 5) {
				ZEPHIR_CALL_METHOD(&_4$$5, this_ptr, "parsekeyvalue", &_5, 26, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_4$$5);
				break;
			}
			if (tokenId == 12) {
				ZEPHIR_CALL_METHOD(&_6$$6, this_ptr, "parsetablepath", &_7, 27, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_6$$6);
				break;
			}
			if (tokenId == 11 || tokenId == 10) {
				ZEPHIR_CALL_METHOD(&_8$$7, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_8$$7);
				break;
			}
			ZEPHIR_CALL_METHOD(&_9$$8, ts, "gettoken", &_10, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$8);
			ZVAL_STRING(&_11$$8, "Expect Key = , [Path] or # Comment");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_12, 28, &_11$$8, &_9$$8);
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

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/^(\\V*)/");
	ZEPHIR_CALL_METHOD(NULL, ts, "moveregex", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	RETURN_MM_LONG(tokenId);

}

/**
 *  Get a value that is not a table or array.
 *  Predict and setup parse for simple value, using peek $tokenId
 */
PHP_METHOD(Toml_Parser, getSimpleValue) {

	zval *tokenId_param = NULL, ts, value, _4, _5, _0$$3, _1$$3, _2$$6, _3$$6, _6$$10, _7$$13, _8$$13;
	zend_long tokenId, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_7$$13);
	ZVAL_UNDEF(&_8$$13);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tokenId_param);

	if (UNEXPECTED(Z_TYPE_P(tokenId_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tokenId' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	tokenId = Z_LVAL_P(tokenId_param);


	ZEPHIR_OBS_VAR(&ts);
	zephir_read_property(&ts, this_ptr, SL("_ts"), PH_NOISY_CC);
	if (tokenId == 9) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "/^(\\'\\'\\')/");
		ZEPHIR_CALL_METHOD(&_0$$3, &ts, "moveregex", NULL, 0, &_1$$3);
		zephir_check_call_status();
		if (zephir_is_true(&_0$$3)) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsemlstring", NULL, 29, &ts);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &ts, "accepttoken", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseliteralstring", NULL, 30, &ts);
			zephir_check_call_status();
		}
		RETURN_CCTOR(&value);
	} else if (tokenId == 7) {
		ZEPHIR_INIT_VAR(&_3$$6);
		ZVAL_STRING(&_3$$6, "/^(\\\"\\\"\\\")/");
		ZEPHIR_CALL_METHOD(&_2$$6, &ts, "moveregex", NULL, 0, &_3$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_2$$6)) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsemlescapestring", NULL, 31, &ts);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &ts, "accepttoken", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseescapestring", NULL, 32, &ts);
			zephir_check_call_status();
		}
		RETURN_CCTOR(&value);
	}
	ZVAL_LONG(&_4, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpset", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_5);
	do {
		if (tokenId == 5) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseinteger", NULL, 33, &ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 2) {
			ZEPHIR_CALL_METHOD(&_6$$10, &ts, "getvalue", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_STRING(&_6$$10, "true")) {
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_BOOL(&value, 1);
			} else {
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_BOOL(&value, 0);
			}
			break;
		}
		if (tokenId == 22) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsefloat", NULL, 34, &ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 3) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parsedatetime", NULL, 35, &ts);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_CALL_METHOD(&_7$$13, &ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$13);
		ZVAL_STRING(&_8$$13, "Value type expected");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 28, &_8$$13, &_7$$13);
		zephir_check_call_status();
		break;
	} while(0);

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpset", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(&value);

}

PHP_METHOD(Toml_Parser, valueWrap) {

	zval *s_param = NULL;
	zval s;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&s);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &s_param);

	if (UNEXPECTED(Z_TYPE_P(s_param) != IS_STRING && Z_TYPE_P(s_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 's' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(s_param) == IS_STRING)) {
		zephir_get_strval(&s, s_param);
	} else {
		ZEPHIR_INIT_VAR(&s);
		ZVAL_EMPTY_STRING(&s);
	}


	ZEPHIR_CONCAT_SVS(return_value, ". Value { ", &s, " }.");
	RETURN_MM();

}

/**
 * A call to expected regular expression failed,
 * so find out what was there by using a more general 
 * expression of space / something on rest of line
 * @param string $msg
 */
PHP_METHOD(Toml_Parser, regexError) {

	zephir_fcall_cache_entry *_6 = NULL, *_8 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId$$4 = 0;
	zval *msg_param = NULL, ts, value, _0, _1, _2, _3, _4$$3, _5$$3, _7$$3, _9$$4, _10$$4, _12$$4, _14$$4, _15$$4, _16$$4;
	zval msg, name$$4, _13$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&name$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&ts);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);

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


	ZEPHIR_OBS_VAR(&ts);
	zephir_read_property(&ts, this_ptr, SL("_ts"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, &ts, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_VSV(&_1, &msg, " on line ", &_0);
	zephir_get_strval(&msg, &_1);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "/^(\\s*\\V*)/");
	ZEPHIR_CALL_METHOD(&_2, &ts, "moveregex", NULL, 0, &_3);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_CALL_METHOD(&value, &ts, "getvalue", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, toml_xarrayable_ce);
		ZEPHIR_CALL_SELF(&_5$$3, "valuewrap", &_6, 36, &value);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_VV(&_7$$3, &msg, &_5$$3);
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", &_8, 16, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "toml/Parser.zep", 366 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_CALL_METHOD(&_9$$4, &ts, "movenextid", NULL, 0);
		zephir_check_call_status();
		tokenId$$4 = zephir_get_intval(&_9$$4);
		ZEPHIR_CALL_METHOD(&value, &ts, "getvalue", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_12$$4, tokenId$$4);
		ZEPHIR_CALL_CE_STATIC(&_10$$4, toml_lexer_ce, "tokenname", &_11, 0, &_12$$4);
		zephir_check_call_status();
		zephir_get_strval(&_13$$4, &_10$$4);
		ZEPHIR_CPY_WRT(&name$$4, &_13$$4);
		ZEPHIR_INIT_VAR(&_14$$4);
		object_init_ex(&_14$$4, toml_xarrayable_ce);
		ZEPHIR_CALL_SELF(&_15$$4, "valuewrap", &_6, 36, &value);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_16$$4);
		ZEPHIR_CONCAT_VSVV(&_16$$4, &msg, ". Got ", &name$$4, &_15$$4);
		ZEPHIR_CALL_METHOD(NULL, &_14$$4, "__construct", &_8, 16, &_16$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_14$$4, "toml/Parser.zep", 375 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Parser, parseKeyValue) {

	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zend_bool isFromInlineTable;
	zval *ts, ts_sub, *isFromInlineTable_param = NULL, keyName, value, token, _0, _1, _4, _5, _7, _2$$3, _3$$3, _6$$4, _8$$5, _9$$7, _10$$8, _11$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&keyName);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$9);

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


	ZEPHIR_CALL_METHOD(&keyName, this_ptr, "parsekeyname", NULL, 37, ts);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "offsetexists", NULL, 0, &keyName);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "Duplicate key");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 28, &_3$$3, &_2$$3);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "/^(\\s*=\\s*)/");
	ZEPHIR_CALL_METHOD(&_4, ts, "moveregex", NULL, 0, &_5);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_4)) {
		ZEPHIR_INIT_VAR(&_6$$4);
		ZVAL_STRING(&_6$$4, "Expected T_EQUAL (=)");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "regexerror", NULL, 38, &_6$$4);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&_7);
	zephir_read_property(&_7, &token, SL("id"), PH_NOISY_CC);
	tokenId = zephir_get_intval(&_7);
	if (tokenId == 12) {
		ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&value, this_ptr, "parsearray", NULL, 39, ts);
		zephir_check_call_status();
		zephir_read_property(&_8$$5, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_8$$5, "offsetset", NULL, 0, &keyName, &value);
		zephir_check_call_status();
	} else if (tokenId == 14) {
		ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "parseinlinetable", NULL, 40, ts, &keyName);
		zephir_check_call_status();
	} else {
		ZVAL_LONG(&_9$$7, tokenId);
		ZEPHIR_CALL_METHOD(&value, this_ptr, "getsimplevalue", NULL, 41, &_9$$7);
		zephir_check_call_status();
		zephir_read_property(&_9$$7, this_ptr, SL("_table"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_9$$7, "offsetset", NULL, 0, &keyName, &value);
		zephir_check_call_status();
	}
	if (!(isFromInlineTable)) {
		ZEPHIR_CALL_METHOD(&_10$$8, this_ptr, "finishline", NULL, 42, ts);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_10$$8);
	} else {
		ZEPHIR_CALL_METHOD(&_11$$9, ts, "movenextid", NULL, 0);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_11$$9);
	}
	RETURN_MM_LONG(tokenId);

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
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseescapestring", NULL, 32, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 9) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseliteralstring", NULL, 30, ts);
			zephir_check_call_status();
			break;
		}
		if (tokenId == 5) {
			ZEPHIR_CALL_METHOD(&value, this_ptr, "parseinteger", NULL, 33, ts);
			zephir_check_call_status();
			break;
		}
		ZEPHIR_CALL_METHOD(&_1$$7, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_2$$7);
		ZVAL_STRING(&_2$$7, "Improper key");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 28, &_2$$7, &_1$$7);
		zephir_check_call_status();
		break;
	} while(0);

	RETURN_CCTOR(&value);

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
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_4$$3, &_3$$3);
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
		ZEPHIR_CALL_METHOD(&_11$$4, ts, "gettoken", NULL, 13);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "Invalid integer number: leading zeros are not allowed");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_12$$4, &_11$$4);
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
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_4$$3, &_3$$3);
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
		ZEPHIR_CALL_METHOD(&_11$$4, ts, "gettoken", NULL, 13);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "Invalid float number: leading zeros are not allowed");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_12$$4, &_11$$4);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_FUNCTION("floatval", NULL, 43, &value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param TokenStream $ts
 * @param type $stripQuote
 * @return string
 */
PHP_METHOD(Toml_Parser, parseEscapeString) {

	zend_bool _2$$3, _3$$3;
	zval value, _10$$5, _13$$6;
	zephir_fcall_cache_entry *_5 = NULL, *_7 = NULL, *_9 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, result, _1, _14$$3, _15$$3, _4$$4, _6$$4, _8$$5, _11$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_13$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpset", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	while (1) {
		if (!(tokenId != 7)) {
			break;
		}
		_2$$3 = (tokenId == 10);
		if (!(_2$$3)) {
			_2$$3 = (tokenId == 4);
		}
		_3$$3 = _2$$3;
		if (!(_3$$3)) {
			_3$$3 = (tokenId == 20);
		}
		if (_3$$3) {
			ZEPHIR_CALL_METHOD(&_4$$4, ts, "gettoken", &_5, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZVAL_STRING(&_6$$4, "Unfinished string value");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_7, 28, &_6$$4, &_4$$4);
			zephir_check_call_status();
		} else if (tokenId == 19) {
			ZEPHIR_CALL_METHOD(&_8$$5, this_ptr, "parseescapedcharacter", &_9, 44, ts);
			zephir_check_call_status();
			zephir_get_strval(&_10$$5, &_8$$5);
			ZEPHIR_CPY_WRT(&value, &_10$$5);
		} else {
			ZEPHIR_CALL_METHOD(&_11$$6, ts, "getvalue", &_12, 0);
			zephir_check_call_status();
			zephir_get_strval(&_13$$6, &_11$$6);
			ZEPHIR_CPY_WRT(&value, &_13$$6);
		}
		ZEPHIR_INIT_LNVAR(_14$$3);
		ZEPHIR_CONCAT_VV(&_14$$3, &result, &value);
		ZEPHIR_CPY_WRT(&result, &_14$$3);
		ZEPHIR_CALL_METHOD(&_15$$3, ts, "movenextid", NULL, 12);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_15$$3);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpset", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(&result);

}

PHP_METHOD(Toml_Parser, parseMLEscapeString) {

	zval result, _10$$9, _12$$10;
	zend_bool doLoop = 0, _8$$7, _9$$7;
	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_15 = NULL, *_19 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1, _2$$3, _3$$6, _5$$6, _7$$8, _11$$9, _13$$10, _14$$11, _16$$11, _17$$11, _18$$12, _20$$12, _21$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_12$$10);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZVAL_LONG(&_0, 4);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpset", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	if (tokenId == 10) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "movenextid", NULL, 12);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_2$$3);
	}
	doLoop = 1;
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (tokenId == 6) {
				doLoop = 0;
				break;
			}
			if (tokenId == 4) {
				ZEPHIR_CALL_METHOD(&_3$$6, ts, "gettoken", &_4, 0);
				zephir_check_call_status();
				ZVAL_LONG(&_5$$6, 6);
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", &_6, 45, &_3$$6, &_5$$6);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 20) {
				do {
					ZEPHIR_CALL_METHOD(&_7$$8, ts, "movenextid", NULL, 12);
					zephir_check_call_status();
					tokenId = zephir_get_intval(&_7$$8);
					_8$$7 = (tokenId == 11);
					if (!(_8$$7)) {
						_8$$7 = (tokenId == 10);
					}
					_9$$7 = _8$$7;
					if (!(_9$$7)) {
						_9$$7 = (tokenId == 20);
					}
				} while (_9$$7);
				break;
			}
			if (tokenId == 11) {
				ZEPHIR_INIT_LNVAR(_10$$9);
				ZEPHIR_CONCAT_VS(&_10$$9, &result, " ");
				ZEPHIR_CPY_WRT(&result, &_10$$9);
				ZEPHIR_CALL_METHOD(&_11$$9, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_11$$9);
				break;
			}
			if (tokenId == 10) {
				ZEPHIR_INIT_LNVAR(_12$$10);
				ZEPHIR_CONCAT_VS(&_12$$10, &result, "\n");
				ZEPHIR_CPY_WRT(&result, &_12$$10);
				ZEPHIR_CALL_METHOD(&_13$$10, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_13$$10);
				break;
			}
			if (tokenId == 19) {
				ZEPHIR_CALL_METHOD(&_14$$11, this_ptr, "parseescapedcharacter", &_15, 44, ts);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_16$$11);
				ZEPHIR_CONCAT_VV(&_16$$11, &result, &_14$$11);
				zephir_get_strval(&result, &_16$$11);
				ZEPHIR_CALL_METHOD(&_17$$11, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_17$$11);
				break;
			}
			ZEPHIR_CALL_METHOD(&_18$$12, ts, "getvalue", &_19, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_20$$12);
			ZEPHIR_CONCAT_VV(&_20$$12, &result, &_18$$12);
			zephir_get_strval(&result, &_20$$12);
			ZEPHIR_CALL_METHOD(&_21$$12, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_21$$12);
			break;
		} while(0);

	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpset", NULL, 0);
	zephir_check_call_status();
	RETURN_CTOR(&result);

}

/**
 * 
 * @param TokenStream $ts
 * @param bool $stripQuote
 * @return string
 */
PHP_METHOD(Toml_Parser, parseLiteralString) {

	zend_bool _1$$3;
	zval result, _11$$5, _12$$5;
	zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL, *_8 = NULL, *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, id = 0;
	zval *ts, ts_sub, token, _0, _6$$3, _7$$3, _2$$4, _4$$4, _9$$5, _13$$5, _14$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, &token, SL("id"), PH_NOISY_CC);
	id = zephir_get_intval(&_0);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	while (1) {
		if (!(id != 9)) {
			break;
		}
		_1$$3 = (id == 10);
		if (!(_1$$3)) {
			_1$$3 = (id == 4);
		}
		if (_1$$3) {
			ZEPHIR_CALL_METHOD(&_2$$4, ts, "gettoken", &_3, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_4$$4);
			ZVAL_STRING(&_4$$4, "Incomplete literal string");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_4$$4, &_2$$4);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "/([^\\x{0}-\\x{19}\\x{27}]+)/u");
		ZEPHIR_CALL_METHOD(&_6$$3, ts, "moveregex", &_8, 0, &_7$$3);
		zephir_check_call_status();
		if (zephir_is_true(&_6$$3)) {
			ZEPHIR_CALL_METHOD(&_9$$5, ts, "getvalue", &_10, 0);
			zephir_check_call_status();
			zephir_get_strval(&_11$$5, &_9$$5);
			ZEPHIR_INIT_LNVAR(_12$$5);
			ZEPHIR_CONCAT_VV(&_12$$5, &result, &_11$$5);
			ZEPHIR_CPY_WRT(&result, &_12$$5);
			ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_13$$5);
			zephir_read_property(&_13$$5, &token, SL("id"), PH_NOISY_CC);
			id = zephir_get_intval(&_13$$5);
		} else {
			ZEPHIR_INIT_NVAR(&_14$$6);
			ZVAL_STRING(&_14$$6, "Bad literal string value");
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_5, 28, &_14$$6, &token);
			zephir_check_call_status();
		}
	}
	ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", NULL, 0);
	zephir_check_call_status();
	RETURN_CTOR(&result);

}

PHP_METHOD(Toml_Parser, parseMLString) {

	zend_bool doLoop = 0;
	zval result, _3$$5, _11$$8, _12$$8;
	zephir_fcall_cache_entry *_6 = NULL, *_8 = NULL, *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1, _2$$3, _4$$5, _5$$7, _7$$7, _9$$8, _13$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZVAL_LONG(&_0, 3);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpset", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&result);
	ZVAL_STRING(&result, "");
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	if (tokenId == 10) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "movenextid", NULL, 12);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_2$$3);
	}
	doLoop = 1;
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (tokenId == 10) {
				ZEPHIR_INIT_LNVAR(_3$$5);
				ZEPHIR_CONCAT_VS(&_3$$5, &result, "\n");
				ZEPHIR_CPY_WRT(&result, &_3$$5);
				ZEPHIR_CALL_METHOD(&_4$$5, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_4$$5);
				break;
			}
			if (tokenId == 8) {
				doLoop = 0;
				break;
			}
			if (tokenId == 4) {
				ZEPHIR_CALL_METHOD(&_5$$7, ts, "gettoken", &_6, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_7$$7);
				ZVAL_STRING(&_7$$7, "Expected token { ''' }");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", &_8, 28, &_7$$7, &_5$$7);
				zephir_check_call_status();
				break;
			}
			ZEPHIR_CALL_METHOD(&_9$$8, ts, "getvalue", &_10, 0);
			zephir_check_call_status();
			zephir_get_strval(&_11$$8, &_9$$8);
			ZEPHIR_INIT_LNVAR(_12$$8);
			ZEPHIR_CONCAT_VV(&_12$$8, &result, &_11$$8);
			ZEPHIR_CPY_WRT(&result, &_12$$8);
			ZEPHIR_CALL_METHOD(&_13$$8, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_13$$8);
			break;
		} while(0);

	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpset", NULL, 0);
	zephir_check_call_status();
	RETURN_CTOR(&result);

}

PHP_METHOD(Toml_Parser, parseEscapedCharacter) {

	zval result, value, _1, _5$$7, _8$$8, _14$$12, _15$$12, _22$$14;
	zephir_fcall_cache_entry *_4 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, ct = 0;
	zval *ts, ts_sub, matches, _0, _2$$7, _3$$7, _6$$8, _7$$8, _9$$11, _10$$11, _11$$11, _13$$12, _16$$13, _17$$13, _18$$14, _19$$14, _20$$14, _21$$14, _23$$15, _24$$15, _25$$15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$7);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_16$$13);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_18$$14);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$15);
	ZVAL_UNDEF(&_25$$15);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_22$$14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "getvalue", NULL, 0);
	zephir_check_call_status();
	zephir_get_strval(&_1, &_0);
	ZEPHIR_CPY_WRT(&value, &_1);
	ct = zephir_fast_strlen_ev(&value);
	if (ct == 1) {
		do {
			if (ZEPHIR_IS_STRING(&value, "n")) {
				ZEPHIR_INIT_VAR(&result);
				ZVAL_STRING(&result, "\n");
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "t")) {
				ZEPHIR_INIT_NVAR(&result);
				ZVAL_STRING(&result, "\t");
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "r")) {
				ZEPHIR_INIT_NVAR(&result);
				ZVAL_STRING(&result, "\r");
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "b")) {
				ZVAL_LONG(&_2$$7, 8);
				ZEPHIR_CALL_FUNCTION(&_3$$7, "chr", &_4, 46, &_2$$7);
				zephir_check_call_status();
				zephir_get_strval(&_5$$7, &_3$$7);
				ZEPHIR_CPY_WRT(&result, &_5$$7);
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "f")) {
				ZVAL_LONG(&_6$$8, 12);
				ZEPHIR_CALL_FUNCTION(&_7$$8, "chr", &_4, 46, &_6$$8);
				zephir_check_call_status();
				zephir_get_strval(&_8$$8, &_7$$8);
				ZEPHIR_CPY_WRT(&result, &_8$$8);
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "\\")) {
				ZEPHIR_INIT_NVAR(&result);
				ZVAL_STRING(&result, "\\");
				break;
			}
			if (ZEPHIR_IS_STRING(&value, "\"")) {
				ZEPHIR_INIT_NVAR(&result);
				ZVAL_STRING(&result, "\"");
				break;
			}
			ZEPHIR_INIT_VAR(&_9$$11);
			object_init_ex(&_9$$11, toml_xarrayable_ce);
			ZEPHIR_CALL_METHOD(&_10$$11, ts, "getline", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_11$$11);
			ZEPHIR_CONCAT_SVSV(&_11$$11, "Invalid escape line ", &_10$$11, " \\", &value);
			ZEPHIR_CALL_METHOD(NULL, &_9$$11, "__construct", &_12, 16, &_11$$11);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_9$$11, "toml/Parser.zep", 691 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} while(0);

	} else if (ct == 5) {
		ZEPHIR_INIT_VAR(&_13$$12);
		ZEPHIR_INIT_VAR(&_14$$12);
		ZEPHIR_CONCAT_SVS(&_14$$12, "\"\\", &value, "\"");
		zephir_json_decode(&_13$$12, &_14$$12, 0 );
		zephir_get_strval(&_15$$12, &_13$$12);
		ZEPHIR_CPY_WRT(&result, &_15$$12);
	} else {
		ZEPHIR_INIT_VAR(&matches);
		ZVAL_NULL(&matches);
		ZEPHIR_INIT_VAR(&_16$$13);
		ZEPHIR_INIT_VAR(&_17$$13);
		ZVAL_STRING(&_17$$13, "/U([0-9a-fA-F]{4})([0-9a-fA-F]{4})/");
		zephir_preg_match(&_16$$13, &_17$$13, &value, &matches, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(&_16$$13)) {
			ZEPHIR_INIT_VAR(&_18$$14);
			zephir_array_fetch_long(&_19$$14, &matches, 1, PH_NOISY | PH_READONLY, "toml/Parser.zep", 702 TSRMLS_CC);
			zephir_array_fetch_long(&_20$$14, &matches, 2, PH_NOISY | PH_READONLY, "toml/Parser.zep", 702 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_21$$14);
			ZEPHIR_CONCAT_SVSVS(&_21$$14, "\"\\u", &_19$$14, "\\u", &_20$$14, "\"");
			zephir_json_decode(&_18$$14, &_21$$14, 0 );
			zephir_get_strval(&_22$$14, &_18$$14);
			ZEPHIR_CPY_WRT(&result, &_22$$14);
		} else {
			ZEPHIR_INIT_VAR(&_23$$15);
			object_init_ex(&_23$$15, toml_xarrayable_ce);
			ZEPHIR_CALL_METHOD(&_24$$15, ts, "getline", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_25$$15);
			ZEPHIR_CONCAT_SVSV(&_25$$15, "Fail unicode match ", &_24$$15, " \\", &value);
			ZEPHIR_CALL_METHOD(NULL, &_23$$15, "__construct", &_12, 16, &_25$$15);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_23$$15, "toml/Parser.zep", 705 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CTOR(&result);

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
 * @param \Toml\TokenStream $ts
 * @return ValueList
 */
PHP_METHOD(Toml_Parser, parseArray) {

	zend_bool doLoop = 0, gotComma = 0;
	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL, *_6 = NULL, *_10 = NULL, *_11 = NULL, *_14 = NULL, *_16 = NULL, *_18 = NULL, *_20 = NULL, *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, rct = 0, id = 0;
	zval *ts, ts_sub, token, value, result, e, _0, _1$$4, _3$$4, _5$$5, _7$$6, _8$$11, _9$$11, _12$$13, _13$$13, _15$$13, _17$$13, _19$$14, _21$$15, _23$$10, _28$$10, _24$$16, _25$$16, _26$$16, _27$$16, _29$$18, _30$$18, _31$$19, _32$$20, _33$$21, _34$$26, _35$$26;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$11);
	ZVAL_UNDEF(&_9$$11);
	ZVAL_UNDEF(&_12$$13);
	ZVAL_UNDEF(&_13$$13);
	ZVAL_UNDEF(&_15$$13);
	ZVAL_UNDEF(&_17$$13);
	ZVAL_UNDEF(&_19$$14);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_23$$10);
	ZVAL_UNDEF(&_28$$10);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$16);
	ZVAL_UNDEF(&_26$$16);
	ZVAL_UNDEF(&_27$$16);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$18);
	ZVAL_UNDEF(&_31$$19);
	ZVAL_UNDEF(&_32$$20);
	ZVAL_UNDEF(&_33$$21);
	ZVAL_UNDEF(&_34$$26);
	ZVAL_UNDEF(&_35$$26);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_INIT_VAR(&result);
	object_init_ex(&result, toml_valuelist_ce);
	ZEPHIR_CALL_METHOD(NULL, &result, "__construct", NULL, 47);
	zephir_check_call_status();
	doLoop = 1;
	ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, &token, SL("id"), PH_NOISY_CC);
	id = zephir_get_intval(&_0);
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (id == 11) {
				ZEPHIR_INIT_NVAR(&_1$$4);
				ZVAL_STRING(&_1$$4, "/(\\s+)/");
				ZEPHIR_CALL_METHOD(NULL, ts, "moveregex", &_2, 0, &_1$$4);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_3$$4);
				zephir_read_property(&_3$$4, &token, SL("id"), PH_NOISY_CC);
				id = zephir_get_intval(&_3$$4);
				break;
			}
			if (id == 10) {
				ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_5$$5);
				zephir_read_property(&_5$$5, &token, SL("id"), PH_NOISY_CC);
				id = zephir_get_intval(&_5$$5);
				break;
			}
			if (id == 23) {
				ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "parsecomment", &_6, 25, ts);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_7$$6);
				zephir_read_property(&_7$$6, &token, SL("id"), PH_NOISY_CC);
				id = zephir_get_intval(&_7$$6);
				break;
			}
			if (id == 4) {
				ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
				zephir_check_call_status();
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "Unfinished array", "toml/Parser.zep", 760);
				return;
			}
			if (id == 13) {
				ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
				zephir_check_call_status();
			}
			doLoop = 0;
			break;
		} while(0);

	}
	rct = 0;
	while (1) {
		if (!(id != 13)) {
			break;
		}
		if (id == 12) {
			ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_9$$11);
			ZVAL_STRING(&_9$$11, "object");
			ZEPHIR_CALL_METHOD(&_8$$11, &result, "allowtype", &_10, 48, &_9$$11);
			zephir_check_call_status();
			if (zephir_is_true(&_8$$11)) {
				ZEPHIR_CALL_METHOD(&value, this_ptr, "parsearray", &_11, 39, ts);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&_12$$13);
				object_init_ex(&_12$$13, toml_xarrayable_ce);
				ZEPHIR_CALL_METHOD(&_13$$13, &result, "gettype", &_14, 49);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_15$$13, ts, "getline", &_16, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_17$$13);
				ZEPHIR_CONCAT_SVSV(&_17$$13, "Cannot add array to list of ", &_13$$13, " at line ", &_15$$13);
				ZEPHIR_CALL_METHOD(NULL, &_12$$13, "__construct", &_18, 16, &_17$$13);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_12$$13, "toml/Parser.zep", 780 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZVAL_LONG(&_19$$14, id);
			ZEPHIR_CALL_METHOD(&value, this_ptr, "getsimplevalue", &_20, 41, &_19$$14);
			zephir_check_call_status();
		}

		/* try_start_1: */

			ZVAL_LONG(&_21$$15, rct);
			ZEPHIR_CALL_METHOD(NULL, &result, "offsetset", &_22, 50, &_21$$15, &value);
			zephir_check_call_status_or_jump(try_end_1);
			rct = (rct + 1);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_NVAR(&_23$$10);
			ZVAL_OBJ(&_23$$10, EG(exception));
			Z_ADDREF_P(&_23$$10);
			if (zephir_instance_of_ev(&_23$$10, toml_xarrayable_ce TSRMLS_CC)) {
				zend_clear_exception(TSRMLS_C);
				ZEPHIR_CPY_WRT(&e, &_23$$10);
				ZEPHIR_INIT_NVAR(&_24$$16);
				object_init_ex(&_24$$16, toml_xarrayable_ce);
				ZEPHIR_CALL_METHOD(&_25$$16, &e, "getmessage", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_26$$16, ts, "getline", &_16, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_27$$16);
				ZEPHIR_CONCAT_VSV(&_27$$16, &_25$$16, " at line ", &_26$$16);
				ZEPHIR_CALL_METHOD(NULL, &_24$$16, "__construct", &_18, 16, &_27$$16);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_24$$16, "toml/Parser.zep", 792 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_OBS_NVAR(&_28$$10);
		zephir_read_property(&_28$$10, &token, SL("id"), PH_NOISY_CC);
		id = zephir_get_intval(&_28$$10);
		gotComma = 0;
		doLoop = 1;
		while (1) {
			if (!(doLoop)) {
				break;
			}
			do {
				if (id == 11) {
					ZEPHIR_INIT_NVAR(&_29$$18);
					ZVAL_STRING(&_29$$18, "/(\\s+)/");
					ZEPHIR_CALL_METHOD(NULL, ts, "moveregex", &_2, 0, &_29$$18);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&_30$$18);
					zephir_read_property(&_30$$18, &token, SL("id"), PH_NOISY_CC);
					id = zephir_get_intval(&_30$$18);
					break;
				}
				if (id == 10) {
					ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&_31$$19);
					zephir_read_property(&_31$$19, &token, SL("id"), PH_NOISY_CC);
					id = zephir_get_intval(&_31$$19);
					break;
				}
				if (id == 23) {
					ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "parsecomment", &_6, 25, ts);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&_32$$20);
					zephir_read_property(&_32$$20, &token, SL("id"), PH_NOISY_CC);
					id = zephir_get_intval(&_32$$20);
					break;
				}
				if (id == 16) {
					if (gotComma) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "No value between commas", "toml/Parser.zep", 824);
						return;
					} else {
						gotComma = 1;
					}
					ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&token, ts, "peektoken", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(&_33$$21);
					zephir_read_property(&_33$$21, &token, SL("id"), PH_NOISY_CC);
					id = zephir_get_intval(&_33$$21);
					break;
				}
				if (id == 13) {
					ZEPHIR_CALL_METHOD(NULL, ts, "accepttoken", &_4, 0);
					zephir_check_call_status();
				}
				doLoop = 0;
				break;
			} while(0);

		}
	}
	if (id != 13) {
		ZEPHIR_CALL_METHOD(&_34$$26, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_35$$26, 13);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 45, &_34$$26, &_35$$26);
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
		ZEPHIR_CALL_METHOD(NULL, &pushed, "__construct", NULL, 2);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &work, "offsetset", NULL, 0, keyName, &pushed);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("_table"), &pushed);
		RETURN_MM_NULL();
	}
	ZEPHIR_CALL_METHOD(&_1, &work, "offsetget", NULL, 0, keyName);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_table"), &_1);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Parser, parseInlineTable) {

	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, *keyName, keyName_sub, priorTable, _0, _1, _2$$3, _3$$4, _4$$4, _6$$5, _7$$6, _9$$6, _10$$6, _8$$7, _11$$8, _12$$9, _13$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&keyName_sub);
	ZVAL_UNDEF(&priorTable);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &ts, &keyName);



	ZVAL_LONG(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushexpset", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&priorTable);
	zephir_read_property(&priorTable, this_ptr, SL("_table"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "pushworktable", NULL, 51, keyName);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_1);
	if (tokenId == 11) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "movenextid", NULL, 12);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_2$$3);
	}
	if (tokenId != 15) {
		ZVAL_BOOL(&_4$$4, 1);
		ZEPHIR_CALL_METHOD(&_3$$4, this_ptr, "parsekeyvalue", &_5, 26, ts, &_4$$4);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_3$$4);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_6$$5, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_6$$5);
		}
	}
	while (1) {
		if (!(tokenId == 16)) {
			break;
		}
		ZEPHIR_CALL_METHOD(&_7$$6, ts, "movenextid", NULL, 12);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_7$$6);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_8$$7, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_8$$7);
		}
		ZVAL_BOOL(&_10$$6, 1);
		ZEPHIR_CALL_METHOD(&_9$$6, this_ptr, "parsekeyvalue", &_5, 26, ts, &_10$$6);
		zephir_check_call_status();
		tokenId = zephir_get_intval(&_9$$6);
		if (tokenId == 11) {
			ZEPHIR_CALL_METHOD(&_11$$8, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_11$$8);
		}
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "popexpset", NULL, 0);
	zephir_check_call_status();
	if (tokenId != 15) {
		ZEPHIR_CALL_METHOD(&_12$$9, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZVAL_LONG(&_13$$9, 15);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "throwtokenerror", NULL, 45, &_12$$9, &_13$$9);
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

	zend_bool _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *ts, ts_sub, tokenId, _0, _2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&tokenId);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/^(\\s*#\\V*|\\s*)/");
	ZEPHIR_CALL_METHOD(NULL, ts, "moveregex", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&tokenId, ts, "movenextid", NULL, 0);
	zephir_check_call_status();
	_1 = !ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 10);
	if (_1) {
		_1 = !ZEPHIR_IS_LONG_IDENTICAL(&tokenId, 4);
	}
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2$$3, ts, "gettoken", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "Expected NEWLINE or EOS");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 28, &_3$$3, &_2$$3);
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
	zephir_throw_exception_debug(&_3, "toml/Parser.zep", 935 TSRMLS_CC);
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
	zephir_is_iterable(&parts, 0, "toml/Parser.zep", 967);
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
	zend_bool isAOT = 0, hitNew = 0, doLoop = 0, preMade = 0, _11$$14, _18$$19, _27$$25;
	zephir_fcall_cache_entry *_3 = NULL, *_17 = NULL, *_22 = NULL, *_23 = NULL, *_24 = NULL, *_25 = NULL, *_26 = NULL, *_29 = NULL, *_33 = NULL, *_34 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pathLine = 0, partsCt = 0, i = 0, firstNew = 0, dotCount = 0, AOTLength = 0, tokenId = 0;
	zval *ts, ts_sub, __$true, __$false, pobj, testObj, tag, partKey, path, _0, _1, _4, _2$$3, _5$$5, _6$$6, _7$$7, _8$$9, _9$$12, _10$$11, _14$$14, _12$$15, _13$$16, _15$$18, _16$$17, _20$$19, _36$$19, _19$$20, _21$$21, _35$$25, _28$$26, _30$$26, _31$$26, _32$$26, _37$$29, _38$$30, _39$$31, _40$$33, _41$$33, _42$$33, _43$$33, _44$$33, _45$$34, _46$$36, _47$$36, _48$$36, _49$$36, _50$$36;
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
	ZVAL_UNDEF(&_14$$14);
	ZVAL_UNDEF(&_12$$15);
	ZVAL_UNDEF(&_13$$16);
	ZVAL_UNDEF(&_15$$18);
	ZVAL_UNDEF(&_16$$17);
	ZVAL_UNDEF(&_20$$19);
	ZVAL_UNDEF(&_36$$19);
	ZVAL_UNDEF(&_19$$20);
	ZVAL_UNDEF(&_21$$21);
	ZVAL_UNDEF(&_35$$25);
	ZVAL_UNDEF(&_28$$26);
	ZVAL_UNDEF(&_30$$26);
	ZVAL_UNDEF(&_31$$26);
	ZVAL_UNDEF(&_32$$26);
	ZVAL_UNDEF(&_37$$29);
	ZVAL_UNDEF(&_38$$30);
	ZVAL_UNDEF(&_39$$31);
	ZVAL_UNDEF(&_40$$33);
	ZVAL_UNDEF(&_41$$33);
	ZVAL_UNDEF(&_42$$33);
	ZVAL_UNDEF(&_43$$33);
	ZVAL_UNDEF(&_44$$33);
	ZVAL_UNDEF(&_45$$34);
	ZVAL_UNDEF(&_46$$36);
	ZVAL_UNDEF(&_47$$36);
	ZVAL_UNDEF(&_48$$36);
	ZVAL_UNDEF(&_49$$36);
	ZVAL_UNDEF(&_50$$36);
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
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_2$$3);
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
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_5$$5);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 1) {
				ZEPHIR_INIT_NVAR(&_6$$6);
				ZVAL_STRING(&_6$$6, "Unexpected '=' in path");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_6$$6);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 11) {
				ZEPHIR_CALL_METHOD(&_7$$7, ts, "movenextid", NULL, 12);
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
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_8$$9);
				zephir_check_call_status();
				break;
			}
			if (tokenId == 13) {
				if (isAOT) {
					if (AOTLength == 0) {
						ZEPHIR_INIT_NVAR(&_9$$12);
						ZVAL_STRING(&_9$$12, "AOT Segment cannot be empty");
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_9$$12);
						zephir_check_call_status();
					}
					isAOT = 0;
					AOTLength = 0;
					ZEPHIR_CALL_METHOD(&_10$$11, ts, "movenextid", NULL, 12);
					zephir_check_call_status();
					tokenId = zephir_get_intval(&_10$$11);
				} else {
					doLoop = 0;
				}
				break;
			}
			if (tokenId == 12) {
				_11$$14 = dotCount < 1;
				if (_11$$14) {
					_11$$14 = zephir_fast_count_int(&parts TSRMLS_CC) > 0;
				}
				if (_11$$14) {
					ZEPHIR_INIT_NVAR(&_12$$15);
					ZVAL_STRING(&_12$$15, "Expected a '.' after path key");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_12$$15);
					zephir_check_call_status();
				}
				if (isAOT) {
					ZEPHIR_INIT_NVAR(&_13$$16);
					ZVAL_STRING(&_13$$16, "Too many consecutive [ in path");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_13$$16);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_14$$14, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_14$$14);
				isAOT = 1;
				break;
			}
			if (tokenId == 17) {
				if (dotCount == 1) {
					ZEPHIR_INIT_NVAR(&_15$$18);
					ZVAL_STRING(&_15$$18, "Found '..' in path");
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_15$$18);
					zephir_check_call_status();
				}
				dotCount = (dotCount + 1);
				ZEPHIR_CALL_METHOD(&_16$$17, ts, "movenextid", NULL, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_16$$17);
				break;
			}
			ZEPHIR_CALL_METHOD(&partKey, this_ptr, "parsekeyname", &_17, 37, ts);
			zephir_check_call_status();
			_18$$19 = dotCount < 1;
			if (_18$$19) {
				_18$$19 = zephir_fast_count_int(&parts TSRMLS_CC) > 0;
			}
			if (_18$$19) {
				ZEPHIR_INIT_NVAR(&_19$$20);
				ZVAL_STRING(&_19$$20, "Expected a '.' after path key");
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_19$$20);
				zephir_check_call_status();
			}
			dotCount = 0;
			ZEPHIR_CALL_METHOD(&_20$$19, &pobj, "offsetexists", NULL, 0, &partKey);
			zephir_check_call_status();
			if (zephir_is_true(&_20$$19)) {
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
					ZVAL_BOOL(&_21$$21, 1);
				} else {
					ZVAL_BOOL(&_21$$21, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, &tag, "__construct", &_22, 53, &partKey, &_21$$21);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&testObj);
				if (isAOT) {
					AOTLength = (AOTLength + 1);
					object_init_ex(&testObj, toml_tablelist_ce);
					ZEPHIR_CALL_METHOD(NULL, &testObj, "__construct", &_23, 54);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &pobj, "offsetset", NULL, 0, &partKey, &testObj);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&pobj, &testObj, "getendtable", &_24, 55);
					zephir_check_call_status();
				} else {
					object_init_ex(&testObj, toml_keytable_ce);
					ZEPHIR_CALL_METHOD(NULL, &testObj, "__construct", &_25, 2);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, &pobj, "offsetset", NULL, 0, &partKey, &testObj);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&pobj, &testObj);
				}
				ZEPHIR_CALL_METHOD(NULL, &testObj, "settag", &_26, 56, &tag);
				zephir_check_call_status();
			} else {
				_27$$25 = Z_TYPE_P(&testObj) == IS_OBJECT;
				if (_27$$25) {
					_27$$25 = zephir_instance_of_ev(&testObj, toml_arrayable_ce TSRMLS_CC);
				}
				preMade = _27$$25;
				if (!(preMade)) {
					ZEPHIR_CALL_METHOD(&_28$$26, this_ptr, "getpathname", &_29, 57, &parts);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&path);
					ZEPHIR_CONCAT_VSV(&path, &_28$$26, ".", &partKey);
					ZEPHIR_INIT_NVAR(&_30$$26);
					object_init_ex(&_30$$26, toml_xarrayable_ce);
					ZEPHIR_SINIT_NVAR(_31$$26);
					ZVAL_LONG(&_31$$26, pathLine);
					ZEPHIR_INIT_LNVAR(_32$$26);
					ZEPHIR_CONCAT_SVSV(&_32$$26, "Duplicate key path: ", &path, " line ", &_31$$26);
					ZEPHIR_CALL_METHOD(NULL, &_30$$26, "__construct", &_33, 16, &_32$$26);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_30$$26, "toml/Parser.zep", 1093 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_34, 58);
				zephir_check_call_status();
				if (isAOT) {
					zephir_update_property_zval(&tag, SL("isAOT"), &__$true);
				} else {
					zephir_update_property_zval(&tag, SL("isAOT"), &__$false);
				}
				zephir_read_property(&_35$$25, &tag, SL("objAOT"), PH_NOISY_CC | PH_READONLY);
				if (zephir_is_true(&_35$$25)) {
					AOTLength = (AOTLength + 1);
					ZEPHIR_CALL_METHOD(&pobj, &testObj, "getendtable", &_24, 55);
					zephir_check_call_status();
				} else {
					ZEPHIR_CPY_WRT(&pobj, &testObj);
				}
			}
			zephir_array_append(&parts, &testObj, PH_SEPARATE, "toml/Parser.zep", 1105);
			partsCt = (partsCt + 1);
			ZEPHIR_CALL_METHOD(&_36$$19, ts, "movenextid", NULL, 12);
			zephir_check_call_status();
			tokenId = zephir_get_intval(&_36$$19);
			break;
		} while(0);

	}
	if (partsCt == 0) {
		ZEPHIR_INIT_VAR(&_37$$29);
		ZVAL_STRING(&_37$$29, "Table path cannot be empty");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "tablepatherror", &_3, 52, &_37$$29);
		zephir_check_call_status();
	}
	if (!(hitNew)) {
		ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_34, 58);
		zephir_check_call_status();
		zephir_read_property(&_38$$30, &tag, SL("objAOT"), PH_NOISY_CC | PH_READONLY);
		if (zephir_is_true(&_38$$30)) {
			zephir_read_property(&_39$$31, &tag, SL("isAOT"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_39$$31)) {
				ZEPHIR_CALL_METHOD(&pobj, &testObj, "newtable", NULL, 59);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_VAR(&_40$$33);
				object_init_ex(&_40$$33, toml_xarrayable_ce);
				ZVAL_BOOL(&_42$$33, 0);
				ZEPHIR_CALL_METHOD(&_41$$33, this_ptr, "getpathname", &_29, 57, &parts, &_42$$33);
				zephir_check_call_status();
				ZEPHIR_SINIT_VAR(_43$$33);
				ZVAL_LONG(&_43$$33, pathLine);
				ZEPHIR_INIT_VAR(&_44$$33);
				ZEPHIR_CONCAT_SVSV(&_44$$33, "Table path mismatch with ", &_41$$33, " line ", &_43$$33);
				ZEPHIR_CALL_METHOD(NULL, &_40$$33, "__construct", &_33, 16, &_44$$33);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_40$$33, "toml/Parser.zep", 1122 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_read_property(&_45$$34, &tag, SL("implicit"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_45$$34)) {
				if (0) {
					zephir_update_property_zval(&tag, SL("implicit"), &__$true);
				} else {
					zephir_update_property_zval(&tag, SL("implicit"), &__$false);
				}
			} else {
				ZEPHIR_INIT_VAR(&_46$$36);
				object_init_ex(&_46$$36, toml_xarrayable_ce);
				ZVAL_BOOL(&_48$$36, 0);
				ZEPHIR_CALL_METHOD(&_47$$36, this_ptr, "getpathname", &_29, 57, &parts, &_48$$36);
				zephir_check_call_status();
				ZEPHIR_SINIT_VAR(_49$$36);
				ZVAL_LONG(&_49$$36, pathLine);
				ZEPHIR_INIT_VAR(&_50$$36);
				ZEPHIR_CONCAT_SVSV(&_50$$36, "Duplicate key path: [", &_47$$36, "] line ", &_49$$36);
				ZEPHIR_CALL_METHOD(NULL, &_46$$36, "__construct", &_33, 16, &_50$$36);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_46$$36, "toml/Parser.zep", 1131 TSRMLS_CC);
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
			zephir_array_fetch_long(&testObj, &parts, i, PH_NOISY, "toml/Parser.zep", 1142 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&tag, &testObj, "gettag", &_34, 58);
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



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "parseobjectpath", NULL, 60, ts);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "finishline", NULL, 42, ts);
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
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "syntaxerror", NULL, 28, &_2, token);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the next tokenId, after skipping any comments and space
 * @param TokenStream $ts
 */
PHP_METHOD(Toml_Parser, parseCommentsAndSpace) {

	zend_bool doLoop = 0;
	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL, *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, tokenId = 0;
	zval *ts, ts_sub, _0, _1$$4, _3$$5, _5$$6, _7$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ts_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_7$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ts);



	ZEPHIR_CALL_METHOD(&_0, ts, "gettokenid", NULL, 0);
	zephir_check_call_status();
	tokenId = zephir_get_intval(&_0);
	doLoop = 1;
	while (1) {
		if (!(doLoop)) {
			break;
		}
		do {
			if (tokenId == 23) {
				ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "parsecomment", &_2, 25, ts);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_1$$4);
				break;
			}
			if (tokenId == 10) {
				ZEPHIR_CALL_METHOD(&_3$$5, ts, "movenextid", &_4, 0);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_3$$5);
				break;
			}
			if (tokenId == 11) {
				ZEPHIR_INIT_NVAR(&_5$$6);
				ZVAL_STRING(&_5$$6, "/(\\s+)/");
				ZEPHIR_CALL_METHOD(NULL, ts, "moveregex", &_6, 0, &_5$$6);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_7$$6, ts, "movenextid", &_4, 12);
				zephir_check_call_status();
				tokenId = zephir_get_intval(&_7$$6);
				break;
			}
			doLoop = 0;
			break;
		} while(0);

	}
	RETURN_MM_LONG(tokenId);

}

PHP_METHOD(Toml_Parser, syntaxError) {

	zend_long ZEPHIR_LAST_CALL_STATUS, line = 0;
	zephir_fcall_cache_entry *_5 = NULL;
	zval *msg_param = NULL, *token, token_sub, _0, _1, _2, _8, _4$$3, _6$$3;
	zval msg, value, _3, _7$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&token_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &msg_param, &token);

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


	zephir_read_property(&_0, token, SL("line"), PH_NOISY_CC | PH_READONLY);
	line = zephir_get_numberval(&_0);
	zephir_read_property(&_1, token, SL("value"), PH_NOISY_CC | PH_READONLY);
	zephir_get_strval(&value, &_1);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, line);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SVSV(&_3, "Error line ", &_2, ": ", &msg);
	ZEPHIR_CPY_WRT(&msg, &_3);
	if (zephir_fast_strlen_ev(&value) > 0) {
		ZEPHIR_CALL_SELF(&_4$$3, "valuewrap", &_5, 36, &value);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		ZEPHIR_CONCAT_VV(&_6$$3, &msg, &_4$$3);
		zephir_get_strval(&msg, &_6$$3);
	} else {
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_VS(&_7$$4, &msg, ".");
		ZEPHIR_CPY_WRT(&msg, &_7$$4);
	}
	ZEPHIR_INIT_VAR(&_8);
	object_init_ex(&_8, toml_xarrayable_ce);
	ZEPHIR_CALL_METHOD(NULL, &_8, "__construct", NULL, 16, &msg);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_8, "toml/Parser.zep", 1233 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

