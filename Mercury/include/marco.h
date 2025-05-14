#ifndef MERCURY_MARCO_HEADER_FILE
#define MERCURY_MARCO_HEADER_FILE

#include <string>

#define TO_STRING(x) std::to_string(x).c_str()

#define MAX_FLOAT 3.4028235e+38
#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : MAX_FLOAT)
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
#define CHECK 1
#define CONST(x) const x
#define IS_TRUE(x) ((x) == 1)
#define IS_FALSE(x) ((x) == 0)
#define TRUE_MARCO 1
#define NULL_MARCO 0
#define INLINE(x) inline x
#define CONSTEXPR(x) constexpr x
#define EXTERN(x) extern x

#define OPCODE(x) \
    switch (x) { \
        case CPUSH_FLOAT: return "PUSH_FLOAT"; \
        case CADDRESS: return "ADDRESS"; \
        case CPOP_JUMP_IF_FALSE: return "POP_JUMP_IF_FALSE"; \
        case CJUMP_TO: return "JUMP_TO"; \
        case CPOP_JUMP_IF_TRUE: return "POP_JUMP_IF_TRUE"; \
        case CPOP_JUMP_IF_FALSE: return "POP_JUMP_IF_FALSE"; \
        case CPOP_JUMP_IF_TRUE: return "POP_JUMP_IF_TRUE"; \
        case CPOP_GLOBAL: return "POP_GLOBAL"; \
        case CPOP_LOCAL: return "POP_LOCAL"; \
        case CPOP_TEMP: return "POP_TEMP"; \
        case CPOP_NORMAL: return "POP_NORMAL"; \
        case CPOP_STRING: return "POP_STRING"; \
        case CPOP_FLOAT: return "POP_FLOAT"; \
        case CPOP_NORMAL_MODE: return "POP_NORMAL_MODE"; \
        case CPOP_TEMP_MODE: return "POP_TEMP_MODE"; \
        case CPOP_GLOBAL: return "POP_GLOBAL"; \
        case CPOP_LOCAL: return "POP_LOCAL"; \
        case CPOP_TEMP: return "POP_TEMP"; \
        case CPOP_NORMAL: return "POP_NORMAL"; \
        case CPOP_STRING: return "POP_STRING"; \
        case CPOP_FLOAT: return "POP_FLOAT"; \
        case CPUSH_NORMAL_MODE: return "PUSH_NORMAL_MODE"; \
        case CPUSH_TEMP_MODE: return "PUSH_TEMP_MODE"; \
        case CLOAD_GLOBAL: return "LOAD_GLOBAL"; \
        case CSTORE_GLOBAL: return "STORE_GLOBAL"; \
        case CBINARY_ADD: return "BINARY_ADD"; \
        case CBINARY_SUB: return "BINARY_SUB"; \
        case CBINARY_MUL: return "BINARY_MUL"; \
        case CBINARY_DIV: return "BINARY_DIV"; \
        case CBINARY_MOD: return "BINARY_MOD"; \
        case CEQUAL: return "EQUAL"; \
        case CNOT_EQUAL: return "NOT_EQUAL"; \
        case CLESS: return "LESS"; \
        case CLESS_EQUAL: return "LESS_EQUAL"; \
        case CGREATER: return "GREATER"; \
        case CGREATER_EQUAL: return "GREATER_EQUAL"; \
        case CNOT: return "NOT"; \
        case CAND: return "AND"; \
        case COR: return "OR"; \
        case CNOT_OR: return "NOT_OR"; \
        case CAND_OR: return "AND_OR"; \
        case CNOT_AND_OR: return "NOT_AND_OR"; \
        case CJUMP_IF_FALSE: return "JUMP_IF_FALSE"; \
        case CJUMP_IF_TRUE: return "JUMP_IF_TRUE"; \
        case CPOP_JUMP_IF_FALSE: return "POP_JUMP_IF_FALSE"; \
        case CPOP_JUMP_IF_TRUE: return "POP_JUMP_IF_TRUE"; \
        case CJUMP_TO: return "JUMP_TO"; \
        case CPOINT_TO: return "POINT_TO"; \
        case CPROGRAM_START: return "PROGRAM_START"; \
        case CPROGRAM_END: return "PROGRAM_END"; \
        case CMAKE_BLOCK: return "MAKE_BLOCK"; \
        case CEND_BLOCK: return "END_BLOCK"; \
        case CMAKE_FUNCTION: return "MAKE_FUNCTION"; \
        case CFUNCTION_CALL: return "FUNCTION_CALL"; \
        case CRETURN: return "RETURN"; \
        case CPRINT: return "PRINT"; \
        case CNONE: return "NONE"; \
    }   

#endif