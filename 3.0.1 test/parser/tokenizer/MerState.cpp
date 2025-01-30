#include "MerState.h"

char_state *_MerReset_Tokenize() {
    
    char_state *tok = (char_state *)malloc(sizeof(char_state));
    if (!tok) return NULL;

    tok->cur 
    = tok->buf
    = tok->inp 
    = tok->cmd_end_char
    = NULL;

    tok->idx 
    = tok->size 
    = tok->token_stacks_idx 
    = tok->tok_idx
    = 0;

    tok->cur_tok_t = NONE;
    tok->isstring = 0;
    
    tok->start = tok->end = NULL;
    tok->token_stacks[0] = {
        .tok = NONE,
        .idx = 0,
        .size = 0,
        .kind = REGULAR_TOK,
        .val = 0,
        .data_type = AUTO,
        .error = 0,
        .cmd_idx = 0,
        .block_idx = 0,
        .str = NULL,
        .var_name = NULL
    };
    return tok;
};

int *MerLexer_Update_token(char_state *cur, tok_state *tok, int type, int val,
const char *t_start, const char *t_end) {

    if (!cur || !tok) return UNIDEN;

    if (cur->tok_idx < cur->size || tok->idx < tok->size) {
        cur->tok_idx = tok->idx;
    }

    if (t_start != NULL && t_end != NULL) {
        tok->start = t_start;
        tok->end = t_end;
    }

    tok->tok = type;
    tok->tok = cur->cur_tok_t;

    tok->val = val;
    return &tok->tok;
}