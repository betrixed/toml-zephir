
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Hold String keyed data in PHP internal object properties table
 * @author Michael Rynn
 */
/**
 * Converts all keys to string, stores values as internal php object property.
 * Handles TableList object as values.
 * Is Recursive for Table objects as value.
 * 
 */
ZEPHIR_INIT_CLASS(Toml_Table) {

	ZEPHIR_REGISTER_CLASS_EX(Toml, Table, toml, table, toml_arrayable_ce, toml_table_method_entry, ZEND_ACC_FINAL_CLASS);

	return SUCCESS;

}

/**
 * @param array 
 */
PHP_METHOD(Toml_Table, mergeArray) {

	zend_string *_2;
	zend_ulong _1;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *kv_param = NULL, key, value, *_0;
	zval kv;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kv);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &kv_param);

	ZEPHIR_OBS_COPY_OR_DUP(&kv, kv_param);


	zephir_is_iterable(&kv, 0, "toml/Table.zep", 31);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&kv), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "offsetset", &_3, 6, &key, &value);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_MM_RESTORE();

}

/**
 * Associate management properties to private tag 
 * @param type $any
 */
PHP_METHOD(Toml_Table, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *aval_param = NULL;
	zval aval;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&aval);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &aval_param);

	if (!aval_param) {
		ZEPHIR_INIT_VAR(&aval);
		array_init(&aval);
	} else {
		zephir_get_arrval(&aval, aval_param);
	}


	if (!(Z_TYPE_P(&aval) == IS_NULL)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "mergearray", NULL, 7, &aval);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * This implements the array-access [],
 * but is not called for property access.
 * Looks like a good place to 
 * substitute global defines for ${defined}
 * @param type $index
 * @param type $value
 * Does not get called when values set as ->property
 * as this uses magic __set
 */
PHP_METHOD(Toml_Table, offsetSet) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *index_param = NULL, *value, value_sub, _0$$3;
	zval index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &index_param, &value);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_STRING && Z_TYPE_P(index_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(index_param) == IS_STRING)) {
		zephir_get_strval(&index, index_param);
	} else {
		ZEPHIR_INIT_VAR(&index);
		ZVAL_EMPTY_STRING(&index);
	}


	if (Z_TYPE_P(value) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, toml_table_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 8, value);
		zephir_check_call_status();
		zephir_update_property_zval_zval(this_ptr, &index, &_0$$3 TSRMLS_CC);
	} else {
		zephir_update_property_zval_zval(this_ptr, &index, value TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_Table, offsetExists) {

	zval *index_param = NULL;
	zval index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_STRING && Z_TYPE_P(index_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(index_param) == IS_STRING)) {
		zephir_get_strval(&index, index_param);
	} else {
		ZEPHIR_INIT_VAR(&index);
		ZVAL_EMPTY_STRING(&index);
	}


	RETURN_MM_BOOL(zephir_isset_property_zval(this_ptr, &index TSRMLS_CC));

}

PHP_METHOD(Toml_Table, offsetGet) {

	zval *index_param = NULL, _0;
	zval index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_STRING && Z_TYPE_P(index_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(index_param) == IS_STRING)) {
		zephir_get_strval(&index, index_param);
	} else {
		ZEPHIR_INIT_VAR(&index);
		ZVAL_EMPTY_STRING(&index);
	}


	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property_zval(&_0, this_ptr, &index, PH_NOISY_CC);
	RETURN_CCTOR(&_0);

}

PHP_METHOD(Toml_Table, offsetUnset) {

	zval *index_param = NULL, __$null;
	zval index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index);
	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_STRING && Z_TYPE_P(index_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(index_param) == IS_STRING)) {
		zephir_get_strval(&index, index_param);
	} else {
		ZEPHIR_INIT_VAR(&index);
		ZVAL_EMPTY_STRING(&index);
	}


	zephir_update_property_zval_zval(this_ptr, &index, &__$null TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Count number of accessible items in internal object properties
 */
PHP_METHOD(Toml_Table, count) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&_0, "get_object_vars", NULL, 2, this_ptr);
	zephir_check_call_status();
	RETURN_MM_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

/**
 * Return object property value from nested objects
 * path separator is '.'
 */
PHP_METHOD(Toml_Table, path) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *path_param = NULL, *defaultValue = NULL, defaultValue_sub, __$null, _0$$3, delimiter, level, keys, key$$4, _3$$4, _2$$6;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&delimiter);
	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&keys);
	ZVAL_UNDEF(&key$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_2$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &path_param, &defaultValue);

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
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}


	if (zephir_isset_property_zval(this_ptr, &path TSRMLS_CC)) {
		ZEPHIR_OBS_VAR(&_0$$3);
		zephir_read_property_zval(&_0$$3, this_ptr, &path, PH_NOISY_CC);
		RETURN_CCTOR(&_0$$3);
	}
	ZEPHIR_INIT_VAR(&delimiter);
	ZVAL_STRING(&delimiter, ".");
	ZEPHIR_CPY_WRT(&level, this_ptr);
	ZEPHIR_INIT_VAR(&keys);
	zephir_fast_explode(&keys, &delimiter, &path, LONG_MAX TSRMLS_CC);
	while (1) {
		if (!(!(ZEPHIR_IS_EMPTY(&keys)))) {
			break;
		}
		ZEPHIR_MAKE_REF(&keys);
		ZEPHIR_CALL_FUNCTION(&key$$4, "array_shift", &_1, 9, &keys);
		ZEPHIR_UNREF(&keys);
		zephir_check_call_status();
		if (!(zephir_isset_property_zval(&level, &key$$4 TSRMLS_CC))) {
			break;
		}
		if (ZEPHIR_IS_EMPTY(&keys)) {
			ZEPHIR_OBS_NVAR(&_2$$6);
			zephir_read_property_zval(&_2$$6, &level, &key$$4, PH_NOISY_CC);
			RETURN_CCTOR(&_2$$6);
		}
		ZEPHIR_OBS_NVAR(&_3$$4);
		zephir_read_property_zval(&_3$$4, &level, &key$$4, PH_NOISY_CC);
		ZEPHIR_CPY_WRT(&level, &_3$$4);
		if (ZEPHIR_IS_EMPTY(&level)) {
			break;
		}
	}
	RETVAL_ZVAL(defaultValue, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Toml_Table, get) {

	zval *index_param = NULL, *defaultValue = NULL, defaultValue_sub, __$null, _0$$3;
	zval index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &index_param, &defaultValue);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_STRING && Z_TYPE_P(index_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(index_param) == IS_STRING)) {
		zephir_get_strval(&index, index_param);
	} else {
		ZEPHIR_INIT_VAR(&index);
		ZVAL_EMPTY_STRING(&index);
	}
	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}


	if (zephir_isset_property_zval(this_ptr, &index TSRMLS_CC)) {
		ZEPHIR_OBS_VAR(&_0$$3);
		zephir_read_property_zval(&_0$$3, this_ptr, &index, PH_NOISY_CC);
		RETURN_CCTOR(&_0$$3);
	}
	RETVAL_ZVAL(defaultValue, 1, 0);
	RETURN_MM();

}

/**
 * Modification to Config - allow recurse option, 
 * false for no recurse. It can't be passed on.
 * @param bool $recurse
 * @return array
 */
PHP_METHOD(Toml_Table, toArray) {

	zend_string *_3;
	zend_ulong _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *recurse_param = NULL, result, key, value, _0, *_1, _6$$4;
	zend_bool recurse, _4$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&key);
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
	ZEPHIR_CALL_FUNCTION(&_0, "get_object_vars", NULL, 2, this_ptr);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "toml/Table.zep", 149);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&key, _3);
		} else {
			ZVAL_LONG(&key, _2);
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
			zephir_array_update_zval(&result, &key, &_6$$4, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&result, &key, &value, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(&result);

}

/** iterate the config tree for $callback on values
 * 
 * @param type $callback
 */
PHP_METHOD(Toml_Table, treeIterateValues) {

	zend_bool _4$$4, _8$$4;
	zend_string *_3;
	zend_ulong _2;
	zephir_fcall_cache_entry *_7 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, key, value, _0, *_1, _5$$4, _6$$4, _9$$4, _10$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	if (!(zephir_is_callable(callback TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "Need callback argument", "toml/Table.zep", 161);
		return;
	}
	ZEPHIR_CALL_FUNCTION(&_0, "get_object_vars", NULL, 2, this_ptr);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "toml/Table.zep", 170);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&key, _3);
		} else {
			ZVAL_LONG(&key, _2);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _1);
		_4$$4 = Z_TYPE_P(&value) == IS_OBJECT;
		if (_4$$4) {
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "\\Toml\\Table");
			ZEPHIR_CALL_FUNCTION(&_6$$4, "is_a", &_7, 3, &value, &_5$$4);
			zephir_check_call_status();
			_8$$4 = zephir_is_true(&_6$$4);
			if (!(_8$$4)) {
				ZEPHIR_INIT_NVAR(&_5$$4);
				ZVAL_STRING(&_5$$4, "\\Toml\\Table");
				ZEPHIR_CALL_FUNCTION(&_9$$4, "is_a", &_7, 3, &value, &_5$$4);
				zephir_check_call_status();
				_8$$4 = zephir_is_true(&_9$$4);
			}
			_4$$4 = _8$$4;
		}
		if (_4$$4) {
			ZEPHIR_CALL_METHOD(NULL, &value, "treeiteratevalues", NULL, 0, callback);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_FUNCTION(&_10$$6, "call_user_func", &_11, 10, callback, &value);
			zephir_check_call_status();
			zephir_update_property_zval_zval(this_ptr, &key, &_10$$6 TSRMLS_CC);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_MM_RESTORE();

}

