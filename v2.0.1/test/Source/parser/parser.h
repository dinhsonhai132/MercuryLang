#ifndef PARSER_H
#define PARSER_H

#include "./lexer/lexer.h"
#include "./lexer/ast.h"
#include <vector>
#include <string>

using namespace std;

class Parser {
private:
    vector<token> tokens;
    int idx;
    token cur_tok;
    AST_node *program;

public:
    token get_ctok();
    token get_ntok();
    token jump_tok(int n);

    AST_node *MerParser_program();
    AST_node *MerParser_statement();
    AST_node *MerParser_print_statement();
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

#endif