/*
------------------------------------------------------------
-- Mercury Language - Parser Header File                 --
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This file defines the parser for Mercury Language. 
-- It processes tokens from the lexer and constructs an 
-- Abstract Syntax Tree (AST).
------------------------------------------------------------
*/

#ifndef PARSE_H
#define PARSE_H

#include "ast.h"
#include "lexer.h"

using namespace std;

class parse {
private:
    vector<token> tokens;
    lexer lex;
public:
    parse(string source) : source(source), lex(lex) {}
    
    program ast_program();
    expression_statement ast_statement();
    identifier ast_identifier();
    literal ast_literal();
    expression ast_expression();
};

#endif