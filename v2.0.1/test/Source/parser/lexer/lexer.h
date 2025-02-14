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

// define token types
#define EOF_T "EOF"
#define ASSGNMENT "ASSIGNMENT"
#define MOD "MOD"
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
#define CONST "CONST"

#define MAX 1024

// define data type
#define INT_T "INT_T"
#define FLOAT_T "FLOAT_T"
#define DOUBLE_T "DOUBLE_T"
#define STRING_T "STRING_T"
#define AUTO_T "AUTO_T"
#define NULL_T "NULL_T"
#define VOID_T "VOID_T"
#define BOOL_T "BOOL_T"
#define CHAR_T "CHAR_T"
#define SHORT_T "SHORT_T"
#define LONG_T "LONG_T"
#define LITERAL_T "LITERAL_T"
#define FUNCTION_T "FUNCTION_T"
#define ARRAY_T "ARRAY_T"
#define STRUCT_T "STRUCT_T"
#define POINTER_T "POINTER_T"
#define CLASS_T "CLASS_T"
#define INTERFACE_T "INTERFACE_T"

struct token
{
    string tok;
    string type;
    float value;

    string name;
    string symbol;
    string string_iden;

    token(string tok, string type, float value, string name, string symbol, string string_iden)
        : tok(tok), type(type), value(value), name(name), symbol(symbol), 
        string_iden(string_iden) {}
};

static inline bool isskippable(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
};

static inline bool is_potential_identifier_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static inline string get_2_char(char c1, char c2)
{
    switch (c1)
    {
    case '=':
        if (c2 == '=')
            return EQUAL;
        break;
    case '<':
        if (c2 == '=')
            return LESS_EQUAL;
        if (c2 == '>')
            return NOT_EQUAL;
        break;
    case '>':
        if (c2 == '=')
            return GREATER_EQUAL;
        break;
    case '&':
        if (c2 == '&')
            return AND;
        break;
    case '|':
        if (c2 == '|')
            return OR;
        break;
    case '*':
        if (c2 == '*')
            return POW;
        break;
    case '!':
        if (c2 == '=')
            return NOT_EQUAL;
        break;
    }
    return "";
}

static inline string get_1_char(char c)
{
    switch (c) {
        case '=':
            return ASSGNMENT;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return DIV;
        case '*':
            return TIME;
        case '!':
            return NOT;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '[':
            return LEFT_BRACKET;
        case ']':
            return RIGHT_BRACKET;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case ':':
            return COLON;
        case '.':
            return DOT;
        case '%':
            return MOD;
    }

    return "";
}

static inline bool is_identifier(string iden)
{
    vector<string> state = {"LET", "PRINT", "IF", "ELSE", "FOR",
                            "WHILE", "RETURN", "FUNC", "INT", "FLOAT", "DOUBLE", "CHAR",
                            "SHORT", "LONG", "AUTO", "VOID", "BOOL", "CHAR", "STRING",
                            "STRUCT", "CLASS", "INTER", "NEW", "DELETE", "CAST",
                            "TRUE", "FALSE", "BREAK", "CONTINUE"};
    for (string s : state)
    {
        if (iden == s)
            return true;
    }
    return false;
}

static inline string return_identifier(string iden) {
    if (iden == "LET")
        return LET;
    else if (iden == "PRINT")
        return PRINT;
    else if (iden == "IF")
        return IF;
    else if (iden == "ELSE")
        return ELSE;
    else if (iden == "FOR")
        return FOR;
    else if (iden == "WHILE")
        return WHILE;
    else if (iden == "RETURN")
        return RETURN;
    else if (iden == "FUNC")
        return FUNCTION;
    else if (iden == "INT")
        return INT;
    else if (iden == "FLOAT")
        return FLOAT;
    else if (iden == "DOU")
        return DOUBLE;
    else if (iden == "CHAR")
        return CHAR;
    else if (iden == "SHORT")
        return SHORT;
    else if (iden == "LONG")
        return LONG;
    else if (iden == "AUTO")
        return AUTO;
    else if (iden == "VOID")
        return VOID;
    else if (iden == "BOOL")
        return BOOL;
    else if (iden == "CHAR")
        return CHAR;
    else if (iden == "STR")
        return STRING;
    else if (iden == "STRUCT")
        return STRUCT;
    else if (iden == "CLASS")
        return CLASS;
    else if (iden == "INTER")
        return INTERFACE;
    else if (iden == "NEW")
        return NEW;
    else if (iden == "DEL")
        return DELETE;
    else if (iden == "CAST")
        return CAST;
    else if (iden == "TRUE")
        return TRUE;
    else if (iden == "FALSE")
        return FALSE;
    else if (iden == "BRK")
        return BREAK;
    else if (iden == "CONT")
        return CONTINUE;
    else if (iden == "INC")
        return INCLUDE;
    else if (iden == "EXT")
        return EXTERN;
    else if (iden == "USING")
        return USING;
    else if (iden == "CONS") {
        return CONST;
    } else
        return "";
}

static inline bool is_keyword(char c)
{
    vector<char> keyword = {
        '+', '-', '*', '/', '(', ')', '{', '}',
        '[', ']', ',', ';', ':', '=', '!', '<',
        '>', '&', '|'};
    for (char k : keyword)
    {
        if (c == k)
            return true;
    }
    return false;
}

vector<token> MerLexer_tokenize(string source);

#endif