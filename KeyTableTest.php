<?php
namespace Tests;


use Toml\KeyTable;
use Toml\Tagable;
use Toml\ValueList;
use Toml\Parser;
use Toml\TokenStream;
use Toml\Lexer;

$kt1 = new KeyTable();
print_r($kt1);

echo "Created " . PHP_EOL;

echo "Count = " . $kt1->count() . PHP_EOL;

$kt1["Key1"] = "Value 1";

echo "Count = " . $kt1->count(). PHP_EOL;

$kt1[123] = "Value 2";

echo "Count = " . $kt1->count(). PHP_EOL;

$a[0] = 0;

$a["Key2"] = 123456;

$kt2 = new KeyTable($a);

print_r($kt2);

echo "Created " . PHP_EOL;
echo "Count = " . $kt2->count(). PHP_EOL;

echo "Value = " . $kt2["Key2"] . PHP_EOL;


$kt1->merge($kt2);

print_r($kt1);

unset($kt1[0]);

print_r($kt1);
$test = isset($kt1[0]) ? "Yes" : "No";

echo "Isset 0 " . $test . PHP_EOL;

$test = isset($kt1["Key2"]) ? "Yes" : "No";

echo "Isset Key2 " . $test . PHP_EOL;


class Tag {
	public $value;
};

$tag = new Tag();

$tag->value = "Tagged";

$kt1->setTag($tag);
print_r($kt1);


$check = $kt1->getTag();
echo "Tag value is " . $check->value . PHP_EOL;


class Tagme {
	private $_tag;

	public function setTag($v) {
		$this->_tag = $v;
	}
	public function getTag(){
		$this->_tag = $v;
	}
}

class Extra extends Tagme {
	public $mydata;
}


$val = new ValueList();

$val[] = "Plus 1";
$val[] = "Plus 2";
$val[4] = "Plus 4";


$val["1234"] = "1234";


$p = new Parser();

$input = <<<'toml'
        backspace = "This string has a \b backspace character."
        tab = "This string has a \t tab character."
        newline = "This string has a \n new line character."
        formfeed = "This string has a \f form feed character."
        carriage = "This string has a \r carriage return character."
        quote = "This string has a \" quote character."
        backslash = "This string has a \\ backslash character."
        notunicode1 = "This string does not have a unicode \\u escape."
        notunicode2 = "This string does not have a unicode \\u0075 escape."
toml;

$result = $p->parse($input);

echo print_r($result,true);