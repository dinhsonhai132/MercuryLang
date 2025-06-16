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

#include "../Mercury/compile.cpp"
#include "../Mercury/string.cpp"
#include "../Mercury/list.cpp"

#include <stdlib.h>
#include <algorithm>

using namespace std;

struct __program_bytecode {
    mCode_T &code;
    Mer_size_t lid;             // id of label
    hash_t hash;
    Mer_size_t glb_id;
    Mer_size_t lc_id;
    Mer_size_t iid;             // id of prg_code
    Mer_size_t oid;             // id of out_code
    Mer_uint8_t icode;          // cur code in prg_code
    Mer_uint8_t ocode;          // cur code in out_code
    unordered_map<Mer_uint8_t, Mer_size_t> label_map;
    Mer_size_t loop_size;
    bool is_in_func;
    const char *file;
    bool is_label = false;
};

__program_bytecode init_program_bytecode(mCode_T &code);

#define MERCURY_ADD_VALUE(stk, value) (stk->s_table->table.push_back(MerCompiler_table_setup(value)))
#define MERCURY_ADD_VALUE_ADDRESS(stk, value, address) (stk->s_table->table.push_back(MerCompiler_table_setup(value, address)))
#define POP_STACK(stk) pop_stack(stk)
#define EAT_STACK(stk) eat_stack(stk)
#define PUSH_STACK(stk, value) push_stack(stk, value)

MERCURY_API unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u, string mode);

MERCURY_API Mer_uint8_t __get_next_code_in_prg_code(__program_bytecode &u);
MERCURY_API Mer_uint8_t __get_next_code_in_out_code(__program_bytecode &u);

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_program(mCode_T &code);
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_statement(__program_bytecode &u, stack *stk);

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_PUSH_FLOAT(__program_bytecode &u, stack *stk);                           // 1
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_PUSH_NORMAL_MODE(__program_bytecode &u, stack *stk);//2
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_GLOBAL(__program_bytecode &u, stack *stk); // 3
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op); // 4
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op);// 5
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk); // 6
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk); // 7
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_FUNCTION_CALL(__program_bytecode &u, stack *stk); // 8
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_JUMP_IF_FALSE(__program_bytecode &u, stack *stk); // 9
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_BUILD_LIST(__program_bytecode &u, stack *stk); // 10
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_GET_ITEM(__program_bytecode &u, stack *stk); // 11
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_STORE_INDEX(__program_bytecode &u, stack *stk); // 12
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_CLEN(__program_bytecode &u, stack *stk); // 13
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_JUMP_TO(__program_bytecode &u, stack *stk); // 14
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk); // 15
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_TRUE(__program_bytecode &u, stack *stk); // 15
MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_FALSE(__program_bytecode &u, stack *stk); // 16

#endif // MERCURY_EVALUATE_H