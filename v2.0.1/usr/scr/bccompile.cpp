#include "bccompile.h"

Program_status init_program_status() {
    Program_status status = Program_status();
    status.cline = 0x0000;
    status.cbyte = 0x0000;
    status.address = 0x0000;
    status.name = "";
    status.status.clear();
    return status;
}

vector<uint8_t> MerCompiler_compile_ast_program(AST_node *ast) {
    Program_status prog = init_program_status();
    vector<uint8_t> code = MerCompiler_compile_ast_statement(ast, prog);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_statement(AST_node *ast, Program_status &prog) {
    if (!ast) return {0x0};

    vector<uint8_t> code;
    AST_node *croot;
    if (ast->children[0]->type == ExpressionStatement) {
        croot = ast->children[0];
    }

    code.push_back(PROGRAM_START);
    vector<uint8_t> result;
    for (auto &child : croot->children) {
        result = MerCompiler_compile_ast(child, prog); 
        code.insert(code.end(), result.begin(), result.end());
        result.clear();
    }

    code.push_back(PROGRAM_END);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast(AST_node *ast, Program_status &prog) {
    if (ast->type == Identifier_) return MerCompiler_compile_ast_identifer(ast, prog);
    if (ast->type == Literal) return MerCompiler_compile_ast_literal(ast, prog);
    if (ast->type == BinaryExpression) return MerCompiler_compile_ast_binary_expression(ast, prog);
    if (ast->type == LetStatement) return MerCompiler_compile_ast_let_statement(ast, prog);
    return {0x0000};
}

vector<uint8_t> MerCompiler_compile_ast_literal(AST_node *ast, Program_status &prog) {
    vector<uint8_t> code;
    code.push_back(PUSH_FLOAT);
    uint8_t cval[sizeof(float)];
    memcpy(cval, &ast->value, sizeof(float));
    code.insert(code.end(), cval, cval + sizeof(float));
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_identifer(AST_node *ast, Program_status &prog) {
  uint8_t vadress;
  vector<uint8_t> code;
  bool found = false;
  for (auto &ps : prog.status) {
    if (ps.name == ast->string_iden) {
      vadress = ps.address;
      found = true;
      break;
    }
  }
  code.push_back(LOAD_GLOBAL);
  code.push_back(vadress - 0x0001);
  return code;
}   

vector<uint8_t> MerCompiler_compile_ast_let_statement(AST_node *ast, Program_status &prog) {
  vector<uint8_t> vval = MerCompiler_compile_ast(ast->var_value, prog);
  Program_status vstatus;
  vector<uint8_t> code;
  string name = ast->var_name;
  code.insert(code.end(), vval.begin(), vval.end());
  code.push_back(STORE_GLOBAL);
  code.push_back(prog.address);
  prog.address += 0x0001;
  prog.name = name;
  prog.status.push_back(prog);
  return code;
}

vector<uint8_t> MerCompiler_compile_ast_binary_expression(AST_node *ast, Program_status &prog) {
    if (!ast->left || !ast->right) return {0x0};

    vector<uint8_t> code;
    vector<uint8_t> left = MerCompiler_compile_ast(ast->left, prog);
    vector<uint8_t> right = MerCompiler_compile_ast(ast->right, prog);
    
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
