#ifndef MERCURY_MARCO_HEADER_FILE
#define MERCURY_MARCO_HEADER_FILE

#include <string>
#include <cmath>
#include "opcode.h"
#include "type.h"

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

#define stack_push(val)                 \
    stk->s_table->table.push_back(val)  \

#define stack_pop() (stk->s_table->table.pop_back())

#define value(val) MerCompiler_table_setup(val, NULL_UINT_8_T)
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
#define str(a) ((a)->is_str)
#define list(a) ((a)->is_list)
#define rbool(a) (a->is_bool)
#define func(a) (a->is_func)
#define both_list(a, b) (both(list(a), list(b)))
#define both_str(a, b) (both(str(a), str(b)))
#define both_func(a, b) (both(func(a), func(b)))
#define both_bool(a, b) (both(rbool(a), rbool(b)))

#define push_true_to_stack()                        \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = true;                 \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 1;                             \
    stack_push(bool_obj);                           

#define push_false_to_stack()                       \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = false;                \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 0;                             \
    stack_push(bool_obj);                           
    

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

const char* show_opcode_name(uint8_t x) {
    if (x == CPUSH_FLOAT)         return "PUSH_FLOAT";
    else if (x == CPUSH_NORMAL_MODE) return "PUSH_NORMAL_MODE";
    else if (x == CBUILD_LIST)    return "BUILD_LIST";
    else if (x == CGET_ITEM)      return "GET_ITEM";
    else if (x == CSTORE_INDEX)   return "STORE_INDEX";
    else if (x == CBINARY_SUBSCRIBE) return "BINARY_SUBSCRIBE";
    else if (x == CLOAD_GLOBAL)   return "LOAD_GLOBAL";
    else if (x == CSTORE_GLOBAL)  return "STORE_GLOBAL";
    else if (x == CBINARY_ADD)    return "BINARY_ADD";
    else if (x == CLOAD_ARGS)     return "LOAD_ARGS";
    else if (x == CBINARY_SUB)    return "BINARY_SUB";
    else if (x == CBINARY_MUL)    return "BINARY_MUL";
    else if (x == CBINARY_DIV)    return "BINARY_DIV";
    else if (x == CBINARY_MOD)    return "BINARY_MOD";
    else if (x == TRUE_ADDRESS)   return "TRUE_ADDRESS";
    else if (x == FALSE_ADDRESS)  return "FALSE_ADDRESS";
    else if (x == CEQUAL)         return "EQUAL";
    else if (x == CNOT_EQUAL)     return "NOT_EQUAL";
    else if (x == CEND_FUNCTION)  return "END_FUNCTION";
    else if (x == CLESS)          return "LESS";
    else if (x == CLESS_EQUAL)    return "LESS_EQUAL";
    else if (x == CGREATER)       return "GREATER";
    else if (x == CGREATER_EQUAL) return "GREATER_EQUAL";
    else if (x == CNOT)           return "NOT";
    else if (x == CLEN)           return "LEN";
    else if (x == CJUMP_IF_FALSE) return "JUMP_IF_FALSE";
    else if (x == CJUMP_IF_TRUE)  return "JUMP_IF_TRUE";
    else if (x == CPOP_JUMP_IF_FALSE) return "POP_JUMP_IF_FALSE";
    else if (x == CPOP_JUMP_IF_TRUE)  return "POP_JUMP_IF_TRUE";
    else if (x == CJUMP_TO)       return "JUMP_TO";
    else if (x == CPROGRAM_START) return "PROGRAM_START";
    else if (x == CPROGRAM_END)   return "PROGRAM_END";
    else if (x == CMAKE_FUNCTION) return "MAKE_FUNCTION";
    else if (x == CFUNCTION_CALL) return "FUNCTION_CALL";
    else if (x == CRETURN)        return "RETURN";
    else if (x == CADDRESS)       return "ADDRESS";
    else                          return "UNKNOWN_OPCODE";
}

#define LIST_VALUE(size_of_list, first_element_value, last_element_value) (size_of_list * (first_element_value + last_element_value) / 2)

#define PRINT_VECTOR(vec) for (int i = 0; i < vec.size(); i++) { cout << vec[i] << endl; }

#endif