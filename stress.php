<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

namespace tests;

use Toml\Parser;
use Toml\Lexer;
use Toml\TokenStream;
use Toml\KeyTable;
use Toml\TableList;
use Toml\TokenList;

use Phalcon\Registry;
use Toml\PartTag;

define('TOP_DIR', __DIR__);
/**
 * Description of stress
 *
 * @author michael
 */
class Stress
{
    //[ 'fruit', 'fruit_variety', 'hard_example',  'hard_example_unicode'];
    protected $tomlTests = [ 'fruit'];
    public function getVersionStr() {
        return "TOML version " . Lexer::getUseVersion() . "  " . Lexer::getTomlVersion();
    }
    

    public function leakOne($monitorMe)
    {
         $k1 = new KeyTable();
         $k1["Key1"] = $monitorMe;
         $k1["Key2"] = $monitorMe;
          echo "leak One ";
        xdebug_debug_zval('monitorMe');
        echo PHP_EOL;
        $k1 = null;
    }
    public function leakTwo($monitorMe)
    {
         $k1 = new Registry();
         $k1["Key1"] = $monitorMe;
         $k1["Key2"] = $monitorMe;
          echo "leak Two ";
        xdebug_debug_zval('monitorMe');
        echo PHP_EOL;
        $k1 = null;
    }
    public function oneSpin($monitorMe) {
        //$data1 = Parser::parseFile($file);

        
        $this->leakTwo($monitorMe);
        //$sub = new KeyTable();
        //$regSub = new Registry();
        //$regSub["Hide"] = $monitorMe;
        //$sub["Hide"] = "Hidden";
        //$reg = new Registry();

        //$reg["Key"] = $regSub;
        
        //$reg["Key2"] = $monitorMe;
       
        //$t1 = new TableList();
       //$t1->getEndTable()["test"] = "Help";
        // memory "leaks if these are not nulled"
        //$k1->offsetUnset("Key");
        
       // $t1 = null;
        //$reg = null;
    }

    public function parseFile($file)
    {

        $data = Parser::parseFile($file);
        echo "OUTOUT = " . print_r($data,true) . PHP_EOL;
    }

    public function tokenFile($file)
    {

        $input = file_get_contents($file);
        $lex = new Lexer();
        $tokenList = $lex->tokenize($input);
         //$result = Parser::parseFile($file);
    }

    public function streamFile($file) {

        $s = new TokenStream();
        $s->setExpList(Lexer::getAllRegex());
        $s->setSingles(Lexer::getAllSingles());
        $s->setUnknownId(Lexer::T_CHAR);
        $s->setNewLineId(Lexer::T_NEWLINE);
        $s->setEOSId(Lexer::T_EOS);
        
        $input = file_get_contents($file);
        $s->setInput($input);

        //$list = [];

        //while ($s->moveNextId() !== Lexer::T_EOS) {
        //    $list[] = clone $s->getToken();
        //}
        print_r($s);
        $maxCount = 3;
        $i = 0;

        while( $i < $maxCount) {
            $s->moveNextId();
            //$token = clone $s->getToken();
            //$list[] = $token;
            $token = $s->getToken();
            echo "Id " . $token->id . " " . $token->value . PHP_EOL;
            if ($token->id === Lexer::T_EOS)
                break;
            $i++;
        }

        echo "Total tokens = $i" . PHP_EOL;
        
        //$tokenList = new TokenList($list);
        $s->token = null;
        $s = null;

    }
    public function outOfMemory() {
        gc_enable();
        echo "Test" . PHP_EOL . PHP_EOL;
        $mod_dir = 
        $tripped = false;
        $memInc = 0.0;
        
        $iterations = 3;
        $start_time = microtime(true);
       
       
        $test = 0;
        $kt = null;
        $monitorMe = new Class{};
        echo "Start Outer" . PHP_EOL;

        $file = TOP_DIR . "/files/config.toml";
        $i = 0;
        $startMem = $endMem = 0;
        $memInit = memory_get_usage();
        $input = <<<'toml'
        t = true
        f = false
toml;
            
            

            //xdebug_debug_zval('monitorMe');
            
            //$this->leakOne($monitorMe);
            for ($i = 0 ; $i < 2; $i++)
            {
                if ($i > 0) {
                    $startMem = memory_get_usage();
                }
                $this->parseFile($file);
            }
            gc_collect_cycles();
            
            //xdebug_debug_zval('monitorMe');
            
        

        $endMem = memory_get_usage();
        $memInc +=  ($endMem - $startMem);
        echo "*** Memory Inc  = " . $memInc . PHP_EOL;
        $monitorMe = null;
        xdebug_debug_zval('monitorMe');

        $end_time = microtime(true);
        echo "$iterations iterations. Average iteration = " . sprintf( "%10.3f",($end_time - $start_time)*1000.0 / $iterations) . " ms" . PHP_EOL;
        echo "Total Memory added = " . ($endMem - $memInit) / 1024.0 . " KB"  . PHP_EOL;

    }
}

$stress = new Stress();

echo $stress->getVersionStr() . PHP_EOL;
$stress->outOfMemory();
