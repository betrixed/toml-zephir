namespace Toml;
/**
 * Description of TokenArray
 * Just enough to satisfy LexerText
 * @author Michael Rynn
 * 
 */
class TokenList
{
    protected _tokens;
    protected _ct;
    protected _index;
    protected _token; // token at current position
    /**
     * Constructor
     * Need to call moveNextId or setOffset to set first location,
     * 
     * @param Token[] List of tokens
     */
    public function __construct(array! tokens)
    {
        let this->_tokens = tokens;
        let this->_ct = count(tokens);
        let this->_index = -1;
        this->moveNextId();
    }

    /**
     * Get the current token offset
     * @return int
     */
    public function getOffset() -> int {
        return this->_index;
    }
    /** 
     * Set current array of tokens position 
     */
    public function setOffset(int! index) -> int {
        if (index < this->_ct) {
            let this->_index = index;
            let this->_token = this->_tokens[index];
            return this->_token->id;
        }
        return 0;
    }
/**
     * Checks if the following tokens in the stream match with the sequence of tokens
     *
     * @param int[] $tokenIds Sequence of token ids
     *
     * @return bool
     */
    public function isNextSequence(array! tokenIds) -> bool
    {
    	var idx, test;
    	int offset, base;
    	let base = (int) this->_index;
    	for idx,test in tokenIds {
            let offset = idx + base;
            if offset < this->_ct {
                if this->_tokens[offset]->id != test {
                    return false;
                }
            }
        }
        return true;
    }    
    
    /**
     * Moves the pointer one token forward
     *
     * @return positive token id, or 0 (false)
     */
    public function moveNextId() -> int
    {
    	int next;
        let next = this->_index + 1;
        let this->_index = next;
        if next < this->_ct {
            let this->_token = this->_tokens[next];
            return this->_token->id;
        }
        let this->_token = null;
        return 0;
    }
    
    /**
     * Token from current parse position
     * @return \Toml\Token
     */
    public function getToken() -> <Token> {
        return this->_token;
    }
    /** 
     * Token id from current parse position
     *  
     */
    public function getTokenId() -> int {
    	if empty this->_token {
    		return 0;
    	}
    	else {
    		return this->_token->id;
    	}
    }
    
    /** 
     * Token value from current parse position
     *  
     */
    public function getValue() -> var {
    	var value;
        if empty this->_token {
    		let value = null;
    	}
    	else {
    		let value = this->_token->value;
    	}
    	return value;
    }
}
