#include "./include/compile.h"

bc_mode_tok init_bc_mode_tok() {
    bc_mode_tok status = bc_mode_tok();
    status.cline = 0x0000;
    status.cbyte = 0x0000;
    status.address = 0x0000;
    status.name = "";
    status.status.clear();
    return status;
}

vector<uint8_t> MerCompiler_compile_ast_program(mAST_T *ast) {
    bc_mode_tok prog = init_bc_mode_tok();
    vector<uint8_t> code = MerCompiler_compile_ast_statement(ast, prog);
    if (code.empty()) {
        mer_run_time_error(to_string(prog.cline), "Error: AST has no children", "", "main.mer");
        return {0x0};
    }

    _MerAST_free(ast);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_statement(mAST_T *ast, bc_mode_tok &prog) {
    if (!ast) return {0x0};

    vector<uint8_t> code;
    
    if (ast->children.empty()) {
      cerr << "Error: AST has no children" << endl;
      return {0x0};
    }

    mAST_T *croot = ast->children[0];
    code.push_back(CPROGRAM_START);
    vector<uint8_t> result;
    for (auto &child : croot->children) {
        result = MerCompiler_compile_ast(child, prog); 
        code.insert(code.end(), result.begin(), result.end());
        result.clear();
    }

    code.push_back(CPROGRAM_END);
    return code;
}

vector<uint8_t> MerCompiler_compile_ast(mAST_T *ast, bc_mode_tok &prog) {
    if (ast->type == Identifier_) return MerCompiler_compile_ast_identifer(ast, prog);
    if (ast->type == Literal) return MerCompiler_compile_ast_literal(ast, prog);
    if (ast->type == BinaryExpression) return MerCompiler_compile_ast_binary_expression(ast, prog);
    if (ast->type == LetStatement) return MerCompiler_compile_ast_let_statement(ast, prog);
    if (ast->type == ExpressionStatement) return MerCompiler_compile_ast_statement(ast, prog);
    if (ast->type == FunctionStatement) return MerCompiler_compile_ast_function(ast, prog);
    if (ast->type == ReturnStatement) return MerCompiler_compile_ast_return_statement(ast, prog);
    if (ast->type == FunctionCallExpression) return MerCompiler_compile_ast_function_call(ast, prog);
    if (ast->type == ComparisonExpression) return MerCompiler_compile_ast_comparison_expression(ast, prog);
    return {0x0000};
}

vector<uint8_t> MerCompiler_compile_ast_comparison_expression(mAST_T *ast, bc_mode_tok &prog) {
    if (!ast->comp_left || !ast->comp_right) return {0x0};

    vector<uint8_t> code;
    vector<uint8_t> left = MerCompiler_compile_ast(ast->comp_left, prog);
    vector<uint8_t> right = MerCompiler_compile_ast(ast->comp_right, prog);
    
    uint8_t oper;

    if (ast->comp_op == EQUAL) oper = CEQUAL;
    if (ast->comp_op == NOT_EQUAL) oper = CNOT_EQUAL;
    if (ast->comp_op == LESS) oper = CLESS;
    if (ast->comp_op == LESS_EQUAL) oper = CLESS_EQUAL;
    if (ast->comp_op == GREATER) oper = CGREATER;
    if (ast->comp_op == GREATER_EQUAL) oper = CGREATER_EQUAL;
    if (ast->comp_op == NOT) oper = CNOT;
    if (ast->comp_op == AND) oper = CAND;
    if (ast->comp_op == OR) oper = COR;

    code.insert(code.end(), left.begin(), left.end());
    code.insert(code.end(), right.begin(), right.end());
    code.insert(code.end(), oper);
    left.clear();
    right.clear();
    return code;
}

vector<uint8_t> MerCompiler_compile_ast_function(mAST_T *ast, bc_mode_tok &prog) {
  vector<uint8_t> body;
  vector<uint8_t> code;
  string func_name = ast->func_name.empty() ? "UnnamedFunction" : ast->func_name;

  for (auto &node : ast->body) {
    vector<uint8_t> result = MerCompiler_compile_ast(node, prog);
    body.insert(body.end(), result.begin(), result.end());
    result.clear();
  }

  code.push_back(CMAKE_FUNCTION);
  prog.address += 0x0001;
  code.push_back(prog.address);
  code.insert(code.end(), body.begin(), body.end());
  code.push_back(CRETURN);

  prog.name = func_name;
  prog.status.push_back(prog);
  
  return code;
}

vector<uint8_t> MerCompiler_compile_ast_function_call(mAST_T *ast, bc_mode_tok &prog) {
  vector<uint8_t> code;
  bool found = false;
  uint8_t vadress;
  for (auto &ps : prog.status) {
    if (ps.name == ast->func_call) {
      vadress = ps.address;
      found = true;
      break;
    }
  }

  if (!found) return {0x0};
  
  code.push_back(CLOAD_GLOBAL);
  code.push_back(vadress);
  code.push_back(CFUNCTION_CALL);
  return code;
}

vector<uint8_t> MerCompiler_compile_ast_return_statement(mAST_T *ast, bc_mode_tok &prog) {
  return {0x0};
}

vector<uint8_t> MerCompiler_compile_ast_literal(mAST_T *ast, bc_mode_tok &prog) {
  vector<uint8_t> code;
  code.push_back(CPUSH_FLOAT);
  uint8_t cval[sizeof(float)];
  memcpy(cval, &ast->value, sizeof(float));
  code.insert(code.end(), cval, cval + sizeof(float));
  return code;
}

vector<uint8_t> MerCompiler_compile_ast_identifer(mAST_T *ast, bc_mode_tok &prog) {
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
  if (!found) return {0x0};
  code.push_back(CLOAD_GLOBAL);
  code.push_back(vadress);
  return code;
}   

vector<uint8_t> MerCompiler_compile_ast_let_statement(mAST_T *ast, bc_mode_tok &prog) {
  vector<uint8_t> vval = MerCompiler_compile_ast(ast->var_value, prog);
  bc_mode_tok vstatus;
  vector<uint8_t> code;
  string name = ast->var_name;
  code.insert(code.end(), vval.begin(), vval.end());
  code.push_back(CSTORE_GLOBAL);
  prog.address += 0x0001;
  code.push_back(prog.address);
  prog.name = name;
  prog.status.push_back(prog);
  return code;
}

vector<uint8_t> MerCompiler_compile_ast_binary_expression(mAST_T *ast, bc_mode_tok &prog) {
    if (!ast->left || !ast->right) return {0x0};

    vector<uint8_t> code;
    vector<uint8_t> left = MerCompiler_compile_ast(ast->left, prog);
    vector<uint8_t> right = MerCompiler_compile_ast(ast->right, prog);
    
    uint8_t oper;

    if (ast->op == PLUS) oper = CBINARY_ADD;
    if (ast->op == MINUS) oper = CBINARY_SUB;
    if (ast->op == DIV) oper = CBINARY_DIV;
    if (ast->op == TIME) oper = CBINARY_MUL;

    code.insert(code.end(), left.begin(), left.end());
    code.insert(code.end(), right.begin(), right.end());
    code.insert(code.end(), oper);
    left.clear();
    right.clear();
    return code;
}
