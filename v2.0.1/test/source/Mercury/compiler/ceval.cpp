#include "../include/ceval.h"
#include "ceval.h"

char *MerBuffer_take_bytecode_from_promt(char *line) {}
char *MerBuffer_take_bytecode_from_file(char *file_name) {}

RunTimeVal *MerCompile_evaluate_program(stack *s) {}
RunTimeVal *MerCompile_evaluate_expression(stack *s) {}
RunTimeVal *MerCompile_evaluate_statement(stack *s) {}

RunTimeVal *MerCompile_Binary_plus(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_minus(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_mul(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_div(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_mod(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_pow(RunTimeVal *left, RunTimeVal *right) {}
RunTimeVal *MerCompile_Binary_increment(RunTimeVal *val) {}
RunTimeVal *MerCompile_Binary_decrement(RunTimeVal *val) {}