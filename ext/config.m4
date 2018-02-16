PHP_ARG_ENABLE(toml, whether to enable toml, [ --enable-toml   Enable Toml])

if test "$PHP_TOML" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, TOML_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_TOML, 1, [Whether you have Toml])
	toml_sources="toml.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c toml/arrayable.zep.c
	toml/box.zep.c
	toml/keytable.zep.c
	toml/lexer.zep.c
	toml/parser.zep.c
	toml/parttag.zep.c
	toml/tablelist.zep.c
	toml/token.zep.c
	toml/tokenlist.zep.c
	toml/tokenstream.zep.c
	toml/valuelist.zep.c
	toml/xarrayable.zep.c "
	PHP_NEW_EXTENSION(toml, $toml_sources, $ext_shared,, )
	PHP_SUBST(TOML_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([toml], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([toml], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/toml], [php_TOML.h])

fi
