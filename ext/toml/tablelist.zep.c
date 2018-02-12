
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"


/**
 * A dumb list of Table objects.
 * This object is limited to storing Table objects in numeric
 * zero-indexed array
*/
ZEPHIR_INIT_CLASS(Toml_TableList) {

	ZEPHIR_REGISTER_CLASS_EX(Toml, TableList, toml, tablelist, toml_arrayable_ce, toml_tablelist_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(toml_tablelist_ce, SL("_list"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Toml_TableList, __construct) {

	zval *arrayOfTable_param = NULL;
	zval arrayOfTable;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arrayOfTable);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &arrayOfTable_param);

	if (!arrayOfTable_param) {
		ZEPHIR_INIT_VAR(&arrayOfTable);
		array_init(&arrayOfTable);
	} else {
	ZEPHIR_OBS_COPY_OR_DUP(&arrayOfTable, arrayOfTable_param);
	}



}

/** 
 * return offset to last Table *
 * @return int
 */
PHP_METHOD(Toml_TableList, getEndIndex) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG((zephir_fast_count_int(&_0 TSRMLS_CC) - 1));

}

/**
 * Return last Table object
 * @return \Toml\Table
 */
PHP_METHOD(Toml_TableList, getEndTable) {

	zval _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_1, &_0, (zephir_fast_count_int(&_2 TSRMLS_CC) - 1), PH_NOISY | PH_READONLY, "toml/TableList.zep", 39 TSRMLS_CC);
	RETURN_CTORW(&_1);

}

PHP_METHOD(Toml_TableList, getTables) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_list");

}

/**
 * Return a new table added to the end of the list
 * @return \Toml\Table
 */
PHP_METHOD(Toml_TableList, newTable) {

	zval item;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&item);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&item);
	object_init_ex(&item, toml_table_ce);
	ZEPHIR_CALL_METHOD(NULL, &item, "__construct", NULL, 8);
	zephir_check_call_status();
	zephir_update_property_array_append(this_ptr, SL("_list"), &item TSRMLS_CC);
	RETURN_CCTOR(&item);

}

/** 
 Add tables from another TableList object
 */
PHP_METHOD(Toml_TableList, addTables) {

	zval *obj, obj_sub, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&obj_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &obj);



	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, obj, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_array_merge(&_0, &_1, &_2 TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("_list"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 * This implements the array-access [],
 * Strictly don't even want to provide such write access
 * so this may just throw exception in future
 * @param type $index
 * @param type $value
 */
PHP_METHOD(Toml_TableList, offsetSet) {

	zval *index_param = NULL, *value, value_sub, _0, _1;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &index_param, &value);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	index = Z_LVAL_P(index_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "\\Toml\\Table");
	ZEPHIR_CALL_FUNCTION(&_1, "is_a", NULL, 3, value, &_0);
	zephir_check_call_status();
	if (!zephir_is_true(&_1)) {
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, index);
	zephir_update_property_array(this_ptr, SL("_list"), &_0, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_TableList, offsetExists) {

	zval *index_param = NULL, _0;
	zend_long index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	index = Z_LVAL_P(index_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_long(&_0, index));

}

PHP_METHOD(Toml_TableList, offsetGet) {

	zval *index_param = NULL, _0, _1;
	zend_long index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	zephir_fetch_params(0, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	index = Z_LVAL_P(index_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_1, &_0, index, PH_NOISY | PH_READONLY, "toml/TableList.zep", 81 TSRMLS_CC);
	RETURN_CTORW(&_1);

}

/**
 * May throw exception in future
 * @param type $index
 */
PHP_METHOD(Toml_TableList, offsetUnset) {

	zval *index_param = NULL, _0;
	zend_long index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	index = Z_LVAL_P(index_param);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset_long(&_0, index, PH_SEPARATE);

}

PHP_METHOD(Toml_TableList, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

/**
 * Return a copy of the TableList as array.
 * Default $recurse is true to return Table content instead of Table object
 * @param bool $recurse
 * @return array
 */
PHP_METHOD(Toml_TableList, toArray) {

	zend_string *_6;
	zend_ulong _5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *recurse_param = NULL, result, _0, _1, _2, _3, idx, value, *_4, _7$$4;
	zend_bool recurse;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&idx);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_7$$4);

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


	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 0);
	ZVAL_LONG(&_2, zephir_fast_count_int(&_0 TSRMLS_CC));
	ZVAL_NULL(&_3);
	ZEPHIR_CALL_FUNCTION(&result, "array_fill", NULL, 11, &_1, &_2, &_3);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_1, 0, "toml/TableList.zep", 113);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_1), _5, _6, _4)
	{
		ZEPHIR_INIT_NVAR(&idx);
		if (_6 != NULL) { 
			ZVAL_STR_COPY(&idx, _6);
		} else {
			ZVAL_LONG(&idx, _5);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _4);
		if (recurse) {
			ZEPHIR_CALL_METHOD(&_7$$4, &value, "toarray", NULL, 0);
			zephir_check_call_status();
			zephir_array_update_zval(&result, &idx, &_7$$4, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&result, &idx, &value, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&idx);
	RETURN_CCTOR(&result);

}

/** Iterate tree for $callback on values of members
 * 
 * @param type $callback
 */
PHP_METHOD(Toml_TableList, treeIterateValues) {

	zend_bool _2$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback_param = NULL, value, _0, *_1;
	zval callback;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback_param);

	if (UNEXPECTED(Z_TYPE_P(callback_param) != IS_STRING && Z_TYPE_P(callback_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'callback' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(callback_param) == IS_STRING)) {
		zephir_get_strval(&callback, callback_param);
	} else {
		ZEPHIR_INIT_VAR(&callback);
		ZVAL_EMPTY_STRING(&callback);
	}


	if (!(zephir_is_callable(&callback TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(toml_xarrayable_ce, "Needs function for callback", "toml/TableList.zep", 122);
		return;
	}
	zephir_read_property(&_0, this_ptr, SL("_list"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "toml/TableList.zep", 130);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _1);
		_2$$4 = Z_TYPE_P(&value) == IS_OBJECT;
		if (_2$$4) {
			_2$$4 = (zephir_is_instance_of(&value, SL("\\Toml\\Table") TSRMLS_CC));
		}
		if (_2$$4) {
			ZEPHIR_CALL_METHOD(NULL, &value, "treeiteratevalues", NULL, 0, &callback);
			zephir_check_call_status();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_MM_RESTORE();

}

