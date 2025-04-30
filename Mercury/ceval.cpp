#include "./include/ceval.h"

table *pop_stack(stack *stk)
{
  if (stk->s_table->table.empty())
  {
    cerr << "Error: Stack underflow" << endl;
    break_point();
    return nullptr;
  }
  table *top = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  return top;
}

table *eat_stack(stack *stk)
{
  if (stk->s_table->table.empty())
  {
    cerr << "Error: Stack underflow" << endl;
    cerr << "eat_stack" << endl;
    return nullptr;
  }
  table *top = stk->s_table->table.back();
  return top;
}

void push_stack(stack *stk, int value)
{
  stk->s_table->table.push_back(MerCompiler_table_setup(value));
}

MERCURY_API Mer_uint8_t __get_next_code_in_prg_code(__program_bytecode &u) {
  return u.code.prg_code.buff[u.iid++];
}

MERCURY_API stack *eval_program(mCode_T &code) {
  __program_bytecode u_program = {code, 0, 0, NULL_UINT_8_T, NULL_UINT_8_T};
  stack *stk = MerCompiler_Stack_new();
  return eval_statement(u_program, stk);
}

MERCURY_API stack *eval_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
  table *top = pop_stack(stk);
  if (IS_FALSE(top->cval)) {
    CONST(Mer_uint8_t) address = __get_next_code_in_prg_code(u);
    Mer_uint8_t code = address;
    for (;;) {
      code = __get_next_code_in_prg_code(u);
      if (code == CADDRESS) {
        code = __get_next_code_in_prg_code(u);
        if (code == address) {
          break;
        } else {
          continue;
        }
      }
    }
  }

  return stk;
}

MERCURY_API stack *eval_statement(__program_bytecode &u, stack *stk) {
  for (;;) {
    Mer_uint8_t code = __get_next_code_in_prg_code(u);
    if (code == CPUSH_FLOAT) {
      stk = eval_PUSH_FLOAT(u, stk);
    } else if (code == CBINARY_ADD || code == CBINARY_SUB || code == CBINARY_MUL || code == CBINARY_DIV) {
      stk = eval_BINARY_OPER(u, stk, code);
    } else if (code == CLOAD_GLOBAL) {
      stk = eval_LOAD_GLOBAL(u, stk);
    } else if (code == CSTORE_GLOBAL) {
      stk = eval_STORE_GLOBAL(u, stk);
    } else if (code == CMAKE_FUNCTION) {
      stk = eval_MAKE_FUNCTION(u, stk);
    } else if (code == CFUNCTION_CALL) {
      stk = eval_FUNCTION_CALL(u, stk);
    } else if (code == CGREATER || code == CEQUAL || code == CNOT_EQUAL || code == CGREATER_EQUAL || code == CLESS_EQUAL || code == CLESS) {
      stk = eval_COMPARE(u, stk, code);
    } else if (code == CRETURN) {
      break;
    } else if (code == CPOP_JUMP_IF_FALSE) {
      stk = eval_POP_JUMP_IF_FALSE(u, stk);
    } 
    else if (code == CPROGRAM_END) {
      break;
    }
  }
  return stk;
}

MERCURY_API stack *eval_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
  table *right = pop_stack(stk);
  table *left = pop_stack(stk);
  if (left == nullptr || right == nullptr) {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  if (op == CLESS) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS(left->cval, right->cval)));
  } else if (op == CGREATER) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER(left->cval, right->cval)));
  } else if (op == CEQUAL) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_EQUAL(left->cval, right->cval)));
  } else if (op == CNOT_EQUAL) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_NOT_EQUAL(left->cval, right->cval)));
  } else if (op == CGREATER_EQUAL) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER_EQUAL(left->cval, right->cval)));
  } else if (op == CLESS_EQUAL) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS_EQUAL(left->cval, right->cval)));
  }
  return stk;
}

MERCURY_API stack *eval_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
  table *right = pop_stack(stk);
  table *left = pop_stack(stk);
  if (left == nullptr || right == nullptr) {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }

  if (op == CBINARY_ADD) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(left->cval, right->cval)));
  } else if (op == CBINARY_SUB) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(left->cval, right->cval)));
  } else if (op == CBINARY_MUL) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(left->cval, right->cval)));
  } else if (op == CBINARY_DIV) {
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(left->cval, right->cval)));
  }
  return stk;
}

MERCURY_API stack *eval_PUSH_FLOAT(__program_bytecode &u, stack *stk) {
  if (u.iid + 4 < u.code.prg_code.buff.size()) {
    Mer_uint32_t int_repr;
    Mer_float float_repr;
    memcpy(&int_repr, &u.code.prg_code.buff[u.iid], 4);
    memcpy(&float_repr, &int_repr, 4);
    stk->s_table->table.push_back(MerCompiler_table_setup(float_repr, NULL_UINT_8_T));
  }
  u.iid += 4;

  return stk;
}

MERCURY_API stack *eval_LOAD_GLOBAL(__program_bytecode &u, stack *stk) {
  Mer_uint8_t code = __get_next_code_in_prg_code(u);
  bool found = false;
  for (int i = 0; i < stk->s_symtable->stack.size(); i++) {
    if (stk->s_symtable->stack[i]->address == code) {
      stk->s_table->table.push_back(MerCompiler_table_setup(stk->s_symtable->stack[i]->value, stk->s_symtable->stack[i]->address));
      found = true;
      break;
    }
  }
  return stk;
}

MERCURY_API stack *eval_STORE_GLOBAL(__program_bytecode &u, stack *stk) {
  Mer_uint8_t code = __get_next_code_in_prg_code(u);
  table *vval = pop_stack(stk);
  stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup("<address...>", vval->cval, "AUTO_T", code));
  return stk;
}

MERCURY_API stack *eval_MAKE_FUNCTION(__program_bytecode &u, stack *stk) {
  Mer_uint8_t code = __get_next_code_in_prg_code(u);

  symtable *func = MerCompiler_symboltable_setup("<address...>", 0, "AUTO_T", code);

  while (code != CRETURN) {
    code = __get_next_code_in_prg_code(u);
    func->tbody.push_back(code);
  }

  func->tbody.push_back(CRETURN);
  stk->s_symtable->stack.push_back(func);
  return stk;
} 

MERCURY_API stack *eval_FUNCTION_CALL(__program_bytecode &u, stack *stk) {
  table *back = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  Mer_uint8_t address = back->address;
  mCode_T body_c;

  for (auto &func_v : stk->s_symtable->stack) {
    if (func_v->address == address) {
      body_c.prg_code.buff.insert(body_c.prg_code.buff.end(), func_v->tbody.begin(), func_v->tbody.end());
      break;
    }
  }

  __program_bytecode u_func = {body_c, 0, 0, NULL_UINT_8_T, NULL_UINT_8_T};
  stk = eval_statement(u_func, stk);
  return stk;
}

MERCURY_API stack *eval_MAKE_BLOCK(__program_bytecode &u, stack *stk) {
  Mer_uint8_t code = __get_next_code_in_prg_code(u);
  symtable *block = MerCompiler_symboltable_setup("<address...>", 0, "AUTO_T", code);
  while (code != CEND_BLOCK) {
    code = __get_next_code_in_prg_code(u);
    block->tbody.push_back(code);
  }
  block->tbody.push_back(CEND_BLOCK);
  stk->s_symtable->stack.push_back(block);
  return stk;
}

MERCURY_API stack *eval_POP_JUMP_IF_TRUE(__program_bytecode &u, stack *stk) {
  Mer_uint8_t code;
  table *top = pop_stack(stk);
  bool found = false;
  if (top->cval == 1) {
    code = __get_next_code_in_prg_code(u);
    for (auto &sym : stk->s_symtable->stack) {
      if (sym->address == code) {
        found = true;
        break;
      }
    }
  } else {
    code = __get_next_code_in_prg_code(u);
  }
  if (found) {
    mCode_T body_if = NULL_CODE;
    body_if.prg_code.buff = stk->s_symtable->stack.back()->tbody;
    __program_bytecode if_block = {body_if, 0, 0, NULL_UINT_8_T, NULL_UINT_8_T};
    stk = eval_statement(if_block, stk);
  }
  return stk;
}