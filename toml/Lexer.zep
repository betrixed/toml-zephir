namespace Toml;

class Lexer {
	const T_BAD = 0;
    const T_EQUAL = 1;
    const T_BOOLEAN = 2;
    const T_DATE_TIME = 3;
    const T_EOS = 4;
    const T_INTEGER = 5;
    const T_3_QUOTATION_MARK = 6;
    const T_QUOTATION_MARK = 7;
    const T_3_APOSTROPHE = 8;
    const T_APOSTROPHE = 9;
    const T_NEWLINE = 10;
    const T_SPACE = 11;
    const T_LEFT_SQUARE_BRACE = 12;
    const T_RIGHT_SQUARE_BRACE = 13;
    const T_LEFT_CURLY_BRACE = 14;
    const T_RIGHT_CURLY_BRACE = 15;
    const T_COMMA = 16;
    const T_DOT = 17;
    const T_UNQUOTED_KEY = 18;
    const T_ESCAPED_CHARACTER = 19;
    const T_ESCAPE = 20;
    const T_BASIC_UNESCAPED = 21;
    const T_FLOAT = 22;
    const T_HASH = 23;
    const T_LITERAL_STRING = 24;
    const T_CHAR = 25; // any other unicode character
    const T_LAST_TOKEN = 25; // limit of token lookup

    const TOML_VERSION = "0.4";
    const USE_VERSION = "Zephir";

    static private _nameList = [
        "T_BAD", //0
        "T_EQUAL", //1
        "T_BOOLEAN", //2
        "T_DATE_TIME", //3
        "T_EOS", //4
        "T_INTEGER", //5
        "T_3_QUOTATION_MARK", //6
        "T_QUOTATION_MARK", //7
        "T_3_APOSTROPHE", //8
        "T_APOSTROPHE", //9
        "T_NEWLINE", //10
        "T_SPACE", //11
        "T_LEFT_SQUARE_BRACE", //12
        "T_RIGHT_SQUARE_BRACE", //13
        "T_LEFT_CURLY_BRACE", //14
        "T_RIGHT_CURLY_BRACE", //15
        "T_COMMA", //16
        "T_DOT", //17
        "T_UNQUOTED_KEY", //18
        "T_ESCAPED_CHARACTER", //19
        "T_ESCAPE", //20
        "T_BASIC_UNESCAPED", //21
        "T_FLOAT", //22
        "T_HASH", //23
        "T_LITERAL_STRING", //24
        "T_CHAR" // 25
    ];



    static private _AllRegExp;
    static private _AllSingles;
    
    static public KeyList = [
        Lexer::T_SPACE,
        Lexer::T_UNQUOTED_KEY,
        Lexer::T_INTEGER
    ];

    static public ScalerList = [
        Lexer::T_BOOLEAN, Lexer::T_DATE_TIME, 
        Lexer::T_FLOAT, Lexer::T_INTEGER
    ];

    static public BasicString = [
        Lexer::T_SPACE, Lexer::T_BASIC_UNESCAPED, 
        Lexer::T_ESCAPED_CHARACTER, Lexer::T_3_QUOTATION_MARK
    ];

    static public LiteralString = [
        Lexer::T_LITERAL_STRING
    ];

    static public LiteralMLString = [
        Lexer::T_LITERAL_STRING, Lexer::T_3_APOSTROPHE
    ];

   static  public function getTomlVersion() -> string
    {
        return Lexer::TOML_VERSION;
    }
    static  public function getUseVersion() -> string
    {
        return Lexer::USE_VERSION;
    }
    static public function tokenName(int tokenId) -> string
    {
        if (tokenId > Lexer::T_LAST_TOKEN || tokenId < 0) {
            let tokenId = 0;
        }
        return self::_nameList[tokenId];
    }

    static public function getExpSet(array! idList) -> <KeyTable> {
        var all;
        var result, id;

        let all = Lexer::getAllRegex();
        
        let result = new KeyTable();
        
        for id in idList {
            result->offsetSet(id,all->offsetGet(id));
        }
        return result;
    }

    static public function getAllSingles() -> <KeyTable> {
        if empty Lexer::_AllSingles {
            var kt;
            let kt = new KeyTable();
            kt->offsetSet("=",Lexer::T_EQUAL);
            kt->offsetSet("[",Lexer::T_LEFT_SQUARE_BRACE);
            kt->offsetSet("]",Lexer::T_RIGHT_SQUARE_BRACE);
            kt->offsetSet(".",Lexer::T_DOT);
            kt->offsetSet(",",Lexer::T_COMMA);
            kt->offsetSet("\"",Lexer::T_QUOTATION_MARK);
            kt->offsetSet(".",Lexer::T_DOT);
            kt->offsetSet("{",Lexer::T_LEFT_CURLY_BRACE);
            kt->offsetSet("}",Lexer::T_RIGHT_CURLY_BRACE);
            kt->offsetSet("'",Lexer::T_APOSTROPHE);
            kt->offsetSet("#",Lexer::T_HASH);
            kt->offsetSet("\\",Lexer::T_ESCAPE);
            kt->offsetSet(" ",Lexer::T_SPACE);
            kt->offsetSet("\t", Lexer::T_SPACE);
            kt->offsetSet("\r", Lexer::T_SPACE);
            // maybe these are not necessary
            kt->offsetSet("\f", Lexer::T_SPACE);
            kt->offsetSet("\b", Lexer::T_SPACE);
            let Lexer::_AllSingles = kt;
        }
        return Lexer::_AllSingles;
    }
    static public function getAllRegex() -> <KeyTable> {
        if empty Lexer::_AllRegExp {
            var kt;
            let kt = new KeyTable();
            
            kt->offsetSet(Lexer::T_EQUAL,"/^(=)/");
            kt->offsetSet(Lexer::T_BOOLEAN,"/^(true|false)/");
            kt->offsetSet(Lexer::T_DATE_TIME,"/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/");
            kt->offsetSet(Lexer::T_FLOAT,"/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/");
            kt->offsetSet(Lexer::T_INTEGER,"/^([+-]?(\\d_?)+)/");
            kt->offsetSet(Lexer::T_3_QUOTATION_MARK,"/^(\"\"\")/");
            kt->offsetSet(Lexer::T_QUOTATION_MARK,"/^(\")/");
            kt->offsetSet(Lexer::T_3_APOSTROPHE,"/^(\'\'\')/");
            kt->offsetSet(Lexer::T_APOSTROPHE,"/^(\')/");
            kt->offsetSet(Lexer::T_HASH,"/^(#)/");
            kt->offsetSet(Lexer::T_SPACE,"/^(\\s+)/");
            kt->offsetSet(Lexer::T_LEFT_SQUARE_BRACE,"/^(\\[)/");
            kt->offsetSet(Lexer::T_RIGHT_SQUARE_BRACE,"/^(\\])/");
            kt->offsetSet(Lexer::T_LEFT_CURLY_BRACE,"/^(\\{)/");
            kt->offsetSet(Lexer::T_RIGHT_CURLY_BRACE,"/^(\\})/");
            kt->offsetSet(Lexer::T_COMMA,"/^(,)/");
            kt->offsetSet(Lexer::T_DOT,"/^(\\.)/");
            kt->offsetSet(Lexer::T_UNQUOTED_KEY,"/^([-A-Z_a-z0-9]+)/");
            kt->offsetSet(Lexer::T_ESCAPED_CHARACTER,
                "/^\\\\(n|t|r|f|b|\\\\|\\\"|u[0-9A-Fa-f]{4,4}|U[0-9A-Fa-f]{8,8})/");
            kt->offsetSet(Lexer::T_ESCAPE,"/^(\\\\)/"); 

            kt->offsetSet(Lexer::T_BASIC_UNESCAPED,
                "/^([^\\x{0}-\\x{19}\\x{22}\\x{5C}]+)/u");
            kt->offsetSet(Lexer::T_LITERAL_STRING,
                    "/^([^\\x{0}-\\x{19}\\x{27}]+)/u");
            let Lexer::_AllRegExp = kt;
        }
        return Lexer::_AllRegExp;
    }
     public function tokenize(string input) -> <TokenList>
    {
        // convert string into array of tokens
        // clone each from the stream
        var stream;
        var list;

        let stream = new TokenStream();
        stream->setExpSet(Lexer::getAllRegex());
        stream->setSingles(Lexer::getAllSingles());
        stream->setUnknownId(Lexer::T_CHAR);
        stream->setNewLineId(Lexer::T_NEWLINE);
        stream->setEOSId(Lexer::T_EOS);
        stream->setInput(input);

        let list = [];

        while (stream->moveNextId() !== Lexer::T_EOS) {
            let list[] = clone stream->getToken();
        }
        let list[] = clone stream->getToken();
        return new TokenList(list);
    }
}