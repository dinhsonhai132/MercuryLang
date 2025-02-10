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
    size_t tok_idx;
    string source;
    token get_current_token() { if (tok_idx < tokens.size() && tok_idx >= 0) return tokens[tok_idx]; };
    token get_next_token() { if (tok_idx + 1 < tokens.size() && tok_idx + 1 >= 0) return tokens[tok_idx++]; };
    void jump_ntok() { if (tok_idx < tokens.size() && tok_idx >= 0) tokens[tok_idx++]; };
    bool is_CurTokEOF(string tok) { return tok == EOF_T; };

public:
    AST_Program AST_tokenize(string source);
    AST_node AST_nodeize(token tok);
    AST_PrintState parse_print();
    AST_Statement parse_statment();
    AST_BinExpression parse_expr();
};

#endif