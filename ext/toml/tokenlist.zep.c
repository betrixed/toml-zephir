
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
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/array.h"


/**
 * Description of TokenArray
 * Just enough to satisfy LexerText
 * @author Michael Rynn
 * 
 */
ZEPHIR_INIT_CLASS(Toml_TokenList) {

	ZEPHIR_REGISTER_CLASS(Toml, TokenList, toml, tokenlist, toml_tokenlist_method_entry, 0);

	zend_declare_property_null(toml_tokenlist_ce, SL("_tokens"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenlist_ce, SL("_ct"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenlist_ce, SL("_index"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(toml_tokenlist_ce, SL("_token"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor
 * Need to call moveNextId or setOffset to set first location,
 * 
 * @param Token[] List of tokens
 */
PHP_METHOD(Toml_TokenList, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *tokens_param = NULL, _0;
	zval tokens;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tokens_param);

	ZEPHIR_OBS_COPY_OR_DUP(&tokens, tokens_param);


	zephir_update_property_zval(this_ptr, SL("_tokens"), &tokens);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, zephir_fast_count_int(&tokens TSRMLS_CC));
	zephir_update_property_zval(this_ptr, SL("_ct"), &_0);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, -1);
	zephir_update_property_zval(this_ptr, SL("_index"), &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "movenextid", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the current token offset
 * @return int
 */
PHP_METHOD(Toml_TokenList, getOffset) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_index");

}

/** 
 * Set current array of tokens position 
 */
PHP_METHOD(Toml_TokenList, setOffset) {

	zval *index_param = NULL, _0, _1$$3, _2$$3, _3$$3, _4$$3;
	zend_long index;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	index = Z_LVAL_P(index_param);


	zephir_read_property(&_0, this_ptr, SL("_ct"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_GT_LONG(&_0, index)) {
		ZEPHIR_INIT_ZVAL_NREF(_1$$3);
		ZVAL_LONG(&_1$$3, index);
		zephir_update_property_zval(this_ptr, SL("_index"), &_1$$3);
		zephir_read_property(&_1$$3, this_ptr, SL("_tokens"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_2$$3, &_1$$3, index, PH_NOISY | PH_READONLY, "toml/TokenList.zep", 41 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("_token"), &_2$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_4$$3);
		zephir_read_property(&_4$$3, &_3$$3, SL("id"), PH_NOISY_CC);
		RETURN_CCTOR(&_4$$3);
	}
	RETURN_MM_LONG(0);

}

/**
 * Checks if the following tokens in the stream match with the sequence of tokens
 *
 * @param int[] $tokenIds Sequence of token ids
 *
 * @return bool
 */
PHP_METHOD(Toml_TokenList, isNextSequence) {

	zend_string *_3;
	zend_ulong _2;
	zend_long offset = 0, base = 0;
	zval *tokenIds_param = NULL, idx, test, _0, *_1, _4$$3, _5$$4, _6$$4, _7$$4;
	zval tokenIds;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tokenIds);
	ZVAL_UNDEF(&idx);
	ZVAL_UNDEF(&test);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tokenIds_param);

	ZEPHIR_OBS_COPY_OR_DUP(&tokenIds, tokenIds_param);


	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_index"), PH_NOISY_CC);
	base = zephir_get_intval(&_0);
	zephir_is_iterable(&tokenIds, 0, "toml/TokenList.zep", 66);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&tokenIds), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&idx);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&idx, _3);
		} else {
			ZVAL_LONG(&idx, _2);
		}
		ZEPHIR_INIT_NVAR(&test);
		ZVAL_COPY(&test, _1);
		offset = (zephir_get_numberval(&idx) + base);
		zephir_read_property(&_4$$3, this_ptr, SL("_ct"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_GT_LONG(&_4$$3, offset)) {
			zephir_read_property(&_5$$4, this_ptr, SL("_tokens"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_long(&_6$$4, &_5$$4, offset, PH_NOISY | PH_READONLY, "toml/TokenList.zep", 61 TSRMLS_CC);
			zephir_read_property(&_7$$4, &_6$$4, SL("id"), PH_NOISY_CC | PH_READONLY);
			if (!ZEPHIR_IS_EQUAL(&_7$$4, &test)) {
				RETURN_MM_BOOL(0);
			}
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&test);
	ZEPHIR_INIT_NVAR(&idx);
	RETURN_MM_BOOL(1);

}

/**
 * Moves the pointer one token forward
 *
 * @return positive token id, or 0 (false)
 */
PHP_METHOD(Toml_TokenList, moveNextId) {

	zend_long next = 0;
	zval __$null, _0, _1, _2$$3, _3$$3, _4$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_index"), PH_NOISY_CC | PH_READONLY);
	next = (zephir_get_numberval(&_0) + 1);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(&_1, next);
	zephir_update_property_zval(this_ptr, SL("_index"), &_1);
	zephir_read_property(&_1, this_ptr, SL("_ct"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_GT_LONG(&_1, next)) {
		zephir_read_property(&_2$$3, this_ptr, SL("_tokens"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_3$$3, &_2$$3, next, PH_NOISY | PH_READONLY, "toml/TokenList.zep", 80 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("_token"), &_3$$3);
		zephir_read_property(&_4$$3, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, &_4$$3, SL("id"), PH_NOISY_CC);
		RETURN_CCTOR(&_5$$3);
	}
	zephir_update_property_zval(this_ptr, SL("_token"), &__$null);
	RETURN_MM_LONG(0);

}

/**
 * Token from current parse position
 * @return \Toml\Token
 */
PHP_METHOD(Toml_TokenList, getToken) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_token");

}

/** 
 * Token id from current parse position
 *  
 */
PHP_METHOD(Toml_TokenList, getTokenId) {

	zval _0, _1$$4, _2$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		RETURN_MM_LONG(0);
	} else {
		zephir_read_property(&_1$$4, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_VAR(&_2$$4);
		zephir_read_property(&_2$$4, &_1$$4, SL("id"), PH_NOISY_CC);
		RETURN_CCTOR(&_2$$4);
	}

}

/** 
 * Token value from current parse position
 *  
 */
PHP_METHOD(Toml_TokenList, getValue) {

	zval value, _0, _1$$4, _2$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		ZEPHIR_INIT_VAR(&value);
		ZVAL_NULL(&value);
	} else {
		zephir_read_property(&_1$$4, this_ptr, SL("_token"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_2$$4, &_1$$4, SL("value"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&value, &_2$$4);
	}
	RETURN_CCTOR(&value);

}

