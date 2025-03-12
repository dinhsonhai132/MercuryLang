#ifndef MERCURY_COMPILER_HEADER_FILE
#define MERCURY_COMPILER_HEADER_FILE

#include <string>
#include "parser.cpp"
using namespace std;

#define BYTECODE_SIZE 1024
#define BYTECODE_INTERGER_CODE_SIZE 1024
#define BYTECODE_IDENTIFIER_CODE_SIZE 1024
#define BYTECODE_CALL_FUNCTION_SIZE 1024

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
char* MVM_compile_statement(AST_node *ast);
char* MVM_compile_ast_let_statement(AST_node *ast);

#endif // MERCURY_COMPILER_HEADER_FILE