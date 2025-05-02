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
#include "Mercury.h"
#include "C:\MercuryLang\Parser\parser.cpp"

using namespace std;

struct __compiler_u {
    Mer_uint8_t address;
    Mer_uint8_t line;
    Mer_uint8_t byte;
    Mer_uint8_t cid;
    Mer_string name;
    Mer_string type;
    GlobalTable tb;
};

MERCURY_API __Mer_return_Code MVM_program(mAST_T *ast);
MERCURY_API __Mer_return_Code MVM_id(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_literal(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_binary_expression(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_function_call(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_if(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_let(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_return(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_identifier(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_id_expression_statment(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_function(mAST_T *ast, __compiler_u &glb);
MERCURY_API __Mer_return_Code MVM_comparison_expression(mAST_T *ast, __compiler_u &glb);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
