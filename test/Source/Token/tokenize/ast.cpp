#include "ast.h"
#include "lexer.h"

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