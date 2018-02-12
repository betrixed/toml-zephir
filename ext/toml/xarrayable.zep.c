
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
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


/**
 * XArrayable, for general exceptions
 * in this namespace.
 *
 * @author michael
 */
ZEPHIR_INIT_CLASS(Toml_XArrayable) {

	ZEPHIR_REGISTER_CLASS_EX(Toml, XArrayable, toml, xarrayable, zend_exception_get_default(TSRMLS_C), toml_xarrayable_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Toml_XArrayable, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *msg_param = NULL;
	zval msg;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&msg);

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


	ZEPHIR_CALL_PARENT(NULL, toml_xarrayable_ce, getThis(), "__construct", NULL, 0, &msg);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

