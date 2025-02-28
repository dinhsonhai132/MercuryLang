#ifndef PARSER_H
#define PARSER_H

#include "C:\Users\dinhs\Documents\Program Language\Mercury-Langluage-main\Mercury-Langluage-main\v2.0.1\test\Source\Parser\Lexer\ast.h"
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Parser {
private:
    vector<token> tokens;
    int idx;
    token cur_tok;
    AST_node *program;

public:

    Parser(vector<token> tokens) : tokens(tokens), idx(0) {}

    bool look_ahead(string tok, int n);

    token get_ctok();
    token get_ntok();
    token jump_tok(int n);

    AST_node *MerParser_program();
    AST_node *MerParser_statement();
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_function_call();
    AST_node *MerParser_expression();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

AST_node *MerAST_make_ast(vector<token> tokens);

#endif