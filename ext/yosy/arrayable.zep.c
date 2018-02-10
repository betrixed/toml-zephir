
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
#include "ext/spl/spl_iterators.h"
#include "kernel/object.h"
#include "kernel/memory.h"


/**
 * Provides array syntax like access to get and set PHP object properties, and
 * restricted conversions to and from array via merge and toArray.
 * The Tag property is for possible management data, without interfering with
 * planned storage implementation.
 * 
 * @author Michael Rynn
 */
ZEPHIR_INIT_CLASS(Yosy_Arrayable) {

	ZEPHIR_REGISTER_CLASS(Yosy, Arrayable, yosy, arrayable, yosy_arrayable_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(yosy_arrayable_ce, SL("_tag"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(yosy_arrayable_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(yosy_arrayable_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

PHP_METHOD(Yosy_Arrayable, setTag) {

	zval *any, any_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&any_sub);

	zephir_fetch_params(0, 1, 0, &any);



	zephir_update_property_zval(this_ptr, SL("_tag"), any);

}

PHP_METHOD(Yosy_Arrayable, getTag) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_tag");

}

PHP_METHOD(Yosy_Arrayable, toArray) {

}

