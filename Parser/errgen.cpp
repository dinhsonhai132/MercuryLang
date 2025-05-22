#include "errgen.h"

mErrgen_T *MerErrGen_init(string buffer) {
    mErrgen_T *errgen = (mErrgen_T *)malloc(sizeof(mErrgen_T));
    mParser_T *parser = _MerParser_init(_MerLexer_init(buffer.c_str()));
    errgen->parser = parser;
    return errgen;
}

void __reset_errgen(mErrgen_T *errgen) {
    free(err_tok(errgen));
    _MerLexer_free(errgen->parser->lexer);
    _MerToken_free(errgen->parser->token);
    _MerToken_free(errgen->parser->next);
    free(errgen->parser);
    free(errgen);
    delete errgen;
}

void __merrgen_loop(mErrgen_T *errgen) {
    int a;
    for (;;) {
        err_tok(errgen) = ntok(errgen);
        string tok = err_tok(errgen)->tok;
        ++errgen->tok_idx;

        if (take_tok(errgen)->tok == EOF_T) {
            break;
        }

        if (tok == LET) {
            err_tok(errgen) = ntok(errgen);
            tok = err_tok(errgen)->tok;
            ++errgen->tok_idx;

            if (tok != VARIABLE) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected identifier in let, missing identifier", "stdin", errgen->parser->lexer->row);
            }
        }

        if (tok == FUNCTION) {
            err_tok(errgen) = ntok(errgen);
            tok = err_tok(errgen)->tok;
            ++errgen->tok_idx;

            if (tok != VARIABLE) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected identifier in let", "stdin", errgen->parser->lexer->row);
            }

            err_tok(errgen) = ntok(errgen);
            tok = err_tok(errgen)->tok;
        }

        if (tok == VARIABLE) {
            err_nt(errgen) = _MerLexer_look_ahead(errgen->parser->lexer);
            if (err_nt(errgen)->tok == LEFT_PAREN) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call, function call is wrong, function call must start with '!' for e.g !main()", "stdin", errgen->parser->lexer->row);                
            }
            
            if (is_constructor(tok)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression, after variable", "stdin", errgen->parser->lexer->row);
            }
        }

        if (errgen->tok_idx == 1) {
            if (conflict_at_start(take_tok(errgen)->tok)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression at start", "stdin", errgen->parser->lexer->row);
            }
        }
    }
    
    __reset_errgen(errgen);
}