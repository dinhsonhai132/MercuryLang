// Copyright (c) 2025-present Dinh Son Hai

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MERCURY_TOKEN_HEADER_FILE
#define MERCURY_TOKEN_HEADER_FILE
#include <string>
#include <vector>
#include <iostream>
#include "C:\MercuryLang\Mercury\error.cpp"
#include "C:\MercuryLang\Parser\war.cpp"

using namespace std;

#define MAX_TOKEN_SIZE 1024

#define EOF_T "EOF"
#define EOL_T "EOL"
#define ASSIGN "ASSIGN"
#define MOD "MOD"
#define INT_ "INT_"
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
#define END_T "END_T"
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
#define DO_T "DO_T"
#define END_LINE "END_LINE"
#define BREAK "BREAK"
#define CONTINUE "CONTINUE"
#define CLASS "CLASS"
#define INTERFACE_ "INTERFACE_"
#define STRUCT "STRUCT"
#define NEW "NEW"
#define DELETE_ "DELETE_"
#define CAST "CAST"
#define FLOAT_ "FLOAT"
#define DOUBLE_ "DOUBLE"
#define CHAR_ "CHAR"
#define SHORT_ "SHORT"
#define LONG_ "LONG"
#define AUTO_ "AUTO"
#define VOID_ "VOID"
#define BOOL_ "BOOL"
#define SEMICOLON "SEMICOLON"
#define COLON "COLON"
#define ARROW "ARROW"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN_T "EXTERN_T"
#define USING "USING"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"
#define PLUS_PLUS "PLUS_PLUS"
#define MINUS_MINUS "MINUS_MINUS"
#define THEN "THEN"

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
#define INTERFACE__T "INTERFACE__T"

#define LITERAL {INT_, FLOAT_, DOUBLE_}
#define IDENTIFIER {DIV, MOD, PLUS, TIME, MINUS, VARIABLE}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT_, FLOAT_, DOUBLE_}
#define TYPE {INT_T, FLOAT_T, DOUBLE_T, CHAR_T, SHORT_T, LONG_T, AUTO_T, VOID_T, BOOL_T, STRING_T, STRUCT_T, CLASS_T}

#define is_tok_literal(tok) (\
    tok == INT_ \
    || tok == FLOAT_ \
    || tok == DOUBLE_ \
)

#define is_tok_identifier(tok) (\
    tok == DIV \
    || tok == MOD \
    || tok == PLUS \
    || tok == TIME \
    || tok == MINUS \
    || tok == VARIABLE \
)

#define is_tok_expr(tok) (\
    is_tok_literal(tok) \
    || is_tok_identifier(tok) \
)

#define is_tok_type(tok) (\
    tok == INT_T \
    || tok == FLOAT_T \
    || tok == DOUBLE_T \
    || tok == CHAR_T \
    || tok == SHORT_T \
    || tok == LONG_T \
    || tok == AUTO_T \
    || tok == VOID_T \
    || tok == BOOL_T \
    || tok == STRING_T \
)

#define isskippable(c) (\
    c == ' ' \
    || c == '\n' \
    || c == '\t' \
    || c == '\r' \
    || c == '\0')

#define is_potential_identifier_char(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')

#define is_potential_literal_char(c) (c >= '0' && c <= '9' || c == '.')

#define is_digit(c) (c >= '0' && c <= '9')

#define is_alpha(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')

#define is_alpha_num(c) (is_alpha(c) || is_digit(c))

#define is_keywords(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == ',' \
    || c == ':' || c == '=' || c == '!' || c == '%' \
    || c == '<' || c == '>' || c == '&' \
    || c == '|')

inline bool is_identifier(string c) {
    return (c == "LET")
    || (c == "PRINT")
    || (c == "IF")
    || (c == "DO")
    || (c == "END")
    || (c == "BREAK")
    || (c == "CONTINUE")
    || (c == "AUTO")
    || (c == "FLOAT")
    || (c == "DOUBLE")
    || (c == "CHAR")
    || (c == "SHORT")
    || (c == "LONG")
    || (c == "VOID")
    || (c == "BOOL")
    || (c == "STR")
    || (c == "STRING")
    || (c == "INCLUDE")
    || (c == "ELSE")
    || (c == "FOR")
    || (c == "WHILE")
    || (c == "RETURN")
    || (c == "FUNC")
    || (c == "CLASS")
    || (c == "STRUCT")
    || (c == "INTERFACE")
    || (c == "NEW")
    || (c == "DELETE")
    || (c == "CAST")
    || (c == "CONST")
    || (c == "THEN");
}

inline const char* GET_1_CHAR(char c) {
    switch (c) {
        case '=': return ASSIGN;
        case '<': return LESS;
        case '>': return GREATER;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return DIV;
        case '%': return MOD;
        case '*': return TIME;
        case '(': return LEFT_PAREN;
        case ')': return RIGHT_PAREN;
        case '{': return LEFT_BRACE;
        case '}': return RIGHT_BRACE;
        case '[': return LEFT_BRACKET;
        case ']': return RIGHT_BRACKET;
    }
    return NULL_T;
}


inline const char* GET_2_CHAR(char c1, char c2) {
    switch (c1) {
        case '=':
            if (c2 == '=') return EQUAL;
            break;
        case '<':
            if (c2 == '=') return LESS_EQUAL;
            break;
        case '>':
            if (c2 == '=') return GREATER_EQUAL;
            break;
        case '+':
            if (c2 == '+') return PLUS_PLUS;
            break;
        case '-':
            if (c2 == '-') return MINUS_MINUS;
            break;
        case '&':
            if (c2 == '&') return AND;
            break;
        case '|':
            if (c2 == '|') return OR;
            break;
        case '*':
            if (c2 == '*') return POW;
            break;
        case '!':
            if (c2 == '=') return NOT_EQUAL;
            break;
        case '/':
            if (c2 == '/') return COMMENT;
            break;
    }

    return NULL_T;
}

inline const char* GET_SYNTAX(string c) {
    if (c == "LET") return LET;
    else if (c == "PRINT") return PRINT;
    else if (c == "IF") return IF;
    else if (c == "ELSE") return ELSE;
    else if (c == "FOR") return FOR;
    else if (c == "WHILE") return WHILE;
    else if (c == "RETURN") return RETURN;
    else if (c == "FUNC") return FUNCTION;
    else if (c == "DO") return DO_T;
    else if (c == "END") return END_T;
    else if (c == "BREAK") return BREAK;
    else if (c == "CONTINUE") return CONTINUE;
    else if (c == "CLASS") return CLASS;
    else if (c == "INTERFACE") return INTERFACE_;
    else if (c == "STRUCT") return STRUCT;
    else if (c == "NEW") return NEW;
    else if (c == "DELETE") return DELETE_;
    else if (c == "CAST") return CAST;
    else if (c == "FLOAT") return FLOAT_;
    else if (c == "DOUBLE") return DOUBLE_;
    else if (c == "CHAR") return CHAR_;
    else if (c == "SHORT") return SHORT_;
    else if (c == "LONG") return LONG_;
    else if (c == "AUTO") return AUTO_;
    else if (c == "VOID") return VOID_;
    else if (c == "THEN") return THEN;
    else if (c == "ELSE") return ELSE;
    else if (c == "BOOL") return BOOL_;
    else if (c == "STR") return STRING;
    return NULL_T;
}

#define REGULAR_TOKEN 20
#define NONE_TOKEN 21

struct mToken_T {
    const char* tok;
    const char* type;
    float value;
    const char* name;
    const char* symbol;
    const char* string_iden;
    int tok_t;

    mToken_T *tok_stack[MAX_TOKEN_SIZE];
    size_t tok_stack_index;
};

mToken_T *_MerInit_token(const char* tok, const char* type, float value, const char* name, const char* symbol, const char* string_iden);
mToken_T *_MerToken_new(void);
int *_MerToken_free(mToken_T *token);

#endif // MERCURY_TOKEN_HEADER_FILE