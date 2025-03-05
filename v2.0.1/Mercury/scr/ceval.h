#ifndef MERCURY_COMPILER_EVALUATE_HEADER_FILE
#define MERCURY_COMPILER_EVALUATE_HEADER_FILE

#include <iostream>
#include <string>
#include <vector>
#include "runtime.cpp"
#include "stack.cpp"
#include "olexer.cpp"

using namespace std;

#define BINARY_ADD(c1, c2) ((c1) + (c2))
#define BINARY_SUB(c1, c2) ((c1) - (c2))
#define BINARY_MUL(c1, c2) ((c1) * (c2))
#define BINARY_DIV(c1, c2) ((c1) / (c2))
#define BINARY_MOD(c1, c2) ((c1) % (c2))
#define BINARY_POW(c1, c2) ((c1) ** (c2))
#define BINARY_INCREMENT(c1) ((c1)++)
#define BINARY_DECREMENT(c1) ((c1)--)

char *MerBuffer_take_bytecode_from_file(char *file_name);
char *MerBuffer_take_bytecode_from_promt(char *line);

RunTimeVal *MerCompile_evaluate_program(stack *s, vector<bytecode_token> *bytecode_ts);
RunTimeVal *MerCompile_evaluate_statement(stack *s, vector<bytecode_token> *bytecode_ts);
RunTimeVal *MerCompile_evaluate_expression(stack *s, vector<bytecode_token> *bytecode_ts);

#endif // MERCURY_COMPILER_EVALUATE_HEADER_FILE