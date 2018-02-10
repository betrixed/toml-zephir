
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
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"


/** 
 * Token used to communicate parse results
 *  
 */
ZEPHIR_INIT_CLASS(Yosy_Token) {

	ZEPHIR_REGISTER_CLASS(Yosy, Token, yosy, token, yosy_token_method_entry, 0);

	zend_declare_property_null(yosy_token_ce, SL("value"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(yosy_token_ce, SL("id"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(yosy_token_ce, SL("line"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(yosy_token_ce, SL("isSingle"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Yosy_Token, set) {

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


	zephir_update_property_zval(this_ptr, SL("value"), &value);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, id);
	zephir_update_property_zval(this_ptr, SL("id"), &_0);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, line);
	zephir_update_property_zval(this_ptr, SL("line"), &_0);
	if (isSingle) {
		zephir_update_property_zval(this_ptr, SL("isSingle"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("isSingle"), &__$false);
	}
	ZEPHIR_MM_RESTORE();

}

