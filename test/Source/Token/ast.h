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

#define Program "Program";
#define ExprStatement "ExprStatement";
#define Identifier "Identifier";
#define Literal "Literal";
#define NumericLiteral "NumericLiteral";
#define StringLiteral "StringLiteral";


#include <vector>
#include <string>

using namespace std;

#ifndef AST_H
#define AST_H


struct statement {
    string type;
}

struct AST_Program {
    string type = Program;
    vector<statement> statements;
}

struct AST_ExprStatement : statement {
    string type = ExprStatement;
}

struct AST_Identifier : AST_ExprStatement {
    string type = Identifier;
    string name;
}

struct AST_Literal : AST_ExprStatement {
    string type = Literal;
    float value;
}

struct 

#endif