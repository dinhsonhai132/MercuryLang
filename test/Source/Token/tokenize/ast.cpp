#include "ast.h"
#include "lexer.h"

#define IDENTIFIER {PRINT, LET, IF, ELSE, FOR, WHILE, FUNCTION, STRUCT, CLASS}
#define LITERAL {INT, FLOAT, VARIABLE}

static inline bool is_Tok_identifier(string tok) {
    vector<string> toks = IDENTIFIER;
    for (string t : toks) {
        if (t == tok) return true;
    }
}

static inline bool is_Tok_Literal(string tok) {
    vector<string> toks = LITERAL;
    for (string t : toks) {
        if (t == tok) return true;
    }
}