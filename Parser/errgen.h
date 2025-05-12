#ifndef MERCURY_ERRGEN_H
#define MERCURY_ERRGEN_H

#include "parser.cpp"

struct mErrgen_T {
    mParser_T *parser;
    size_t tok_idx;
};

#define conflict_at_start(a) ( \
    (a == PLUS) || (a == MINUS) || (a == TIME) || (a == DIV) || \
    (a == PLUS_PLUS) || (a == MINUS_MINUS) || (a == GREATER_EQUAL) || (a == LESS_EQUAL) || \
    (a == AND) || (a == OR) || (a == NOT) || (a == NOT_EQUAL) || (a == POW) || \
    (a == EQUAL) || (a == LESS) || (a == GREATER) || (a == MOD) || \
    (a == LEFT_PAREN) || (a == RIGHT_PAREN) || (a == LEFT_BRACE) || (a == RIGHT_BRACE) || \
    (a == LEFT_BRACKET) || (a == RIGHT_BRACKET) || (a == SEMICOLON) || (a == COLON) || \
    (a == ARROW) || (a == COMMA) || (a == ASSIGN) \
)

#define incr_err_idx(errgen) (++errgen->tok_idx)
#define take_tok(errgen) errgen->parser->token

mErrgen_T *MerErrGen_init(string buffer);
void __reset_errgen(mErrgen_T *errgen);
void __merrgen_loop(mErrgen_T *errgen);

#endif