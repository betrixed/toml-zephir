
extern zend_class_entry *yosy_xarrayable_ce;

ZEPHIR_INIT_CLASS(Yosy_XArrayable);

PHP_METHOD(Yosy_XArrayable, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_xarrayable___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_xarrayable_method_entry) {
	PHP_ME(Yosy_XArrayable, __construct, arginfo_yosy_xarrayable___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
