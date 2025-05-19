#ifndef MERCURY_ERRGEN_H
#define MERCURY_ERRGEN_H

#include "parser.cpp"

struct mErrgen_T {
    mParser_T *parser;
    size_t tok_idx;
};

#define err_tok(errgen) (errgen->parser->token)
#define err_nt(errgen) (errgen->parser->next)
#define ntok(errgen) (_MerLexer_get_next_tok(errgen->parser->lexer))
#define is_op_expr(tok) (tok == PLUS || tok == MINUS || tok == TIME || tok == DIV || tok == MOD)
#define is_assign(tok) (tok == ASSIGN)
#define is_comparison(tok) (tok == LESS || tok == LESS_EQUAL || tok == GREATER || tok == GREATER_EQUAL)
#define is_logic(tok) (tok == AND || tok == OR || tok == NOT)
#define is_constructor(tok) (is_op_expr(tok) || is_assign(tok) || is_comparison(tok) || is_logic(tok))


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