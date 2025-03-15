#include "compile.h"
#include "olexer.cpp"
#include <string.h>

char *MVM_compile_ast(AST_node *ast)
{
    if (!ast) return nullptr;

    if (ast->type == Identifier_) return MVM_compile_ast_identifier(ast);
    if (ast->type == Literal) return MVM_compile_ast_literal(ast);
    if (ast->type == ExpressionStatement) return MVM_compile_statement(ast);
    if (ast->type == CallExpression) return MVM_compile_ast_call_expression(ast);
    if (ast->type == FunctionCallExpression) return MVM_compile_ast_function_call_expression(ast);
    if (ast->type == LetStatement) return MVM_compile_ast_let_statement(ast);
    if (ast->type == StringExpression) return MVM_compile_ast_string_expression(ast);
    if (ast->type == BinaryExpression) return MVM_compile_ast_binary_expression(ast);
    if (ast->type == ReturnStatement) return MVM_compile_ast_return_statement(ast);
    return nullptr;
}

char *MVM_compile_program(AST_node *ast)
{
    if (!ast) return nullptr;

    char *bytecoden = new char[BYTECODE_SIZE];
    memset(bytecoden, 0, BYTECODE_SIZE);
    snprintf(bytecoden, BYTECODE_SIZE, "PROGRAM_START\n");
    char *code;
    if (ast->children[0]->type == ExpressionStatement) code = MVM_compile_statement(ast);
    
    if (code) {
        strcat(bytecoden, code);
        delete[] code;
    }

    strcat(bytecoden, "PROGRAM_END\n");
    return bytecoden;
}

char *MVM_compile_statement(AST_node *ast) {
    if (!ast) return nullptr;

    char *bytecoden = new char[BYTECODE_SIZE];
    memset(bytecoden, 0, BYTECODE_SIZE);

    for (auto &node : ast->children) {
        char *code = MVM_compile_ast(node);
        if (code) {
            strcat(bytecoden, code);
            delete[] code;
        }
    }

    return bytecoden;
}

char *MVM_compile_ast_let_statement(AST_node *ast) {
    if (!ast) return nullptr;
    if (!ast->var_value) return nullptr;

    char *bytecoden = new char[BYTECODE_SIZE];
    char *value = new char[BYTECODE_IDENTIFIER_CODE_SIZE];
    char *var_value = MVM_compile_ast(ast->var_value);

    memset(bytecoden, 0, BYTECODE_SIZE);
    memset(value, 0, BYTECODE_IDENTIFIER_CODE_SIZE);
    memset(var_value, 0, BYTECODE_SIZE);

    var_value = MVM_compile_ast(ast->var_value);
    strcat(bytecoden, var_value);
    snprintf(value, BYTECODE_IDENTIFIER_CODE_SIZE, "STORE_GLOBAL %s;\n", ast->var_name.c_str());
    strcat(bytecoden, value);

    if (var_value) delete[] var_value;
    if (value) delete[] value;


    return bytecoden;
}

char *MVM_compile_ast_function_call_expression(AST_node *ast) {
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_IDENTIFIER_CODE_SIZE];
    snprintf(value, BYTECODE_IDENTIFIER_CODE_SIZE, "LOAD_GLOBAL %s;\n", ast->func_call.c_str());
    for (auto &node : ast->args) {
        char *arg = MVM_compile_ast(node);
        strcat(value, arg);
        delete[] arg;
    }

    strcat(value, "CALL_FUNCTION\n");
    return value;
}

char *MVM_compile_ast_literal(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_INTERGER_CODE_SIZE];
    snprintf(value, BYTECODE_INTERGER_CODE_SIZE, "PUSH_FLOAT %f;\n", ast->value);
    return value;
}

char *MVM_compile_ast_identifier(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_IDENTIFIER_CODE_SIZE];
    snprintf(value, BYTECODE_IDENTIFIER_CODE_SIZE, "LOAD_GLOBAL %s;\n", ast->string_iden.c_str());
    return value;
}

char *MVM_compile_ast_call_expression(AST_node *ast)
{
    if (!ast) return nullptr;

    char *value = new char[BYTECODE_CALL_FUNCTION_SIZE];
    snprintf(value, BYTECODE_CALL_FUNCTION_SIZE, "LOAD_GLOBAL %s;\n", ast->string_iden.c_str());
    return value;
}

char *MVM_compile_ast_binary_expression(AST_node *ast)
{
    if (!ast) return nullptr;

    const char *oper;
    if (ast->op == PLUS) oper = "BINARY_ADD;";
    if (ast->op == MINUS) oper = "BINARY_SUB;";
    if (ast->op == TIME) oper = "BINARY_MUL;";
    if (ast->op == DIV) oper = "BINARY_DIV;";

    char *left = MVM_compile_ast(ast->left);
    char *right = MVM_compile_ast(ast->right);
    
    if (!left || !right) {
        delete[] left;
        delete[] right;
        return nullptr;
    }

    char *value = new char[BYTECODE_INTERGER_CODE_SIZE];
    snprintf(value, BYTECODE_INTERGER_CODE_SIZE, "%s%s%s\n", left, right, oper);

    delete[] left;
    delete[] right;
    return value;
}

char *MVM_compile_ast_string_expression(AST_node *ast) {
    return strdup("PUSH_STRING\n");
}

char *MVM_compile_ast_return_statement(AST_node *ast) {
    return strdup("STATEMENT\n");
}

char *MVM_compile_ast_function_statement(AST_node *ast) {
    return strdup("DEFINE_FUNC\n");
}
