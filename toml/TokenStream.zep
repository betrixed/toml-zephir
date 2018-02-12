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
    protected _matches;
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
     * Argument is reference to associative array[int] of string regular expressions
     * @param array $ref
     */
    public function setExpList(var ref) -> void {
        let this->_regex = ref;
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

                  
    public function hasPendingTokens() -> bool {
        return (this->_id != this->_eosId);
    }

     /**
     * Get all token details of parse step
     * @return \Yosy\Token
     */
    public function getToken() -> var
    {
        var token = this->_token;
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
    public function setLines(var lines) -> void {
        let this->_lines = lines;
        let this->_lineNo = 0;
        let this->_offset = 0;
        let this->_lineCount = count(lines->_me);
        let this->_curLine = (this->_lineCount > 0) ? lines->_me[0] : null;
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
    	var id, pattern, takeoff;
        var matches;
        var nextLine;
        var tid, uni;
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

        for id, pattern in this->_regex->_store {
            if (preg_match(pattern, this->_curLine, matches)) {
                let this->_value = matches[1];
		        let this->_id = id;
		        let this->_isSingle = false;
		        let this->_line = this->_tokenLine;
		        
		        let takeoff = strlen(matches[1]);
		        let this->_offset += takeoff;
		        let this->_curLine = substr(this->_curLine, takeoff);
		        return this->_id;
    		}
        }
        // no expressions matched, as a default, classify unicode character
        // get next unicode character using mb_substr,
        // then chop this using substr
        let uni = mb_substr(this->_curLine,0,1);
        let takeoff = strlen(uni);
        let this->_offset += takeoff; 
        let this->_curLine = substr(this->_curLine, takeoff);
        let this->_value = uni;
        
        // There are a lot of single character lexer Ids, so just look
        // them up in a table. If its not there, it is the all purpose 'T_CHAR'
        

        if !fetch tid, this->_singles->_store[uni]  {
        	let tid = this->_unknownId;
        	let this->_isSingle = false;
        }
        else {
        	let this->_isSingle = true;
        }
        let this->_id = tid;
        return tid;
    }   
}
