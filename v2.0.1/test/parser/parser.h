#ifndef MERCURY_PARSER_HEADER_FILE
#define MERCURY_PARSER_HEADER_FILE

#include <iostream>
#include <vector>
#include <string>
#include "C:\MercuryLang-main\v2.0.1\parser\ast.cpp"
#include "C:\MercuryLang-main\v2.0.1\parser\lexer\lexer.cpp"
#include "C:\MercuryLang-main\v2.0.1\parser\lexer\buffer.cpp"

struct mParser_T {
    mLexer_T *lexer;
    mToken_T *token;
};

mParser_T *_MerParser_new(void);
mParser_T *_MerParser_init(mLexer_T *lexer);
mParser_T *_MerParser_free(mParser_T *parser);

mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right);
mAST_T *MerParser_parse_program(mParser_T *parser);
mAST_T *MerParser_parse(mParser_T *parser);
mAST_T *MerParser_parse_primary_expression(mParser_T *parser);
mAST_T *MerParser_parse_additive_expression(mParser_T *parser);
mAST_T *MerParser_parse_multiplicative_expression(mParser_T *parser);
mAST_T *MerParser_parse_expression_statement(mParser_T *parser);
mAST_T *MerParser_parse_let_statement(mParser_T *parser);
mAST_T *MerParser_parse_function_statement(mParser_T *parser);
mAST_T *MerParser_parse_function_call_expression(mParser_T *parser);

#endif // MERCURY_PARSER_HEADER_FILE