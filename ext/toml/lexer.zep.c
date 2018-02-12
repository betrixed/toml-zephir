
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
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Toml_Lexer) {

	ZEPHIR_REGISTER_CLASS(Toml, Lexer, toml, lexer, toml_lexer_method_entry, 0);

	zend_declare_property_null(toml_lexer_ce, SL("_nameList"), ZEND_ACC_STATIC|ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("Singles"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("Regex"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(toml_lexer_ce, SL("BriefList"), ZEND_ACC_STATIC|ZEND_ACC_PUBLIC TSRMLS_CC);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BAD"), 0);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_EQUAL"), 1);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BOOLEAN"), 2);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_DATE_TIME"), 3);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_EOS"), 4);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_INTEGER"), 5);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_3_QUOTATION_MARK"), 6);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_QUOTATION_MARK"), 7);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_3_APOSTROPHE"), 8);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_APOSTROPHE"), 9);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_NEWLINE"), 10);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_SPACE"), 11);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LEFT_SQUARE_BRACE"), 12);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_RIGHT_SQUARE_BRACE"), 13);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LEFT_CURLY_BRACE"), 14);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_RIGHT_CURLY_BRACE"), 15);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_COMMA"), 16);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_DOT"), 17);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_UNQUOTED_KEY"), 18);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_ESCAPED_CHARACTER"), 19);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_ESCAPE"), 20);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_BASIC_UNESCAPED"), 21);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_FLOAT"), 22);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_HASH"), 23);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_CHAR"), 24);

	zephir_declare_class_constant_long(toml_lexer_ce, SL("T_LAST_TOKEN"), 24);

	zephir_declare_class_constant_string(toml_lexer_ce, SL("TOML_VERSION"), "0.4");

	return SUCCESS;

}

PHP_METHOD(Toml_Lexer, tomlVersion) {

	zval *this_ptr = getThis();


	RETURN_STRING("0.4");

}

PHP_METHOD(Toml_Lexer, tokenName) {

	zend_bool _0;
	zval *tokenId_param = NULL, _1, _2;
	zend_long tokenId;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	zephir_fetch_params(0, 1, 0, &tokenId_param);

	tokenId = zephir_get_intval(tokenId_param);


	_0 = tokenId > 24;
	if (!(_0)) {
		_0 = tokenId < 0;
	}
	if (_0) {
		tokenId = 0;
	}
	zephir_read_static_property_ce(&_1, toml_lexer_ce, SL("_nameList"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_2, &_1, tokenId, PH_NOISY | PH_READONLY, "toml/Lexer.zep", 116 TSRMLS_CC);
	RETURN_CTORW(&_2);

}

void zephir_init_static_properties_Toml_Lexer(TSRMLS_D) {

	zval _1;
	zval _0, _2, _3, _4;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, 11);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 18);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 5);
	zephir_array_fast_append(&_0, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("BriefList"), &_0);
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 20, 0 TSRMLS_CC);
	add_index_stringl(&_2, 1, SL("/^(=)/"));
	add_index_stringl(&_2, 2, SL("/^(true|false)/"));
	add_index_stringl(&_2, 3, SL("/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/"));
	add_index_stringl(&_2, 22, SL("/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/"));
	add_index_stringl(&_2, 5, SL("/^([+-]?(\\d_?)+)/"));
	add_index_stringl(&_2, 6, SL("/^(\"\"\")/"));
	add_index_stringl(&_2, 7, SL("/^(\")/"));
	add_index_stringl(&_2, 8, SL("/^(\'\'\')/"));
	add_index_stringl(&_2, 9, SL("/^(\')/"));
	add_index_stringl(&_2, 23, SL("/^(#)/"));
	add_index_stringl(&_2, 11, SL("/^(\\s+)/"));
	add_index_stringl(&_2, 12, SL("/^(\\[)/"));
	add_index_stringl(&_2, 13, SL("/^(\\])/"));
	add_index_stringl(&_2, 14, SL("/^(\\{)/"));
	add_index_stringl(&_2, 15, SL("/^(\\})/"));
	add_index_stringl(&_2, 16, SL("/^(,)/"));
	add_index_stringl(&_2, 17, SL("/^(\\.)/"));
	add_index_stringl(&_2, 18, SL("/^([-A-Z_a-z0-9]+)/"));
	add_index_stringl(&_2, 19, SL("/^(\\\(b|t|n|f|r|\"|\\\\|u[0-9AaBbCcDdEeFf]{4,4}|U[0-9AaBbCcDdEeFf]{8,8}))/"));
	add_index_stringl(&_2, 21, SL("/^([\\x{20}-\\x{21}\\x{23}-\\x{26}\\x{28}-\\x{5A}\\x{5E}-\\x{10FFFF}]+)/u"));
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("Regex"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 11, 0 TSRMLS_CC);
	add_assoc_long_ex(&_3, SL("="), 1);
	add_assoc_long_ex(&_3, SL("["), 12);
	add_assoc_long_ex(&_3, SL("]"), 13);
	add_assoc_long_ex(&_3, SL("."), 17);
	add_assoc_long_ex(&_3, SL(","), 16);
	add_assoc_long_ex(&_3, SL("{"), 14);
	add_assoc_long_ex(&_3, SL("}"), 15);
	add_assoc_long_ex(&_3, SL("\""), 7);
	add_assoc_long_ex(&_3, SL("'"), 9);
	add_assoc_long_ex(&_3, SL("#"), 23);
	add_assoc_long_ex(&_3, SL("\\"), 20);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("Singles"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 25, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BAD");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EQUAL");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BOOLEAN");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DATE_TIME");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_EOS");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_INTEGER");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_QUOTATION_MARK");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_QUOTATION_MARK");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_3_APOSTROPHE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_APOSTROPHE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_NEWLINE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_SPACE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_SQUARE_BRACE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_SQUARE_BRACE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_LEFT_CURLY_BRACE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_RIGHT_CURLY_BRACE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_COMMA");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_DOT");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_UNQUOTED_KEY");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPED_CHARACTER");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_ESCAPE");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_BASIC_UNESCAPED");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_FLOAT");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_HASH");
	zephir_array_fast_append(&_4, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "T_CHAR");
	zephir_array_fast_append(&_4, &_1);
	zend_update_static_property(toml_lexer_ce, ZEND_STRL("_nameList"), &_4);
	ZEPHIR_MM_RESTORE();

}

