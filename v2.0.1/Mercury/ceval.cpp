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

stack *MerCompilerBytecode_evaluate_program(vector<uint8_t> code)
{
  ctoken ptoken = MerByteCodeTokenize_tokenize_code(code);
  stack *stk = MerCompiler_Stack_new();
  return stk = MerCompilerBytecode_evaluate_statement(ptoken, stk);
}

stack *MerCompilerBytecode_evaluate_statement(ctoken ptoken, stack *stk)
{
  size_t tok_idx = 0;

  while (tok_idx < ptoken.ctokens.size())
  {
    ctoken btok = ptoken.ctokens[tok_idx];
    stk = MerCompilerBytecode_evaluate(btok, stk);
    tok_idx++;
  }

  return stk;
}

stack *MerCompilerBytecode_evaluate(ctoken ptoken, stack *stk)
{
  switch (ptoken.code)
  {
  case CPUSH_FLOAT:
    stk = MerCompilerBytecode_evaluate_PUSH_FLOAT(ptoken, stk);
    return stk;
  case CLOAD_GLOBAL:
    stk = MerCompilerBytecode_evaluate_LOAD_GLOBAL(ptoken, stk);
    return stk;
  case CSTORE_GLOBAL:
    stk = MerCompilerBytecode_evaluate_STORE_GLOBAL(ptoken, stk);
    return stk;
  case CBINARY_ADD:
    stk = MerCompilerBytecode_evaluate_BINARY_ADD(ptoken, stk);
    return stk;
  case CBINARY_SUB:
    stk = MerCompilerBytecode_evaluate_BINARY_SUB(ptoken, stk);
    return stk;
  case CBINARY_MUL:
    stk = MerCompilerBytecode_evaluate_BINARY_MUL(ptoken, stk);
    return stk;
  case CBINARY_DIV:
    stk = MerCompilerBytecode_evaluate_BINARY_DIV(ptoken, stk);
    return stk;
  case CPOP_NORMAL_MODE:
    stk = MerCompilerBytecode_evaluate_POP_NORMAL_MODE(ptoken, stk);
    return stk;
  case CFUNCTION_CALL:
    stk = MerCompilerBytecode_evaluate_FUNCTION_CALL(ptoken, stk);
    return stk;
  case CRETURN:
    stk = MerCompilerBytecode_evaluate_RETURN(ptoken, stk);
    return stk;
  case CMAKE_FUNCTION:
    stk = MerCompilerBytecode_evaluate_MAKE_FUNCTION(ptoken, stk);
    return stk;
  case CEQUAL:
    stk = MerCompilerBytecode_evaluate_EQUAL(ptoken, stk);
    return stk;
  case CNOT_EQUAL:
    stk = MerCompilerBytecode_evaluate_NOT_EQUAL(ptoken, stk);
    return stk;
  case CLESS:
    stk = MerCompilerBytecode_evaluate_LESS(ptoken, stk);
    return stk;
  case CLESS_EQUAL:
    stk = MerCompilerBytecode_evaluate_LESS_EQUAL(ptoken, stk);
    return stk;
  case CGREATER:
    stk = MerCompilerBytecode_evaluate_GREATER(ptoken, stk);
    return stk;
  case CGREATER_EQUAL:
    stk = MerCompilerBytecode_evaluate_GREATER_EQUAL(ptoken, stk);
    return stk;
  }
  return stk;
}

stack *MerCompilerBytecode_evaluate_EQUAL(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval == t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_NOT_EQUAL(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval != t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_LESS(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval < t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_LESS_EQUAL(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval <= t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_GREATER(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval > t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_GREATER_EQUAL(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(t1->cval >= t2->cval ? 1 : 0));
  return stk;
}

stack *MerCompilerBytecode_evaluate_FUNCTION_CALL(ctoken ptoken, stack *stk)
{
  table *func = stk->s_table->table.back();
  stk->s_table->table.pop_back();

  uint8_t faddress = func->address;
  vector<uint8_t> body;
  bool found = false;
  for (int i = 0; i < stk->s_symtable->stack.size(); i++)
  {
    if (stk->s_symtable->stack[i]->address == faddress)
    {
      body = stk->s_symtable->stack[i]->tbody;
      found = true;
      break;
    }
  }

  if (!found)
  {
    cerr << "Error: Function not found" << endl;
    return stk;
  };

  ctoken body_token = MerByteCodeTokenize_tokenize_code(body);
  for (int i = 0; i < body_token.ctokens.size(); i++)
  {
    ctoken btok = body_token.ctokens[i];
    stk = MerCompilerBytecode_evaluate(btok, stk);
  }

  return stk;
}

stack *MerCompilerBytecode_evaluate_RETURN(ctoken ptoken, stack *stk)
{
  return stk;
}

stack *MerCompilerBytecode_evaluate_MAKE_FUNCTION(ctoken ptoken, stack *stk)
{
  vector<uint8_t> body = ptoken.bbody;
  symtable *sym = MerCompiler_symboltable_setup("", 0, "FUNCTION", ptoken.address);
  sym->tbody = body;
  stk->s_symtable->stack.push_back(sym);
  return stk;
}

stack *MerCompilerBytecode_evaluate_PUSH_FLOAT(ctoken ptoken, stack *stk)
{
  stk->s_table->table.push_back(MerCompiler_table_setup(ptoken.rval));
  return stk;
}

stack *MerCompilerBytecode_evaluate_POP_NORMAL_MODE(ctoken ptoken, stack *stk)
{
  pop_stack(stk);
  return stk;
}

stack *MerCompilerBytecode_evaluate_LOAD_GLOBAL(ctoken ptoken, stack *stk)
{
  for (int i = 0; i < stk->s_symtable->stack.size(); i++)
  {
    if (stk->s_symtable->stack[i]->address == ptoken.address)
    {
      stk->s_table->table.push_back(MerCompiler_table_setup(stk->s_symtable->stack[i]->value, stk->s_symtable->stack[i]->address));
      return stk;
    }
  }

  return stk;
}

stack *MerCompilerBytecode_evaluate_STORE_GLOBAL(ctoken ptoken, stack *stk)
{
  table *vval = pop_stack(stk);
  stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup("<address...>", vval->cval, "AUTO_T", ptoken.address));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_ADD(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(t1->cval, t2->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_DIV(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(t2->cval, t1->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_MUL(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(t2->cval, t1->cval)));
  return stk;
}

stack *MerCompilerBytecode_evaluate_BINARY_SUB(ctoken ptoken, stack *stk)
{
  table *t2 = pop_stack(stk);
  table *t1 = pop_stack(stk);
  if (t1 == nullptr || t2 == nullptr)
  {
    cerr << "Error: Stack underflow" << endl;
    return stk;
  }
  stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(t2->cval, t1->cval)));
  return stk;
}
