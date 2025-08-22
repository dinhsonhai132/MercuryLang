#include "token.h"

mToken_T *_MerToken_new(void) {
    mToken_T *token = new mToken_T;
    token->tok = "";
    token->type = "";
    token->value = 0.0;
    token->name = "";
    token->index = 0;
    token->symbol = "";
    token->string_iden = "";
    return token;
}

int *_MerToken_free(mToken_T *token) {
    delete token;    
    return NULL;
}

mToken_T *_MerInit_token(string tok, string type, float value, string name, string symbol, string string_iden) {
    mToken_T *token = _MerToken_new();
    token->tok = tok;
    token->type = type;
    token->value = value;
    token->name = name;
    token->symbol = symbol;
    token->string_iden = string_iden;
    return token;
}