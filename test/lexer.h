/*
------------------------------------------------------------
-- Mercury Language - Lexer Header File                  --
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This file defines the lexer for Mercury Language. 
-- The lexer is responsible for tokenizing the source code 
-- into a sequence of tokens that the parser can process.
------------------------------------------------------------
*/

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INT "INT"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define DIV "DIV"
#define TIME "TIME"
#define VARIABLE "VARIABLE"
#define STRING "STRING"
#define PRINT "PRINT"
#define LET "LET"
#define DOT "DOT"
#define COMMA "COMMA"
#define ASSIGN "ASSIGN"
#define IF "IF"
#define ELSE "ELSE"
#define FOR "FOR"
#define WHILE "WHILE"
#define RETURN "RETURN"
#define FUNCTION "FUNCTION"
#define LEFT_PAREN "LEFT_PAREN"
#define RIGHT_PAREN "RIGHT_PAREN"
#define LEFT_BRACKET "LEFT_BRACKET"
#define RIGHT_BRACKET "RIGHT_BRACKET"
#define LEFT_BRACE "LEFT_BRACE"
#define RIGHT_BRACE "RIGHT_BRACE"
#define EQUAL "EQUAL"
#define NOT_EQUAL "NOT_EQUAL"
#define LESS "LESS"
#define LESS_EQUAL "LESS_EQUAL"
#define GREATER "GREATER"
#define GREATER_EQUAL "GREATER_EQUAL"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define BREAK "BREAK"
#define CONTINUE "CONTINUE"
#define CLASS "CLASS"
#define INTERFACE "INTERFACE"
#define STRUCT "STRUCT"
#define NEW "NEW"
#define DELETE "DELETE"
#define CAST "CAST"
#define FLOAT "FLOAT"
#define DOUBLE "DOUBLE"
#define CHAR "CHAR"
#define SHORT "SHORT"
#define LONG "LONG"
#define AUTO "AUTO"
#define VOID "VOID"
#define BOOL "BOOL"
#define SEMICOLON "SEMICOLON"
#define COLON "COLON"
#define ARROW "ARROW"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN "EXTERN"
#define USING "USING"
#define POW "POW"

#define MAX 1024

enum data_type {
    INT_T, FLOAT_T, DOUBLE_T, STRING_T, AUTO_T, NULL_T, VOID_T,
    BOOL_T, CHAR_T, SHORT_T, LONG_T, LITERAL_T,
    FUNCTION_T, ARRAY_T, STRUCT_T, POINTER_T, CLASS_T, INTERFACE_T
};

struct token {
    string tok;
    data_type type;
    float value;
    string name;

    token(string tok, data_type type, float value, string name)
        : tok(tok), type(type), value(value), name(name) {}
};

class lexer {
private:
    int idx;
    string source;
    vector<token> tokens;
public:
    lexer(string source) : source(source), idx(0) {}
    vector<token> tokenize();
};

static inline bool isskippable(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
};

static inline bool is_potential_identifier(char c) {
    return isalnum(c) || c == '_';
}

static inline string get_2_char(char c1, char c2) {
    switch(c1) {
        case '=': if (c2 == '=') return EQUAL; break;
        case '<': if (c2 == '=') return LESS_EQUAL;
                  if (c2 == '>') return NOT_EQUAL; break;
        case '>': if (c2 == '=') return GREATER_EQUAL; break;
        case '&': if (c2 == '&') return AND; break;
        case '|': if (c2 == '|') return OR; break;
        case '*': if (c2 == '*') return POW; break;
        case '!': if (c2 == '=') return NOT_EQUAL; break;
    }
    return "";
}

static inline string get_1_char(char c) {
    switch(c) {
        case '=': return EQUAL;
        case '<': return LESS;
        case '>': return GREATER;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return DIV;
        case '*': return TIME;
        case '!': return NOT;
        case '(': return LEFT_PAREN;
        case ')': return RIGHT_PAREN;
        case '{': return LEFT_BRACE;
        case '}': return RIGHT_BRACE;
        case '[': return LEFT_BRACKET;
        case ']': return RIGHT_BRACKET;
        case ',': return COMMA;
        case ';': return SEMICOLON;
        case ':': return COLON;
    }
    return "";
}

static inline bool is_keyword(char c) {
    vector<char> keyword = {'+', '-', '*', '/', '(', ')', '{', '}', '[', ']', ',', ';', ':'};
    for (char k : keyword) {
        if (c == k) return true;
    }
    return false;
}

#endif
