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

#include "C:\MercuryLang\v2.0.1\Mercury\compile.cpp"
#include "C:\MercuryLang\v2.0.1\mercury\stack.cpp"

#include <stdlib.h>

using namespace std;

#define MERCURY_ADD_VALUE(stk, value) (stk->s_table->table.push_back(MerCompiler_table_setup(value)))
#define MERCURY_ADD_VALUE_ADDRESS(stk, value, address) (stk->s_table->table.push_back(MerCompiler_table_setup(value, address)))

#define IS_TRUE(x) ((x) != 0)
#define IS_FALSE(x) (!(x != 0))

void push_stack(stack *stk, int value);
table *pop_stack(stack *stk);
table *eat_stack(stack *stk);

struct __program_bytecode {
    mCode_T &code;
    Mer_size_t iid;             // id of prg_code
    Mer_size_t oid;             // id of out_code
    Mer_uint8_t icode;          // cur code in prg_code
    Mer_uint8_t ocode;          // cur code in out_code
};

MERCURY_API Mer_uint8_t __get_next_code_in_prg_code(__program_bytecode &u);
MERCURY_API Mer_uint8_t __get_next_code_in_out_code(__program_bytecode &u);
MERCURY_API stack *eval_program(mCode_T &code);
MERCURY_API stack *eval_statement(__program_bytecode &u, stack *stk);

#endif // MERCURY_EVALUATE_H
