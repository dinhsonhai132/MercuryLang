#include "ceval.h"

stack *MerCompiler_evaluate_program(char *code, stack *stk) {
    stk = MerCompiler_evaluate_statement(code, stk);
    return stk;
}

stack *MerCompiler_evaluate_statement(char *code, stack *stk) {
    size_t global_idx = 0;
    vector<bytecode_token> ctoks = MerCompile_bytecode_tokenizer(code);
    while (global_idx < ctoks.size()) {
        bytecode_token cctoks = ctoks[global_idx];
        stk = MerCompiler_evaluate(cctoks, stk);
        global_idx++;
    }
    return stk;
}

stack *MerCompiler_evaluate(bytecode_token ctoks, stack *stk) {
    if (ctoks.ctype == PUSH_FLOAT) {
        stk = MerCompiler_evaluate_PUSH_FLOAT(ctoks, stk);
    } else if (ctoks.ctype == BINARY_ADD) {
        stk = MerCompiler_evaluate_BINARY_ADD(ctoks, stk);
    } else if (ctoks.ctype == BINARY_SUB) {
        stk = MerCompiler_evaluate_BINARY_SUB(ctoks, stk);
    } else if (ctoks.ctype == BINARY_MUL) {
        stk = MerCompiler_evaluate_BINARY_MUL(ctoks, stk);
    } else if (ctoks.ctype == BINARY_DIV) {
        stk = MerCompiler_evaluate_BINARY_DIV(ctoks, stk);
    }
    return stk;
}

stack *MerCompiler_evaluate_PUSH_FLOAT(bytecode_token ctoks, stack *stk) {
    stk->s_table->table.push_back(MerCompiler_table_setup(ctoks.value));
    return stk;
}

stack *MerCompiler_evaluate_POP_NORMAL_MODE(bytecode_token ctoks, stack *stk) {
    stk->s_table->table.pop_back();
    return stk;
}

stack *MerCompiler_evaluate_BINARY_ADD(bytecode_token ctoks, stack *stk) {
    table *t1 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    table *t2 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(t1->cval, t2->cval)));
    return stk;
}

stack *MerCompiler_evaluate_BINARY_SUB(bytecode_token ctoks, stack *stk) {
    table *t1 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    table *t2 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(t2->cval, t1->cval)));
    return stk;
}

stack *MerCompiler_evaluate_BINARY_MUL(bytecode_token ctoks, stack *stk) {
    table *t1 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    table *t2 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(t1->cval, t2->cval)));
    return stk;
}

stack *MerCompiler_evaluate_BINARY_DIV(bytecode_token ctoks, stack *stk) {
    table *t1 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    table *t2 = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(t2->cval, t1->cval)));
    return stk;
}

stack *MerCompiler_evaluate_LOAD_GLOBAL(bytecode_token ctok, stack *stk) {
    for (auto &t : stk->s_symtable->stack) {
        if (t->name == ctok.name) {
            stk->s_table->table.push_back(MerCompiler_table_setup(t->value));
            return stk;
        }
    }
    return stk;
}

stack *MerCompiler_evaluate_STORE_GLOBAL(bytecode_token ctok, stack *stk) {
    stk->s_symtable->stack.push_back(MerCompiler_symboltable_setup(ctok.name, stk->s_table->table.back()->cval, "AUTO_T", 0x0000));
    stk->s_table->table.pop_back();
    return stk;
}