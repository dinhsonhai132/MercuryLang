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

#ifndef MECURY_EVALUATE_H
#define MECURY_EVALUATE_H

#include "C:\MercuryLang\Mercury\compile.cpp"
#include "C:\MercuryLang\Mercury\stack.cpp"

#include <stdlib.h>

using namespace std;

#define MERCURY_ADD_VALUE(stk, value) (stk->s_table->table.push_back(MerCompiler_table_setup(value)))
#define MERCURY_ADD_VALUE_ADDRESS(stk, value, address) (stk->s_table->table.push_back(MerCompiler_table_setup(value, address)))

void push_stack(stack *stk, int value);
table *pop_stack(stack *stk);
table *eat_stack(stack *stk);

struct __program_bytecode {
    mCode_T &code;
    Mer_size_t lid;             // id of label
    Mer_size_t iid;             // id of prg_code
    Mer_size_t oid;             // id of out_code
    Mer_uint8_t icode;          // cur code in prg_code
    Mer_uint8_t ocode;          // cur code in out_code
    unordered_map<Mer_uint8_t, Mer_size_t> label_map;
    Mer_size_t loop_size;
};

unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u);

MERCURY_API Mer_uint8_t __get_next_code_in_prg_code(__program_bytecode &u);
MERCURY_API Mer_uint8_t __get_next_code_in_out_code(__program_bytecode &u);

MERCURY_API stack *eval_PUSH_FLOAT(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_LOAD_GLOBAL(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op);
MERCURY_API stack *eval_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op);
MERCURY_API stack *eval_STORE_GLOBAL(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_POP_JUMP_IF_TRUE(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_MAKE_BLOCK(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_MAKE_FUNCTION(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_FUNCTION_CALL(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_PRINT(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_JUMP_IF_FALSE(__program_bytecode &u, stack *stk);
MERCURY_API stack *eval_program(mCode_T &code);
MERCURY_API stack *eval_statement(__program_bytecode &u, stack *stk);

#endif // MERCURY_EVALUATE_H
