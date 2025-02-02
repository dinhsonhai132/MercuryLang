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

#include "ast.cpp"
#include "lexer.cpp"

using namespace std;


class parse {
private:
    vector<token> tokens;
    size_t tok_idx;
    lexer lex;
    string source;

    token current_token() { return tokens[tok_idx]; };

    token next_token() { return tokens[tok_idx + 1]; };

    bool is_CurTok_Literal() { return is_Tok_Literal(current_token().tok) }

    bool is_CurTok_identifier() { return is_Tok_identifier(current_token().tok) }

    bool is_CurTokEOF() { return current_token().tok == EOF };

public:
    parse(string source) : source(source), lex(lex), tok_idx(0) {}
    
    AST_Program AST_tokenize();

    statement AST_statement();

    AST_ExprStatement AST_exprstatement();

    AST_ExprStatement AST_primary_expr();

    AST_Literal AST_parse_literal();
};

#endif