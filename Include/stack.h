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

#define GC_HEAD \
    int ref_count = 1;

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
    bool is_list; \
    bool is_obj; \
    bool is_opcode;

#define HEAD_VALUE \
    mString_T *f_str_v; \
    mVariable_T *var_v; \
    mFunc_T func_v; \
    mCode_T *code_v; \
    mIter_T *iter_v; \
    mType_T *type_v; \
    mList_T *list_v; \
    mObject_T *obj_v; \
    mOpCode_T *opcode_v; \
    mFunc_object_T *func_obj_v; \

#define HEAD_STACK \
    float cval; \
    int cidx; \
    float cbuf; \
    uint8_t address; \
    string err; \
    bool is_builtin; \
    string name; \
    float value; \
    int size; \
    bool is_same; \
    string type; \
    bool is_local; \
    Mer_real_string str_v; \
    vector<uint8_t> tbody;


typedef struct __table
{
    GC_HEAD
    HEAD_STACK 
    HEAD_OBJ
    HEAD_VALUE
    FLAG
    OTHER
    vector<__table *> table;
} table;

typedef struct __symboltable
{
    GC_HEAD
    HEAD_STACK;
    HEAD_OBJ;
    HEAD_VALUE;
    FLAG
    OTHER
    table *tab;
} symtable;

typedef struct __stack
{
    string code;
    string bcode;
    int cvalue;
    string iden;
    string err;

    table *s_table;
    symtable *s_symtable;
    symtable *s_global;
    symtable *s_local;
} stack;

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
void push_stack(stack *stk, int value);

#endif // MERCURY_STACK_CORE_HEADER
