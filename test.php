<?php

namespace tests;

use Toml\Box;
use Toml\KeyTable;
use Toml\Table;
use Toml\ValueList;
use Toml\TableList;


echo "Hello Toml Tests" . PHP_EOL;

$mystr = "Test Box" . PHP_EOL;

$box = new Box($mystr);

echo "Box encloses " . $box->_me . PHP_EOL;

$tab = new KeyTable();

$idx = strval("123"); // An integer key value, as a string

$tab[$idx] = 100;
$tab[0] = "100";


$a = [];


$idx = "1234567898765432109876543210"; // a really big integer
$a[$idx] = 100;
$a["123"] = "100";



print_r($tab);

foreach($tab->_store as $key => $value) {
	echo "$key " . gettype($key) . " " . $value . " " . gettype($value) . PHP_EOL;
}

foreach($a as $key => $value) {
	echo "$key " . gettype($key) . " " . $value . " " . gettype($value) . PHP_EOL;
}

// Now try to retrieve
echo "Try string number '$idx' as key ' = " . $a["123"]. PHP_EOL;


// Try a Table

$toml = new Table();
$toml["100"] = "Value 1";

$list = new TableList();
$end = $list->getEndTable();

$end["199"] = "Value 199";

echo var_export($list);

foreach(get_object_vars($toml) as $key => $value) {
	echo "$key " . gettype($key) . " " . $value . " " . gettype($value) . PHP_EOL;
}

$index = "100";

class Test {
	public $type;
	public $value;
};
$a = [];
$a[$index] = "Array Index";
echo "Type of index is " . gettype($index) . PHP_EOL;
$b = new Test();
$b->type = gettype($index);
$b->{"200"} = "Value 2";
$b->$index = "Another way";
++$index;
echo "Type of index++ is " . gettype($index) . PHP_EOL;
$b->value = $index;


$table = [];
$table[$index] = "As Array";

print_r($b);
echo "For each property " . PHP_EOL;
foreach(get_object_vars($b) as $key => $value) {
	echo "$key (" . gettype($key) . ") is " . $value . " Value is " . gettype($value) . " " . $value . PHP_EOL;
}

echo "For each array" . PHP_EOL;

foreach($table as $key => $value) {
	echo "$key (" . gettype($key) . ") is " . $value . " Value is " . gettype($value) . " " . $value . PHP_EOL;
}

$vlist = new ValueList();

$vlist[0] = 100;
$vlist[1] = 1;

