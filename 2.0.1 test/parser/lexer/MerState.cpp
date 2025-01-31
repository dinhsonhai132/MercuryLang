#include "MerState.h"

char_state *_MerReset_Tokenize() {
    
    char_state *tok = (char_state *)malloc(sizeof(char_state));
    if (!tok) return NULL;

    tok->cur 
    = tok->buf
    = tok->inp 
    = NULL;

    tok->idx 
    = tok->token_stacks_idx 
    = tok->tok_idx
    = 0;

    tok->cur_tok_t = NONE;
    tok->isstring = 0;

    tok->tokc_idx = 0;
    tok->cend_t = NULL;
    tok->cstart_t = NULL;
    tok->isend = EOK;
    tok->status = ERROR_NO;
    tok->end_idx = 0;
    
    tok->start = tok->end = NULL;
    tok->token_stacks[0] = {
        .tok = NONE,
        .idx = 0,
        .size = 0,
        .iscmd = FALSE,
        .isblock = FALSE,
        .kind = REGULAR_TOK,
        .val = 0,
        .data_type = AUTO,
        .error = 0,
        .cmd_block_idx = 0,
        .cmd_idx = 0,
        .block_idx = 0,
        .str = NULL,
        .str_iden = NULL
    };
    return tok;
};

int *MerLexer_Update_token(char_state *cur, tok_state *tok, int type, int val,
const char *t_start, const char *t_end) {

    if (!cur || !tok) return UNIDEN;

    if (cur->tok_idx < cur->size || tok->idx < tok->size) {
        cur->tok_idx = tok->idx;
        cur->tokc_idx = 1;
        cur->cstart_t = cur->cur;
        cur->cend_t = cur->cur + tok->size;
        cur->end_idx = *cur->cur + tok->size;
    }

    if (t_start != NULL && t_end != NULL) {
        tok->start = t_start;
        tok->end = t_end;
    }

    if (tok->iscmd == TRUE) {
        tok->cmd_idx = 1;
        tok->cmd_block_idx = 0;
        tok->block_idx = 0;
    }

    tok->tok = type;
    cur->cur_tok_t = tok->tok;
    tok->val = val;

    return type;
}