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
MERCURY_API Mer_uint8_t __get_next_code_in_out_code(__program_bytecode &u) {
  return u.code.out_code.buff[u.oid++];
}

MERCURY_API stack *eval_program(mCode_T &code) {
  stack *stk = MerCompiler_Stack_new();
  __program_bytecode prg = {code, 0, 0, NULL_UINT_8_T, NULL_UINT_8_T};
  stk = eval_statement(prg, stk);
  return stk;
}

MERCURY_API stack *eval_statement(__program_bytecode &u, stack *stk) {
  for (;;) {
    Mer_uint8_t code = __get_next_code_in_prg_code(u);
    if (code == CPUSH_FLOAT) {
      if (u.iid + 4 < u.code.prg_code.buff.size()) {
        Mer_uint32_t int_repr;
        Mer_float float_repr;
        memcpy(&int_repr, &u.code.prg_code.buff[u.iid], 4);
        memcpy(&float_repr, &int_repr, 4);
        stk->s_table->table.push_back(MerCompiler_table_setup(float_repr, NULL_UINT_8_T));
      }
      u.iid += 4;
    } else if (code == CBINARY_ADD) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(left->cval, right->cval)));
    } else if (code == CBINARY_SUB) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(left->cval, right->cval)));
    } else if (code == CBINARY_MUL) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(left->cval, right->cval)));
    } else if (code == CBINARY_DIV) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(left->cval, right->cval)));
    } else if (code == CLOAD_GLOBAL) {
      code = __get_next_code_in_prg_code(u);
      for (int i = 0; i < stk->s_symtable->stack.size(); i++) {
        if (stk->s_symtable->stack[i]->address == code) {
          stk->s_table->table.push_back(MerCompiler_table_setup(stk->s_symtable->stack[i]->value, stk->s_symtable->stack[i]->address));
          break;
        }
      }
    } else if (code == CSTORE_GLOBAL) {
      code = __get_next_code_in_prg_code(u);
      table *vval = pop_stack(stk);
      stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup("<address...>", vval->cval, "AUTO_T", code));
    } else if (code == CMAKE_FUNCTION) {
      code = __get_next_code_in_prg_code(u);
      stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup("<address...>", 0, "FUNCTION", code));
      while (code != CRETURN) {
        code = __get_next_code_in_prg_code(u);
        stk->s_symtable->stack.back()->tbody.push_back(code);
      }
    } else if (code == CFUNCTION_CALL) {
      code = __get_next_code_in_prg_code(u);
      vector<Mer_uint8_t> body;

      for (int i = 0; i < stk->s_symtable->stack.size(); i++) {
        if (code == stk->s_symtable->stack[i]->address) {
          body = stk->s_symtable->stack[i]->tbody;
          break;
        } 
      }
      
      mCode_T body_c = NULL_CODE;
      body_c.prg_code.buff.insert(body_c.prg_code.buff.end(), body.begin(), body.end());
      __program_bytecode body_u = {body_c, 0, 0, NULL_UINT_8_T, NULL_UINT_8_T};
      stk = eval_statement(body_u, stk);
    } else if (code == CLESS) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS(left->cval, right->cval)));
    } else if (code == CGREATER) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER(left->cval, right->cval)));
    } else if (code == CEQUAL) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_EQUAL(left->cval, right->cval)));
    } else if (code == CNOT_EQUAL) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_NOT_EQUAL(left->cval, right->cval)));  
    } else if (code == CGREATER_EQUAL) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER_EQUAL(left->cval, right->cval)));
    } else if (code == CLESS_EQUAL) {
      table *right = pop_stack(stk);
      table *left = pop_stack(stk);
      if (left == nullptr || right == nullptr) {
        cerr << "Error: Stack underflow" << endl;
        return stk;
      }
      stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS_EQUAL(left->cval, right->cval)));
    } else if (code == CRETURN) {
      break;
    }
    else if (code == CPROGRAM_END) {
      break;
    }
  }

  return stk;
}
