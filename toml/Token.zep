/*
 * This file is adapted from the Yosymfony\Toml package.
 *
 * (c) YoSymfony <http://github.com/yosymfony>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Toml;

/** 
 * Token used to communicate parse results
 *  
 */
class  Token {
    public value;
    public id;// integer identity!
    public line;
    public isSingle;


    public function __construct() {
        /*let this->value = "";
        let this->id = 0;
        let this->line = -1;
        let this->isSingle = false;
        */
    }
    public function set(string! value, int id, int line, bool isSingle=false) -> void
    {
        let this->value = value;
        let this->id = id;
        let this->line = line;
        let this->isSingle = isSingle;
    }
}