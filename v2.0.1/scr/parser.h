#ifndef MERCURY_PARSER_HEADER_FILE
#define MERCURY_PARSER_HEADER_FILE

#include <iostream>
#include <vector>
#include <string>

#include "lexer.cpp"
#include "ast.cpp"
#include "object.cpp"
#include "buffer.cpp"

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
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_function_call_statement();
    AST_node *MerParser_let_statement();
    AST_node *MerParser_return_statement();
    AST_node *MerParser_statement();
    AST_node *MerParser_function_body_expression();
    AST_node *MerParser_function_expression_statement();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

AST_node *MerAST_make_AST(vector<token> tokens);

#endif // MERCURY_PARSER_HEADER_FILE