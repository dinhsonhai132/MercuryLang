#include "ceval.h"

stack *MerCompile_evaluate::MerCompile_evaluate_program() {
    return MerCompile_evaluate_statement();
}

stack *MerCompile_evaluate::MerCompile_evaluate_statement() {
    for (auto &tok : ctoks) {
        st = MerCompile_evaluate_bytecode(tok);
    }
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode(bytecode_token ctok) {
    if (ctok.ctype == PUSH_FLOAT) {
        return MerCompile_evaluate_bytecode_PUSH_FLOAT(ctok);
    } else if (ctok.ctype == RETURN) {
        return MerCompile_evaluate_bytecode_RETURN_VALUE(ctok);
    } else if (ctok.ctype == CALL_FUNCTION) {
        return MerCompile_evaluate_bytecode_CALL_FUNCTION(ctok);
    } else if (ctok.ctype == LOAD_GLOBAL) {
        return MerCompile_evaluate_bytecode_LOAD_GLOBAL(ctok);
    } else if (ctok.ctype == STORE_GLOBAL) {
        return MerCompile_evaluate_bytecode_STORE_GLOBAL(ctok);
    } else if (ctok.ctype == POP_FLOAT) {
        return MerCompile_evaluate_bytecode_POP(ctok);
    } else if (ctok.ctype == BINARY_ADD) {
        return MerCompiler_evauate_bytecode_BINARY_ADD(ctok);
    } else if (ctok.ctype == BINARY_SUB) {
        return MerCompiler_evauate_bytecode_BINARY_SUB(ctok);
    } else if (ctok.ctype == BINARY_MUL) {
        return MerCompiler_evauate_bytecode_BINARY_MUL(ctok);
    } else if (ctok.ctype == BINARY_DIV) {
        return MerCompiler_evauate_bytecode_BINARY_DIV(ctok);
    }
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_PUSH_FLOAT(bytecode_token ctok) {
    st->s_table->table[st->s_table->cidx++] = MerCompiler_table_setup(ctok.value);
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_LOAD_GLOBAL(bytecode_token ctok) {
    string iden = ctok.name;
    for (auto &sym : st->s_symtable->stack) {
        if (sym->name == iden) {
            st->s_table->table[st->s_table->cidx++] = MerCompiler_table_setup(sym->value);
        }
    }
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_STORE_GLOBAL(bytecode_token ctok) {
    string iden = ctok.name;
    st->s_symtable->stack[st->s_symtable->cidx++] = MerCompiler_symboltable_setup(iden, st->s_table->table[st->s_table->cidx - 1]->cval, "AUTO_T");
    st->s_table->table[st->s_table->cidx--] = NULL;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_POP(bytecode_token ctok) {
    st->s_table->table[st->s_table->cidx--] = NULL;
}