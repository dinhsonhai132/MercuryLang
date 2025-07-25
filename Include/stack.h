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

#ifndef MERCURY_STACK_CORE_HEADER
#define MERCURY_STACK_CORE_HEADER

#include <cstddef>
#include <string>
#include <vector>
#include <cstdint>

#include "Mercury.h"

using namespace std;

#define OTHER \
    bool is_in_glb; \
    bool is_in_lc; \
    Mer_uint8_t address_of; \


#define HEAD_OBJ \
    mObject_T *f_address; \
    mObject_T *f_type; \
    mObject_T *f_name; \
    mObject_T *f_value; \
    mObject_T *f_size; \
    mObject_T *f_local; \
    mObject_T *f_global; \
    mObject_T *f_string; \
    mObject_T *f_hash; \
    mObject_T *f_error;

#define FLAG \
    bool is_str; \
    bool is_var; \
    bool is_func; \
    bool is_code; \
    bool is_type; \
    bool is_iter; \
    bool is_bool; \
    bool is_list; \
    bool is_obj; \
    bool is_opcode;

#define HEAD_VALUE \
    mString_T *f_str_v; \
    mVariable_T *var_v; \
    mFunc_T func_v; \
    mBool_T *bool_v; \
    mCode_T *code_v; \
    mIter_T *iter_v; \
    mList_T *list_v; \
    mObject_T *obj_v; \
    mOpCode_T *opcode_v; \
    mFunc_object_T *func_obj_v; \

#define HEAD_STACK \
    Mer_number_t cbuf; \
    Mer_number_t value; \
    Mer_number_t cval; \
    Mer_index_t size; \
    Mer_index_t cidx; \
    Mer_uint8_t address; \
    Mer_real_string name; \
    Mer_real_string type; \
    Mer_real_string str_v; \
    Mer_real_string err; \
    Mer_flag_t is_builtin; \
    Mer_flag_t is_same; \
    Mer_flag_t is_local; \
    vector<Mer_uint8_t> tbody;

typedef struct __table
{
    int ref_count = 0;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER
    vector<__table *> table;

} table;

typedef struct __symboltable
{
    int ref_count = 0;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER
    table *tab;
} symtable;

typedef struct __stack
{
    table *s_table;
    symtable *s_symtable;
    symtable *s_global;
    symtable *s_local;

    size_t code_idx; // Debug
    string code_name; // Debug
    Mer_uint8_t raw_debug; // Debug
} stack;

typedef struct __call_context {
    mCode_T &code;
    
    Mer_uint8_t address;
    __call_context *caller;

    table* return_val;

    mFunc_object_T* func_obj;

    vector<symtable *> local;
} CallContext;

#define incr_stk_idx(stk) \
    stk->code_idx++; \

stack *MerCompiler_Stack_new(void);
table *MerCompiler_Table_new(void);
symtable *MerCompiler_SymbolTable_new(void);

int MerCompiler_free_stack(stack *s);
int MerCompiler_free_table(table *t);
int MerCompiler_free_symboltable(symtable *s);

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy);
table *MerCompiler_table_setup(float cval, uint8_t address = 0x00);
symtable *MerCompiler_symboltable_setup(string name, float value, string type, uint8_t address);
table *pop_stack(stack *stk);
table *eat_stack(stack *stk);

#define STACK_PUSH(stk, value) \
    stk->s_table->table.push_back(value);

#define STACK_POP(stk) \
    stk->s_table->table.pop_back();

#define STACK_VAL(a) \
    MerCompiler_table_setup(a, NULL_UINT_8_T);

#endif // MERCURY_STACK_CORE_HEADER
