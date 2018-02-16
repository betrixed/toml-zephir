
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/memory.h"


/**
* Transcribed from a version adapated from Yosymfony/Toml 
* 
* @author Michael Rynn
*/
ZEPHIR_INIT_CLASS(Toml_PartTag) {

	ZEPHIR_REGISTER_CLASS(Toml, PartTag, toml, parttag, toml_parttag_method_entry, 0);

	zend_declare_property_null(toml_parttag_ce, SL("partKey"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parttag_ce, SL("isAOT"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parttag_ce, SL("objAOT"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_parttag_ce, SL("implicit"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Toml_PartTag, __construct) {

	zend_bool objAOT;
	zval *key, key_sub, *objAOT_param = NULL, __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);

	zephir_fetch_params(0, 2, 0, &key, &objAOT_param);

	if (UNEXPECTED(Z_TYPE_P(objAOT_param) != IS_TRUE && Z_TYPE_P(objAOT_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'objAOT' must be a bool") TSRMLS_CC);
		RETURN_NULL();
	}
	objAOT = (Z_TYPE_P(objAOT_param) == IS_TRUE);


	zephir_update_property_zval(this_ptr, SL("partKey"), key);
	if (objAOT) {
		zephir_update_property_zval(this_ptr, SL("isAOT"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("isAOT"), &__$false);
	}
	if (objAOT) {
		zephir_update_property_zval(this_ptr, SL("objAOT"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("objAOT"), &__$false);
	}
	if (0) {
		zephir_update_property_zval(this_ptr, SL("implicit"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("implicit"), &__$false);
	}

}

