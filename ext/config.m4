PHP_ARG_ENABLE(yosy, whether to enable yosy, [ --enable-yosy   Enable Yosy])

if test "$PHP_YOSY" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, YOSY_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_YOSY, 1, [Whether you have Yosy])
	yosy_sources="yosy.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c yosy/arrayable.zep.c
	yosy/box.zep.c
	yosy/keytable.zep.c
	yosy/token.zep.c
	yosy/tokenstream.zep.c
	yosy/valuelist.zep.c
	yosy/xarrayable.zep.c
	yosy/toml/lexer.zep.c "
	PHP_NEW_EXTENSION(yosy, $yosy_sources, $ext_shared,, )
	PHP_SUBST(YOSY_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([yosy], [pcre])
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
					PHP_ADD_EXTENSION_DEP([yosy], [json])
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

	PHP_INSTALL_HEADERS([ext/yosy], [php_YOSY.h])

fi
