#ifndef MERCURY_MARCO_HEADER_FILE
#define MERCURY_MARCO_HEADER_FILE
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
#define CONST(x) const x
#endif