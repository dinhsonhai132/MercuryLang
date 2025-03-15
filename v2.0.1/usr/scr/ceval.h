#ifndef MERCURY_COMPILER_EVALUATE_HEADER_FILE
#define MERCURY_COMPILER_EVALUATE_HEADER_FILE

#include <iostream>
#include <string>
#include <vector>
#include "runtime.cpp"
#include "stack.cpp"
#include "olexer.cpp"

using namespace std;

#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c1) / (c2))
#define MERCURY_BINARY_MOD(c1, c2) ((c1) % (c2))
#define MERCURY_BINARY_POW(c1, c2) ((c1) ** (c2))
#define MERCURY_BINARY_INCREMENT(c1) ((c1)++)
#define MERCURY_BINARY_DECREMENT(c1) ((c1)--)

stack *MerCompiler_evaluate_program(char *code, stack *stk);
stack *MerCompiler_evaluate_statement(char *code, stack *stk);
stack *MerCompiler_evaluate(bytecode_token ctok, stack *stk);

stack *MerCompiler_evaluate_PUSH_FLOAT(bytecode_token ctok, stack *stk);
stack *MerCompiler_evaluate_POP_NORMAL_MODE(bytecode_token ctok, stack *stk);

stack *MerCompiler_evaluate_BINARY_ADD(bytecode_token ctok, stack *stk);
stack *MerCompiler_evaluate_BINARY_SUB(bytecode_token ctok, stack *stk);
stack *MerCompiler_evaluate_BINARY_MUL(bytecode_token ctok, stack *stk);
stack *MerCompiler_evaluate_BINARY_DIV(bytecode_token ctok, stack *stk);

#endif // MERCURY_COMPILER_EVALUATE_HEADER_FILE
