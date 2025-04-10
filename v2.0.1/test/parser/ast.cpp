#include "ast.h"

mAST_T *_MerAST_new(void) {
    return new mAST_T();
}

mAST_T *_MerAST_make_parent(string type) {
    mAST_T *node = _MerAST_new();
    node->type = type;
    return node;
}

mAST_T *_MerAST_make(string type, string tok, float value, const char* dt, const char* iden) {
    mAST_T *node = _MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = iden;
    return node;
}