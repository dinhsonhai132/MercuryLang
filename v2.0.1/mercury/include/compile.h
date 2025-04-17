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
#include "C:\MercuryLang\v2.0.1\parser\parser.cpp"

using namespace std;

#define CPUSH_FLOAT              0x01
#define CPUSH_NORMAL_MODE        0x02
#define CPUSH_TEMP_MODE          0x03

#define CLOAD_GLOBAL             0x04
#define CSTORE_GLOBAL            0x05

#define CEQUAL                   0xE3
#define CNOT_EQUAL               0xE4
#define CLESS                    0xE5
#define CLESS_EQUAL              0xE6
#define CGREATER                 0xE7
#define CGREATER_EQUAL           0xE8
#define CNOT                     0xE9
#define CAND                     0xEA
#define COR                      0xEC
#define CNOT_OR                  0xED
#define CAND_OR                  0xEE
#define CNOT_AND_OR              0xEF

#define CPOP_NORMAL_MODE         0x06
#define CPOP_TEMP_MODE           0x07

#define CPROGRAM_START           0xA1
#define CPROGRAM_END             0xFF

#define CBINARY_ADD              0xB1
#define CBINARY_SUB              0xB2
#define CBINARY_MUL              0xB3
#define CBINARY_DIV              0xB4

#define CMAKE_FUNCTION           0xC1
#define CFUNCTION_CALL           0xC2

#define CRETURN                  0xF1

struct bc_mode_tok {
    uint8_t cline;
    uint8_t code;
    uint8_t cbyte;
    uint8_t address;
    string name;
    vector<uint8_t> buff;
    vector<bc_mode_tok> status;
};

bc_mode_tok init_bc_mode_tok(void);

vector<uint8_t> MerCompiler_compile_ast_program(mAST_T *ast);
vector<uint8_t> MerCompiler_compile_ast_statement(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_let_statement(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_literal(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_identifer(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_binary_expression(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_function(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_function_call(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_return_statement(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_comparison_expression(mAST_T *ast, bc_mode_tok &prog);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
