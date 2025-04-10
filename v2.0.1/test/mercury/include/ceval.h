#ifndef MECURY_EVALUATE_H
#define MECURY_EVALUATE_H

#include "C:\MercuryLang-main\v2.0.1\mercury\btok.cpp"
#include "C:\MercuryLang-main\v2.0.1\mercury\stack.cpp"

#include <stdlib.h>
using namespace std;

#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : 0)
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))

stack *MerCompilerBytecode_evaluate_program(vector<uint8_t> code);
stack *MerCompilerBytecode_evaluate_statement(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_POP_NORMAL_MODE(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_PUSH_FLOAT(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_LOAD_GLOBAL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_STORE_GLOBAL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_ADD(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_DIV(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_MUL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_SUB(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_MAKE_FUNCTION(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_FUNCTION_CALL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_RETURN(ctoken ptoken, stack *stk);

#endif //MECURY_EVALUATE_H
