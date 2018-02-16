
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"


/**
 * @author Michael Rynn
 */
/**
 * This is more general, no frills, object wrap of a PHP array
 * It is more inefficient than a bare PHP array.
 * The internal $_store is public for easy iteration.
 * Any PHP key type is allowed. 
 * Strict TOML04 - says integer key values  must 
 * be converted to strings!
 * 
 * Hence if we parsed an integer key, and converted it, and set the key as a string
 * and then extracted the key later, it would of integer type again, due to PHP's
 * convert everything that looks like an integer, to an integer,  for Array keys.
 * "1" and intval(1) are the PHP same key,
 * stored as binary integer. Hash algorithms are faster on binary integers, because the Hash,
 * usually becomes a binary integer value, restricted to hash table storage.
 * Quite often integer values are what is intended.

 * It makes sense for internet HTML forms convenience, where everything is text,
 * and numeric values are returned as string. 

 * If the numeric string is beyond an upper limit of representation it remains a string,
 * and in this case can never be an integer.
 * So if this class was used as TOML tables, all integer keys may need to be converted back to 
 * string on retrieval.
 * This class gives a standard "referenced" array as object without a reference operator &
 */
ZEPHIR_INIT_CLASS(Toml_KeyTable) {

	ZEPHIR_REGISTER_CLASS(Toml, KeyTable, toml, keytable, toml_keytable_method_entry, ZEND_ACC_FINAL_CLASS);

	zend_declare_property_null(toml_keytable_ce, SL("_store"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_keytable_ce, SL("_tag"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(toml_keytable_ce TSRMLS_CC, 1, toml_arrayable_ce);
	return SUCCESS;

}

PHP_METHOD(Toml_KeyTable, __construct) {

	zend_string *_2$$3;
	zend_ulong _1$$3;
	zval *seed_param = NULL, key$$3, value$$3, *_0$$3, init$$5;
	zval seed;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&seed);
	ZVAL_UNDEF(&key$$3);
	ZVAL_UNDEF(&value$$3);
	ZVAL_UNDEF(&init$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &seed_param);

	if (!seed_param) {
		ZEPHIR_INIT_VAR(&seed);
		array_init(&seed);
	} else {
		zephir_get_arrval(&seed, seed_param);
	}


	if (!(ZEPHIR_IS_EMPTY(&seed))) {
		zephir_is_iterable(&seed, 0, "toml/KeyTable.zep", 46);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&seed), _1$$3, _2$$3, _0$$3)
		{
			ZEPHIR_INIT_NVAR(&key$$3);
			if (_2$$3 != NULL) { 
				ZVAL_STR_COPY(&key$$3, _2$$3);
			} else {
				ZVAL_LONG(&key$$3, _1$$3);
			}
			ZEPHIR_INIT_NVAR(&value$$3);
			ZVAL_COPY(&value$$3, _0$$3);
			zephir_update_property_array(this_ptr, SL("_store"), &key$$3, &value$$3 TSRMLS_CC);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value$$3);
		ZEPHIR_INIT_NVAR(&key$$3);
	} else {
		ZEPHIR_INIT_VAR(&init$$5);
		array_init(&init$$5);
		zephir_update_property_zval(this_ptr, SL("_store"), &init$$5);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Toml_KeyTable, getTag) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_tag");

}

PHP_METHOD(Toml_KeyTable, setTag) {

	zval *tag, tag_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tag_sub);

	zephir_fetch_params(0, 1, 0, &tag);



	zephir_update_property_zval(this_ptr, SL("_tag"), tag);

}

/**
 * @param type $index
 */
PHP_METHOD(Toml_KeyTable, offsetSet) {

	zval *index, index_sub, *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&value_sub);

	zephir_fetch_params(0, 2, 0, &index, &value);



	zephir_update_property_array(this_ptr, SL("_store"), index, value TSRMLS_CC);

}

PHP_METHOD(Toml_KeyTable, offsetExists) {

	zval *index, index_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &index);



	zephir_read_property(&_0, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset(&_0, index));

}

PHP_METHOD(Toml_KeyTable, offsetGet) {

	zval *index, index_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	zephir_fetch_params(0, 1, 0, &index);



	zephir_read_property(&_0, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_1, &_0, index, PH_NOISY | PH_READONLY, "toml/KeyTable.zep", 75 TSRMLS_CC);
	RETURN_CTORW(&_1);

}

PHP_METHOD(Toml_KeyTable, offsetUnset) {

	zval *index, index_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &index);



	zephir_read_property(&_0, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, index, PH_SEPARATE);

}

PHP_METHOD(Toml_KeyTable, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

PHP_METHOD(Toml_KeyTable, get) {

	zval *index, index_sub, *defaultValue = NULL, defaultValue_sub, __$null, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&defaultValue_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &index, &defaultValue);

	if (!defaultValue) {
		defaultValue = &defaultValue_sub;
		defaultValue = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, index)) {
		zephir_read_property(&_2, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, index, PH_NOISY, "toml/KeyTable.zep", 90 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(&_0, defaultValue);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Return array copy of everything with nested KeyTable object
 * mediation removed.
 * Modification to Config - allow recurse option, 
 * false for no recurse. It can't be passed on.
 * @param bool $recurse
 * @return array
 */
PHP_METHOD(Toml_KeyTable, toArray) {

	zend_string *_4$$3;
	zend_ulong _3$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *recurse_param = NULL, result, key, value, _0, _1$$3, *_2$$3, _7$$5;
	zend_bool recurse, _5$$4, _6$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &recurse_param);

	if (!recurse_param) {
		recurse = 1;
	} else {
		recurse = zephir_get_boolval(recurse_param);
	}


	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	zephir_read_property(&_0, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
	if (!(ZEPHIR_IS_EMPTY(&_0))) {
		zephir_read_property(&_1$$3, this_ptr, SL("_store"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_1$$3, 0, "toml/KeyTable.zep", 113);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_1$$3), _3$$3, _4$$3, _2$$3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_4$$3 != NULL) { 
				ZVAL_STR_COPY(&key, _4$$3);
			} else {
				ZVAL_LONG(&key, _3$$3);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _2$$3);
			_5$$4 = recurse;
			if (_5$$4) {
				_5$$4 = Z_TYPE_P(&value) == IS_OBJECT;
			}
			_6$$4 = _5$$4;
			if (_6$$4) {
				_6$$4 = (zephir_instance_of_ev(&value, toml_arrayable_ce TSRMLS_CC));
			}
			if (_6$$4) {
				ZEPHIR_CALL_METHOD(&_7$$5, &value, "toarray", NULL, 0);
				zephir_check_call_status();
				zephir_array_update_zval(&result, &key, &_7$$5, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&result, &key, &value, PH_COPY | PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
	}
	RETURN_CCTOR(&result);

}

/**
 * @param myKeyTable should be a KeyTable
 * @return KeyTable
 */
PHP_METHOD(Toml_KeyTable, merge) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *kt, kt_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kt_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &kt);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "_merge", NULL, 1, kt);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Merge values in $config, into the properties of $instance
 * 
 * @param \Yosy\KeyTable $config
 * @param \Yosy\KeyTable  $instance
 * @return \Yosy\KeyTable 
 */
PHP_METHOD(Toml_KeyTable, _merge) {

	zend_bool _5$$6, _6$$6;
	zend_string *_3;
	zend_ulong _2;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *kt, kt_sub, *target = NULL, target_sub, __$null, key, value, myObj, _0, *_1, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&kt_sub);
	ZVAL_UNDEF(&target_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&myObj);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &kt, &target);

	if (!target) {
		target = &target_sub;
		ZEPHIR_CPY_WRT(target, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(target);
	}


	if (!(Z_TYPE_P(target) == IS_OBJECT)) {
		ZEPHIR_CPY_WRT(target, this_ptr);
	}
	zephir_read_property(&_0, kt, SL("_store"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "toml/KeyTable.zep", 155);
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
		ZEPHIR_OBS_NVAR(&myObj);
		zephir_read_property(&_4$$4, target, SL("_store"), PH_NOISY_CC | PH_READONLY);
		if (!(zephir_array_isset_fetch(&myObj, &_4$$4, &key, 0 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(&myObj);
			ZVAL_NULL(&myObj);
		}
		if (Z_TYPE_P(&myObj) == IS_OBJECT) {
			_5$$6 = (zephir_is_instance_of(&myObj, SL("Yosy\\KeyTable") TSRMLS_CC));
			if (_5$$6) {
				_5$$6 = Z_TYPE_P(&value) == IS_OBJECT;
			}
			_6$$6 = _5$$6;
			if (_6$$6) {
				_6$$6 = (zephir_instance_of_ev(&value, toml_keytable_ce TSRMLS_CC));
			}
			if (_6$$6) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "_merge", &_7, 1, &value, &myObj);
				zephir_check_call_status();
				continue;
			}
		}
		zephir_update_property_array(target, SL("_store"), &key, &value TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETVAL_ZVAL(target, 1, 0);
	RETURN_MM();

}

