#include "bceval.h"

stack *MerCompilerBytecode_evaluate_program(vector<uint8_t> code) {
  ctoken ptoken = MerByteCodeTokenize_tokenize_program(code);
  stack *stk = MerCompiler_Stack_new();
  return stk = MerCompilerBytecode_evaluate_statement(ptoken, stk);
}

stack *MerCompilerBytecode_evaluate_statement(ctoken ptoken, stack *stk) {
    size_t tok_idx = 0;

    while (tok_idx < ptoken.ctokens.size()) {
        stk = MerCompilerBytecode_evaluate(ptoken.ctokens[tok_idx], stk);
        tok_idx++;
    }

    return stk;
}

stack *MerCompilerBytecode_evaluate(ctoken ptoken, stack *stk) {
  switch (ptoken.code) {
    case PUSH_FLOAT:
      stk = MerCompilerBytecode_evaluate_PUSH_FLOAT(ptoken, stk);
      break;
    case LOAD_GLOBAL:
      stk = MerCompilerBytecode_evaluate_LOAD_GLOBAL(ptoken, stk);
      break;
    case STORE_GLOBAL:
      stk = MerCompilerBytecode_evaluate_STORE_GLOBAL(ptoken, stk);
      break;
    case BINARY_ADD:
      stk = MerCompilerBytecode_evaluate_BINARY_ADD(ptoken, stk);
      break;
    case BINARY_SUB:
      stk = MerCompilerBytecode_evaluate_BINARY_SUB(ptoken, stk);
      break;
    case BINARY_MUL:
      stk = MerCompilerBytecode_evaluate_BINARY_MUL(ptoken, stk);
      break;
    case BINARY_DIV:
      stk = MerCompilerBytecode_evaluate_BINARY_DIV(ptoken, stk);
      break;
  }
  return stk;
}

stack *MerCompilerBytecode_evaluate_PUSH_FLOAT(ctoken ptoken, stack *stk) {
  stk->s_table->table.push_back(MerCompiler_table_setup(ptoken.rval));
  return stk;
}

stack *MerCompilerBytecode_evaluate_POP_NORMAL_MODE(ctoken ptoken, stack *stk) {
  stk->s_table->table.pop_back();
  return stk;
}

stack *MerCompilerBytecode_evaluate_LOAD_GLOBAL(ctoken ptoken, stack *stk) {
  for (auto &sym : stk->s_symtable->stack) {
    if (sym->address == ptoken.address) {
      stk->s_table->table.push_back(MerCompiler_table_setup(sym->value));
      break;
    }
  }
  return stk;
}

stack *MerCompilerBytecode_evaluate_STORE_GLOBAL(ctoken ptoken, stack *stk) {
  table *vval = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup("<address...>", vval->cval, "AUTO_T", ptoken.address));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_ADD(ctoken ptoken, stack *stk) {
  table *t1 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  table *t2 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(t1->cval, t2->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_DIV(ctoken ptoken, stack *stk) {
  table *t1 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  table *t2 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(t2->cval, t1->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_MUL(ctoken ptoken, stack *stk) {
  table *t1 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  table *t2 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(t2->cval, t1->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_SUB(ctoken ptoken, stack *stk) {
  table *t1 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  table *t2 = stk->s_table->table.back();
  stk->s_table->table.pop_back();
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(t2->cval, t1->cval)));
  return stk;
}


