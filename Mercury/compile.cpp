#include "./include\compile.h"

MERCURY_API __Mer_return_Code MVM_id(mAST_T *ast, __compiler_u &glb) {
  if (!ast) return NULL_CODE;

  if (ast->type == Identifier_) return MVM_identifier(ast, glb);
  if (ast->type == Literal) return MVM_literal(ast, glb);
  if (ast->type == BinaryExpression) return MVM_binary_expression(ast, glb);
  if (ast->type == FunctionCallExpression) return MVM_function_call(ast, glb);
  if (ast->type == IfStatement) return MVM_if(ast, glb);
  if (ast->type == LetStatement) return MVM_let(ast, glb);
  if (ast->type == ReturnStatement) return MVM_return(ast, glb);
  if (ast->type == ExpressionStatement) return MVM_id_expression_statment(ast, glb);
  if (ast->type == FunctionStatement) return MVM_function(ast, glb); 
  if (ast->type == ComparisonExpression) return MVM_comparison_expression(ast, glb);
  if (ast->type == PrintStatement) return MVM_print(ast, glb);
  if (ast->type == WhileStatement) return MVM_while(ast, glb);

  return NULL_CODE;
}

MERCURY_API __Mer_return_Code MVM_print(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code _code = MVM_id(ast->print_v, glb);
  INSERT_VEC(result, _code);
  PUSH(result, CPRINT);
  return result;
}

MERCURY_API __Mer_return_Code MVM_while(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code while_cond = MVM_id(ast->while_cond, glb);
  __Mer_return_Code while_body = NULL_CODE;

  for (auto child : ast->while_body) {
    __Mer_return_Code _code = MVM_id(child, glb);
    INSERT_VEC(while_body, _code);
    _code.prg_code.buff.clear();
  }

  Mer_uint8_t while_begin = ++glb.address;
  Mer_uint8_t while_end = ++glb.address;

  PUSH(result, CADDRESS);
  PUSH(result, while_begin);
  INSERT_VEC(result, while_cond);
  PUSH(result, CJUMP_IF_FALSE);
  PUSH(result, while_end);
  INSERT_VEC(result, while_body);
  PUSH(result, CJUMP_TO);
  PUSH(result, while_begin);
  PUSH(result, CADDRESS);
  PUSH(result, while_end);
  PUSH(result, CNONE);

  return result;
}

MERCURY_API __Mer_return_Code MVM_literal(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t cval[sizeof(float)];
  memcpy(cval, &ast->value, sizeof(float));
  result.prg_code.buff.push_back(CPUSH_FLOAT);
  result.prg_code.buff.insert(result.prg_code.buff.end(), cval, cval + sizeof(float));
  return result;  
}

MERCURY_API __Mer_return_Code MVM_binary_expression(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code _left = MVM_id(ast->left, glb);
  __Mer_return_Code _right = MVM_id(ast->right, glb);

  Mer_uint8_t _oper;
  if (ast->op == PLUS) _oper = CBINARY_ADD;
  else if (ast->op == MINUS) _oper = CBINARY_SUB;
  else if (ast->op == DIV) _oper = CBINARY_DIV;
  else if (ast->op == TIME) _oper = CBINARY_MUL;

  __Mer_return_Code result = NULL_CODE;
  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);
  return result;
}

MERCURY_API __Mer_return_Code MVM_function_call(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;

  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->func_call.c_str());
  for (auto &item : glb.tb) {
    if (item->__name == name) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    mer_error(SYSTEM_ERROR, "Function not found: " + ast->func_call);
    return NULL_CODE;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);
  PUSH(result, CFUNCTION_CALL);
  return result;    
}

MERCURY_API __Mer_return_Code MVM_if(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code comp = NULL_CODE;
  __Mer_return_Code if_body = NULL_CODE;
  __Mer_return_Code else_body = NULL_CODE;
  
  comp = MVM_id(ast->comp, glb);
  
  if (!ast->comp) mer_error(SYSTEM_ERROR, "Syntax error: Invalid condition in if statement");

  glb.address += 0x0001;
  Mer_uint8_t end_if = glb.address;
  glb.byte += 0x0002;
  glb.line += 0x0001;

  for (auto child : ast->then_body) {
    __Mer_return_Code _code = MVM_id(child, glb);
    INSERT_VEC(if_body, _code);
    _code.prg_code.buff.clear();
  }

  if (ast->has_else) {
    for (auto child : ast->else_body) {
      __Mer_return_Code _code = MVM_id(child, glb);
      INSERT_VEC(else_body, _code);
      _code.prg_code.buff.clear();
    }

    Mer_uint8_t label_else = ++glb.address;

    INSERT_VEC(result, comp);
    PUSH(result, CPOP_JUMP_IF_FALSE);
    PUSH(result, label_else);

    INSERT_VEC(result, if_body);
    PUSH(result, CJUMP_TO);
    PUSH(result, end_if);
    
    PUSH(result, CADDRESS);
    PUSH(result, label_else);
    INSERT_VEC(result, else_body);

    PUSH(result, CADDRESS);
    PUSH(result, end_if);

    return result;
  }

  INSERT_VEC(result, comp);
  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, end_if);
  INSERT_VEC(result, if_body);
  PUSH(result, CADDRESS);
  PUSH(result, end_if);
  return result;
}

MERCURY_API __Mer_return_Code MVM_let(mAST_T *ast, __compiler_u &glb) {
  Mer_string name = strdup(ast->var_name.c_str());
  Mer_real_string real_name = ast->var_name;
  glb.address += 0x0001;
  glb.byte += 0x0002;
  glb.line += 0x0001;

  __Mer_return_Code var_val = MVM_id(ast->var_value, glb);
  __Mer_return_Code result = NULL_CODE;
  glb.tb.push_back(create_global_table_ptr(glb.address, name, real_name));

  INSERT_VEC(result, var_val);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, glb.address);
  return result;
}

MERCURY_API __Mer_return_Code MVM_return(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  PUSH(result, CRETURN);
  return result;
}

MERCURY_API __Mer_return_Code MVM_identifier(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->string_iden.c_str());
  if (name != ast->string_iden) mer_error(SYSTEM_ERROR, "Bet: " + ast->string_iden);

  for (auto &item : glb.tb) {
    if (item->__name == name) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    if (ast->tok == VARIABLE) mer_error(SYSTEM_ERROR, "Variable not found: " + ast->string_iden);
    return NULL_CODE;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);
  return result;
}

MERCURY_API __Mer_return_Code MVM_program(mAST_T *ast) {
  __compiler_u glb;
  return MVM_id_expression_statment(ast, glb);
}

MERCURY_API __Mer_return_Code MVM_id_expression_statment(mAST_T *ast, __compiler_u &glb) {
  
  __Mer_return_Code code = NULL_CODE;

  mAST_T *root;
  if (ast->children[0]->type == ExpressionStatement) {
    root = ast->children[0];
  }

  PUSH(code, CPROGRAM_START);
  for (auto child : root->children) {
    __Mer_return_Code _code = MVM_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(code, CPROGRAM_END);
  return code;
}

MERCURY_API __Mer_return_Code MVM_function(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code body = NULL_CODE;
  glb.address += 0x0001;
  Mer_uint8_t func_address = glb.address;
  Mer_real_string name = ast->func_name;
  Mer_string func_name = strdup(ast->func_name.c_str());

  glb.byte += 0x0002;
  glb.line += 0x0001;
  glb.tb.push_back(create_global_table_ptr(glb.address, func_name, name));

  for (auto child : ast->body) {
    __Mer_return_Code _code = MVM_id(child, glb);
    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CMAKE_FUNCTION);
  PUSH(result, func_address);
  INSERT_VEC(result, body);
  PUSH(result, CRETURN);

  return result;
}

MERCURY_API __Mer_return_Code MVM_comparison_expression(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code _left = MVM_id(ast->comp_left, glb);
  __Mer_return_Code _right = MVM_id(ast->comp_right, glb);

  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t _oper;

  if (ast->comp_op == EQUAL) _oper = CEQUAL;
  else if (ast->comp_op == NOT_EQUAL) _oper = CNOT_EQUAL;
  else if (ast->comp_op == LESS) _oper = CLESS;
  else if (ast->comp_op == LESS_EQUAL) _oper = CLESS_EQUAL;
  else if (ast->comp_op == GREATER) _oper = CGREATER;
  else if (ast->comp_op == GREATER_EQUAL) _oper = CGREATER_EQUAL;
  else if (ast->comp_op == NOT) _oper = CNOT;
  else if (ast->comp_op == AND) _oper = CAND;
  else if (ast->comp_op == OR) _oper = COR;

  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);


  return result;
}
