#include "errgen.h"

mErrgen_T *MerErrGen_init(string buffer) {
    mErrgen_T *errgen = (mErrgen_T *)malloc(sizeof(mErrgen_T));
    mParser_T *parser = _MerParser_init(_MerLexer_init(buffer.c_str()));
    errgen->parser = parser;
    return errgen;
}

void __reset_errgen(mErrgen_T *errgen) {
    errgen->parser = _MerParser_new();
}
void __merrgen_loop(mErrgen_T *errgen) {
    for (;;) {
        errgen->parser->token = _MerLexer_get_next_tok(errgen->parser->lexer);
        string tok = errgen->parser->token->tok;
        ++errgen->tok_idx;

        if (take_tok(errgen)->tok == EOF_T) {
            break;
        }

        if (tok == LET) {
            errgen->parser->token = _MerLexer_get_next_tok(errgen->parser->lexer);
            tok = errgen->parser->token->tok;
            ++errgen->tok_idx;

            if (tok != VARIABLE) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected identifier in let", "stdin", errgen->parser->lexer->row);
            }
        }

        if (tok == FUNCTION) {
            errgen->parser->token = _MerLexer_get_next_tok(errgen->parser->lexer);
            tok = errgen->parser->token->tok;
            ++errgen->tok_idx;

            if (tok != VARIABLE) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected identifier in let", "stdin", errgen->parser->lexer->row);
            }

            errgen->parser->token = _MerLexer_get_next_tok(errgen->parser->lexer);
            tok = errgen->parser->token->tok;
        }

        if (errgen->tok_idx == 1) {
            if (conflict_at_start(take_tok(errgen)->tok)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression at start", "stdin", errgen->parser->lexer->row);
            }
        }
    }

    __reset_errgen(errgen);
}