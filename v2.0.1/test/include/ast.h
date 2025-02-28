#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define Program "Program"
#define PrintStatement "PrintStatement"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define CallExpression "CallExpression"
#define Identifier_ "Identifier"
#define Literal "Literal"
#define IntegerLiteral "IntegerLiteral"
#define StringLiteral "StringLiteral"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"

struct AST_node {
    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    AST_node *poutput;

    bool constant;
    bool global;
    bool local;
    string var_name;
    string data_type;
    AST_node *var_value;

    string func_name;
    vector<AST_node*> body;
    vector<AST_node*> args;
    AST_node *calle;
    AST_node *memobject;
    AST_node *property;
    bool computed;
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

AST_node *MerAST_new(void);
AST_node *MerAST_make(string type, string tok, float value, string dt);
AST_node *MerAST_make_parent(string type);

#endif // AST_H