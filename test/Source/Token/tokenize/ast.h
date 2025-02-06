/*
------------------------------------------------------------
-- Mercury Language - Abstract Syntax Tree (AST) Header  --
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This file defines the Abstract Syntax Tree (AST) for 
-- Mercury Language, replacing token-based structures from 
-- token.cpp with a structured syntax tree.
------------------------------------------------------------
*/

#define Program "Program"
#define ExprStatement "ExprStatement"
#define Identifier "Identifier"
#define Literal "Literal"
#define BinaryExpression "BinaryExpression"
#define NullExpression "NullExpression"
#define PrintStatement "PrintStatement"
#define StoreVariable "StoreVariable"

#include "lexer.h"
#define IDENTIFIER {PRINT, LET, IF, ELSE, FOR, WHILE, FUNCTION, STRUCT, CLASS}
#define LITERAL {INT, FLOAT, VARIABLE}
#define NULL_EXPRESSION {NULL, SEMICOLON, EOF_T}

#include <vector>
#include <string>

using namespace std;

#ifndef AST_H
#define AST_H

struct statement {
    string type;
};

struct AST_Program : statement {
    string type = Program;
    vector<statement> statements;
};

struct AST_ExprStatement : statement {
    string type = ExprStatement;
};

struct AST_Identifier : AST_ExprStatement {
    string type = Identifier;
    string name;
};

struct AST_Literal : AST_ExprStatement {
    string type = Literal;
    float value;
};

struct AST_BinaryExpression : AST_ExprStatement {
    string type = BinaryExpression;
    string op;
    AST_ExprStatement left;
    AST_ExprStatement right;
};

struct AST_NullExpression : AST_ExprStatement {
    string type = NullExpression;
};

struct AST_PrintStatement : AST_ExprStatement {
    string type = PrintStatement;
    string output;
};

struct AST_StoreVariable : AST_ExprStatement {
    string name;
    AST_ExprStatement value;
};

static inline bool is_Tok_identifier(string tok);
static inline bool is_Tok_Literal(string tok);
static inline bool is_Tok_Null(string tok);

#endif