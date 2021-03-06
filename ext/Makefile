srcdir = /var/www/parracan.org/private/toml-zephir/ext
builddir = /var/www/parracan.org/private/toml-zephir/ext
top_srcdir = /var/www/parracan.org/private/toml-zephir/ext
top_builddir = /var/www/parracan.org/private/toml-zephir/ext
EGREP = /usr/bin/grep -E
SED = /usr/bin/sed
CONFIGURE_COMMAND = './configure' '--enable-toml'
CONFIGURE_OPTIONS = '--enable-toml'
SHLIB_SUFFIX_NAME = so
SHLIB_DL_SUFFIX_NAME = so
ZEND_EXT_TYPE = zend_extension
RE2C = re2c
AWK = gawk
shared_objects_toml = toml.lo kernel/main.lo kernel/memory.lo kernel/exception.lo kernel/debug.lo kernel/backtrace.lo kernel/object.lo kernel/array.lo kernel/string.lo kernel/fcall.lo kernel/require.lo kernel/file.lo kernel/operators.lo kernel/math.lo kernel/concat.lo kernel/variables.lo kernel/filter.lo kernel/iterator.lo kernel/time.lo kernel/exit.lo toml/arrayable.lo toml/box.lo toml/keytable.lo toml/lexer.lo toml/parser.lo toml/parttag.lo toml/tablelist.lo toml/token.lo toml/tokenlist.lo toml/tokenstream.lo toml/valuelist.lo toml/xarrayable.lo
PHP_PECL_EXTENSION = toml
TOML_SHARED_LIBADD =
PHP_MODULES = $(phplibdir)/toml.la
PHP_ZEND_EX =
all_targets = $(PHP_MODULES) $(PHP_ZEND_EX)
install_targets = install-modules install-headers
prefix = /usr
exec_prefix = $(prefix)
libdir = ${exec_prefix}/lib
prefix = /usr
phplibdir = /var/www/parracan.org/private/toml-zephir/ext/modules
phpincludedir = /usr/include/php
CC = gcc
CFLAGS = -O2 -fvisibility=hidden -Wparentheses -flto -DZEPHIR_RELEASE=1
CFLAGS_CLEAN = $(CFLAGS)
CPP = gcc -E
CPPFLAGS = -DHAVE_CONFIG_H
CXX =
CXXFLAGS =
CXXFLAGS_CLEAN = $(CXXFLAGS)
EXTENSION_DIR = /usr/lib/php/modules
PHP_EXECUTABLE = /usr/bin/php
EXTRA_LDFLAGS =
EXTRA_LIBS =
INCLUDES = -I/usr/include/php -I/usr/include/php/main -I/usr/include/php/TSRM -I/usr/include/php/Zend -I/usr/include/php/ext -I/usr/include/php/ext/date/lib
LFLAGS =
LDFLAGS =
SHARED_LIBTOOL =
LIBTOOL = $(SHELL) $(top_builddir)/libtool
SHELL = /bin/sh
INSTALL_HEADERS = ext/toml/php_TOML.h
mkinstalldirs = $(top_srcdir)/build/shtool mkdir -p
INSTALL = $(top_srcdir)/build/shtool install -c
INSTALL_DATA = $(INSTALL) -m 644

DEFS = -DPHP_ATOM_INC -I$(top_builddir)/include -I$(top_builddir)/main -I$(top_srcdir)
COMMON_FLAGS = $(DEFS) $(INCLUDES) $(EXTRA_INCLUDES) $(CPPFLAGS) $(PHP_FRAMEWORKPATH)

all: $(all_targets)
	@echo
	@echo "Build complete."
	@echo "Don't forget to run 'make test'."
	@echo

build-modules: $(PHP_MODULES) $(PHP_ZEND_EX)

build-binaries: $(PHP_BINARIES)

libphp$(PHP_MAJOR_VERSION).la: $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS)
	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -rpath $(phptempdir) $(EXTRA_LDFLAGS) $(LDFLAGS) $(PHP_RPATHS) $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS) $(EXTRA_LIBS) $(ZEND_EXTRA_LIBS) -o $@
	-@$(LIBTOOL) --silent --mode=install cp $@ $(phptempdir)/$@ >/dev/null 2>&1

libs/libphp$(PHP_MAJOR_VERSION).bundle: $(PHP_GLOBAL_OBJS) $(PHP_SAPI_OBJS)
	$(CC) $(MH_BUNDLE_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(PHP_GLOBAL_OBJS:.lo=.o) $(PHP_SAPI_OBJS:.lo=.o) $(PHP_FRAMEWORKS) $(EXTRA_LIBS) $(ZEND_EXTRA_LIBS) -o $@ && cp $@ libs/libphp$(PHP_MAJOR_VERSION).so

install: $(all_targets) $(install_targets)

install-sapi: $(OVERALL_TARGET)
	@echo "Installing PHP SAPI module:       $(PHP_SAPI)"
	-@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	-@if test ! -r $(phptempdir)/libphp$(PHP_MAJOR_VERSION).$(SHLIB_DL_SUFFIX_NAME); then \
		for i in 0.0.0 0.0 0; do \
			if test -r $(phptempdir)/libphp$(PHP_MAJOR_VERSION).$(SHLIB_DL_SUFFIX_NAME).$$i; then \
				$(LN_S) $(phptempdir)/libphp$(PHP_MAJOR_VERSION).$(SHLIB_DL_SUFFIX_NAME).$$i $(phptempdir)/libphp$(PHP_MAJOR_VERSION).$(SHLIB_DL_SUFFIX_NAME); \
				break; \
			fi; \
		done; \
	fi
	@$(INSTALL_IT)

install-binaries: build-binaries $(install_binary_targets)

install-modules: build-modules
	@test -d modules && \
	$(mkinstalldirs) $(INSTALL_ROOT)$(EXTENSION_DIR)
	@echo "Installing shared extensions:     $(INSTALL_ROOT)$(EXTENSION_DIR)/"
	@rm -f modules/*.la >/dev/null 2>&1
	@$(INSTALL) modules/* $(INSTALL_ROOT)$(EXTENSION_DIR)

install-headers:
	-@if test "$(INSTALL_HEADERS)"; then \
		for i in `echo $(INSTALL_HEADERS)`; do \
			i=`$(top_srcdir)/build/shtool path -d $$i`; \
			paths="$$paths $(INSTALL_ROOT)$(phpincludedir)/$$i"; \
		done; \
		$(mkinstalldirs) $$paths && \
		echo "Installing header files:          $(INSTALL_ROOT)$(phpincludedir)/" && \
		for i in `echo $(INSTALL_HEADERS)`; do \
			if test "$(PHP_PECL_EXTENSION)"; then \
				src=`echo $$i | $(SED) -e "s#ext/$(PHP_PECL_EXTENSION)/##g"`; \
			else \
				src=$$i; \
			fi; \
			if test -f "$(top_srcdir)/$$src"; then \
				$(INSTALL_DATA) $(top_srcdir)/$$src $(INSTALL_ROOT)$(phpincludedir)/$$i; \
			elif test -f "$(top_builddir)/$$src"; then \
				$(INSTALL_DATA) $(top_builddir)/$$src $(INSTALL_ROOT)$(phpincludedir)/$$i; \
			else \
				(cd $(top_srcdir)/$$src && $(INSTALL_DATA) *.h $(INSTALL_ROOT)$(phpincludedir)/$$i; \
				cd $(top_builddir)/$$src && $(INSTALL_DATA) *.h $(INSTALL_ROOT)$(phpincludedir)/$$i) 2>/dev/null || true; \
			fi \
		done; \
	fi

PHP_TEST_SETTINGS = -d 'open_basedir=' -d 'output_buffering=0' -d 'memory_limit=-1'
PHP_TEST_SHARED_EXTENSIONS =  ` \
	if test "x$(PHP_MODULES)" != "x"; then \
		for i in $(PHP_MODULES)""; do \
			. $$i; $(top_srcdir)/build/shtool echo -n -- " -d extension=$$dlname"; \
		done; \
	fi; \
	if test "x$(PHP_ZEND_EX)" != "x"; then \
		for i in $(PHP_ZEND_EX)""; do \
			. $$i; $(top_srcdir)/build/shtool echo -n -- " -d $(ZEND_EXT_TYPE)=$(top_builddir)/modules/$$dlname"; \
		done; \
	fi`
PHP_DEPRECATED_DIRECTIVES_REGEX = '^(magic_quotes_(gpc|runtime|sybase)?|(zend_)?extension(_debug)?(_ts)?)[\t\ ]*='

test: all
	@if test ! -z "$(PHP_EXECUTABLE)" && test -x "$(PHP_EXECUTABLE)"; then \
		INI_FILE=`$(PHP_EXECUTABLE) -d 'display_errors=stderr' -r 'echo php_ini_loaded_file();' 2> /dev/null`; \
		if test "$$INI_FILE"; then \
			$(EGREP) -h -v $(PHP_DEPRECATED_DIRECTIVES_REGEX) "$$INI_FILE" > $(top_builddir)/tmp-php.ini; \
		else \
			echo > $(top_builddir)/tmp-php.ini; \
		fi; \
		INI_SCANNED_PATH=`$(PHP_EXECUTABLE) -d 'display_errors=stderr' -r '$$a = explode(",\n", trim(php_ini_scanned_files())); echo $$a[0];' 2> /dev/null`; \
		if test "$$INI_SCANNED_PATH"; then \
			INI_SCANNED_PATH=`$(top_srcdir)/build/shtool path -d $$INI_SCANNED_PATH`; \
			$(EGREP) -h -v $(PHP_DEPRECATED_DIRECTIVES_REGEX) "$$INI_SCANNED_PATH"/*.ini >> $(top_builddir)/tmp-php.ini; \
		fi; \
		TEST_PHP_EXECUTABLE=$(PHP_EXECUTABLE) \
		TEST_PHP_SRCDIR=$(top_srcdir) \
		CC="$(CC)" \
			$(PHP_EXECUTABLE) -n -c $(top_builddir)/tmp-php.ini $(PHP_TEST_SETTINGS) $(top_srcdir)/run-tests.php -n -c $(top_builddir)/tmp-php.ini -d extension_dir=$(top_builddir)/modules/ $(PHP_TEST_SHARED_EXTENSIONS) $(TESTS); \
		TEST_RESULT_EXIT_CODE=$$?; \
		rm $(top_builddir)/tmp-php.ini; \
		exit $$TEST_RESULT_EXIT_CODE; \
	else \
		echo "ERROR: Cannot run tests without CLI sapi."; \
	fi

clean:
	find . -name \*.gcno -o -name \*.gcda | xargs rm -f
	find . -name \*.lo -o -name \*.o | xargs rm -f
	find . -name \*.la -o -name \*.a | xargs rm -f
	find . -name \*.so | xargs rm -f
	find . -name .libs -a -type d|xargs rm -rf
	rm -f libphp$(PHP_MAJOR_VERSION).la $(SAPI_CLI_PATH) $(SAPI_CGI_PATH) $(SAPI_MILTER_PATH) $(SAPI_LITESPEED_PATH) $(SAPI_FPM_PATH) $(OVERALL_TARGET) modules/* libs/*

distclean: clean
	rm -f Makefile config.cache config.log config.status Makefile.objects Makefile.fragments libtool main/php_config.h main/internal_functions_cli.c main/internal_functions.c stamp-h buildmk.stamp Zend/zend_dtrace_gen.h Zend/zend_dtrace_gen.h.bak Zend/zend_config.h TSRM/tsrm_config.h
	rm -f php7.spec main/build-defs.h scripts/phpize
	rm -f ext/date/lib/timelib_config.h ext/mbstring/oniguruma/config.h ext/mbstring/libmbfl/config.h ext/oci8/oci8_dtrace_gen.h ext/oci8/oci8_dtrace_gen.h.bak
	rm -f scripts/man1/phpize.1 scripts/php-config scripts/man1/php-config.1 sapi/cli/php.1 sapi/cgi/php-cgi.1 ext/phar/phar.1 ext/phar/phar.phar.1
	rm -f sapi/fpm/php-fpm.conf sapi/fpm/init.d.php-fpm sapi/fpm/php-fpm.service sapi/fpm/php-fpm.8 sapi/fpm/status.html
	rm -f ext/iconv/php_have_bsd_iconv.h ext/iconv/php_have_glibc_iconv.h ext/iconv/php_have_ibm_iconv.h ext/iconv/php_have_iconv.h ext/iconv/php_have_libiconv.h ext/iconv/php_iconv_aliased_libiconv.h ext/iconv/php_iconv_supports_errno.h ext/iconv/php_php_iconv_h_path.h ext/iconv/php_php_iconv_impl.h
	rm -f ext/phar/phar.phar ext/phar/phar.php
	if test "$(srcdir)" != "$(builddir)"; then \
	  rm -f ext/phar/phar/phar.inc; \
	fi
	$(EGREP) define'.*include/php' $(top_srcdir)/configure | $(SED) 's/.*>//'|xargs rm -f

prof-gen:
	CCACHE_DISABLE=1 $(MAKE) PROF_FLAGS=-fprofile-generate all

prof-clean:
	find . -name \*.lo -o -name \*.o | xargs rm -f
	find . -name \*.la -o -name \*.a | xargs rm -f
	find . -name \*.so | xargs rm -f
	rm -f libphp$(PHP_MAJOR_VERSION).la $(SAPI_CLI_PATH) $(SAPI_CGI_PATH) $(SAPI_MILTER_PATH) $(SAPI_LITESPEED_PATH) $(SAPI_FPM_PATH) $(OVERALL_TARGET) modules/* libs/*

prof-use:
	CCACHE_DISABLE=1 $(MAKE) PROF_FLAGS=-fprofile-use all


.PHONY: all clean install distclean test prof-gen prof-clean prof-use
.NOEXPORT:
toml.lo: /var/www/parracan.org/private/toml-zephir/ext/toml.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml.c -o toml.lo 
kernel/main.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/main.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/main.c -o kernel/main.lo 
kernel/memory.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/memory.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/memory.c -o kernel/memory.lo 
kernel/exception.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/exception.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/exception.c -o kernel/exception.lo 
kernel/debug.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/debug.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/debug.c -o kernel/debug.lo 
kernel/backtrace.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/backtrace.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/backtrace.c -o kernel/backtrace.lo 
kernel/object.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/object.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/object.c -o kernel/object.lo 
kernel/array.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/array.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/array.c -o kernel/array.lo 
kernel/string.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/string.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/string.c -o kernel/string.lo 
kernel/fcall.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/fcall.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/fcall.c -o kernel/fcall.lo 
kernel/require.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/require.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/require.c -o kernel/require.lo 
kernel/file.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/file.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/file.c -o kernel/file.lo 
kernel/operators.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/operators.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/operators.c -o kernel/operators.lo 
kernel/math.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/math.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/math.c -o kernel/math.lo 
kernel/concat.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/concat.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/concat.c -o kernel/concat.lo 
kernel/variables.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/variables.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/variables.c -o kernel/variables.lo 
kernel/filter.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/filter.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/filter.c -o kernel/filter.lo 
kernel/iterator.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/iterator.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/iterator.c -o kernel/iterator.lo 
kernel/time.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/time.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/time.c -o kernel/time.lo 
kernel/exit.lo: /var/www/parracan.org/private/toml-zephir/ext/kernel/exit.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/kernel/exit.c -o kernel/exit.lo 
toml/arrayable.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/arrayable.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/arrayable.zep.c -o toml/arrayable.lo 
toml/box.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/box.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/box.zep.c -o toml/box.lo 
toml/keytable.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/keytable.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/keytable.zep.c -o toml/keytable.lo 
toml/lexer.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/lexer.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/lexer.zep.c -o toml/lexer.lo 
toml/parser.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/parser.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/parser.zep.c -o toml/parser.lo 
toml/parttag.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/parttag.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/parttag.zep.c -o toml/parttag.lo 
toml/tablelist.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/tablelist.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/tablelist.zep.c -o toml/tablelist.lo 
toml/token.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/token.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/token.zep.c -o toml/token.lo 
toml/tokenlist.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/tokenlist.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/tokenlist.zep.c -o toml/tokenlist.lo 
toml/tokenstream.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/tokenstream.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/tokenstream.zep.c -o toml/tokenstream.lo 
toml/valuelist.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/valuelist.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/valuelist.zep.c -o toml/valuelist.lo 
toml/xarrayable.lo: /var/www/parracan.org/private/toml-zephir/ext/toml/xarrayable.zep.c
	$(LIBTOOL) --mode=compile $(CC)  -I. -I/var/www/parracan.org/private/toml-zephir/ext $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)  -c /var/www/parracan.org/private/toml-zephir/ext/toml/xarrayable.zep.c -o toml/xarrayable.lo 
$(phplibdir)/toml.la: ./toml.la
	$(LIBTOOL) --mode=install cp ./toml.la $(phplibdir)

./toml.la: $(shared_objects_toml) $(TOML_SHARED_DEPENDENCIES)
	$(LIBTOOL) --mode=link $(CC) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(LDFLAGS) -o $@ -export-dynamic -avoid-version -prefer-pic -module -rpath $(phplibdir) $(EXTRA_LDFLAGS) $(shared_objects_toml) $(TOML_SHARED_LIBADD)

