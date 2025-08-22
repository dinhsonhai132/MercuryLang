#ifndef MERCURY_MARCO_HEADER_FILE
#define MERCURY_MARCO_HEADER_FILE

#include <string>
#include <cmath>
#include "opcode.h"
#include "type.h"
#include "define.h"

#ifdef str
#undef str
#endif

#define TO_STRING(x) std::to_string(x).c_str()

#define MAX_FLOAT 3.4028235e+38
#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : MAX_FLOAT)
#define MERCURY_BINARY_POW(c1, c2) (powf((c1), (c2)))
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))
#define MERCURY_BINARY_MOD(c1, c2) ((c1) % (c2))
#define MERCURY_BINARY_AND(c1, c2) ((c1) & (c2))
#define MERCURY_BINARY_OR(c1, c2) ((c1) | (c2))
#define MERCURY_BINARY_XOR(c1, c2) ((c1) ^ (c2))
#define MERCURY_BINARY_SHL(c1, c2) ((c1) << (c2))
#define MERCURY_BINARY_SHR(c1, c2) ((c1) >> (c2))
#define MERCURY_BINARY_NOT(c1) (~(c1))
#define MERCURY_BINARY_GREATER(c1, c2) ((c1) > (c2))
#define MERCURY_BINARY_LESS(c1, c2) ((c1) < (c2))
#define MERCURY_BINARY_GREATER_EQUAL(c1, c2) ((c1) >= (c2))
#define MERCURY_BINARY_LESS_EQUAL(c1, c2) ((c1) <= (c2))
#define MERCURY_BINARY_EQUAL(c1, c2) ((c1) == (c2))
#define MERCURY_BINARY_NOT_EQUAL(c1, c2) ((c1) != (c2))
#define MERCURY_INSERT(code, ins, size) code.insert(code.end(), ins, ins + size);
#define MERCURY_PUSH(code, ins) code.push_back(ins);
#define MERCURY_POP(code) code.pop_back();
#define INCREMENT(var) var++;
#define DECREMENT(var) var--;
#define INCREMENT_BY(var, value) var += value;
#define DECREMENT_BY(var, value) var -= value;
#define INCR_BYTE_uint8_t(var) var += 0x0001;
#define DECR_BYTE_uint8_t(var) var -= 0x0001;
#define INCR_BYTE_uint16_t(var) var += 0x0001;
#define DECR_BYTE_uint16_t(var) var -= 0x0001;
#define INCR_BYTE_uint32_t(var) var += 0x0001;
#define DECR_BYTE_uint32_t(var) var -= 0x0001;

#define stack_push(val) push_stack(stk, val)

#define stack_pop() (stk->s_table->table.pop_back())

#define MER_VALUE(val) MerCompiler_table_setup(val, NULL_UINT_8_T)
#define NULL_VALUE value(0)

#define CHECK 1
#define CONST_M(x) const x
#define IS_TRUE(x) ((x) == 1)
#define IS_FALSE(x) ((x) == 0)
#define TRUE_MARCO 1
#define NULL_MARCO 0
#define INLINE(x) inline x
#define CONSTEXPR(x) constexpr x
#define EXTERN(x) extern x

#define both(a, b) (a && b)
#define tstr(a) ((a)->is_str)
#define tlist(a) ((a)->is_list)
#define trbool(a) (a->is_bool)
#define tfunc(a) (a->is_func)
#define both_list(a, b) (both(tlist(a), tlist(b)))
#define both_str(a, b) (both(tstr(a), tstr(b)))
#define both_func(a, b) (both(tfunc(a), tfunc(b)))
#define both_bool(a, b) (both(trbool(a), trbool(b)))

#define push_true_to_stack()                        \
    table *true_value = MerCompiler_Table_new();      \
    true_value->bool_v = MerCompiler_bool_new();      \
    true_value->bool_v->value = true;                 \
    true_value->is_bool = true;                       \
    true_value->cval = 1;                             \
    stack_push(true_value);                           \

#define push_false_to_stack()                       \
    table *false_value = MerCompiler_Table_new();      \
    false_value->bool_v = MerCompiler_bool_new();      \
    false_value->bool_v->value = false;                \
    false_value->is_bool = true;                       \
    false_value->cval = 0;                             \
    stack_push(false_value);                           
    

#define TRUE_VALUE                                  \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = true;                 \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 1;                             \

#define FALSE_VALUE                                 \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = false;                \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 0;                             \

#define MERCURY_ADD_VALUE(stk, value) (stk->s_table->table.push_back(MerCompiler_table_setup(value)))
#define MERCURY_ADD_VALUE_ADDRESS(stk, value, address) (stk->s_table->table.push_back(MerCompiler_table_setup(value, address)))
#define POP_STACK(stk) pop_stack(stk)    
#define EAT_STACK(stk) eat_stack(stk)
#define POP() pop_stack(stk)
#define PUSH_STACK(stk, value) push_stack(stk, value)

#define LIST_VALUE(size_of_list, first_element_value, last_element_value) (size_of_list * (first_element_value + last_element_value) / 2)

#define PRINT_VECTOR(vec) for (int i = 0; i < vec.size(); i++) { cout << vec[i] << endl; }

#endif