#include "../Include/compile.h"
bool skip = false;

__compiler_u compiler_init(void) {
  __compiler_u glb;
  glb.address = 0x20;
  glb.cid = 0x0000;
  glb.name = nullptr;
  glb.type = nullptr;
  glb.is_in_func = false;
  glb.para_address = 0x0000;
  glb.file = "stdin";
  return glb;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_id(mAST_T *ast, __compiler_u &glb) {
  if (!ast) return NULL_CODE;

  if (ast->type == Identifier_)             return MerCompiler_compile_ast_identifier(ast, glb);
  if (ast->type == Literal)                 return MerCompiler_compile_ast_literal(ast, glb);
  if (ast->type == FunctionStatement)       return MerCompiler_compile_ast_function(ast, glb); 
  if (ast->type == BinaryExpression)        return MerCompiler_compile_ast_binary_expression(ast, glb);
  if (ast->type == FunctionCallExpression)  return MerCompiler_compile_ast_function_call(ast, glb);
  if (ast->type == IfStatement)             return MerCompiler_compile_ast_if(ast, glb);
  if (ast->type == LetStatement)            return MerCompiler_compile_ast_let(ast, glb);
  if (ast->type == ReturnStatement)         return MerCompiler_compile_ast_return(ast, glb);
  if (ast->type == ExpressionStatement)     return MerCompiler_compile_ast_id_expression_statment(ast, glb);
  if (ast->type == ComparisonExpression)    return MerCompiler_compile_ast_comparison_expression(ast, glb);
  if (ast->type == AssignStatement)         return MerCompiler_compile_ast_assign(ast, glb);
  if (ast->type == WhileStatement)          return MerCompiler_compile_ast_while(ast, glb);
  if (ast->type == StringIdentifier)        return MerCompiler_compile_ast_string_identifier(ast, glb);
  if (ast->type == ListStatement)           return MerCompiler_compile_ast_list(ast, glb);
  if (ast->type == ArrayExpression)         return MerCompiler_compile_ast_array(ast, glb);
  if (ast->type == ExtractExpression)       return MerCompiler_compile_ast_extract(ast, glb);
  if (ast->type == StoreIndexStatement)     return MerCompiler_compile_ast_store_index_statement(ast, glb);
  if (ast->type == ForInStatement)          return MerCompiler_compile_ast_for_in_statement(ast, glb);
  if (ast->type == LoopStatement)           return MerCompiler_compile_ast_loop(ast, glb);
  if (ast->type == BreakStatement)          return MerCompiler_compile_ast_break(ast, glb);
  if (ast->type == ContinueStatement)       return MerCompiler_compile_ast_continue(ast, glb);
  if (ast->type == TrueExpression)          return MerCompiler_compile_ast_true(ast, glb);
  if (ast->type == FalseExpression)         return MerCompiler_compile_ast_false(ast, glb);
  if (ast->type == AndExpression)           return MerCompiler_compile_ast_and_expression(ast, glb);
  if (ast->type == NotExpression)           return MerCompiler_compile_ast_not_expression(ast, glb);
  if (ast->type == OrExpression)            return MerCompiler_compile_ast_or_expression(ast, glb);
  if (ast->type == ImportStatement)         return MerCompiler_compile_ast_import(ast, glb);
  if (ast->type == DefineStatement)         return MerCompiler_compile_ast_define(ast, glb);
  if (ast->type == DefineExpression)        return MerCompiler_compile_ast_define_expression(ast, glb);
  if (ast->type == IncludeStatement)        return MerCompiler_compile_ast_include(ast, glb);
  if (ast->type == ClassStatement)          return MerCompiler_compile_ast_class_statement(ast, glb);
  if (ast->type == AttrExpression)          return MerCompiler_compile_ast_attribute_expression(ast, glb);

  return NULL_CODE;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_attribute_expression(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;

  Mer_real_string class_name = ast->attr_iden;
  Mer_uint8_t class_address = NULL_UINT_8_T;

  bool found = false;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == class_name) {
      class_address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found class while compiling", glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, class_address);

  glb.is_in_func = true;

  for (auto &item : ast->attrs) {
    if (item->type == Identifier_) {
      __Mer_return_Code code = NULL_CODE;
      Mer_uint8_t address = NULL_UINT_8_T;
      bool found = false;

      for (auto &item2 : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
        if (item2->__name == item->string_iden) {
          address = item2->__Address;
          found = true;
          break;
        }
      }

      if (!found) {
        string msg = "Error cannot found attribute '" + item->string_iden + "' while compiling";
        MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
      }

      PUSH(code, CLOAD_ATTR);
      PUSH(code, address);

      INSERT_VEC(result, code);
    } else if (item->type == FunctionCallExpression) {
      __Mer_return_Code code = NULL_CODE;
      Mer_uint8_t address = NULL_UINT_8_T;
      bool found = false;

      for (auto &item2 : GLOBAL_TABLE) {
        if (item2->__name == item->func_call) {
          address = item2->__Address;
          found = true;
          break;
        }
      }

      if (!found) {
        string msg = "Error cannot found attribute '" + item->string_iden + "' while compiling";
        MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
      }

      PUSH(code, CLOAD_METHOD);
      PUSH(code, address);

      PUSH(code, CCALL_METHOD);

      INSERT_VEC(result, code);
    }
  }

  glb.is_in_func = false;

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_class_statement(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;

  Mer_uint8_t class_address = create_label(glb);        

  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(class_address, ast->class_name.c_str(), ast->class_name));

  glb.is_in_func = true;

  PUSH(result, CCLASS_BEGIN);

  for (auto &item : ast->members) {
    __Mer_return_Code code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(result, code);
  }
  
  PUSH(result, CCLASS_END);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, class_address);

  glb.is_in_func = false;

  return result;

}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_define_expression(mAST_T *ast, __compiler_u &glb) {
  bool found = false;
  mCode_T code = NULL_CODE;
  for (auto &item : code_s) {
    if (item.name == ast->string_iden) {
      found = true;
      code = item.code;
      break;
    }
  }

  if (!found) {
    string msg = ast->string_iden + " not defined";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  return code;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_define(mAST_T *ast, __compiler_u &glb) {
  mCode_T code = MerCompiler_compile_ast_id(ast->define_val, glb);
  code_s.push_back(code_stack {create_label(glb), ast->string_iden, code});
  return NULL_CODE;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_id_expression_statment(mAST_T *ast, __compiler_u &glb) {
  
  __Mer_return_Code code = NULL_CODE;
  code.cfile = ast->file;

  mAST_T *root;
  if (ast->children[0]->type == ExpressionStatement) {
    root = ast->children[0];
  }

  PUSH(code, CPROGRAM_START);
  
  for (auto child : root->children) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(code, CPROGRAM_END);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_id_expression_statment] [pass]" << endl;
  #endif
  return code;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_import(mAST_T *ast, __compiler_u &glb) {
  string path = ast->string_iden;

  if (glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Can not import in function", glb.file, ast->true_line);
  }

  for (auto &item : import) {
    if (item == path) {
      MerDebug_print_error(COMPILER_ERROR, "File already imported", glb.file, ast->true_line);
    }
  }

  import.push_back(path);

  vector<string> paths = list_files_in_folder("C:\\MercuryLang\\Libs");
  const char *buff;
  bool found = false;
  for (auto &item : paths) {
    if (item == path) {
      path = "C:\\MercuryLang\\Libs\\" + item;
      buff = MerBuffer_read_file(path);
      found = true;
      break; 
    }
  }

  if (!found) {
    paths = list_folder("C:\\MercuryLang\\Libs\\__Libs__");
    for (auto &item : paths) {
      if (item == path) {
        path = "C:\\MercuryLang\\Libs\\__Libs__\\" + item + "\\main.mer";
        buff = MerBuffer_read_file(path);
        import.push_back(path);
        found = true;
        break; 
      }
    }

    if (!found) {
      MerDebug_print_error(COMPILER_ERROR, "File not found, make sure it exists in ..\\MercuryLang\\Libs or ..\\MercuryLang\\Libs\\__Libs__", glb.file, ast->true_line);
    }
  }

  mLexer_T *lexer = _MerLexer_init(buff);
  mParser_T *parser = _MerParser_init(lexer);
  mAST_T *new_ast = MerParser_parse_program(parser);
  mCode_T code = NULL_CODE;

  mAST_T *root;
  if (new_ast->children[0]->type == ExpressionStatement) {
    root = new_ast->children[0];
  }

  for (auto child : root->children) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }
  
  return code;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_include(mAST_T *ast, __compiler_u &glb) {
  string path = ast->string_iden;
  if (glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Can not include in function", glb.file, ast->true_line);
  }

  for (auto &item : import) {
    if (item == path) {
      MerDebug_print_error(COMPILER_ERROR, "File already imported", glb.file, ast->true_line);
    }
  }

  // check if file is .mer
  if (path.find(".mer") == string::npos) {
    MerDebug_print_error(COMPILER_ERROR, "Include file must be .mer", glb.file, ast->true_line);
  }

  import.push_back(path);
  const char* buff = MerBuffer_read_file(path);

  mLexer_T *lexer = _MerLexer_init(buff);
  mParser_T *parser = _MerParser_init(lexer);
  mAST_T *new_ast = MerParser_parse_program(parser);
  mCode_T code = NULL_CODE;

  mAST_T *root;
  if (new_ast->children[0]->type == ExpressionStatement) {
    root = new_ast->children[0];
  }

  for (auto child : root->children) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }
  
  return code;
}


MERCURY_API __Mer_return_Code MerCompiler_compile_ast_or_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T left = MerCompiler_compile_ast_id(ast->left, glb);
  mCode_T right = MerCompiler_compile_ast_id(ast->right, glb);
  INSERT_VEC(result, left);
  INSERT_VEC(result, right);
  PUSH(result, COR);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_call_with_args(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T args = NULL_CODE;
  
  Mer_uint8_t address = NULL_UINT_8_T;
  Mer_uint8_t args_size = NULL_UINT_8_T;
  bool found = false;
  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__Name == ast->func_call) {
      address = item->__Address;
      args_size = item->args_size;
      found = true;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found global function while compiling", glb.file, ast->true_line);
  }


  for (auto &item : ast->args) {
    mCode_T _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(args, _code);
    _code.prg_code.buff.clear();
  }

  INSERT_VEC(result, args);
  PUSH(result, CFUNCTION_CALL_WITH_ARGS);
  PUSH(result, address);
  PUSH(result, args_size);

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_not_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = MerCompiler_compile_ast_id(ast->not_expr, glb);
  PUSH(result, CNOT);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_and_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T left = MerCompiler_compile_ast_id(ast->left, glb);
  mCode_T right = MerCompiler_compile_ast_id(ast->right, glb);
  
  INSERT_VEC(result, left);
  INSERT_VEC(result, right); 

  PUSH(result, CAND);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_with_args(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T body = NULL_CODE;
  Mer_uint8_t size = ast->args_idens.size();
  Mer_uint8_t func_address = create_label(glb);
  
  for (auto &node : ast->args_idens) {
    Mer_uint8_t address = create_label(glb);
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, node.c_str(), node));
  }

  __global *func_glb = CREAT_GLOBAL_TABLE(func_address, ast->func_name.c_str(), ast->func_name);
  func_glb->args_size = size;
  GLOBAL_TABLE.push_back(func_glb);

  for (auto &node : ast->body) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(node, glb);
    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CMAKE_FUNCTION_WITH_ARGS);
  PUSH(result, func_address);
  PUSH(result, size);

  INSERT_VEC(result, body);

  PUSH(result, CRETURN);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_true(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  PUSH(result, CLOAD_TRUE);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_false(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  PUSH(result, CLOAD_FALSE);
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_break(mAST_T *ast, __compiler_u &glb) {
    __Mer_return_Code result = NULL_CODE;
    if (glb.loop.empty()) {
        MerDebug_print_error(COMPILER_ERROR, "break outside of loop", glb.file, ast->true_line);
        return result;
    }

    PUSH(result, CJUMP_TO);
    PUSH(result, glb.loop.back().break_label);
    return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_continue(mAST_T *ast, __compiler_u &glb) {
    __Mer_return_Code result = NULL_CODE;
    if (glb.loop.empty()) {
        MerDebug_print_error(COMPILER_ERROR, "continue outside of loop", glb.file, ast->true_line);
        return result;
    }

    PUSH(result, CJUMP_TO);
    PUSH(result, glb.loop.back().continue_label);
    return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_loop(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code body = NULL_CODE;
  __Mer_return_Code _code = NULL_CODE;

  Mer_uint8_t label_start = create_label(glb);
  Mer_uint8_t label_end = create_label(glb);
  glb.loop.push_back(loop_stack { label_start, label_end });

  for (auto &node : ast->do_body) {
    _code = MerCompiler_compile_ast_id(node, glb);
    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CADDRESS);
  PUSH(result, label_start);
  
  INSERT_VEC(result, body);
  PUSH(result, CJUMP_TO);
  PUSH(result, label_start); 

  PUSH(result, CADDRESS);
  PUSH(result, label_end);

  glb.loop.pop_back();

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_store_index_statement(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code mul_extract = NULL_CODE;
  __Mer_return_Code value = MerCompiler_compile_ast_id(ast->array_store_value, glb);
  __Mer_return_Code index = MerCompiler_compile_ast_id(ast->array_store->extract_value, glb);

  Mer_uint8_t list_address = NULL_UINT_8_T;  
  Mer_real_string list_name = ast->array_store->extract_name.c_str();

  bool found = false;
  for (auto &global : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (global->__name == ast->array_store->extract_name) {
      list_address = global->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "List not found, can not store value in list", glb.file, ast->true_line);
  }

  if (ast->array_store->is_mul_extract) {
      PUSH(result, CLOAD_GLOBAL);
      PUSH(result, list_address);

      INSERT_VEC(result, index);
      PUSH(result, CGET_ITEM);

      size_t size = ast->array_store->mul_extract.size();
      size_t id = 0;

      for (auto &node : ast->array_store->mul_extract) {
          mul_extract = MerCompiler_compile_ast_id(node, glb);

          if (id < size - 1) {
              INSERT_VEC(result, mul_extract);
              PUSH(result, CGET_ITEM);
          } else {
              INSERT_VEC(result, mul_extract);
          }

          id++;
      }

      INSERT_VEC(result, value);
      PUSH(result, CSTORE_INDEX);

      return result;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, list_address);

  INSERT_VEC(result, index);

  INSERT_VEC(result, value);
  PUSH(result, CSTORE_INDEX);

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_extract(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;

  bool found = false;
  Mer_uint8_t list_address = NULL_UINT_8_T;

  if (ast->is_value_extract) {
    __Mer_return_Code value = MerCompiler_compile_ast_id(ast->extract_value, glb);
    __Mer_return_Code result = NULL_CODE;
    __Mer_return_Code index = NULL_CODE;

    INSERT_VEC(result, value);

    for (auto &item : ast->mul_extract) {
      __Mer_return_Code _code = MerCompiler_compile_ast_id(item, glb);
      INSERT_VEC(result, _code);
      PUSH(result, CGET_ITEM);
    }

    return result;
  }

  for (auto &global : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (global->__name == ast->extract_name) {
      found = true;
      list_address = global->__Address;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "List not found, can not extract value from list", glb.file, ast->true_line);
  }

  __Mer_return_Code _code = MerCompiler_compile_ast_id(ast->extract_value, glb);
  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, list_address);

  INSERT_VEC(result, _code);
  PUSH(result, CGET_ITEM);

  if (ast->is_mul_extract) {
    for (auto &item : ast->mul_extract) {
      __Mer_return_Code _code = MerCompiler_compile_ast_id(item, glb);
      INSERT_VEC(result, _code);
      PUSH(result, CGET_ITEM);
    }
  }

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_array(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code array = NULL_CODE;

  if (ast->type != ArrayExpression) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating array", glb.file, ast->true_line);
  }
  
  if (!ast->is_alone_val) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating array", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->list.size();

  for (auto &item : ast->list) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(array, _code);
  }

  INSERT_VEC(result, array);
  PUSH(result, CBUILD_LIST);
  PUSH(result, size);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_array] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_list(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code list = NULL_CODE;

  if (ast->type != ListStatement) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating list", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->list.size();
  Mer_uint8_t address = create_label(glb);

  for (auto &item : ast->list) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(list, _code);
  }

  INSERT_VEC(result, list);
  PUSH(result, CBUILD_LIST);
  PUSH(result, size);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, address);

  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, ast->list_name.c_str(), ast->list_name));

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_list] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_string_identifier(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code str = NULL_CODE;
  
  if (ast->type != StringIdentifier) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating string identifier", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->str_v.size();
  
  vector<Mer_uint8_t> str_v;
  for (auto &item : ast->str_v) {
    str_v.push_back(item);
  }

  str.prg_code.buff.insert(str.prg_code.buff.end(), str_v.begin(), str_v.end());

  PUSH(result, CPUSH_NORMAL_MODE);
  PUSH(result, size);
  INSERT_VEC(result, str);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_string_identifier] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_assign(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code _ass = NULL_CODE;
  if (!ast->assign_value) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid assign statement", glb.file, ast->true_line);
  }

  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t address;
  bool found = false;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == ast->assign_iden) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    address = create_label(glb);
    glb.is_in_func ? LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(address, ast->assign_iden.c_str(), ast->assign_iden)) : GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, ast->assign_iden.c_str(), ast->assign_iden));
  }

  if (ast->is_assign_operator) {
    if (!found) {
      MerDebug_print_error(COMPILER_ERROR, "Variable not found, can not assign to it", glb.file, ast->true_line);
    }

    Mer_uint8_t opcode = NULL_UINT_8_T;
    if (ast->is_plus_assign) {
      opcode = CBINARY_ADD;
    } else if (ast->is_minus_assign) {
      opcode = CBINARY_SUB;
    } else if (ast->is_mul_assign) {
      opcode = CBINARY_MUL;
    } else if (ast->is_div_assign) {
      opcode = CBINARY_DIV;
    } else if (ast->is_mod_assign) {
      opcode = CBINARY_MOD;
    } else {
      MerDebug_system_error(COMPILER_ERROR, "Invalid assign operator", glb.file);
    }

    PUSH(_ass, CLOAD_GLOBAL);
    PUSH(_ass, address);

    __Mer_return_Code _code = MerCompiler_compile_ast_id(ast->assign_value, glb);
    INSERT_VEC(_ass, _code);

    PUSH(_ass, opcode);

    INSERT_VEC(result, _ass);
    PUSH(result, CSTORE_GLOBAL);
    PUSH(result, address);
  } else {
    _ass = MerCompiler_compile_ast_id(ast->assign_value, glb);
    INSERT_VEC(result, _ass);
    PUSH(result, CSTORE_GLOBAL);
    PUSH(result, address);
  }

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_assign] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_while(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code while_cond = MerCompiler_compile_ast_id(ast->while_cond, glb);
  __Mer_return_Code while_body = NULL_CODE;
  __Mer_return_Code _code = NULL_CODE;

  Mer_uint8_t while_begin = create_label(glb);
  Mer_uint8_t while_end = create_label(glb);

  glb.loop.push_back(loop_stack { while_begin, while_end });

  for (auto child : ast->while_body) {
    _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(while_body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CADDRESS);
  PUSH(result, while_begin);

  INSERT_VEC(result, while_cond);

  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, while_end);

  INSERT_VEC(result, while_body);

  PUSH(result, CJUMP_TO);
  PUSH(result, while_begin);

  PUSH(result, CADDRESS);
  PUSH(result, while_end);

  glb.loop.pop_back();

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_while] [pass]" << endl;
  #endif
  
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_for_in_statement(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code for_body = NULL_CODE;
  __Mer_return_Code for_loop_iter = NULL_CODE;

  bool found = false;

  Mer_uint8_t __iter = create_label(glb);
  Mer_uint8_t __i = create_label(glb);
  Mer_uint8_t __value = create_label(glb);

  Mer_uint8_t loop_start = create_label(glb);
  Mer_uint8_t loop_end = create_label(glb);

  glb.loop.push_back(loop_stack { loop_start, loop_end });

  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__iter, __iter__, __iter__));
  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__i, __i__, __i__));

  LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__iter, __iter__, __iter__));
  LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__i, __i__, __i__));


  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == ast->in_iden) {
      __value = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__value, ast->in_iden.c_str(), ast->in_iden));
    LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__value, ast->in_iden.c_str(), ast->in_iden));
  }

  for (auto child : ast->in_body) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(for_body, _code);
    _code.prg_code.buff.clear();
  }

  for_loop_iter = MerCompiler_compile_ast_id(ast->in_value, glb);

  INSERT_VEC(result, for_loop_iter);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CPUSH_FLOAT);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x00);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CADDRESS);
  PUSH(result, loop_start);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CLEN);
  
  PUSH(result, CLESS);

  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, loop_end);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CGET_ITEM);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __value);

  INSERT_VEC(result, for_body);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CPUSH_FLOAT);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x80);
  PUSH(result, 0x3F);

  PUSH(result, CBINARY_ADD);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CJUMP_TO);
  PUSH(result, loop_start);

  PUSH(result, CADDRESS);
  PUSH(result, loop_end);

  glb.loop.pop_back();  

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_for_in_statement] [pass]" << endl;
  #endif
  
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_literal(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t cval[sizeof(float)];

  memcpy(cval, &ast->value, sizeof(float));
  result.prg_code.buff.push_back(CPUSH_FLOAT);
  result.prg_code.buff.insert(result.prg_code.buff.end(), cval, cval + sizeof(float));

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_literal] [pass]" << endl;
  #endif
  return result;  
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_binary_expression(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code _left = MerCompiler_compile_ast_id(ast->left, glb);
  __Mer_return_Code _right = MerCompiler_compile_ast_id(ast->right, glb);

  Mer_uint8_t _oper;
  if (ast->op == PLUS)           _oper = CBINARY_ADD;
  else if (ast->op == MINUS)     _oper = CBINARY_SUB;
  else if (ast->op == DIV)       _oper = CBINARY_DIV;
  else if (ast->op == MOD)       _oper = CBINARY_MOD;
  else if (ast->op == TIME)      _oper = CBINARY_MUL;
  else if (ast->op == POW)       _oper = CBINARY_POW;

  __Mer_return_Code result = NULL_CODE;
  
  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_binary_expression] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function_call(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;

  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->func_call.c_str());
  __global *func;
  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == name && !item->is_let) {
      address = item->__Address;
      found = true;
      func = item;
      break;
    }
  }

  if (!found and glb.is_in_func) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__name == name && !item->is_let) {
        address = item->__Address;
        found = true;
        func = item;
        break;
      }
    }
  }

  if (!found) {
    Mer_real_string str = ast->func_call.c_str();
    if (str == "print") {
      Mer_real_string msg = "Function not found '" + str + "', you forgot to import \"IO\"?";
      MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    }
    Mer_real_string msg = "Function not found '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    return NULL_CODE;
  }

  Mer_size_t args_size = 0;
  if (ast->is_having_args) {
    for (auto child : ast->args) {
      __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
      INSERT_VEC(result, _code);
      _code.prg_code.buff.clear();
      ++args_size;
    }
  }

  if (is_a_builtin(ast->func_call)) {
    // do nothing
  } else if (args_size > func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Too many arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  } else if (args_size < func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Not enough arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);
  PUSH(result, CFUNCTION_CALL);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_function_call] [pass]" << endl;
  #endif

  return result;    
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_if(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code comp = NULL_CODE;
  __Mer_return_Code if_body = NULL_CODE;
  __Mer_return_Code else_body = NULL_CODE;
  
  comp = MerCompiler_compile_ast_id(ast->comp, glb);
  
  if (!ast->comp) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid if statement", glb.file, ast->true_line);
  }

  Mer_uint8_t end_if = create_label(glb);
  Mer_uint8_t label_else = create_label(glb);

  for (auto child : ast->then_body) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(if_body, _code);
    _code.prg_code.buff.clear();
  }

  INSERT_VEC(result, comp);
  
  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, label_else);

  INSERT_VEC(result, if_body);
  
  PUSH(result, CJUMP_TO);
  PUSH(result, end_if);

  PUSH(result, CADDRESS);
  PUSH(result, label_else);

  if (ast->has_elif) {
    for (auto &child : ast->elif_body) {
      __Mer_return_Code elifcomp = MerCompiler_compile_ast_id(child->comp, glb);
      __Mer_return_Code elifbody = NULL_CODE;

      for (auto child : child->then_body) {
        __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
        INSERT_VEC(elifbody, _code);
        _code.prg_code.buff.clear();
      }

      label_else = create_label(glb);

      INSERT_VEC(result, elifcomp);
      
      PUSH(result, CPOP_JUMP_IF_FALSE);
      PUSH(result, label_else);
      
      INSERT_VEC(result, elifbody);
      
      PUSH(result, CJUMP_TO);
      PUSH(result, end_if);
    }
  }

  PUSH(result, CADDRESS);
  PUSH(result, label_else);
  
  if (ast->has_else) {
    for (auto child : ast->else_body) {
      __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
      INSERT_VEC(else_body, _code);
      _code.prg_code.buff.clear();
    }

    INSERT_VEC(result, else_body);
  }

  PUSH(result, CADDRESS);
  PUSH(result, end_if);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_if] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_let(mAST_T *ast, __compiler_u &glb) {
  Mer_string name = strdup(ast->var_name.c_str());
  Mer_real_string real_name = ast->var_name;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == real_name) {
      found = true;
      address = item->__Address;
    }
  }

  __Mer_return_Code var_val = MerCompiler_compile_ast_id(ast->var_value, glb);
  __Mer_return_Code result = NULL_CODE;

  if (!found) {
    address = create_label(glb);
    glb.is_in_func ? LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(address, name, real_name)) : GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, name, real_name));
  }

  INSERT_VEC(result, var_val);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_let] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_return(mAST_T *ast, __compiler_u &glb) {
  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_return] [building]" << endl;
  #endif

  if (!glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Return outside of function", glb.file, ast->true_line);
  }

  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code ret_val = MerCompiler_compile_ast_id(ast->return_v, glb);
  
  INSERT_VEC(result, ret_val);
  PUSH(result, CRETURN);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_return] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_identifier(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->string_iden.c_str());
  if (name != ast->string_iden) {
    MerDebug_system_error(COMPILER_ERROR, "Invalid identifier", glb.file);
  }

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == name && item->is_let) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found and glb.is_in_func) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__name == name && !item->is_let) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    string msg = "Variable not found '" + ast->string_iden + "'";
    MerDebug_system_error(COMPILER_ERROR, msg.c_str(), glb.file);
    return NULL_CODE;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_identifier] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_program(mAST_T *ast, __compiler_u &glb) {
  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_program] [start]" << endl;
  #endif

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_program] [pass]" << endl;
  #endif

  return MerCompiler_compile_ast_id_expression_statment(ast, glb);
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_string_var(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  Mer_string name = strdup(ast->str_var_name.c_str());
  Mer_real_string real_name = ast->str_var_name;
  glb.address += 0x0001;

  __Mer_return_Code str_val = MerCompiler_compile_ast_id(ast->str_var_value, glb);
  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(glb.address, name, real_name));

  INSERT_VEC(result, str_val);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, glb.address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_string_var] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_function(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code result = NULL_CODE;
  __Mer_return_Code body = NULL_CODE;
  Mer_uint8_t func_address = create_label(glb);
  Mer_real_string name = ast->func_name;
  Mer_string func_name = strdup(ast->func_name.c_str());
  Mer_uint8_t args_size = ast->args_size;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == func_name) {
      Mer_real_string msg = "Function already defined: '" + ast->func_name + "'";
      MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    }
  }

  __global *glb_tab = CREAT_GLOBAL_TABLE(func_address, func_name, name);
  glb_tab->is_let = false; 
  glb_tab->args_size = args_size;

  if (ast->is_having_args) {
    for (auto &item : ast->args_idens) {
      LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(create_para(glb), item.c_str(), item));
      ++glb_tab->true_args_size;
    }
  }

  GLOBAL_TABLE.push_back(glb_tab);

  glb.is_in_func = true;
  for (auto child : ast->body) {
    __Mer_return_Code _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }
  glb.is_in_func = false;

  PUSH(result, CMAKE_FUNCTION);
  
  PUSH(result, func_address);
  PUSH(result, args_size);

  INSERT_VEC(result, body);
  
  PUSH(result, CEND_FUNCTION);

  LOCAL_TABLE.clear();
  glb.para_address = NULL_UINT_8_T;

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_function] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API __Mer_return_Code MerCompiler_compile_ast_comparison_expression(mAST_T *ast, __compiler_u &glb) {
  __Mer_return_Code _left = MerCompiler_compile_ast_id(ast->comp_left, glb);
  __Mer_return_Code _right = MerCompiler_compile_ast_id(ast->comp_right, glb);

  __Mer_return_Code result = NULL_CODE;
  Mer_uint8_t _oper;

  if (ast->comp_op == EQUAL) _oper = CEQUAL;
  else if (ast->comp_op == NOT_EQUAL) _oper = CNOT_EQUAL;
  else if (ast->comp_op == LESS) _oper = CLESS;
  else if (ast->comp_op == LESS_EQUAL) _oper = CLESS_EQUAL;
  else if (ast->comp_op == GREATER) _oper = CGREATER;
  else if (ast->comp_op == GREATER_EQUAL) _oper = CGREATER_EQUAL;
  else if (ast->comp_op == IS) _oper = CIS;

  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_comparison_expression] [pass]" << endl;
  #endif

  return result;
}