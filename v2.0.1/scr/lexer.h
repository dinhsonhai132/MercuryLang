#ifndef MERCURY_LEXER_TOKENIZE_HEADER_FILE
#define MERCURY_LEXER_TOKENIZE_HEADER_FILE

#include <string>
#include <vector>
#include <iostream>
using namespace std;

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
#define DO "DO"
#define END "END"
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
#define EXTERN "EXTERN"
#define USING "USING"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"

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

#define MAX 1024

#define LITERAL {INT_, FLOAT_, DOUBLE_}
#define IDENTIFIER {DIV, MOD, PLUS, TIME, MINUS, VARIABLE}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT_, FLOAT_, DOUBLE_}
#define TYPE {INT_T, FLOAT_T, DOUBLE_T, CHAR_T, SHORT_T, LONG_T, AUTO_T, VOID_T, BOOL_T, STRING_T, STRUCT_T, CLASS_T}

#define isskippable(c) (\
    c == ' ' \
    || c == '\n' \
    || c == '\t' \
    || c == '\r' \
    || c == '\0')

#define is_potential_identifier_char(c) (c >= 'a' && c <= 'z' \
    || c >= 'A' && c <= 'Z' \
    || c == '_')

#define is_potential_literal_char(c) (c >= '0' && c <= '9' || c == '.')

#define is_digit(c) (c >= '0' && c <= '9')

static inline string get_1_char(char c);
static inline string get_2_char(char c1, char c2);
static inline string return_identifier(string iden);

static inline bool is_identifier(string iden);
static inline bool is_keyword(char c);
static inline bool Is_tok_type(string tok);
static inline bool Is_tok_identifier(string tok);
static inline bool Is_tok_literal(string tok);

struct token {
    string tok;
    string type;
    float value;

    string name;
    string symbol;
    string string_iden;

    token() : tok(""), type(""), value(0.0), name(""), symbol(""), string_iden("") {};
    token(string tok, string type, float value, string name, string symbol, string string_iden) : tok(tok), type(type), value(value), name(name), symbol(symbol), string_iden(string_iden) {}
};

static inline bool Is_tok_eof(token tok);
vector<token> MerLexer_tokenize(string source);

#endif // MERCURY_LEXER_TOKENIZE_HEADER_FILE