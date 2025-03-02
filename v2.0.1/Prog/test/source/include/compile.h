#ifndef COMPILE_H
#define COMPILE_H
#include <vector>

#include <cstring>
#include "parser.h"
using namespace std;

char* MVM_compile_program(AST_node *ast);
char* MVM_compile_ast(AST_node *ast);
char* MVM_compile_ast_binary_expression(AST_node *ast);
char* MVM_compile_ast_call_expression(AST_node *ast);
char* MVM_compile_ast_function_call_expression(AST_node *ast);
char* MVM_compile_ast_function_statement(AST_node *ast);
char* MVM_compile_ast_identifier(AST_node *ast);
char* MVM_compile_ast_literal(AST_node *ast);
char* MVM_compile_ast_return_statement(AST_node *ast);
char* MVM_compile_ast_string_expression(AST_node *ast);

#endif // COMPILE_H