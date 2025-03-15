#include "lexer.h"
using namespace std;

static inline string get_2_char(char c1, char c2)
{
    switch (c1)
    {
    case '=':
        if (c2 == '=')
            return EQUAL;
        break;
    case '<':
        if (c2 == '=')
            return LESS_EQUAL;
        if (c2 == '>')
            return NOT_EQUAL;
        break;
    case '>':
        if (c2 == '=')
            return GREATER_EQUAL;
        break;
    case '&':
        if (c2 == '&')
            return AND;
        break;
    case '|':
        if (c2 == '|')
            return OR;
        break;
    case '*':
        if (c2 == '*')
            return POW;
        break;
    case '!':
        if (c2 == '=')
            return NOT_EQUAL;
        break;
    }
    return "";
}

static inline string get_1_char(char c)
{
    switch (c) {
        case '=':
            return ASSIGN;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return DIV;
        case '*':
            return TIME;
        case '!':
            return NOT;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '[':
            return LEFT_BRACKET;
        case ']':
            return RIGHT_BRACKET;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case ':':
            return COLON;
        case '.':
            return DOT;
        case '%':
            return MOD;
    }

    return "";
}

static inline bool is_identifier(string iden)
{
    vector<string> state = {"LET", "PRINT", "IF", "ELSE", "FOR",
                            "WHILE", "RETURN", "FUNC", "INT", "FLOAT", "DOUBLE", "CHAR",
                            "SHORT", "LONG", "AUTO", "VOID", "BOOL", "CHAR", "STRING",
                            "STRUCT", "CLASS", "INTER", "NEW", "DELETE", "CAST",
                            "TRUE", "BREAK", "CONTINUE"};
    for (string s : state)
    {
        if (iden == s)
            return true;
    }
    return false;
}

static inline string return_identifier(string iden) {
    if (iden == "LET")
        return LET;
    else if (iden == "PRINT")
        return PRINT;
    else if (iden == "IF")
        return IF;
    else if (iden == "ELSE")
        return ELSE;
    else if (iden == "FOR")
        return FOR;
    else if (iden == "WHILE")
        return WHILE;
    else if (iden == "RETURN")
        return RETURN;
    else if (iden == "FUNC")
        return FUNCTION;
    else if (iden == "INT")
        return INT_;
    else if (iden == "FLOAT")
        return FLOAT_;
    else if (iden == "DOU")
        return DOUBLE_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "SHORT")
        return SHORT_;
    else if (iden == "LONG")
        return LONG_;
    else if (iden == "AUTO")
        return AUTO_;
    else if (iden == "VOID")
        return VOID_;
    else if (iden == "BOOL")
        return BOOL_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "STR")
        return STRING;
    else if (iden == "STRUCT")
        return STRUCT;
    else if (iden == "CLASS")
        return CLASS;
    else if (iden == "INTER")
        return INTERFACE_;
    else if (iden == "NEW")
        return NEW;
    else if (iden == "DEL")
        return DELETE_;
    else if (iden == "CAST")
        return CAST;
    else if (iden == "BRK")
        return BREAK;
    else if (iden == "CONT")
        return CONTINUE;
    else if (iden == "INC")
        return INCLUDE;
    else if (iden == "EXT")
        return EXTERN;
    else if (iden == "USING")
        return USING;
    else if (iden == "CONS")
        return CONST_;

    return "";
}

static inline bool is_keyword(char c)
{
    vector<char> keyword = {
        '+', '-', '*', '/', '(', ')', '{', '}',
        '[', ']', ',', ';', ':', '=', '!', '<',
        '>', '&', '|'};
    for (char k : keyword)
    {
        if (c == k)
            return true;
    }
    return false;
}

static inline bool Is_tok_eof(token tok) {
    return tok.tok == EOF_T;
}

static inline bool Is_tok_expr(string tok)
{
    for (auto &tk : EXPR)
    {
        if (tk == tok)
        {
            return true;
        }
    }
}

inline bool Is_tok_type(string tok)
{
    for (auto &tk : TYPE)
    {
        if (tk == tok)
        {
            return true;
        }
    }
    return false;
}

static inline bool Is_tok_literal(string tok)
{
    for (auto &tk : LITERAL)
    {
        if (tk == tok)
        {
            return true;
        }
    }
    return false;
}

static inline bool Is_tok_identifier(string tok)
{
    for (auto &tk : IDENTIFIER)
    {
        if (tk == tok)
        {
            return true;
        }
    }
    return false;
}

static inline bool is_tok_eol(string tok) {
    return tok == EOL_T;
}


vector<token> MerLexer_tokenize(string source)
{
    int idx = 0;
    vector<token> tokens;
    while (idx < source.length()) {
        char c = source[idx];

        if (is_potential_identifier_char(c))
        { // execute char identifier and syntax
            string iden = "";
            bool found = false;

            while (is_potential_identifier_char(c))
            {
                iden += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            if (is_identifier(iden)) {
                tokens.push_back(token(return_identifier(iden), NULL_T, 0.0, iden.c_str(), iden.c_str(), iden.c_str()));
            } else {
                tokens.push_back(token(VARIABLE, NULL_T, 0.0, iden.c_str(), iden.c_str(), iden.c_str()));
            }
        }
        else if (is_digit(c))
        { // execute number
            string num = "";
            int dot_count = 0;
            while (is_potential_literal_char(c)) 
            {
                if (c == '.')
                {
                    dot_count++;
                    if (dot_count > 1)
                        break;
                }
                num += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            float num_value = atof(num.c_str());
            tokens.push_back(token(dot_count == 0 ? INT_ : FLOAT_,
                                   dot_count == 0 ? INT_T : FLOAT_T, num_value, num.c_str(), num.c_str(), num.c_str()));
        }
        else if (c == '"')
        { // execute string
            string str = "";
            idx++;
            while (source[idx] != '"')
            {
                str += source[idx];
                idx++;
            }
            tokens.push_back(token(STRING, STRING_T, 0.0, str.c_str(), str.c_str(), str.c_str()));
            idx++;
        } else if (c == '!') { //define function call
            idx++;
            char c2 = source[idx];
            string name;
            if (is_potential_identifier_char(c2)) {
                while (is_potential_identifier_char(c2)) {
                    name += c2;
                    idx++;
                    if (idx >= source.length()) {
                        break;
                    }
                    c2 = source[idx];
                }
            }
            tokens.push_back(token(FUNCTION_CALL, AUTO_T, 0.0, name.c_str(), name.c_str(), name.c_str()));
        } else if (c == '&') { //define para
            idx++;
            char c2 = source[idx];
            string name;
            if (is_potential_identifier_char(c2)) {
                while (is_potential_identifier_char(c2)) {
                    name += c2;
                    idx++;
                    if (idx >= source.length()) {
                        break;
                    }
                    c2 = source[idx];
                }
            }
            tokens.push_back(token(ARG, AUTO_T, 0.0, name.c_str(), name.c_str(), name.c_str()));
        }
        else if (is_keyword(c))
        { // execute keyword
            char c2 = source[idx + 1];
            if (is_keyword(c2) && c2 != ')')
            {
                string keyword = string(1, c) + string(1, c2);
                tokens.push_back(token(get_2_char(c, c2), NULL_T, 0.0, keyword.c_str(), keyword.c_str(), keyword.c_str()));
                idx += 2;
            }
            else
            {
                tokens.push_back(token(get_1_char(c), NULL_T, 0.0, string(1, c), string(1, c), string(1, c)));
                idx++;
            }
        } else if (isskippable(c)){
            idx++;
        } else {
            idx++;
        }
    }
    tokens.push_back(token(EOF_T, NULL_T, 0.0, "", "\n", ""));
    return tokens;
}