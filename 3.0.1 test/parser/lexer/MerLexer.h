#include "MerCore.h"
#include "MerState.h"
#ifndef MER_LEXER_H
#define MER_LEXER_

int MerLexer_getn_char(char_state *cur);
int MerLexer_getn_tok(char_state *cur, tok_state *tok);

#endif