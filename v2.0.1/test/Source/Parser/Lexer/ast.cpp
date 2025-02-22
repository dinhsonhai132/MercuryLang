#include"ast.h"

AST_node *MerAST_new(void) { 
    AST_node* node = (AST_node*)calloc(1, sizeof(AST_node));

    node->type = Program;
    node->tok = "";
    node->poutput = NULL;
    node->value = 0.0;
    node->string_iden = "";
    node->constant = false;
    node->global = false;
    node->local = false;
    node->var_name = "";
    node->data_type = "";
    node->func_name = "";
    node->var_value = NULL;
    node->body = vector<AST_node*>();
    node->args = vector<AST_node*>();
    node->return_value = 0.0;
    node->func_type = "";
    node->op = "";
    node->left = NULL;
    node->right = NULL;
    node->list_name = "";
    node->list_type = "";
    node->list = vector<AST_node*>();
    node->children = vector<AST_node*>();
    node->condtion = false;

    return node;
}

AST_node *MerAST_make(string type, string tok, float value, string dt) {
    AST_node* node = MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    return node;
}

AST_node *MerAST_make_parent(string type) {
    AST_node* node = MerAST_new();
    node->type = type;
    return node;
}

bool Is_tok_eof(token tok) {
    return tok.tok == EOF_T;
}

bool Is_tok_type(token tok) {
    for (auto &tk : TYPE) {
        if (tk == tok.tok) {
            return true;
        }
    }
}

bool Is_tok_literal(string tok) {
    for (auto &tk : LITERAL) {
        if (tk == tok) {
            return true;
        }
    }
}

bool Is_tok_identifier(string tok) {
    for (auto &tk : IDENTIFIER) {
        if (tk == tok) {
            return true;
        }
    }
}

bool Is_tok_expression(string tok) {
    for (auto &tk : EXPR) {
        if (tk == tok) {
            return true;
        }
    }
}   
