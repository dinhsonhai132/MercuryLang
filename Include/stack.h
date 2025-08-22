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
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER_STACK
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHER_STACKWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER_STACK DEALINGS IN THE
// SOFTWARE.

#ifndef MERCURY_STACK_CORE_HEADER
#define MERCURY_STACK_CORE_HEADER

#include <cstddef>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "Mercury.h"

using namespace std;

#define OTHER_STACK \
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
    bool is_str = false; \
    bool is_var = false; \
    bool is_instance = false; \
    bool is_func = false; \
    bool is_class = false; \
    bool is_code = false; \
    bool is_type = false; \
    bool is_iter = false; \
    bool is_bool = false; \
    bool is_list = false; \
    bool is_obj = false; \
    bool is_opcode = false;

#define HEAD_VALUE \
    mString_T *f_str_v; \
    mVariable_T *var_v; \
    mFunc_T func_v; \
    mBool_T *bool_v; \
    mCode_T *code_v; \
    mIter_T *iter_v; \
    mClass_T *class_ref; \
    mClass_T *class_v; \
    mList_T *list_v; \
    mObject_T *obj_v; \
    mOpCode_T *opcode_v; \
    mFunc_object_T *func_obj_v; \

#define HEAD_STACK \
    Mer_number_t cbuf = 0; \
    Mer_number_t value = 0; \
    Mer_number_t cval = 0; \
    Mer_index_t size = 0; \
    Mer_index_t cidx = 0; \
    Mer_uint8_t address = 0; \
    Mer_real_string name; \
    Mer_real_string type; \
    Mer_real_string str_v; \
    Mer_real_string err; \
    Mer_flag_t is_builtin = false; \
    Mer_flag_t is_same = false; \
    Mer_flag_t is_local = false; \
    vector<Mer_uint8_t> tbody;

typedef struct __table
{
    int ref_count = 0;
    bool gc_freed = false;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER_STACK
    vector<__table *> table;
    __table* class_p;

} table;

typedef struct __symboltable
{
    int ref_count = 0;
    bool gc_freed = false;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER_STACK
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
table *table_clone_shallow(table *dst, table *src);
void reset_table(table *t);
table *push_stack(stack *stk, table *t);

extern vector<table*> GARBAGE_POOL; 

#define STACK_PUSH(stk, value) \
    stk->s_table->table.push_back(value);

#define STACK_POP(stk) \
    stk->s_table->table.pop_back();

#define STACK_VAL(a) \
    MerCompiler_table_setup(a, NULL_UINT_8_T);

#endif // MERCURY_STACK_CORE_HEADER
