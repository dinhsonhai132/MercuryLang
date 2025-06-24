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
#include "syntax.cpp"
#include "../../Parser/error.cpp"
#include "../../Mercury/error.cpp"

using namespace std;

#define MAX_TOKEN_SIZE 1024

#define EOF_T "EOF"
#define EOL_T "EOL"
#define ASSIGN "ASSIGN"
#define MOD "MOD"
#define IS "IS"
#define INT_ "INT_"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define STR "STR"
#define LIST "LIST"
#define EXTRACT "EXTRACT"
#define DIV "DIV"
#define TIME "TIME"
#define VARIABLE "VARIABLE"
#define STRING "STRING"
#define LET "LET"
#define IS "IS"
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
#define ASSERT "ASSERT"
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
#define LOOP "LOOP"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN_T "EXTERN_T"
#define USING "USING"
#define VOID_T "VOID_T"
#define TRUE_T "TRUE_T"
#define FALSE_T "FALSE_T"
#define BREAK_T "BREAK_T"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"
#define PLUS_PLUS "PLUS_PLUS"
#define MINUS_MINUS "MINUS_MINUS"
#define THEN "THEN"
#define IN "IN"
#define PLUS_EQUAL "PLUS_EQUAL"
#define MINUS_EQUAL "MINUS_EQUAL"
#define TIMES_EQUAL "TIMES_EQUAL"
#define DIV_EQUAL "DIV_EQUAL"
#define MOD_EQUAL "MOD_EQUAL"

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
    tok == EOF_T \
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
    || c == '<' || c == '>' || c == '&' || c == '\\' \
    || c == '^' || c == ';' || c == '!' \
    || c == '[' || c == ']' || c == '.' \
    || c == '|')


#ifdef MERCURY_LANG3
inline bool is_identifier(string c) {
    return (c == "let")
    || (c == "if")
    || (c == "do")
    || (c == "end")
    || (c == "function")
    || (c == "break")
    || (c == "continue")
    || (c == "auto")
    || (c == "is")
    || (c == "float")
    || (c == "double")
    || (c == "char")
    || (c == "list")
    || (c == "short")
    || (c == "true")
    || (c == "false")
    || (c == "long")
    || (c == "void")    
    || (c == "bool")
    || (c == "str")
    || (c == "string")
    || (c == "loop")
    || (c == "not")
    || (c == "include")
    || (c == "else")
    || (c == "for")
    || (c == "while")
    || (c == "local")
    || (c == "assert")
    || (c == "in")
    || (c == "return")
    || (c == "func")
    || (c == "class")
    || (c == "struct")
    || (c == "interface")
    || (c == "new")
    || (c == "delete")
    || (c == "cast")
    || (c == "const")
    || (c == "and")
    || (c == "or")
    || (c == "not")
    || (c == "then");
}

inline const char* GET_SYNTAX(string c) {
    if (c == "let" || c == "local") return LET;
    else if (c == "if") return IF;
    else if (c == "else") return ELSE;
    else if (c == "for") return FOR;
    else if (c == "while") return WHILE;
    else if (c == "in") return IN;
    else if (c == "not") return NOT;
    else if (c == "return") return RETURN;
    else if (c == "assert") return ASSERT;
    else if (c == "func" || c == "function") return FUNCTION;
    else if (c == "include") return INCLUDE;
    else if (c == "and") return AND;
    else if (c == "true") return TRUE_T;
    else if (c == "false") return FALSE_T;
    else if (c == "or") return OR;
    else if (c == "do") return DO_T;
    else if (c == "is") return IS;
    else if (c == "end") return END_T;
    else if (c == "break") return BREAK;
    else if (c == "loop") return LOOP;
    else if (c == "continue") return CONTINUE;
    else if (c == "class") return CLASS;
    else if (c == "interface") return INTERFACE_;
    else if (c == "struct") return STRUCT;
    else if (c == "new") return NEW;
    else if (c == "list") return LIST;
    else if (c == "delete") return DELETE_;
    else if (c == "cast") return CAST;
    else if (c == "void") return VOID_T;
    else if (c == "double") return DOUBLE_;
    else if (c == "char") return CHAR_;
    else if (c == "short") return SHORT_;
    else if (c == "long") return LONG_;
    else if (c == "auto") return AUTO_;
    else if (c == "then") return THEN;
    else if (c == "else") return ELSE;
    else if (c == "bool") return BOOL_;
    else if (c == "string") return STR;
    return NULL;
}
#else

inline bool is_identifier(const std::string& c) {
    return (c == LET_S)
    || (c == IF_S)
    || (c == LOCAL_S)
    || (c == DO_S)
    || (c == END_S)
    || (c == BREAK_S)
    || (c == CONTINUE_S)
    || (c == AUTO_S)
    || (c == FLOAT_S)
    || (c == DOUBLE_S)
    || (c == CHAR_S)
    || (c == LIST_S)
    || (c == ASSERT_S)
    || (c == NOT_S)
    || (c == AND_S)
    || (c == OR_S)
    || (c == SHORT_S)
    || (c == IS_S)
    || (c == LONG_S)
    || (c == VOID_S)
    || (c == BOOL_S)
    || (c == STR_S)
    || (c == LOOP_S)
    || (c == STRING_S)
    || (c == INCLUDE_S)
    || (c == ELSE_S)
    || (c == FOR_S)
    || (c == WHILE_S)
    || (c == RETURN_S)
    || (c == FUNCTION_S)
    || (c == IN_S)
    || (c == CLASS_S)
    || (c == STRUCT_S)
    || (c == INTERFACE_S)
    || (c == NEW_S)
    || (c == DELETE_S)
    || (c == CAST_S)
    || (c == CONST_S)
    || (c == THEN_S);
}

inline const char* GET_SYNTAX(const std::string& c) {
    if (c == LET_S || c == LOCAL_S) return LET;
    else if (c == IF_S) return IF;
    else if (c == ELSE_S) return ELSE;
    else if (c == FOR_S) return FOR;
    else if (c == WHILE_S) return WHILE;
    else if (c == IN_S) return IN;
    else if (c == NOT_S) return NOT;
    else if (c == LOOP_S) return LOOP;
    else if (c == RETURN_S) return RETURN;
    else if (c == FUNCTION_S) return FUNCTION;
    else if (c == IS_S) return IS;
    else if (c == DO_S) return DO_T;
    else if (c == END_S) return END_T;
    else if (c == INCLUDE_S) return INCLUDE;
    else if (c == AND_S) return AND;
    else if (c == OR_S) return OR;
    else if (c == BREAK_S) return BREAK;
    else if (c == CONTINUE_S) return CONTINUE;
    else if (c == CLASS_S) return CLASS;
    else if (c == INTERFACE_S) return INTERFACE_;
    else if (c == STRUCT_S) return STRUCT;
    else if (c == NEW_S) return NEW;
    else if (c == LIST_S) return LIST;
    else if (c == DELETE_S) return DELETE_;
    else if (c == CAST_S) return CAST;
    else if (c == FLOAT_S) return FLOAT_;
    else if (c == DOUBLE_S) return DOUBLE_;
    else if (c == CHAR_S) return CHAR_;
    else if (c == SHORT_S) return SHORT_;
    else if (c == LONG_S) return LONG_;
    else if (c == AUTO_S) return AUTO_;
    else if (c == VOID_S) return VOID_T;
    else if (c == THEN_S) return THEN;
    else if (c == BOOL_S) return BOOL_;
    else if (c == STRING_S) return STR;
    return NULL_T;
}
#endif

inline const char* GET_1_CHAR(char c) {
    switch (c) {
        case '=': return ASSIGN;
        case '<': return LESS;
        case '>': return GREATER;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return DIV;
        case ';': return SEMICOLON;
        case ':': return COLON;
        case '!': return NOT;
        case ',': return COMMA;
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
            if (c2 == '=') return PLUS_EQUAL;
            break;
        case '-':
            if (c2 == '-') return MINUS_MINUS;
            if (c2 == '=') return MINUS_EQUAL;
            break;
        case '&':
            if (c2 == '&') return AND;
            break;
        case '|':
            if (c2 == '|') return OR;
            break;
        case '*':
            if (c2 == '*') return POW;
            if (c2 == '=') return TIMES_EQUAL;
            break;
        case '!':
            if (c2 == '=') return NOT_EQUAL;
            break;
        case '/':
            if (c2 == '/') return COMMENT;
            if (c2 == '=') return DIV_EQUAL;
            break;
        case '%':
            if (c2 == '=') return MOD_EQUAL;
            break;
    }

    return 0;
}

#define REGULAR_TOKEN 20
#define NONE_TOKEN 21

struct mToken_T {
    const char* tok;
    mToken_T *next;
    const char* type;
    float value;
    size_t index;
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
