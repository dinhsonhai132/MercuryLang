#include "C:\Users\hadin\OneDrive\Desktop\Mercury-Langluage-main\2.0.1 test\include\MerCore.h"
#ifndef MER_STATE_H
#define MER_STATE_H
#define MAXTOKEN 500

typedef enum TOKEN_MODE_TYPE {
    STR_TOK, EXPR_TOK, REGULAR_TOK, METHOD_TOK, NULL_TOK
} token_kind;

typedef struct MER_CURRENT_TOKEN_STATEMENT {
    int tok;                                                        // current token
    int val;                                                        // value of the token    
    Mer_ssize_t idx;                                                // index of the token
    Mer_ssize_t size;                                               // size of the token like [PRINT]: "print" is 5
    token_kind kind;                                                // kind of the token (string tok, integer tok, regular tok, etc...)

    int data_type;                                                  // datatype of the token (STRING, INT, FLOAT, etc...)
    int error;                                                      // (in update) check if error

    int iscmd;
    int isblock;
    int cmd_block_idx;                                              // position of command in command block (command block can be like: PRINT x + 1; LET x = 0 is command block)
    int block_idx;                                                  // position of command block
    int cmd_idx;                                                    // position of command

    char *str;                                                      // for string
    char *str_iden;                                                 // for variable or function name,...
    const char *start, *end;                                        // start and end of the tokens
} tok_state;

typedef struct MER_CURRENT_CHAR_STATEMENT {
    char *cur;                                                      // current char
    char *buf;                                                      // input
    char *inp;                                                      // the end of the buf

    Mer_ssize_t idx;                                                // index of char
    Mer_ssize_t tok_idx;                                            // postion of token index
    int cur_tok_t;                                                  // token of the char
    int isstring;                                                   // check if this char is in string token
    int end_idx;

    int tokc_idx;                                                   // index of char in token
    char *cend_t;                                                   // the end of the token
    char *cstart_t;                                                 // start of the token

    int inp_t                                                       // index the end of the token
    int status;                                                     // status of the token ERROR_NO is no error
    int isend;                                                      // check if this char is end

    const char *start, *end;                                        // start or end of the cur

    tok_state token_stacks[MAXTOKEN];                               // token stack store tokens
    Mer_ssize_t token_stacks_idx;                                   // token stacks index
} char_state;

// update tokens 
int *MerLexer_Update_token(char_state *cur, tok_state *tok, int type, int val, 
const char *t_start, const char *t_end);

char_state *MerLexer_Token_setup(char_state *cur);

#endif