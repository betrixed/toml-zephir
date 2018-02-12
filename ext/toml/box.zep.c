
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


/**
 * Enable boxing an array type to emulate a reference
 * @author Michael Rynn
 */
ZEPHIR_INIT_CLASS(Toml_Box) {

	ZEPHIR_REGISTER_CLASS(Toml, Box, toml, box, toml_box_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(toml_box_ce, SL("_me"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Toml_Box, __construct) {

	zval *me, me_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&me_sub);

	zephir_fetch_params(0, 1, 0, &me);



	zephir_update_property_zval(this_ptr, SL("_me"), me);

}

