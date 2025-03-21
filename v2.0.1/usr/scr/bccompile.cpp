#include "bccompile.h"

vector<uint8_t> MerCompiler_compile_ast_program(AST_node *ast, vector<uint8_t> &address) {
    vector<uint8_t> caddress;
    vector<uint8_t> code = MerCompiler_compile_ast_statement(ast, address);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_statement(AST_node *ast, vector<uint8_t> &address) {
    if (!ast) return {0x0};

    vector<uint8_t> code;
    AST_node *croot;
    if (ast->children[0]->type == ExpressionStatement) {
        croot = ast->children[0];
    }

    code.push_back(PROGRAM_START);
    vector<uint8_t> result;
    vector<uint8_t> caddress;
    for (auto &child : croot->children) {
        result = MerCompiler_compile_ast(child, caddress); 
        code.insert(code.end(), result.begin(), result.end());
        result.clear();
    }

    code.push_back(PROGRAM_END);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast(AST_node *ast, vector<uint8_t> &address) {
    if (!ast) return {0x0};
    if (ast->type == Identifier_) return MerCompiler_compile_ast_identifer(ast, address);
    if (ast->type == Literal) return MerCompiler_compile_ast_literal(ast, address);
    if (ast->type == BinaryExpression) return MerCompiler_compile_ast_binary_expression(ast, address);
    return {0x0};
}

vector<uint8_t> MerCompiler_compile_ast_literal(AST_node *ast, vector<uint8_t> &address) {
    vector<uint8_t> code;
    code.push_back(PUSH_FLOAT);
    uint8_t cval[sizeof(float)];
    memcpy(cval, &ast->value, sizeof(float));
    code.insert(code.end(), cval, cval + sizeof(float));
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_identifer(AST_node *ast, vector<uint8_t> &address) {
    return {0x0};
}   
vector<uint8_t> MerCompiler_compile_ast_binary_expression(AST_node *ast, vector<uint8_t> &address) {
    if (!ast->left || !ast->right) return {0x0};

    vector<uint8_t> code;
    vector<uint8_t> caddress;
    vector<uint8_t> left = MerCompiler_compile_ast(ast->left, caddress);
    vector<uint8_t> right = MerCompiler_compile_ast(ast->right, caddress);
    
    uint8_t oper;

    if (ast->op == PLUS) oper = BINARY_ADD;
    if (ast->op == MINUS) oper = BINARY_SUB;
    if (ast->op == DIV) oper = BINARY_DIV;
    if (ast->op == TIME) oper = BINARY_MUL;

    code.insert(code.end(), left.begin(), left.end());
    code.insert(code.end(), right.begin(), right.end());
    code.insert(code.end(), oper);
    left.clear();
    right.clear();
    return code;
}
