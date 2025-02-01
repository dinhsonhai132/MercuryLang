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
#define Identifier "Identifier";
#define Literal "Literal";
#define ExpressionStatement "ExpressionStatement";

#include <vector>
#include <string>

using namespace std;

#ifndef AST_H
#define AST_H


struct statement {
    string type;
}

struct program {
    string type = Program;
    vector<statement> statements;
}

struct expression_statement : program {
    string type = ExpressionStatement
}

struct identifier : expression_statement {
    string type = Identifier;
    string name;
}

struct literal : expression_statement {
    string type = Literal;
    string value;
}

#endif