
extern zend_class_entry *yosy_box_ce;

ZEPHIR_INIT_CLASS(Yosy_Box);

PHP_METHOD(Yosy_Box, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_box___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, me)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_box_method_entry) {
	PHP_ME(Yosy_Box, __construct, arginfo_yosy_box___construct, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL|ZEND_ACC_CTOR)
	PHP_FE_END
};
