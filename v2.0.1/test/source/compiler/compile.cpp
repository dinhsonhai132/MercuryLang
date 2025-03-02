#include "./include/compile.h"
#include "./include/bytecode.h"

char* MVM_compile_ast(AST_node *ast) {
    if (ast->type == Literal) return MVM_compile_ast_literal(ast);
    if (ast->type == Identifier_) return MVM_compile_ast_identifier(ast);
    if (ast->type == CallExpression) return MVM_compile_ast_call_expression(ast);
    if (ast->type == BinaryExpression) return MVM_compile_ast_binary_expression(ast);
    if (ast->type == FunctionCallExpression) return MVM_compile_ast_function_call_expression(ast);
    if (ast->type == StringExpression) return MVM_compile_ast_string_expression(ast);
    if (ast->type == ReturnStatement) return MVM_compile_ast_return_statement(ast);
    if (ast->type == FunctionStatement) return MVM_compile_ast_function_statement(ast);
    return (char*) calloc(1, sizeof(char));
}

char* MVM_compile_program(AST_node *ast) {
    char *value = (char*) calloc(1, sizeof(char));

    for (auto &node : ast->children) {
        char *next_value = MVM_compile_ast(node);
        value = (char*) realloc(value, (strlen(value) + strlen(next_value) + 1) * sizeof(char));
        strcat(value, next_value);
    }

    size_t len = strlen(value) + 8;
    char *final_value = (char*) malloc(len);
    strcpy(final_value, "_Start\n");
    strcat(final_value, value);

    free(value);
    return final_value;
}

char* MVM_compile_ast_literal(AST_node *ast) {
    
}

char* MVM_compile_ast_identifier(AST_node *ast) {}

char* MVM_compile_ast_call_expression(AST_node *ast) {}

char* MVM_compile_ast_binary_expression(AST_node *ast) {}

char* MVM_compile_ast_function_call_expression(AST_node *ast) {}

char* MVM_compile_ast_string_expression(AST_node *ast) {}

char* MVM_compile_ast_return_statement(AST_node *ast) {}

char* MVM_compile_ast_function_statement(AST_node *ast) {}