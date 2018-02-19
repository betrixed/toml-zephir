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
	    // consts for parser expression tables
    const E_KEY = 0;
    const E_VALUE = 1;
    const E_LSTRING = 2;
    const E_BSTRING = 3;
    const E_ALL = 4;

    // Waiting for a test case that shows $useKeyStore is needed
    //private useKeyStore = false;
    //private keys = []; //usage controlled by $useKeyStore
    //private currentKeyPrefix = ''; //usage controlled by $useKeyStore

    private _root = null; // root Table object
    private _table = null; // dyanamic reference to current Table object
// For regex table stack
    private _ts = null;
     // Current regex table type
    private _expSetId = -1;
    // Stack of regex types.
    private _expStack;
    private _stackTop;

    
    // Regular expressions, as class constants
    static private _keyRegex;  
    static private _valRegex;
    static private _regBasic;
    static private _regLiteral;

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
                    let result = Lexer::getExpSet(Lexer::BriefList);
                    let self::_keyRegex = result;
                }
                break;
            case Parser::E_BSTRING:
                let result = self::_regBasic;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::BasicStringList);
                    let self::_regBasic = result;
                }
                break;
            case Parser::E_LSTRING:
                let result = self::_regLiteral;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::LiteralStringList);
                    let self::_regLiteral = result;
                }
                break;
            case Parser::E_VALUE:
                let result = self::_valRegex;
                if empty result {
                    let result = Lexer::getExpSet(Lexer::FullList);
                    let self::_valRegex = result;
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
        let this->_expSetId = value;
        switch (value) {
            case Parser::E_KEY:
                this->_ts->setExpList(Parser::_keyRegex);
                break;
            case Parser::E_BSTRING:
                this->_ts->setExpList(Parser::_regBasic);
                break;
            case Parser::E_LSTRING:
                this->_ts->setExpList(Parser::_regLiteral);
                break;
            case Parser::E_VALUE:
            default:
                this->_ts->setExpList(Parser::_valRegex);
                break;
        }
    }

    /*
      public function setupTokenize() {
      this->regex = & Lexer::$Regex;
      this->token = new Token();
      }
     * 
     */

    /**
     * Everything that must be setup before calling setInput
     */
    public function __construct()
    {
    	var ts;

        let this->_root = new KeyTable();
        let this->_table = this->_root;
        let this->_expStack = new \SplFixedArray();
        let this->_stackTop = 0;
        let Parser::_keyRegex = this->getExpSet(Parser::E_KEY);
        let Parser::_valRegex = this->getExpSet(Parser::E_VALUE);
        let Parser::_regBasic = this->getExpSet(Parser::E_BSTRING);
        let Parser::_regLiteral = this->getExpSet(Parser::E_LSTRING);

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

        var toml, parser, result;

        let toml = file_get_contents(path);

        // Remove BOM if present
        let toml = preg_replace("/^" . pack("H*", "EFBBBF") . "/", "", toml);

        let parser = new Parser();
        let result = parser->parse(toml);
        return result;
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
    */

    public function parse(var input) -> array
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
        
        let tokenId = (int) ts->moveNextId();

        while (tokenId != Lexer::T_EOS) {
            //$tokenName = Lexer::tokenName($tokenId)
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
                    this->unexpectedTokenError(ts->getToken(), "Expect Key = , [Path] or # Comment" );
                    break;
            }
        }
    }

    public function hitGetTokenId() -> var 
    {
        return this->_ts->getTokenId();
    }

    /** 
     * Skip comment, and return next none-comment token or NEWLINE or EOS
     *  
     */
    private function parseComment(<TokenStream> ts) -> int
    {
        int tokenId;
        let tokenId = (int) ts->getTokenId();
        if tokenId != Lexer::T_HASH {
            this->throwTokenError(ts->getToken(), tokenId);
        }
        // parsing a comment so use basic string expression set
        this->pushExpSet(Parser::E_BSTRING);
        while (true) {
            let tokenId = (int) ts->moveNextId();
            if (tokenId == Lexer::T_NEWLINE) || (tokenId == Lexer::T_EOS) {
                break;
            }
        }
        this->popExpSet();
        return tokenId;
    }

    /**
     * Move off T_SPACE token to next
     * @param TokenStream $ts
     * @return int
     */
    private function skipSpace(<TokenStream> ts) -> int
    {
    	int tokenId;
        let tokenId = (int) ts->getTokenId();
        if (tokenId == Lexer::T_SPACE) {
            let tokenId = (int) ts->moveNextId();
        }
        return tokenId;
    }

    private function parseKeyValue(<TokenStream> ts, bool! isFromInlineTable = false) -> int
    {
    	var keyName, value;
    	int tokenId;

        let keyName = this->parseKeyName(ts);
        //echo "KeyName = " . keyName . PHP_EOL;
        
        //if (this->useKeyStore) {
        //    this->mustBeUnique(this->currentKeyPrefix . $keyName);
        //} else {
        if (this->_table->offsetExists(keyName)) {
            this->errorUniqueKey(keyName);
        }
        //}

        // get next none-space token
        let tokenId = (int) ts->moveNextId();
        if tokenId == Lexer::T_SPACE {
            let tokenId = (int) ts->moveNextId();
        }
        if tokenId != Lexer::T_EQUAL {
            this->throwTokenError(ts->getToken(), Lexer::T_EQUAL);
        }
        this->pushExpSet(Parser::E_VALUE);
        
        let tokenId = (int)  ts->moveNextId();//clear EQUAL
        if tokenId == Lexer::T_SPACE {
            let tokenId = (int)  ts->moveNextId();
        }

        if tokenId == Lexer::T_LEFT_SQUARE_BRACE {
        	let value = this->parseArray(ts);
            this->_table->offsetSet(keyName, value);
        } 
        elseif tokenId == Lexer::T_LEFT_CURLY_BRACE {
            this->parseInlineTable(ts, keyName);
        } 
        else {
            let value = this->parseSimpleValue(ts);
            this->_table->offsetSet(keyName, value);
        }
        this->popExpSet();
        let tokenId = (int)  ts->moveNextId(); // clear value parse ends
        if !isFromInlineTable {
            return this->finishLine(ts);
        } else {
            return tokenId;
        }
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
                let value = this->parseBasicString(ts);
                break;
            case Lexer::T_APOSTROPHE:
                let value = this->parseLiteralString(ts);
                break;
            case Lexer::T_INTEGER :
                let value = this->parseInteger(ts);
                break;
            default:
                this->unexpectedTokenError(ts->getToken(), "Improper key");
                break;
        }
        return value;
    }

    /**
     * @return object An object with two public properties: value and type.
     * Returned object must be cloned to keep values of returned instance.
     */
    private function parseSimpleValue(<TokenStream> ts) -> var
    {
        // reuse same instance
        int tokenId;
        var value;

        let tokenId = (int) ts->getTokenId();
        
        switch (tokenId) {
            case Lexer::T_BOOLEAN:
                let value = this->parseBoolean(ts);
                break;
            case Lexer::T_INTEGER:
                let value = this->parseInteger(ts);
                 break;
            case Lexer::T_FLOAT:
                let value = this->parseFloat(ts);
                 break;
            case Lexer::T_QUOTATION_MARK:
                let value = this->parseBasicString(ts);
                 break;
            case Lexer::T_3_QUOTATION_MARK:
                let value = this->parseMultilineBasicString(ts);
                 break;
            case Lexer::T_APOSTROPHE:
                let value = this->parseLiteralString(ts);
                 break;
            case Lexer::T_3_APOSTROPHE:
                let value = this->parseMultilineLiteralString(ts);
                 break;
            case Lexer::T_DATE_TIME:
                let value = this->parseDatetime(ts);
                 break;
            default:
                this->unexpectedTokenError(ts->getToken(), "Value expected: boolean, integer, string or datetime");
                break;
        }
        return value;
    }

    private function parseBoolean(<TokenStream> ts) -> bool
    {
    	var result;
    	let result = ts->getValue() == "true" ? true : false;
        return result;
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
                    "Invalid integer number: leading zeros are not allowed.", ts->getToken()
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

    /** In path parsing, we may want to keep quotes, because they can be used
     *  to enclose a '.' as a none separator. 
     * @param TokenStream $ts
     * @param type $stripQuote
     * @return string
     */
    private function parseBasicString(<TokenStream> ts) -> string
    {
        this->pushExpSet(Parser::E_BSTRING);
        
        int tokenId;
        string value;
        var result = "";

        let tokenId = (int) ts->getTokenId();
        if (tokenId != Lexer::T_QUOTATION_MARK) {
            this->throwTokenError(ts->getToken(), Lexer::T_QUOTATION_MARK);
        }

        let tokenId = (int) ts->moveNextId();
        while (tokenId != Lexer::T_QUOTATION_MARK) {
        	
            if ((tokenId == Lexer::T_NEWLINE) || (tokenId == Lexer::T_EOS) || (tokenId
                    == Lexer::T_ESCAPE)) {
                // throws
                this->unexpectedTokenError(ts->getToken(), "This character is not valid");
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

    private function parseMultilineBasicString(<TokenStream> ts) -> string
    {
        // TODO: inline assert can be dropped in final version
        int tokenId;
        boolean doLoop;
        string result;

        let tokenId = (int) ts->getTokenId();
        if tokenId != Lexer::T_3_QUOTATION_MARK {
            this->throwTokenError(ts->getToken(), Lexer::T_3_QUOTATION_MARK);
        }
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
                    this->popExpSet();
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
    	int tokenId;
    	string result;

    	let tokenId = (int) ts->getTokenId();
        if tokenId != Lexer::T_APOSTROPHE {
            this->throwTokenError(ts->getToken(), Lexer::T_APOSTROPHE);
        }

        this->pushExpSet(Parser::E_LSTRING);

        let tokenId = (int) ts->moveNextId();

        let result = "";
        while (tokenId != Lexer::T_APOSTROPHE) {
            if ((tokenId == Lexer::T_NEWLINE) || (tokenId == Lexer::T_EOS)) {
                this->unexpectedTokenError(ts->getToken(), "This character is not valid.");
            }
            let result = result . (string) ts->getValue();
            let tokenId =  (int) ts->moveNextId();
        }
        this->popExpSet();
        return result;
    }

    private function parseMultilineLiteralString(<TokenStream> ts) -> string
    {
    	int tokenId;
    	string result;

    	let tokenId = (int) ts->getTokenId();
        if (tokenId != Lexer::T_3_APOSTROPHE) {
            this->throwTokenError(ts->getToken(), Lexer::T_3_APOSTROPHE);
        }
        this->pushExpSet(Parser::E_LSTRING);

        let result = "";

        let tokenId = (int) ts->moveNextId();
        if (tokenId == Lexer::T_NEWLINE) {
            let tokenId = (int) ts->moveNextId();
        }

        while (true) {

            if (tokenId == Lexer::T_3_APOSTROPHE) {
                break;
            }
            if (tokenId == Lexer::T_EOS) {
                this->unexpectedTokenError(ts->getToken(), "Expected token T_3_APOSTROPHE");
            }
            let result = result . (string) ts->getValue();
            let tokenId = (int) ts->moveNextId();
        }
        this->popExpSet();

        if (tokenId != Lexer::T_3_APOSTROPHE) {
            this->throwTokenError(ts->getToken(), Lexer::T_3_APOSTROPHE);
        }

        return result;
    }

    private function parseEscapedCharacter(<TokenStream> ts) -> string
    {
    	string value;
    	int ct;
        let value = (string) ts->getValue();
        
        let ct = value->length();

        if (ct == 2) {
        	string c1;
        	let c1 = (string) substr(value,1,1);

        	switch(c1) {
        		case "n":
        			return "\n";
        		case "t":
        			return "\t";
        		case "r":
        			return "\r";
    			case "b":
    				return "\b";
				case "f": 
					return chr(12);
    			case "\\":
    				return  "\\";
    			case "\"":
    				return "\"";
    			default:
    			break;
    		}
        }
    	
       

        if ct == 6 {
        	//echo "Length 6" . PHP_EOL;
            return json_decode("\"" . value . "\"");
        }

        var matches;
        //echo "U match " . value . PHP_EOL;
        preg_match("/\\\\U([0-9a-fA-F]{4})([0-9a-fA-F]{4})/", value, matches);

        return json_decode("\"\\u" . matches[1] . "\\u" . matches[2] . "\"");
    }

    private function parseDatetime(<TokenStream> ts) -> <Datetime>
    {
        var date;
        let date = ts->getValue();
        return new \Datetime(date);
    }

    /**
     * Recursive call of itself.
     * @param \Tomlmfony\Toml\TokenStream $ts
     * @return array
     */
    private function parseArray(<TokenStream> ts) -> <ValueList>
    {
        int tokenId, rct;
        var value;
        var result, e;

        let tokenId = (int) ts->getTokenId();
        if (tokenId != Lexer::T_LEFT_SQUARE_BRACE) {
            this->throwTokenError(ts->getToken(), Lexer::T_LEFT_SQUARE_BRACE);
        }
        let result = new ValueList();
        let tokenId = (int) ts->moveNextId();
        while (tokenId == Lexer::T_SPACE || tokenId == Lexer::T_NEWLINE) {
            let tokenId = (int) ts->moveNextId();
        }
        if (tokenId == Lexer::T_HASH) {
            let tokenId = (int) this->parseCommentsAndSpace(ts);
        }
            
        let rct = 0;
        while (tokenId != Lexer::T_RIGHT_SQUARE_BRACE) {
            if (tokenId == Lexer::T_LEFT_SQUARE_BRACE) {
                let value = this->parseArray(ts);
            } else {
                // Returned value is a singular class instance to pass parameters
                let value = this->parseSimpleValue(ts);
            }

            try {
	            result->offsetSet(rct, value);
	            let rct = rct + 1;
	        }
	        catch  XArrayable, e {
	        	throw new XArrayable( e->getMessage() . " at line " . ts->getLine());
	        }

            let tokenId = (int) ts->moveNextId();
            while (tokenId === Lexer::T_SPACE || tokenId === Lexer::T_NEWLINE) {
                let tokenId = (int)ts->moveNextId();
            }

             if (tokenId == Lexer::T_HASH) {
                let tokenId = (int)this->parseCommentsAndSpace(ts);
            }
            
            if (tokenId == Lexer::T_COMMA) {
                //easy, to another value
                let tokenId = (int)ts->moveNextId();
            }
            elseif (tokenId != Lexer::T_RIGHT_SQUARE_BRACE) {
                // should be finished
                this->unexpectedTokenError(ts->getToken(),"Expect '.' or ']' after array item");
            }

            while (tokenId == Lexer::T_SPACE || tokenId == Lexer::T_NEWLINE) {
                let tokenId = (int)ts->moveNextId();
            }

            if (tokenId == Lexer::T_HASH) {
                let tokenId = (int)this->parseCommentsAndSpace(ts);
            }
        }
        if (tokenId != Lexer::T_RIGHT_SQUARE_BRACE) {
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
        }
        // TODO: Else or Assert??
        let this->_table = work->offsetGet(keyName);
    }

    private function parseInlineTable(<TokenStream> ts, var keyName) -> void
    {
    	int tokenId;
    	var priorTable;

    	let tokenId = (int) ts->getTokenId();
        if (tokenId != Lexer::T_LEFT_CURLY_BRACE) {
            this->throwTokenError(ts->getToken(), Lexer::T_LEFT_CURLY_BRACE);
        }
        this->pushExpSet(Parser::E_KEY); // looking for keys

        let priorTable = this->_table;

        this->pushWorkTable(keyName);

        /*if (this->useKeyStore) {
            $priorcurrentKeyPrefix = this->currentKeyPrefix;
            this->currentKeyPrefix = this->currentKeyPrefix . $keyName . ".";
        }*/

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

        let tokenId = ts->getTokenId();
        if (tokenId === Lexer::T_SPACE) {
            let tokenId = ts->moveNextId();
        }
        if (tokenId === Lexer::T_HASH) {
            let tokenId = this->parseComment($ts);
        }
        if (tokenId !== Lexer::T_NEWLINE && tokenId !== Lexer::T_EOS) {
            this->unexpectedTokenError(ts->getToken(), "Expected T_NEWLINE or T_EOS.");
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
                        let tokenId = (int) ts->moveNextId();
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
        this->unexpectedTokenError(token, "Expected " . tokenName);
    }


    /**
     * Return the next tokenId, after skipping any comments and space
     * @param TokenStream $ts
     */
    private function parseCommentsAndSpace(<TokenStream> ts) -> int
    {
    	int tokenId;
        let tokenId = (int)ts->getTokenId();
        if (tokenId == Lexer::T_HASH) {
            let tokenId = (int)this->parseComment(ts);
        }
        while (tokenId == Lexer::T_NEWLINE) {
            let tokenId = (int)ts->moveNextId();
            if (tokenId == Lexer::T_SPACE) {
                let tokenId = (int)ts->moveNextId();
            }
            if (tokenId == Lexer::T_HASH) {
                let tokenId = (int)this->parseComment(ts);
            }
        }
        return tokenId;
    }

    private function errorUniqueKey(string! keyName)
    {
        this->syntaxError(sprintf(
                        "The key { %s } has already been defined previously.", keyName
        ));
    }



    private function unexpectedTokenError(<Token> token, string expectedMsg = null) -> void
    {
    	string name, value, msg;
    	int line;

        let name = (string) Lexer::tokenName(token->id);
        let line = token->line;
        let value = token->value;

        let msg = (string) sprintf("Syntax error: unexpected token %s at line %s", name, line);
        //echo "Test Message " . msg . PHP_EOL;
        if !token->isSingle {
            let msg = msg . " value { '" . value . "' }. ";
        } else {
            let msg = msg .  ".";
        }
        if !empty expectedMsg {
             let msg = msg .  " " . expectedMsg;
        }

        throw new XArrayable(msg);
    }

    private function syntaxError(string! msg, <Token> token = null) -> void
    {
    	string name, value, tokenMsg;
    	int line;

        if !empty(token) {
            let name = (string) Lexer::tokenName(token->id);
            let line = token->line;
            let value = token->value;
            let tokenMsg = (string) sprintf(" Token: %s line: %s", name, line);
            if !token->isSingle {
                let tokenMsg = tokenMsg . " value { '" . value . "' }.";
            } else {
                let tokenMsg = tokenMsg . ".";
            }
            let msg  = msg . tokenMsg;
        }
        throw new XArrayable(msg);
    }

}
