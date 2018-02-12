<?php

namespace tests;

use Toml\Box;
use Toml\KeyTable;

echo "Hello Toml Tests" . PHP_EOL;

$mystr = "Test Box" . PHP_EOL;

$box = new Box($mystr);

echo "Box encloses " . $box->_me . PHP_EOL;

$tab = new KeyTable();

$idx = strval("1");

$tab[$idx] = 1;
$tab[0] = "100";


print_r($tab);

foreach($tab->_store as $key => $value) {
	echo "$key " . gettype($key) . " " . $value . " " . gettype($value) . PHP_EOL;
}