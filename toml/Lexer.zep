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
    const T_CHAR = 24; // any other unicode character
    const T_LAST_TOKEN = 24; // limit of token lookup

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
        "T_CHAR" // 24
    ];

   // Zephir cannot parse class constants eg Lexer::stuff used as keys in key:value
   static public Singles = [
        "=" : Lexer::T_EQUAL,
        "[" : Lexer::T_LEFT_SQUARE_BRACE,
        "]" : Lexer::T_RIGHT_SQUARE_BRACE,
        "." : Lexer::T_DOT,
        "," : Lexer::T_COMMA,
        "{" : Lexer::T_LEFT_CURLY_BRACE,
        "}" : Lexer::T_RIGHT_CURLY_BRACE,
        "\"" : Lexer::T_QUOTATION_MARK,
        "'" : Lexer::T_APOSTROPHE,
        "#" : Lexer::T_HASH,
        "\\" : Lexer::T_ESCAPE
    ];


    static private _AllRegExp;
    static private _AllSingles;
    
    static public BriefList = [
        Lexer::T_SPACE,
        Lexer::T_UNQUOTED_KEY,
        Lexer::T_INTEGER
    ];

    static public FullList = [
        Lexer::T_SPACE, Lexer::T_BOOLEAN, Lexer::T_DATE_TIME, Lexer::T_FLOAT, Lexer::T_INTEGER, 
        Lexer::T_3_QUOTATION_MARK, Lexer::T_3_APOSTROPHE,
        Lexer::T_UNQUOTED_KEY,
        Lexer::T_ESCAPED_CHARACTER
    ];

    static public BasicStringList = [
        Lexer::T_SPACE, Lexer::T_BASIC_UNESCAPED, 
        Lexer::T_ESCAPED_CHARACTER, Lexer::T_3_QUOTATION_MARK
    ];

    static public LiteralStringList = [
        Lexer::T_BASIC_UNESCAPED, Lexer::T_ESCAPED_CHARACTER, Lexer::T_3_APOSTROPHE
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
            let Lexer::_AllSingles = new KeyTable();
            Lexer::_AllSingles->offsetSet("=",Lexer::T_EQUAL);
            Lexer::_AllSingles->offsetSet("[",Lexer::T_LEFT_SQUARE_BRACE);
            Lexer::_AllSingles->offsetSet("]",Lexer::T_RIGHT_SQUARE_BRACE);
            Lexer::_AllSingles->offsetSet(".",Lexer::T_DOT);
            Lexer::_AllSingles->offsetSet(",",Lexer::T_COMMA);
            Lexer::_AllSingles->offsetSet("\"",Lexer::T_QUOTATION_MARK);
            Lexer::_AllSingles->offsetSet(".",Lexer::T_DOT);
            Lexer::_AllSingles->offsetSet("{",Lexer::T_LEFT_CURLY_BRACE);
            Lexer::_AllSingles->offsetSet("}",Lexer::T_RIGHT_CURLY_BRACE);
            Lexer::_AllSingles->offsetSet("'",Lexer::T_APOSTROPHE);
            Lexer::_AllSingles->offsetSet("#",Lexer::T_HASH);
            Lexer::_AllSingles->offsetSet("\\",Lexer::T_ESCAPE);
        }
        return Lexer::_AllSingles;
    }
    static public function getAllRegex() -> <KeyTable> {
        if empty Lexer::_AllRegExp {
            let Lexer::_AllRegExp = new KeyTable();
            Lexer::_AllRegExp->offsetSet(Lexer::T_EQUAL,"/^(=)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_BOOLEAN,"/^(true|false)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_DATE_TIME,"/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_FLOAT,"/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_INTEGER,"/^([+-]?(\\d_?)+)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_3_QUOTATION_MARK,"/^(\"\"\")/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_QUOTATION_MARK,"/^(\")/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_3_APOSTROPHE,"/^(\'\'\')/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_APOSTROPHE,"/^(\')/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_HASH,"/^(#)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_SPACE,"/^(\\s+)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_LEFT_SQUARE_BRACE,"/^(\\[)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_RIGHT_SQUARE_BRACE,"/^(\\])/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_LEFT_CURLY_BRACE,"/^(\\{)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_RIGHT_CURLY_BRACE,"/^(\\})/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_COMMA,"/^(,)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_DOT,"/^(\\.)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_UNQUOTED_KEY,"/^([-A-Z_a-z0-9]+)/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_ESCAPED_CHARACTER,"/^(\\\\(b|t|n|f|r|\"|\\\\|u[0-9AaBbCcDdEeFf]{4,4}|U[0-9AaBbCcDdEeFf]{8,8}))/");
            Lexer::_AllRegExp->offsetSet(Lexer::T_BASIC_UNESCAPED,"/^([\\x{20}-\\x{21}\\x{23}-\\x{26}\\x{28}-\\x{5A}\\x{5E}-\\x{10FFFF}]+)/u");
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
        stream->setExpList(Lexer::getAllRegex());
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