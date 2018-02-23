PHP and TOML
============

This zephir version of toml parser was initially based Yosymfony/Toml, authored by Víctor Puertas

This compiled extension uses namespace Toml.

The php interpreted-only version that performs much the same
with the same php-unit test rig error messages is at [Betrixed/Toml](https://github.com/betrixed/toml), as forked and modified by Michael Rynn.

The zephir version is a bit faster than the interpreted PHP. How much faster will depend on the test benchmark method. Php 7.2 is being used here. 

For the initial interation the difference from interpreted to compiled was about 20% faster. This narrowed with subsequent iterations, to maybe around 15%. The php-code and regular expression compiled cache is expected to narrow the difference with subsequent runs.
