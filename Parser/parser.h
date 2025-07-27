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
#include "ast.cpp"
#include "./lexer/lexer.cpp"

struct mParser_T {
    mLexer_T *lexer;
    mToken_T *token;
    mToken_T *next;
    bool is_eof = false;
};

static inline vector<string> para_temp = {};
static inline vector<string> lib_iden = {"print", "empty", "input", "to_list", "range", "type", "write", "sin", "cos", "tan", "cot", "sqrt", "split", "size", "pop", "watch", "puts", "push", "ch", "glb", "sub", "help", "exit", "pause", "eval", "cls", "same", "random", "randint", "sleep", "isdigit", "to_str", "to_int", "hash", "factorial"};

#define TRUE_LINE(parser) (parser->lexer->row)

mParser_T *_MerParser_new(void);
mParser_T *_MerParser_init(mLexer_T *lexer);
int _MerParser_free(mParser_T *parser);

mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right);

mAST_T *MerParser_parse_operator_expression(mAST_T *left, string op, mAST_T *right, string type);

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

mAST_T *MerParser_parse_while_statement(mParser_T *parser);

mAST_T *MerParser_parse_assignment_statement(mParser_T *parser);

mAST_T *MerParser_parse_string_expression(mParser_T *parser);

mAST_T *MerParser_parse_list_statement(mParser_T *parser);

mAST_T *MerParser_parse_variable_statement(mParser_T *parser);

mAST_T *MerParser_parse_extract_expression(mParser_T *parser);

mAST_T *MerParser_parse_string_statement(mParser_T *parser);

mAST_T *MerParser_parse_array_expression(mParser_T *parser);

mAST_T *MerParser_parse_for_statement(mParser_T *parser);

mAST_T *MerParser_parse_loop_statement(mParser_T *parser);

mAST_T *MerParser_parse_and_expression(mParser_T *parser);

mAST_T *MerParser_parse_or_expression(mParser_T *parser);

mAST_T *MerParser_parse_not_expression(mParser_T *parser);

mAST_T *MerParser_parse_logical_expression(mParser_T *parser);

mAST_T *MerParser_parse_import_statement(mParser_T *parser);

mAST_T *MerParser_parse_define_statement(mParser_T *parser);

mAST_T *MerParser_parse_parent_expression(mParser_T *parser);

mAST_T *MerParser_parse_dictionary_expression(mParser_T *parser);

mAST_T *MerParser_parse_include_statement(mParser_T *parser);

mAST_T *MerParser_parse_store_index_statement(mParser_T *parser, mAST_T *left);

#endif // MERCURY_PARSER_HEADER_FILE