#ifndef MERCURY_MARCO_HEADER_FILE
#define MERCURY_MARCO_HEADER_FILE

#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : 0)
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))
#define MERCURY_BINARY_MOD(c1, c2) ((c1) % (c2))
#define MERCURY_BINARY_AND(c1, c2) ((c1) & (c2))
#define MERCURY_BINARY_OR(c1, c2) ((c1) | (c2))
#define MERCURY_BINARY_XOR(c1, c2) ((c1) ^ (c2))
#define MERCURY_BINARY_NOT(c1) (~(c1))
#define MERCURY_BINARY_SHL(c1, c2) ((c1) << (c2))
#define MERCURY_BINARY_SHR(c1, c2) ((c1) >> (c2))
#define MERCURY_BINARY_NOT(c1) (~(c1))
#define MERCURY_BINARY_GREATER(c1, c2) ((c1) > (c2))
#define MERCURY_BINARY_LESS(c1, c2) ((c1) < (c2))
#define MERCURY_BINARY_GREATER_EQUAL(c1, c2) ((c1) >= (c2))
#define MERCURY_BINARY_LESS_EQUAL(c1, c2) ((c1) <= (c2))
#define MERCURY_BINARY_EQUAL(c1, c2) ((c1) == (c2))
#define MERCURY_BINARY_NOT_EQUAL(c1, c2) ((c1) != (c2))
#define IS_TRUE(x) ((x) != 0)
#define IS_FALSE(x) (!(x != 0))

#endif