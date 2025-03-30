#include "ast.h"

AST_node *MerAST_new(void) {
    return new AST_node();
}

AST_node *MerAST_make_parent(string type) {
    AST_node *node = MerAST_new();
    node->type = type;
    return node;
}

AST_node *MerAST_make(string type, string tok, float value, string dt, string iden) {
    AST_node *node = MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = iden;
    return node;
}