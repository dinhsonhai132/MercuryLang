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

#ifndef MERCURY_BYTECODE_COMPILER_HEADER
#define MERCURY_BYTECODE_COMPILER_HEADER

#include <cstdint>
#include <string>
#include <cstring>
#include <iomanip>
#include "C:\MercuryLang\v2.0.1\Mercury\include\Mercury.h"

using namespace std;

struct compiler_unit
{
    Mer_uint8_t cline;
    Mer_uint8_t code;
    Mer_uint8_t cbyte;
    Mer_uint8_t address;
    string name;
    vector<Mer_uint8_t> buff;
    vector<compiler_unit> status;
};

compiler_unit init_bc_mode_tok(void);

vector<Mer_uint8_t> MerCompiler_compile_ast_program(mAST_T *ast);
vector<Mer_uint8_t> MerCompiler_compile_ast_statement(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_let_statement(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_literal(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_identifer(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_if_statement(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_binary_expression(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_function(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_function_call(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_return_statement(mAST_T *ast, compiler_unit &prog);
vector<Mer_uint8_t> MerCompiler_compile_ast_comparison_expression(mAST_T *ast, compiler_unit &prog);

mCode_T MVM_id(mAST_T *ast, mCode_T &code);
mCode_T MVM_literal(mAST_T *ast, mCode_T &code);
mCode_T MVM_binary_expression(mAST_T *ast, mCode_T &code);
mCode_T MVM_function_call(mAST_T *ast, mCode_T &code);
mCode_T MVM_if(mAST_T *ast, mCode_T &code);
mCode_T MVM_let(mAST_T *ast, mCode_T &code);
mCode_T MVM_return(mAST_T *ast, mCode_T &code);
mCode_T MVM_identifier(mAST_T *ast, mCode_T &code);
mCode_T MVM_program(mAST_T *ast, mCode_T &code);
mCode_T MVM_id_expression_statment(mAST_T *ast, mCode_T &code);
mCode_T MVM_function(mAST_T *ast, mCode_T &code);
mCode_T MVM_comparison_expression(mAST_T *ast, mCode_T &code);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
