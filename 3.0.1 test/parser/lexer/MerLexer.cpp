#include "MerLexer.h"

#define Check_char_identifier(x) ( \
    (x >= 'a' && x <= 'z') || \
    (x >= 'A' && x <= 'Z') || \
    (x == '_') \
)

#define Check_Var_name_identifier(x) { \
    (x >= 'a' && x <= 'z') || \
    (x >= 'A' && x <= 'Z') || \
    (x >= '0' && x <= '9') || \
    (x == '_') \
}

int MerLexer_getn_char(char_state *cur) {
    if (!cur || !cur->cur || cur->idx >= cur->size) {
        return EOF;
    }

    cur->idx++;
    return Mer_CHARMASK(*cur->cur++);
}

int MerLexer_getn_tok(char_state *cur, tok_state *tok, const char *start, const char *end) {
    int c;
    c = MerLexer_getn_char(cur);
    if (c == '+') {
        tok->idx++;
        tok->val = 0;
    }
}