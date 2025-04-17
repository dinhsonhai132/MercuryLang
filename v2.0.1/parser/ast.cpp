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

int _MerAST_free(mAST_T *ast) {
    if (ast == nullptr) return _SUCCESS;

    if (ast->left) _MerAST_free(ast->left);
    if (ast->right) _MerAST_free(ast->right);
    if (ast->comp) _MerAST_free(ast->comp);
    if (ast->comp_left) _MerAST_free(ast->comp_left);
    if (ast->comp_right) _MerAST_free(ast->comp_right);
    if (ast->var_value) _MerAST_free(ast->var_value);
    if (ast->return_v) _MerAST_free(ast->return_v);
    if (ast->poutput) _MerAST_free(ast->poutput);

    for (mAST_T* node : ast->args) {
        _MerAST_free(node);
    }
    for (mAST_T* node : ast->body) {
        _MerAST_free(node);
    }
    for (mAST_T* node : ast->then_body) {
        _MerAST_free(node);
    }
    for (mAST_T* node : ast->else_body) {
        _MerAST_free(node);
    }
    for (mAST_T* node : ast->list) {
        _MerAST_free(node);
    }
    for (mAST_T* node : ast->children) {
        _MerAST_free(node);
    }

    delete ast;

    return _SUCCESS;
}

