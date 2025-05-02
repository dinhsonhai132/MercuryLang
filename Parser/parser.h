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

#ifndef MERCURY_PARSER_HEADER_FILE
#define MERCURY_PARSER_HEADER_FILE

#include <iostream>
#include <vector>
#include <string>
#include "C:\MercuryLang\Parser\ast.cpp"
#include "C:\MercuryLang\Parser\lexer\lexer.cpp"
#include "C:\MercuryLang\Parser\lexer\buffer.cpp"

struct mParser_T {
    mLexer_T *lexer;
    mToken_T *token;
};

mParser_T *_MerParser_new(void);
mParser_T *_MerParser_init(mLexer_T *lexer);
int _MerParser_free(mParser_T *parser);

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
mAST_T *MerParser_parse_return_statement(mParser_T *parser);
mAST_T *MerParser_parse_comparison_expression(mParser_T *parser);
mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right);
mAST_T *MerParser_parse_if_statement(mParser_T *parser);
mAST_T *MerParser_parse_print_statement(mParser_T *parser);
// mAST_T *MerParser_parse_while_statement(mParser_T *parser);
// mAST_T *MerParser_parse_for_statement(mParser_T *parser);

#endif // MERCURY_PARSER_HEADER_FILE