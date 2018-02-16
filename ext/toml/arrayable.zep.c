
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Provides array syntax like access to get and set PHP object properties, and
 * restricted conversions to and from array via merge and toArray.
 * The Tag property is for possible management data, without interfering with
 * planned storage implementation.
 * 
 * @author Michael Rynn
 */
ZEPHIR_INIT_CLASS(Toml_Arrayable) {

	ZEPHIR_REGISTER_INTERFACE(Toml, Arrayable, toml, arrayable, toml_arrayable_method_entry);

	zend_class_implements(toml_arrayable_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(toml_arrayable_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Toml_Arrayable, toArray);

ZEPHIR_DOC_METHOD(Toml_Arrayable, getTag);

ZEPHIR_DOC_METHOD(Toml_Arrayable, setTag);

