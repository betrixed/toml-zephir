namespace Yosy\Toml;

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

    // Zephir cannot parse class constants as keys in key:value
    static public Regex = [
        1 : "/^(=)/",
        2 : "/^(true|false)/",
        3 : "/^(\\d{4}-\\d{2}-\\d{2}(T\\d{2}:\\d{2}:\\d{2}(\\.\\d{6})?(Z|-\\d{2}:\\d{2})?)?)/",
        22 : "/^([+-]?((((\\d_?)+[\\.]?(\\d_?)*)[eE][+-]?(\\d_?)+)|((\\d_?)+[\\.](\\d_?)+)))/",
        5 : "/^([+-]?(\\d_?)+)/",
        6 : "/^(\"\"\")/",
        7 : "/^(\")/",
        8 : "/^(\'\'\')/",
        9 : "/^(\')/",
        23 : "/^(#)/",
        11 : "/^(\\s+)/",
        12: "/^(\\[)/",
        13 : "/^(\\])/",
        14 : "/^(\\{)/",
        15 : "/^(\\})/",
        16 : "/^(,)/",
        17 : "/^(\\.)/",
        18 : "/^([-A-Z_a-z0-9]+)/",
        19 : "/^(\\\(b|t|n|f|r|\"|\\\\|u[0-9AaBbCcDdEeFf]{4,4}|U[0-9AaBbCcDdEeFf]{8,8}))/",
        21 : "/^([\\x{20}-\\x{21}\\x{23}-\\x{26}\\x{28}-\\x{5A}\\x{5E}-\\x{10FFFF}]+)/u"
    ];

    static public BriefList = [
        Lexer::T_SPACE,
        Lexer::T_UNQUOTED_KEY,
        Lexer::T_INTEGER
    ];

    public function tomlVersion() -> string
    {
        return self::TOML_VERSION;
    }

    static public function tokenName(int tokenId) -> string
    {
        if (tokenId > Lexer::T_LAST_TOKEN || tokenId < 0) {
            let tokenId = 0;
        }
        return self::_nameList[tokenId];
    }
}