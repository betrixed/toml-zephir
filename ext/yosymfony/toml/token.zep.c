
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"


/** 
 * Useful to pass around values,
 * and hold intermediate parse result
 *  
 */
ZEPHIR_INIT_CLASS(Yosymfony_Toml_Token) {

	ZEPHIR_REGISTER_CLASS(Yosymfony\\Toml, Token, yosymfony, toml_token, yosymfony_toml_token_method_entry, 0);

	zend_declare_property_null(yosymfony_toml_token_ce, SL("_value"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yosymfony_toml_token_ce, SL("_id"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yosymfony_toml_token_ce, SL("_line"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(yosymfony_toml_token_ce, SL("_isSingle"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yosymfony_Toml_Token, getValue) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_value");

}

PHP_METHOD(Yosymfony_Toml_Token, getId) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_id");

}

PHP_METHOD(Yosymfony_Toml_Token, getLine) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_line");

}

PHP_METHOD(Yosymfony_Toml_Token, __construct) {

	zval __$true, __$false, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "");
	zephir_update_property_zval(this_ptr, SL("_value"), &_0);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, 0);
	zephir_update_property_zval(this_ptr, SL("_id"), &_1);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, -1);
	zephir_update_property_zval(this_ptr, SL("_line"), &_1);
	if (0) {
		zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Yosymfony_Toml_Token, set) {

	zend_bool isSingle;
	zend_long id, line;
	zval *value_param = NULL, *id_param = NULL, *line_param = NULL, *isSingle_param = NULL, __$true, __$false, _0;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &value_param, &id_param, &line_param, &isSingle_param);

	if (UNEXPECTED(Z_TYPE_P(value_param) != IS_STRING && Z_TYPE_P(value_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'value' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(value_param) == IS_STRING)) {
		zephir_get_strval(&value, value_param);
	} else {
		ZEPHIR_INIT_VAR(&value);
		ZVAL_EMPTY_STRING(&value);
	}
	id = zephir_get_intval(id_param);
	line = zephir_get_intval(line_param);
	if (!isSingle_param) {
		isSingle = 0;
	} else {
		isSingle = zephir_get_boolval(isSingle_param);
	}


	zephir_update_property_zval(this_ptr, SL("_value"), &value);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, id);
	zephir_update_property_zval(this_ptr, SL("_id"), &_0);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, line);
	zephir_update_property_zval(this_ptr, SL("_line"), &_0);
	if (isSingle) {
		zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("_isSingle"), &__$false);
	}
	ZEPHIR_MM_RESTORE();

}

