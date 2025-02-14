#ifndef AST_H
#define AST_H

#define Program "Program"
#define PrintStatement "PrintStatement"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define Expression "Expression"
#define Function "Function"
#define CallExpression "CallExpression"
#define Identifier "Identifier"
#define Literal "Literal"
#define IntegerLiteral "IntegerLiteral"
#define StringLiteral "StringLiteral"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"

#include <string>
#include <vector>
#include "lexer.h"

#define LITERAL {INT, FLOAT, DOUBLE}
#define IDENTIFIER {LET, PRINT, IF, ELSE, FOR, WHILE}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT, FLOAT, DOUBLE}

using namespace std;

struct AST_node {
    string type;
    string tok;
    float value;
    string string_iden;
    
    bool constant;
    bool global;
    bool local;
    string var_name;
    string data_type;

    string func_name;
    vector<AST_node*> body;
    vector<AST_node*> args;
    float return_value;
    string func_type;

    string op;
    AST_node* left;
    AST_node* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<AST_node*> list;

    vector<AST_node*> children;
};

bool Is_tok_literal(string tok);
bool Is_tok_identifier(string tok);
bool Is_tok_expression(string tok);
bool Is_tok_eof(token tok);
AST_node *MerAST_new();
AST_node *MerAST_make(string type, string tok, float value, string dt);
AST_node *MerAST_make_parent(string type);

#endif