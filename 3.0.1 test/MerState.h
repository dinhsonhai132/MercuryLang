#ifndef MER_STATE_H
#define MER_STATE_H
#include "MerCore.h"
typedef enum TOKEN_MODE_TYPE {
    STR_TOK, EXPR_TOK, REGULAR_TOK, METHOD_TOK, NULL_TOK
} token_kind;

typedef struct MER_CURRENT_TOKEN_STATEMENT {
    int type;
    int val;
    char *cur;
    int idx;
    token_kind kind;
    Mer_ssize_t size;
    const char *end, *start;
} tok_state;

#endif