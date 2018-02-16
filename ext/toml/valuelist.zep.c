
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
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"


/**
 * Description of ValueList
 * Constrains flexible PHP array into taking only one type of data.
 * After assigning the first value, all values must be the same type.
 * @author Michael Rynn
 * 
 */
ZEPHIR_INIT_CLASS(Toml_ValueList) {

	ZEPHIR_REGISTER_CLASS(Toml, ValueList, toml, valuelist, toml_valuelist_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(toml_valuelist_ce, SL("_type"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_valuelist_ce, SL("_list"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_valuelist_ce, SL("_tag"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(toml_valuelist_ce TSRMLS_CC, 1, toml_arrayable_ce);
	return SUCCESS;

}

PHP_METHOD(Toml_ValueList, getType) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_type");

}

PHP_METHOD(Toml_ValueList, __construct) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("_list"), &_0);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_ValueList, getTag) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_tag");

}

PHP_METHOD(Toml_ValueList, setTag) {

	zval *tag, tag_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tag_sub);

	zephir_fetch_params(0, 1, 0, &tag);



	zephir_update_property_zval(this_ptr, SL("_tag"), tag);

}

PHP_METHOD(Toml_ValueList, offsetSet) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *offset = NULL, offset_sub, *value, value_sub, vtype, ct, _0, _1, _5, _2$$4, _3$$4, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&offset_sub);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&vtype);
	ZVAL_UNDEF(&ct);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &offset, &value);

	ZEPHIR_SEPARATE_PARAM(offset);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&ct);
	ZVAL_LONG(&ct, zephir_fast_count_int(&_0 TSRMLS_CC));
	ZEPHIR_INIT_VAR(&vtype);
	zephir_gettype(&vtype, value TSRMLS_CC);
	zephir_read_property(&_1, this_ptr, SL("_type"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_LONG_IDENTICAL(&ct, 0)) {
		zephir_update_property_zval(this_ptr, SL("_type"), &vtype);
	} else if (!ZEPHIR_IS_IDENTICAL(&_1, &vtype)) {
		ZEPHIR_INIT_VAR(&_2$$4);
		object_init_ex(&_2$$4, toml_xarrayable_ce);
		zephir_read_property(&_3$$4, this_ptr, SL("_type"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_4$$4);
		ZEPHIR_CONCAT_SVSV(&_4$$4, "Type ", &vtype, " cannot be added to ValueList of ", &_3$$4);
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 16, &_4$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$4, "toml/ValueList.zep", 41 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_gettype(&_5, offset TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(offset)) {
		ZEPHIR_CPY_WRT(offset, &ct);
	} else if (!ZEPHIR_IS_STRING_IDENTICAL(&_5, "integer")) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "ValueList only takes integer offsets", "toml/ValueList.zep", 47);
		return;
	}
	zephir_update_property_array(this_ptr, SL("_list"), offset, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_ValueList, offsetExists) {

	zval *offset_param = NULL, _0;
	zend_long offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &offset_param);

	offset = zephir_get_intval(offset_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_long(&_0, offset));

}

PHP_METHOD(Toml_ValueList, offsetGet) {

	zval *offset_param = NULL, _0, _1;
	zend_long offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &offset_param);

	offset = zephir_get_intval(offset_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_OBS_VAR(&_1);
	zephir_array_fetch_long(&_1, &_0, offset, PH_NOISY, "toml/ValueList.zep", 59 TSRMLS_CC);
	RETURN_CCTOR(&_1);

}

PHP_METHOD(Toml_ValueList, offsetUnset) {

	zval *offset_param = NULL, _0;
	zend_long offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &offset_param);

	offset = zephir_get_intval(offset_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset_long(&_0, offset, PH_SEPARATE);

}

PHP_METHOD(Toml_ValueList, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

PHP_METHOD(Toml_ValueList, get) {

	zval *offset_param = NULL, *defaultValue = NULL, defaultValue_sub, __$null, _0, _1$$3, _2$$3;
	zend_long offset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	zephir_fetch_params(0, 1, 1, &offset_param, &defaultValue);

	offset = zephir_get_intval(offset_param);
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_long(&_0, offset)) {
		zephir_read_property(&_1$$3, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_2$$3, &_1$$3, offset, PH_NOISY | PH_READONLY, "toml/ValueList.zep", 76 TSRMLS_CC);
		RETURN_CTORW(&_2$$3);
	} else {
		RETVAL_ZVAL(defaultValue, 1, 0);
		return;
	}

}

/**
 * Return array copy of everything with nested ValueList object
 * mediation removed.
 * Modification to Config - allow recurse option, 
 * false for no recurse. It can't be passed on.
 * @param bool $recurse
 * @return array
 */
PHP_METHOD(Toml_ValueList, toArray) {

	zend_string *_3;
	zend_ulong _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *recurse_param = NULL, result, idx, value, _0, *_1, _6$$4;
	zend_bool recurse, _4$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&idx);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &recurse_param);

	if (!recurse_param) {
		recurse = 1;
	} else {
	if (UNEXPECTED(Z_TYPE_P(recurse_param) != IS_TRUE && Z_TYPE_P(recurse_param) != IS_FALSE)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'recurse' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	recurse = (Z_TYPE_P(recurse_param) == IS_TRUE);
	}


	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "toml/ValueList.zep", 105);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&idx);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&idx, _3);
		} else {
			ZVAL_LONG(&idx, _2);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _1);
		_4$$3 = recurse;
		if (_4$$3) {
			_4$$3 = Z_TYPE_P(&value) == IS_OBJECT;
		}
		_5$$3 = _4$$3;
		if (_5$$3) {
			_5$$3 = (zephir_instance_of_ev(&value, toml_arrayable_ce TSRMLS_CC));
		}
		if (_5$$3) {
			ZEPHIR_CALL_METHOD(&_6$$4, &value, "toarray", NULL, 0);
			zephir_check_call_status();
			zephir_array_update_zval(&result, &idx, &_6$$4, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&result, &idx, &value, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&idx);
	RETURN_CCTOR(&result);

}

