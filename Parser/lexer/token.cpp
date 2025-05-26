#include "token.h"

mToken_T *_MerToken_new(void) {
    mToken_T *token = (mToken_T *)malloc(sizeof(mToken_T));
    token->tok = NULL;
    token->type = NULL;
    token->value = 0.0;
    token->name = NULL;
    token->index = 0;
    token->symbol = NULL;
    token->string_iden = NULL;
    return token;
}

int *_MerToken_free(mToken_T *token) {
    free(token);
    return NULL;
}

mToken_T *_MerInit_token(const char* tok,const char* type, float value,const char* name,const char* symbol,const char* string_iden) {
    mToken_T *token = _MerToken_new();
    token->tok = tok;
    token->type = type;
    token->value = value;
    token->name = name;
    token->symbol = symbol;
    token->string_iden = string_iden;
    return token;
}