#ifndef COMPILE_H
#define COMPILE_H
#include <vector>

#include "parser.h"
using namespace std;

char* MVM_f(AST_node *ast);
char* MVM_bin_expr(AST_node *ast);
char* MVM_call_expr(AST_node *ast);

#endif // COMPILE_H