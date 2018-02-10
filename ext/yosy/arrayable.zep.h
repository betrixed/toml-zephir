
extern zend_class_entry *yosy_arrayable_ce;

ZEPHIR_INIT_CLASS(Yosy_Arrayable);

PHP_METHOD(Yosy_Arrayable, setTag);
PHP_METHOD(Yosy_Arrayable, getTag);
PHP_METHOD(Yosy_Arrayable, toArray);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yosy_arrayable_settag, 0, 0, 1)
	ZEND_ARG_INFO(0, any)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yosy_arrayable_method_entry) {
	PHP_ME(Yosy_Arrayable, setTag, arginfo_yosy_arrayable_settag, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_Arrayable, getTag, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Yosy_Arrayable, toArray, NULL, ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
