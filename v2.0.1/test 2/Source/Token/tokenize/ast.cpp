#include "ast.h"
#define IDENTIFIER {PRINT, LET, IF, ELSE, FOR, WHILE, FUNCTION, STRUCT, CLASS}
#define LITERAL {INT, FLOAT, VARIABLE}
#define BIN {PLUS, MINUS, TIME, DIV, INT, FLOAT, VARIABLE}
#define NULL_EXPRESSION {NULL, SEMICOLON, EOF_T}

static bool is_Tok_identifier(string tok)
{
    vector<string> toks = IDENTIFIER;
    for (string t : toks)
    {
        if (t == tok)
            return true;
    }
}

static bool is_Tok_Literal(string tok)
{
    vector<string> toks = LITERAL;
    for (string t : toks)
    {
        if (t == tok)
            return true;
    }
}

static bool is_Tok_Null(string tok)
{
    vector<string> toks = NULL_EXPRESSION;
    for (string t : toks)
    {
        if (t == tok)
            return true;
    }
}

static bool is_Tok_BinExpression(string tok)
{
    vector<string> toks = BIN;
    for (string t : toks)
    {
        if (t == tok)
            return true;
    }
}