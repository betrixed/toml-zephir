
extern zend_class_entry *yosy_token_ce;

ZEPHIR_INIT_CLASS(Yosy_Token);

PHP_METHOD(Yosy_Token, __construct);
PHP_METHOD(Yosy_Token, set);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_token_set, 0, 0, 3)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, isSingle)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_token_method_entry) {
	PHP_ME(Yosy_Token, __construct, NULL, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Yosy_Token, set, arginfo_yosy_token_set, ZEND_ACC_FINAL|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
