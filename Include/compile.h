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

#include "data.h"
#include "../Mercury/initialize.cpp"
#include "../Parser/parser.cpp"

using namespace std;

struct loop_stack {
    Mer_uint8_t continue_label;
    Mer_uint8_t break_label;
};

struct code_stack {
    Mer_uint8_t address;
    string name;
    mCode_T &code;
};

struct __compiler_u {
    const char* file;
    Mer_uint8_t address;
    Mer_uint8_t para_address;
    Mer_uint8_t cid;
    Mer_string name;
    bool is_in_func = false;
    Mer_string type;
    vector<loop_stack> loop;
};

__compiler_u compiler_init(void);

vector<string> import;
vector<code_stack> code_s;


#define INC_U(u) (u.byte++, u.cid++)

#define create_label(glb) ++glb.address
#define create_para(glb) ++glb.para_address

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_program(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_id(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_literal(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_binary_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_call(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_string_identifier(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_if(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_let(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_return(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_identifier(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_id_expression_statment(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_print(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_comparison_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_while(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_list(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_assign(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_string_var(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_array(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_extract(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_store_index_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_for_in_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_loop(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_break(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_continue(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_true(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_false(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_with_args(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_call_with_args(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_and_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_not_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_or_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_import(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_include(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_define(mAST_T *ast, __compiler_u &glb);

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_define_expression(mAST_T *ast, __compiler_u &glb);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
