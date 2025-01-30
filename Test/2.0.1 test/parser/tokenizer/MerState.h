#ifndef MER_STATE_H
#define MER_STATE_H
#include "MerCore.h"

#define MAXTOKEN 500

typedef enum TOKEN_MODE_TYPE {
    STR_TOK, EXPR_TOK, REGULAR_TOK, METHOD_TOK, NULL_TOK
} token_kind;

typedef struct MER_CURRENT_TOKEN_STATEMENT {
    int tok;
    Mer_ssize_t idx;
    Mer_ssize_t size;
    token_kind kind;
    int val;

    int data_type;
    int error;
    int cmd_idx;
    int block_idx;
    
    char *str;
    char *var_name;
    const char *start, *end;
} tok_state;

typedef struct MER_CURRENT_CHAR_STATEMENT {

    char *cur;
    char *buf;
    char *inp;

    char *cmd_end_char;
    Mer_ssize_t idx;
    Mer_ssize_t tok_idx;
    int cur_tok_t;
    int isstring;

    const char *start, *end;
    Mer_ssize_t size;

    tok_state token_stacks[MAXTOKEN];
    Mer_ssize_t token_stacks_idx;

} char_state;

int *MerLexer_Update_token(char_state *cur, tok_state *tok, int type, int val, 
const char *t_start, const char *t_end);
char_state *_MerReset_Tokenize();

#endif