/**
* Transcribed from a version adapated from Yosymfony/Toml 
* 
* @author Michael Rynn
*/
namespace Toml;



/**
 * Parser for TOML strings (specification version 0.4.0).
 *
 * @author Victor Puertas <vpgugr@vpgugr.com>
 */
class Parser
{
    const E_KEY = 0;
    const E_SCALER = 1;
    const E_LSTRING = 2;
    const E_MLSTRING = 3;
    const E_BSTRING = 4;
    const E_ALL = 5;

    const IM_SPACE = "/(\\s+)/"; //immediate white space
    private _root = null; // root Table object
    private _table = null; // dyanamic reference to current Table object
// Token stream
    private _ts = null;

 // Current regex table type
    private _expSetId = -1;
    // Stack of regex types.
    private _expStack;
    private _stackTop;


    // Regular expressions, as class constants
    static private _keyRegex;  
    static private _valRegex;
    static private _regEString;
    static private _regLString;
    static private _regMLString;
   
     /**
     * Set the expression set to the previous on the
     * expression set stack (a stack of integers) 
     */
    public function popExpSet() -> void
    {
        int value;
        int top;
        var stack;
        let stack = this->_expStack;
        let top = (int) this->_stackTop;

        if top > 0 {
            let top = top - 1;
            let value = (int) stack->offsetGet(top);
            this->setExpSet(value);
            let this->_stackTop = top;
            return;
        }
        throw new XArrayable("popExpSet on empty stack"); 
    }

    /**
     * Push a known expression set defined by a 
     * constant
     * @param int $value
     */
    public function pushExpSet(int! value) ->  void
    {
        // save current value
        var stack;
        int ct,top;
        let stack = this->_expStack;
        let top = (int) this->_stackTop; // top is insertion index
        let ct = (int) stack->count();
        if ct <= top { 
            // expand
            stack->setSize(top+16);
        }
        stack->offsetSet(top,this->_expSetId);
        let this->_stackTop = top+1;
        this->setExpSet(value);
    }

    public static function getExpSet(int! value) -> <KeyTable>
    {
        var result;

        switch (value) {
            case Parser::E_KEY:
                let result = self::_keyRegex;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::KeyList);
                    let self::_keyRegex = result;
                }
                break;
            case Parser::E_BSTRING:
                let result = self::_regEString;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::BasicString);
                    let self::_regEString = result;
                }
                break;
            case Parser::E_LSTRING:
                let result = self::_regLString;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::LiteralString);
                    let self::_regLString = result;
                }
                break;
            case Parser::E_SCALER:
                let result = self::_valRegex;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::ScalerList);
                    let self::_valRegex = result;
                }
                break;
            case Parser::E_MLSTRING:
                let result = self::_regMLString;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::LiteralMLString);
                    let self::_regMLString = result;
                }
                break;   
            case Parser::E_ALL:
                let result = Lexer::getAllRegex();
                break;
            default:
                throw new XArrayable("Not a defined table constant for getExpSet");
        }    
        return result;
    }
    private function setExpSet(int! value) -> void
    {
        var obj;     
        switch (value) {
            case Parser::E_KEY:
                let obj = Parser::_keyRegex;
                break;
            case Parser::E_SCALER:
                let obj = Parser::_valRegex;
                break;
            case Parser::E_LSTRING:
                let obj = Parser::_regLString;
                break;
            case Parser::E_BSTRING:
                let obj = Parser::_regEString;
                break;
            case Parser::E_MLSTRING:
                let obj = Parser::_regMLString;
                break;
            default:
                throw new XArrayable("Invalid expression set constant " . value);
        }
        let this->_expSetId = value;
        this->_ts->setExpSet(obj);
    }

    /**
     * Setup class constants
     */
    public function __construct()
    {
    	var ts;

        let this->_root = new KeyTable();
        let this->_table = this->_root;
        let this->_expStack = new \SplFixedArray();
        let this->_stackTop = 0;
        let Parser::_keyRegex = this->getExpSet(Parser::E_KEY);
        let Parser::_valRegex = this->getExpSet(Parser::E_SCALER);
        let Parser::_regEString = this->getExpSet(Parser::E_BSTRING);
        let Parser::_regLString = this->getExpSet(Parser::E_LSTRING);
        let Parser::_regMLString = this->getExpSet(Parser::E_MLSTRING);

        let ts = new TokenStream();
        ts->setSingles(Lexer::getAllSingles());
        ts->setUnknownId(Lexer::T_CHAR);
        ts->setNewLineId(Lexer::T_NEWLINE);
        ts->setEOSId(Lexer::T_EOS);
        let this->_ts = ts; // setExpSet requires this
        // point to the base regexp array
        this->setExpSet(Parser::E_KEY);
    }

    /**
     * Reads string from specified file path and parses it as TOML.
     *
     * @param (string) File path
     *
     * @return (array) Toml::parse() result
     */
    public static function parseFile(string! path) -> array
    {
        if (!is_file(path)) {
            throw new XArrayable("File path not a file " . path);
        }

        var toml, parser;

        let toml = file_get_contents(path);

        // Remove BOM if present
        let toml = preg_replace("/^" . pack("H*", "EFBBBF") . "/", "", toml);

        let parser = new Parser();
        return parser->parse(toml);
    }
    private function prepareInput(var input) -> void 
    {
        if (preg_match("//u", input) === false) {
            throw new XArrayable("The TOML input does not appear to be valid UTF-8.");
        }
        var iclean;
        let iclean = str_replace(["\r\n", "\r"], "\n", input);
        let iclean = str_replace("\t", " ", iclean);

        this->_ts->setInput(iclean);   
    }
    /**
     * {@inheritdoc}
     */
    public function parse(string! input) -> array
    {
        this->prepareInput(input);
        this->implementation(this->_ts);
        return this->_root->toArray();
    }
    public function getRoot() -> <KeyTable>
    {
        return this->_root;
    }
    /**
     * Process all tokens until T_EOS
     * @param TokenStream $ts
     */
    private function implementation(<TokenStream> ts) -> void
    {

        int tokenId;
        let this->_table = this->_root;
        //echo "Start " . print_r(this,true) . PHP_EOL;
        let tokenId = (int) ts->moveNextId();

        while (tokenId != Lexer::T_EOS) {
            switch (tokenId) {
                case Lexer::T_HASH :
                    let tokenId = (int) this->parseComment(ts);
                    break;
                case Lexer::T_QUOTATION_MARK:
                case Lexer::T_UNQUOTED_KEY:
                case Lexer::T_APOSTROPHE :
                case Lexer::T_INTEGER :
                    let tokenId = (int) this->parseKeyValue(ts);
                    break;
                case Lexer::T_LEFT_SQUARE_BRACE:
                    let tokenId = (int) this->parseTablePath(ts);
                    break;
                case Lexer::T_SPACE :
                case Lexer::T_NEWLINE:
                    // loop again
                    let tokenId = (int) ts->moveNextId();
                    break;
                default:
                    this->syntaxError("Expect Key = , [Path] or # Comment", ts->getToken());
                    break;
            }
        }
    }


    /** 
     * Skip comment, and return next none-comment token or NEWLINE or EOS
     *  
     */
    private function parseComment(<TokenStream> ts) -> int
    {
        int tokenId;
        // Assert : Presume called because parser found a '#'
        // Go to next vertical whitespace.
        ts->moveRegex("/^(\\V*)/");
        let tokenId = (int) ts->moveNextId();
        return tokenId;
    }
    /**
     *  Get a value that is not a table or array.
     *  Predict and setup parse for simple value, using peek $tokenId
     */
    private function getSimpleValue(int! tokenId) -> var {  
        var ts;
        var value;

        let ts = this->_ts;
        if tokenId == Lexer::T_APOSTROPHE {
            // 3 or 1 quote? [\\x{27}]{3,3}
            if ts->moveRegex("/^(\\'\\'\\')/") {
                let value = this->parseMLString(ts);
            }
            else {
                ts->acceptToken();
                let value = this->parseLiteralString(ts);
            }
            //echo "Value (') = " . value . PHP_EOL;
            return value;
        } 
        elseif tokenId == Lexer::T_QUOTATION_MARK {
            // 3 or 1 quote? [\\x{22}]{3,3}
            if ts->moveRegex("/^(\\\"\\\"\\\")/") {
                let value = this->parseMLEscapeString(ts);
            }
            else {
                ts->acceptToken();
                let value = this->parseEscapeString(ts);
            }
            //echo "Value (\") = " . value . PHP_EOL;
            //echo print_r(this) . PHP_EOL;
            return value;
        }
        this->pushExpSet(Parser::E_SCALER);
        // reject token Id and process regular expressions
        
        let tokenId =  (int) ts->moveNextId();
        switch (tokenId) {
            case Lexer::T_INTEGER:
                let value = this->parseInteger(ts);
                break;
            case Lexer::T_BOOLEAN:
                let value = (ts->getValue() == "true") ? true : false;
                break;
            case Lexer::T_FLOAT:
                let value = this->parseFloat(ts);
                break;       
            case Lexer::T_DATE_TIME:
                let value = this->parseDatetime(ts);
                break;
            default:
                this->syntaxError("Value type expected",ts->getToken());
                break;
        }
        this->popExpSet();
        //echo "Value (" . tokenId . ") = " . value . PHP_EOL;
        return value;
        
    }

    static private function valueWrap(string! s) ->string {
        return ". Value { " . s . " }.";
    }

    /**
     * A call to expected regular expression failed,
     * so find out what was there by using a more general 
     * expression of space / something on rest of line
     * @param string $msg
     */
    private function regexError(string! msg) ->void {
        var ts, value;
        let ts = this->_ts;
        
        let msg = msg . " on line " . ts->getLine();
        if ts->moveRegex("/^(\\s*\\V*)/") {
            let value = ts->getValue();
            throw new XArrayable(msg  . self::valueWrap(value));
        }
        else {
            int tokenId;
            string name;

            let tokenId = (int) ts->moveNextId();
            let value = ts->getValue();
            let name = (string) Lexer::tokenName(tokenId);
            throw new XArrayable(msg . ". Got " . name . self::valueWrap(value));
        }
    }

    private function parseKeyValue(<TokenStream> ts, bool! isFromInlineTable = false) -> int
    {
    	var keyName, value, token;
    	int tokenId;

        let keyName = this->parseKeyName(ts);
        //echo "parseKeyName " . keyName . PHP_EOL;
        
        //if (this->useKeyStore) {
        //    this->mustBeUnique(this->currentKeyPrefix . $keyName);
        //} else {
        if (this->_table->offsetExists(keyName)) {
            this->syntaxError("Duplicate key", ts->getToken());
        }
        //}

        if ts->moveRegex("/^(\\s*=\\s*)/") === false {
            // nothing moved what is actually there?
            this->regexError("Expected T_EQUAL (=)");
        }
        // E_SCALER has a lot of regular expressions in fixed order.
        // Predict a smaller set to use, in micro - management style.
        let token = ts->peekToken();
        let tokenId = (int) token->id;
        if tokenId == Lexer::T_LEFT_SQUARE_BRACE {
            ts->acceptToken();
        	let value = this->parseArray(ts);
            this->_table->offsetSet(keyName, value);
        } 
        elseif tokenId == Lexer::T_LEFT_CURLY_BRACE {
            ts->acceptToken();
            this->parseInlineTable(ts, keyName);
        } 
        else {
            let value = this->getSimpleValue(tokenId);
            this->_table->offsetSet(keyName, value);
        }
        
        if !isFromInlineTable {
            let tokenId = (int) this->finishLine(ts);
        } else {
            let tokenId = (int)  ts->moveNextId(); // clear value parse ends
           
        }
         return tokenId;
    }

    /**
    * Return a value
    */
    private function parseKeyName(<TokenStream> ts) -> var
    {
    	int tokenId;
    	var value;

        let tokenId = (int) ts->getTokenId();
        switch (tokenId) {
            case Lexer::T_UNQUOTED_KEY:
                let value = ts->getValue();
                break;
            case Lexer::T_QUOTATION_MARK:
                let value = this->parseEscapeString(ts);
                break;
            case Lexer::T_APOSTROPHE:
                let value = this->parseLiteralString(ts);
                break;
            case Lexer::T_INTEGER :
                let value = this->parseInteger(ts);
                break;
            default:
                this->syntaxError("Improper key", ts->getToken());
                break;
        }
        return value;
    }


    private function parseInteger(<TokenStream> ts) -> int
    {
        var value;
        let value = ts->getValue();

        if (preg_match("/([^\\d]_[^\\d])|(_$)/", value)) {
            this->syntaxError(
               "Invalid integer number: underscore must be surrounded by at least one digit", ts->getToken()
            );
        }

        let value = str_replace("_", "", value);

        if (preg_match("/^0\\d+/", value)) {
            this->syntaxError(
                    "Invalid integer number: leading zeros are not allowed", ts->getToken()
            );
        }

        return intval(value);
    }

    private function parseFloat(<TokenStream> ts) -> float
    {
    	var value;
        let value = ts->getValue();

        if (preg_match("/([^\\d]_[^\\d])|_[eE]|[eE]_|(_$)/", value)) {
            this->syntaxError(
                    "Invalid float number: underscore must be surrounded by at least one digit", $ts->getToken()
            );
        }

        let value = str_replace("_", "", value);

        if (preg_match("/^0\\d+/", $value)) {
            this->syntaxError(
                    "Invalid float number: leading zeros are not allowed", ts->getToken()
            );
        }

        return floatval(value);
    }

    /**
     * @param TokenStream $ts
     * @param type $stripQuote
     * @return string
     */
    private function parseEscapeString(<TokenStream> ts) -> string
    {
        this->pushExpSet(Parser::E_BSTRING);
        
        int tokenId;
        string value;
        var result;

        let result = "";
        let tokenId = (int) ts->moveNextId();
        while (tokenId != Lexer::T_QUOTATION_MARK) {
        	
            if ((tokenId == Lexer::T_NEWLINE) || (tokenId == Lexer::T_EOS) || (tokenId
                    == Lexer::T_ESCAPE)) {
                // throws
                this->syntaxError("Unfinished string value", ts->getToken());
            } elseif (tokenId == Lexer::T_ESCAPED_CHARACTER) {
                let value = (string) this->parseEscapedCharacter(ts);
            } else {
                let value = (string)ts->getValue();
            }
            let result = result . value;
            let tokenId = (int) ts->moveNextId();
        }
        this->popExpSet();
        return result;
    }

    private function parseMLEscapeString(<TokenStream> ts) -> string
    {
        // TODO: inline assert can be dropped in final version
        int tokenId;
        boolean doLoop;
        string result;

        this->pushExpSet(Parser::E_BSTRING);

        
        let result = "";
        let tokenId = (int) ts->moveNextId();
        if (tokenId == Lexer::T_NEWLINE) {
            let tokenId = (int) ts->moveNextId();
        }
        let doLoop = true;
        while (doLoop) {
            switch (tokenId) {
                case Lexer::T_3_QUOTATION_MARK :
                    
                    let doLoop = false;
                    break;
                case Lexer::T_EOS:
                    this->throwTokenError(ts->getToken(), Lexer::T_3_QUOTATION_MARK);
                    break;
                case Lexer::T_ESCAPE:
                    do {
                       let  tokenId = (int) ts->moveNextId();
                    } while ((tokenId == Lexer::T_SPACE) || (tokenId == Lexer::T_NEWLINE) 
                    	|| (tokenId == Lexer::T_ESCAPE));
                    break;
                case Lexer::T_SPACE:
                    let result = result . " "; // reduce to single space
                    let tokenId = (int) ts->moveNextId();
                    break;
                case Lexer::T_NEWLINE:
                    let result = result . "\n";
                    let tokenId = (int) ts->moveNextId();
                    break;
                case Lexer::T_ESCAPED_CHARACTER:
                    let result = result . this->parseEscapedCharacter(ts);
                    let tokenId = (int) ts->moveNextId();
                    break;
                default:
                    let result = result . ts->getValue();
                    let tokenId = (int) ts->moveNextId();
                    break;
            }
        }
        this->popExpSet();
        return result;
    }

    /**
     * 
     * @param TokenStream $ts
     * @param bool $stripQuote
     * @return string
     */
    private function parseLiteralString(<TokenStream> ts) -> string
    {
    	int id;
    	string result;
        var token;

        let token = ts->peekToken();
        let id = (int) token->id;
        let result = "";
        while (id !== Lexer::T_APOSTROPHE) {
            if ((id === Lexer::T_NEWLINE) || (id === Lexer::T_EOS)) {
                this->syntaxError("Incomplete literal string", ts->getToken());
            }
            if (ts->moveRegex("/([^\\x{0}-\\x{19}\\x{27}]+)/u")) {
                let result = result . (string) ts->getValue();
                let token = ts->peekToken();
                let id = (int) token->id;
            }
            else {
                this->syntaxError("Bad literal string value", token);
            }
        }
        ts->acceptToken();
        return result;
    }

    private function parseMLString(<TokenStream> ts) -> string
    {
    	int tokenId;
    	string result;
        boolean doLoop;

        this->pushExpSet(Parser::E_MLSTRING);
        let result = "";

        let tokenId = (int) ts->moveNextId();
        if (tokenId == Lexer::T_NEWLINE) {
            let tokenId = (int) ts->moveNextId();
        }

        let doLoop = true;
        while (doLoop) {
            switch(tokenId) {
                case Lexer::T_NEWLINE:
                    let result = result . "\n";
                    let tokenId = (int) ts->moveNextId();
                    break;
                case Lexer::T_3_APOSTROPHE:
                    let doLoop = false;
                    break;  
                case Lexer::T_EOS:
                    this->syntaxError("Expected token { ''' }", ts->getToken());
                    break;
                default:
                    let result = result . (string) ts->getValue();
                    let tokenId = (int) ts->moveNextId();
                    //echo "ML String " . result . " Next: " . tokenId . PHP_EOL;
                    break;
            }

        }
        this->popExpSet();
        return result;
    }

    private function parseEscapedCharacter(<TokenStream> ts) -> string
    {
    	string result, value;
        var matches;
    	int ct;
        let value = (string) ts->getValue();
        //echo "Escaped " . value . PHP_EOL;
        let ct = value->length();

        if (ct == 1) {

        	switch(value) {
        		case "n":
        			let result = "\n";
                    break;
        		case "t":
        			let result = "\t";
                    break;
        		case "r":
        			let result = "\r";
                    break;
    			case "b":
    				let result = (string) chr(8);
                    break;
				case "f": 
					let result = (string) chr(12);
                    break;
    			case "\\":
    				let result = "\\";
                    break;
    			case "\"":
    				let result = "\"";
    			    break;
                default:
                    throw new XArrayable("Invalid escape line " . ts->getLine() . " \\" . value);
    		}
        }
    	elseif ct == 5 {
            let result = (string) json_decode("\"\\" . value . "\"");
            //echo "JSON-5 " . value . " is " . result . PHP_EOL;
        }
        else {
            let matches = null;
            //echo "U match " . value . PHP_EOL;
            if (preg_match("/U([0-9a-fA-F]{4})([0-9a-fA-F]{4})/", value, matches)) {
                let result = (string) json_decode("\"\\u" . matches[1] . "\\u" . matches[2] . "\"");
            }
            else {
                throw new XArrayable("Fail unicode match " . ts->getLine() . " \\" . value);
            }
            //echo "JSON-7 " . value . " is " . result . PHP_EOL;
        }
        //echo "Escape result = " . result . PHP_EOL;
        return result;
    }

    private function parseDatetime(<TokenStream> ts) -> <Datetime>
    {
        var date;
        let date = ts->getValue();
        return new \Datetime(date);
    }

    /**
     * Recursive call of itself.
     * @param \Toml\TokenStream $ts
     * @return ValueList
     */
    private function parseArray(<TokenStream> ts) -> <ValueList>
    {
        var token;
        var value;
        var result, e;
        int rct, id;
        boolean doLoop, gotComma;
        // Assert called here because a '[' was parsed
        let result = new ValueList();
        

        let doLoop = true;
        let token =  ts->peekToken();
        let id = (int) token->id;
        while(doLoop) {
            switch(id) {
                case Lexer::T_SPACE:
                    // swallow immediate space
                    ts->moveRegex(Parser::IM_SPACE);
                    let token = ts->peekToken();
                    let id = (int) token->id;
                    break; 
                case Lexer::T_NEWLINE:
                    ts->acceptToken();
                    let token = ts->peekToken();
                    let id = (int) token->id;
                    break;
                case Lexer::T_HASH:
                    ts->acceptToken();
                    this->parseComment(ts); 
                    let token = ts->peekToken();
                    let id = (int) token->id;
                    break; 
                case Lexer::T_EOS:
                    ts->acceptToken();
                    throw new XArrayable("Unfinished array");
                 case Lexer::T_RIGHT_SQUARE_BRACE:
                    // empty array
                    ts->acceptToken(); 
                default:
                    let doLoop = false;
                    break;
            }
        }

        //echo "parseArray id " . id . PHP_EOL;
        let rct = 0;
        while (id != Lexer::T_RIGHT_SQUARE_BRACE) {
            if (id == Lexer::T_LEFT_SQUARE_BRACE) {
                ts->acceptToken(); 
                if (result->allowType("object")) {
                    let value = this->parseArray(ts);
                }
                else {
                    throw new XArrayable( "Cannot add array to list of " 
                        . result->getType() . " at line " . ts->getLine());
                }
            } else {
                // Returned value is a singular class instance to pass parameters
                let value = this->getSimpleValue(id);
            }

            try {
	            result->offsetSet(rct, value);
	            let rct = rct + 1;
	        }
	        catch  XArrayable, e {
	        	throw new XArrayable( e->getMessage() . " at line " . ts->getLine());
	        }

            let token = ts->peekToken();
            //echo "parseArray token " . print_r(token, true) . PHP_EOL;
            let id = (int) token->id;
            let gotComma = false;
            let doLoop = true;
            while(doLoop)
            {

                //echo "parseArray switch " . id . PHP_EOL;
                switch(id) {
                    case Lexer::T_SPACE:
                        // swallow immediate space
                        ts->moveRegex(Parser::IM_SPACE);
                        let token = ts->peekToken();
                        let id = (int) token->id;
                        break;
                    case Lexer::T_NEWLINE:
                        ts->acceptToken();
                        let token = ts->peekToken();
                        let id = (int) token->id;
                        break;
                    case Lexer::T_HASH:
                        ts->acceptToken();
                        this->parseComment(ts); 
                        let token = ts->peekToken();
                        let id = (int) token->id;
                        break;
                    case Lexer::T_COMMA:
                        if gotComma {
                            throw new XArrayable("No value between commas");
                        }
                        else {
                            let gotComma = true;
                        }
                        ts->acceptToken();
                        let token = ts->peekToken();
                        let id = (int) token->id;
                        break;
                    case Lexer::T_RIGHT_SQUARE_BRACE:
                        ts->acceptToken();
                    default:
                        let doLoop = false;
                        break;
                } 
            }
        }
        if (id != Lexer::T_RIGHT_SQUARE_BRACE) {
            this->throwTokenError(ts->getToken(), Lexer::T_RIGHT_SQUARE_BRACE);
        }

        return result;
    }

    /**
     * Used by parseInlineTable, to push a new Table as a value
     *  and set current work table to it.
     * @param string $keyName
     */
    private function pushWorkTable(var keyName) -> void
    {
        var work, pushed;
        let work = this->_table;

        if ! work->offsetExists(keyName) {
        	let pushed = new KeyTable();
            work->offsetSet(keyName, pushed);
            let this->_table = pushed;
            return;
        }
        // TODO: Else or Assert??
        let this->_table = work->offsetGet(keyName);
    }

    private function parseInlineTable(<TokenStream> ts, var keyName) -> void
    {
    	int tokenId;
    	var priorTable;
        // Assert called here because parsed a '{'
        this->pushExpSet(Parser::E_KEY); // looking for keys

        let priorTable = this->_table;

        this->pushWorkTable(keyName);

        let tokenId = (int) ts->moveNextId();
        if (tokenId == Lexer::T_SPACE) {
            let tokenId = (int) ts->moveNextId();
        }

        if (tokenId != Lexer::T_RIGHT_CURLY_BRACE) {
            let tokenId = (int) this->parseKeyValue($ts,true);
            if (tokenId == Lexer::T_SPACE) {
                let tokenId = (int) ts->moveNextId();
            }
        }

        while (tokenId == Lexer::T_COMMA) {
            let tokenId = (int) ts->moveNextId();
            if (tokenId == Lexer::T_SPACE) {
                let tokenId = (int) ts->moveNextId();
            }
            let tokenId = (int) this->parseKeyValue($ts, true);
            if (tokenId == Lexer::T_SPACE) {
                let tokenId = (int) ts->moveNextId();
            }
        }
        this->popExpSet();
        if (tokenId != Lexer::T_RIGHT_CURLY_BRACE) {
            this->throwTokenError(ts->getToken(), Lexer::T_RIGHT_CURLY_BRACE);
        }

        /*if (this->useKeyStore) {
            this->currentKeyPrefix = $priorcurrentKeyPrefix;
        }*/

        let this->_table = priorTable;
    }

    /**
     * Nothing more of interest on the line,
     * anything besides a comment is an error
     * Used by parseObjectPath and parseKeyValue
     */
    private function finishLine(<TokenStream> ts) -> int
    {
    	var tokenId;

        ts->moveRegex("/^(\\s*#\\V*|\\s*)/");
        let tokenId = ts->moveNextId(); 
        if (tokenId !== Lexer::T_NEWLINE && tokenId !== Lexer::T_EOS) {
            this->syntaxError("Expected NEWLINE or EOS",ts->getToken());
        }
        return tokenId;
    }

    private function tablePathError(string! msg)
    {
    	string errMsg;
    	//echo "Table path error: " . msg . PHP_EOL;
    	let errMsg = msg . " at line " . this->_ts->getLine();
        throw new XArrayable(errMsg);
    }
    /**
     * From array of Table/TableList generate its key path
     * using the object tags
     * @param array of parts
     * @return string
     */
    private function getPathName(array! parts, bool! withIndex = true) -> string {
        string result, bit;
        var idx, p, tag;

        let result = "";
        for idx, p in parts {
            let tag = p->getTag();
            if tag->objAOT {
                 let bit = "[" . tag->partKey;
                 if (withIndex) {
                     let bit = bit . "/" . p->getEndIndex();
                 }
                 let bit = bit . "]";
            }
            else {
                let bit = "{" . tag->partKey . "}";
            }
            if idx==0 {
                let result = bit;
            }
            else {
                let result = result . bit;
            }
        }
        return result;
    }
    /**
     * Convert the path string, into the array with the path of
     * Table and TableList objects indicated.
     * @param TokenStream $ts
     */
    private function parseObjectPath(<TokenStream> ts) -> void
    {
    	var pobj, testObj, tag;
    	var partKey, path;
    	boolean isAOT, hitNew, doLoop, preMade;
    	int pathLine;
    	int partsCt, i, firstNew;
    	int dotCount;
    	int AOTLength;
    	int tokenId;

    	array parts = [];

        let isAOT = false;
        let hitNew = false;

        let partsCt = 0;
        let AOTLength = 0;
        let dotCount = 0;
        let firstNew = -1;

        let pobj = this->_root;
        let testObj = null;


        let pathLine = (int) ts->getLine();
        let tokenId = (int) ts->getTokenId();

        if (tokenId != Lexer::T_LEFT_SQUARE_BRACE) {
            this->tablePathError("Path start [ expected");
        }
        let tokenId = (int) ts->moveNextId();
        let doLoop = true;
        while (doLoop) {
            switch (tokenId) {
                case Lexer::T_HASH:
                    this->tablePathError("Unexpected '#' in path");
                    break;
                case Lexer::T_EQUAL:
                    this->tablePathError("Unexpected '=' in path");
                    break;
                case Lexer::T_SPACE:
                    let tokenId = (int) ts->moveNextId();
                    break;
                case Lexer::T_EOS:
                	let doLoop = false;
                    break; //2
                case Lexer::T_NEWLINE:
                    this->tablePathError("New line in unfinished path");
                    break;
                case Lexer::T_RIGHT_SQUARE_BRACE:

                    if isAOT {
                        if AOTLength == 0 {
                            this->tablePathError("AOT Segment cannot be empty");
                        }
                        let isAOT = false;
                        let AOTLength = 0;
                        let tokenId = (int) ts->moveNextId();
 
                    } else {
                        //let tokenId = (int) ts->moveNextId();
                        let doLoop = false;

                    }
                    break;
                case Lexer::T_LEFT_SQUARE_BRACE:
                    if (dotCount < 1 && count(parts) > 0) {
                        this->tablePathError("Expected a '.' after path key");
                    }
                    if (isAOT) {
                        // one too many
                        this->tablePathError("Too many consecutive [ in path");
                    }
                    let tokenId = (int) ts->moveNextId();
                    let isAOT = true;

                    break;
                case Lexer::T_DOT:
                    if dotCount == 1 {
                        this->tablePathError("Found '..' in path");
                    }
                    let dotCount = dotCount+1;

                    let tokenId = (int) ts->moveNextId();
                    break;
                case Lexer::T_QUOTATION_MARK:
                default:
                    let partKey = this->parseKeyName(ts);
                    if dotCount < 1 && count(parts) > 0 {
                        this->tablePathError("Expected a '.' after path key");
                    }
                    let dotCount = 0;

                    let testObj = pobj->offsetExists(partKey) ? pobj->offsetGet(partKey) : null;
                    if empty testObj {
                        // create object and tags
                        if !hitNew {
                            let hitNew = true;
                            let firstNew = partsCt;
                        }
                        let tag = new PartTag(partKey, isAOT);
                        if isAOT {
                            let AOTLength = AOTLength + 1; 
                            let testObj = new TableList();
                            // store TableList as part
                            pobj->offsetSet(partKey, testObj);
                            let pobj = testObj->getEndTable();
                        } else {
                            let testObj = new KeyTable();
                            pobj->offsetSet(partKey, testObj);
                            let pobj = testObj;
                        }
                        testObj->setTag(tag);
                    } else {
                        // Must be Arrayable, had all parts so far
                        let preMade = (is_object(testObj) && testObj instanceof \Toml\Arrayable);
                        if !preMade {
                            let path = this->getPathName(parts) . "." . partKey;
                            throw new XArrayable("Duplicate key path: " . path . " line " . pathLine);
                        }
                        let tag = testObj->getTag();
                        let tag->isAOT = isAOT; 
                        // TOM04 allows path inconsistancy, isAOT ?? objAOT 
                        if tag->objAOT { 
                            let AOTLength = AOTLength + 1;
                            let pobj = testObj->getEndTable();
                        } else { // found a Table object
                            let pobj = testObj;
                        }
                    }
                    let parts[] = testObj; // Table or TableList
                    let partsCt = partsCt + 1;
                    let tokenId = (int) ts->moveNextId();
                    break;
            }
        }
        // check the rules
        if (partsCt == 0) {
            this->tablePathError("Table path cannot be empty");
        }
       
        if !hitNew {
            let tag = testObj->getTag();
            if tag->objAOT {
                if tag->isAOT {
                    let pobj = testObj->newTable();
                } else {
                    throw new XArrayable("Table path mismatch with " . this->getPathName(parts,false) . " line " . pathLine);
                }
            } else {
                // terminates in reused table name?
                // OK if end part was implicit              
                if tag->implicit {
                    // last part no longer implicit
                    let tag->implicit = false;
                } else {
                    throw new XArrayable("Duplicate key path: [" . this->getPathName(parts,false) . "] line " . pathLine);
                }
            }
        } else {
            // all the parts from the $firstNew and before the last part
            // were created 'implicitly', so use the tag property to store
            // implicit flag
            // Reuse testObj
            let partsCt = partsCt - 1;
            let i = firstNew;
            while ( i < partsCt ) {
            	let testObj = parts[i];
            	let tag = testObj->getTag();
            	let tag->implicit = true;
            	let i = i + 1;
            }
        }

        let this->_table = pobj;
        //this->currentKeyPrefix = this->getPathName($parts);
    }

    /**
     * @param TokenStream $ts
     * For mixed AOT and table paths, some rules to be followed, or else.
     * For existing paths, a new AOT-T is created if end of path is AOT
     * New path dynamic AOT segments always create an initial AOT-T
     * Existing AOT segments ended with a Table Path are unaltered.
     * 
     * Traverse the path parts and adjust workArray
     * 
     * Would be nice to have a token that says "I am relative" to last path,
     * //TODO: Try relative paths and replacement. Means more tokens to LEXER
     * If first character is a "plus" + , it extends and replaces last path
     * If first character is a "minus" - , it extends last path without replacement
     * 
     */
    private function parseTablePath(<TokenStream> ts) -> int
    {
        //echo "parseTablePath" . PHP_EOL;
        this->parseObjectPath(ts);

        return this->finishLine(ts);
    }

    /** 
    * 
    */
    private function throwTokenError(<Token> token, int! expectedId) -> void
    {
        var tokenName;

        let tokenName = Lexer::tokenName(expectedId);
        this->syntaxError("Expected " . tokenName, token);
    }


    /**
     * Return the next tokenId, after skipping any comments and space
     * @param TokenStream $ts
     */
    private function parseCommentsAndSpace(<TokenStream> ts) -> int
    {
    	int tokenId;
        boolean doLoop;
        let tokenId = (int)ts->getTokenId();
        let doLoop = true;
        while(doLoop) {
            switch(tokenId) {
            case Lexer::T_HASH:
                let tokenId = (int) this->parseComment(ts);
                break;
            case Lexer::T_NEWLINE:
                let tokenId = (int) ts->moveNextId();
                break;
            case Lexer::T_SPACE:
                ts->moveRegex(Parser::IM_SPACE);
                let tokenId = (int) ts->moveNextId();
                break;
            default:
                let doLoop = false;
                break;
            }
        }
        return tokenId;
    }


    private function syntaxError(string! msg, <Token> token) -> void
    {
    	string value;
    	int line;

        let line = token->line;
        let value = token->value;
        let msg = "Error line " . line . ": " . msg;
        if strlen(value) > 0 {
            let msg = msg . self::valueWrap(value);
        }
        else {
            let msg = msg .  ".";
        }
        throw new XArrayable(msg);
    }

}
