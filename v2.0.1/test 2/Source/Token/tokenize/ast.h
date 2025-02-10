#ifndef AST_H
#define AST_H

#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

#define Program "Program"
#define ExprStatement "ExprStatement"
#define Identifier "Identifier"
#define Literal "Literal"
#define BinaryExpression "BinaryExpression"
#define NullExpression "NullExpression"
#define PrintStatement "PrintStatement"
#define StoreVariable "StoreVariable"
#define VarDeclaration "VarDeclaration"

struct AST_node {
    string type;
    string iden;
    float value;

    string tok;
    string data_type;
    string symbol;
};

struct AST_Program {
    string type = Program;
    vector<AST_Statement> statements;
};

struct AST_Statement {
    string type = ExprStatement;
    virtual ~AST_Statement() {}
};

struct AST_BinExpression : AST_Statement {
    AST_BinExpression() { type = BinaryExpression; }
    vector<AST_node> exprs;
};

struct AST_PrintState : AST_Statement {
    AST_PrintState() { type = PrintStatement; }
    string output;
    AST_BinExpression exprs;
};

static inline bool is_Tok_identifier(string tok);
static inline bool is_Tok_Literal(string tok);
static inline bool is_Tok_Null(string tok);
static inline bool is_Tok_BinExpression(string tok);

#endif
