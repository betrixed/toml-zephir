namespace Toml;

class TokenStream
{
    protected _lines; // all lines
    protected _lineCount;
    
    protected _curLine;
    protected _id;
    protected _value;
    protected _lineNo;    // line number of curLine
    protected _tokenLine;  // line number of current token
    protected _isSingle; // was found in single character list

    protected _offset; // unparsed offset on current line
    protected _regex; // Object of type KeyTable to current set of tokens being searched for
    protected _singles; // Reference to single character lookup for tokenId
    protected _unknownId; // int value to represent single character not in singles.
    protected _newLineId; //
    protected _eosId;

    protected _token;  // The one and only token instance
    // topLevel parse
    
    
    public function __construct() {
        let this->_token = new Token();
    }
    public function setEOSId(int! id) {
        let this->_eosId = id;
    }    
    public function setNewLineId(int! id) {
        let this->_newLineId = $id;
    }
    public function setUnknownId(int! id)
    {
        let this->_unknownId = $id;
    }

   /**
     * Return current expression set object
     */
    public function getExpSet() -> var {
        return this->_regex;
    }
    /**
     * Argument is reference to associative array[int] of string regular expressions
     * @param array $ref
     */
    public function setExpSet(var obj) -> void {
        let this->_regex = obj;
    }
    /** 
     * For lookup of tokenId of single character string
     * Argument is reference to associative array[string] of int 
     * @param array $ref
     */
    
    public function setSingles(var ref) -> void {
        let this->_singles = ref;
    }

     public function setInput(string! input) -> void
     {
     	var boxme;

     	let boxme = new Box(explode("\n", input));

        this->setLines(boxme);
     }

            
    public function getLine() -> int {
        return this->_tokenLine;
    }      
    
    public function hasPendingTokens() -> bool {
        return (this->_id != this->_eosId);
    }

     /**
     * Get all token details of parse step
     * @return \Yosy\Token
     */
    public function getToken() -> var
    {
        var token;
        let token = this->_token;
        token->set( this->_value, this->_id, this->_tokenLine, this->_isSingle);
        return token;
    }

    /**
     * Return the current token value, do next parse step
     * @return string
     */
    public function getValue() -> string {
        return this->_value;
    }
    
    /**
     * Fetch the internal token id without advancing parse
     */
    public function getTokenId() -> int {
        return this->_id;
    }

    /** 
      * This sets the parse state to before the first line.
      * To get the first token, call moveNextId
      */
    public function setLines(var boxed) -> void {
        var ct;
        let ct = count(boxed->_me);
        let this->_lines = boxed;
        let this->_lineNo = 0;
        let this->_offset = 0;
        let this->_lineCount = ct;
        let this->_curLine = (ct > 0) ? boxed->_me[0] : null;
    }
/** Return the single character at the front of the parse. 
     *  Does not alter this objects internal state values,
     *  except for properties of Token, which must be treated as read-only. 
     *  Maybe can use this to 'predict' the next expression set to use.
     *  Return "value" and single character TokenId in the Token.
     *  Cannot return tokenId for multi-character regular expressions,
     *  which is the whole idea.
     */
    public function peekToken() -> <Token> {
        // Put next characters in $test, not altering TokenStream state.
        var test;
        var token;
        int nextLine;

        let test = this->_curLine;
        let token = this->_token;
        if empty test {
            let nextLine = (int) this->_lineNo + 1;
            let token->line = nextLine;
            let token->isSingle = true;
            if nextLine < this->_lineCount {
                let token->value = "";
                let token->id = this->_newLineId;  
            }
            else {
                let token->value = "";
                let token->id = this->_eosId;
            }
            return token;
        }
        var uni;

        let uni = mb_substr(test, 0, 1); // possible to be multi-byte character
        let token->value = uni;
        let token->line = this->_tokenLine;
        if !this->_singles->offsetExists(uni) {
            let token->id = this->_unknownId;
            let token->_isSingle = false;
        }
        else {
            let token->id = (int) this->_singles->offsetGet(uni);
            let token->_isSingle = true;
        }
        return  token;
    }
/**
     * If a peekNextChar has been done, this uses internal Token values to 
     * advance the parse (namely the string length of the value),
     * on the current line. It is important that token values have not been altered,
     * and parse position has not been altered prior to calling this method.
     * 
     * A call to getToken, will still return same values as the Token;
     */
    public function acceptToken() -> void {
        var token;

        let token = this->_token;
        if token->id === this->_eosId {
            let this->_value = "";
            let this->_id = this->_eosId;
            return;
        }
        elseif token->id === this->_newLineId {
            int nextLine;
            // do the next line
            let nextLine = (int) this->_lineNo + 1;
            let this->_curLine = this->_lines->_me[nextLine];
            let this->_offset = 0;
            let this->_value = "";
            let this->_id = this->_newLineId;
            let this->_lineNo = nextLine;
            return;
        }
        elseif this->_offset === 0 {
            let this->_tokenLine = this->_lineNo + 1;
        }
        int takeoff;

        let takeoff = (int) strlen(token->value);
        let this->_curLine = substr(this->_curLine, takeoff);
        let this->_offset =  this->_offset + takeoff;
        let this->_id = token->id;
        let this->_isSingle = token->isSingle;
        let this->_value = token->value;
        return;
    }
    /**
     * Try regular expression, and return capture, if any.
     * Assumes previous peekToken returned a known token.
     * Leaves tokenId as unknownId.
     * 
     * @param string $pattern 
     * @return boolean , true if match found
     * Pattern must be such that preg_match can return match
     *  array with 2 items.
     *  If returns true, then getValue() returns the capture.
     */
    public function moveRegex(string! pattern) -> boolean {
        var test;
        int takeOff;
        var matches;
        let test = this->_curLine;
        let matches = null;
        if (preg_match(pattern, test, matches)) {
            let this->_value = matches[1];
            let this->_isSingle = false;
            let this->_id = this->_unknownId;
            let takeOff = strlen(matches[0]);
            let this->_offset = this->_offset + takeOff;
            let this->_curLine = substr(test, takeOff);
            return true;
        }   
        return false;
    }

/** 
     * Advance the parse then return the internal token id.
     */
    public function moveNextId() -> int
    {
        return this->parseNextId(this->_regex);
    }
    

        /**
     * Set up the internal current token values, from the current parse
     * position in the line, and move the parse position to the next. Return
     * a token id.
     * Returned token id may be a NEWLINE or EOS, before the
     * $patterns are checked. If neither NEWLINE, EOS, or any of the 
     * $patterns match, the next unicode character is checked against the
     * assigned Singles table, and its token id is returned, or else
     * the character value is assigned the UnknownId
     * @param \Yosy\KeyTable $patterns
     * @return int
     */
    
    private function parseNextId(var patterns) -> int {
        var id, pattern;
        
        int takeoff;
        int nextLine;
        int tid;
        var uni;
        var test;

        if (empty(this->_curLine)) {
            let nextLine = this->_lineNo + 1;
            if (nextLine < this->_lineCount) {
               let this->_curLine = this->_lines->_me[nextLine];
               let this->_offset = 0;
               let this->_value = "\n";
               let this->_id = this->_newLineId;
               let this->_lineNo = nextLine;
            }
            else {
               let this->_value = "";
               let this->_id = this->_eosId;
            }
            let this->_isSingle = true; // not unknownId single
            return this->_id;
        }
        elseif (this->_offset == 0) {
            let this->_tokenLine = this->_lineNo + 1;
        }

        let test = this->_curLine;
        let this->_curLine = null;
        
        for id, pattern in this->_regex->_store {
            var matches = null; // !! Here stops memory leak !!
            if (preg_match(pattern, test, matches)) {
                let this->_value = matches[1];
                let this->_id = id;
                let this->_isSingle = false;
                let this->_line = this->_tokenLine;
                
                let takeoff = (int) strlen(matches[0]);
                let this->_offset += takeoff;

                let this->_curLine = substr(test, takeoff);
                //let matches = null;
                return this->_id;
            }
        }
        
        // no expressions matched, as a default, classify unicode character
        // get next unicode character using mb_substr,
        // then chop this using substr
        let uni = mb_substr(test,0,1);
        let takeoff = (int) strlen(uni);
        let this->_offset += takeoff; 
        let this->_curLine = substr(test, takeoff);
        let this->_value = uni;
        
        // There are a lot of single character lexer Ids, so just look
        // them up in a table. If its not there, it is the all purpose 'T_CHAR'
        

        if !this->_singles->offsetExists(uni) {
            let tid = (int) this->_unknownId;
            let this->_isSingle = false;
        }
        else {
            let tid = (int) this->_singles->offsetGet(uni);
            let this->_isSingle = true;
        }
        let this->_id = tid;
        return tid;
    }   
}
