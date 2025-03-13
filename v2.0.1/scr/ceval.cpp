#include "ceval.h"

stack *MerCompile_evaluate::MerCompile_evaluate_program() {
    st = MerCompile_evaluate_statement();
    return st;
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
        return MerCompiler_evaluate_bytecode_BINARY_ADD(ctok);
    } else if (ctok.ctype == BINARY_SUB) {
        return MerCompiler_evaluate_bytecode_BINARY_SUB(ctok);
    } else if (ctok.ctype == BINARY_MUL) {
        return MerCompiler_evaluate_bytecode_BINARY_MUL(ctok);
    } else if (ctok.ctype == BINARY_DIV) {
        return MerCompiler_evaluate_bytecode_BINARY_DIV(ctok);
    }
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_PUSH_FLOAT(bytecode_token ctok) {
    st->s_table->table[global_table_idx++] = MerCompiler_table_setup(ctok.value);
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_POP(bytecode_token ctok) {
    st->s_table->table[global_table_idx--] = nullptr;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_STORE_GLOBAL(bytecode_token ctok) {
    st->s_symtable->stack[global_symtable_idx++] = MerCompiler_symboltable_setup(ctok.name, st->s_table->table[global_table_idx - 1]->cval, "AUTO_T");
    st->s_table->table[global_table_idx - 1] = nullptr;
    global_table_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_LOAD_GLOBAL(bytecode_token ctok) {
    for (int i = 0; i < global_symtable_idx; i++) {
        if (st->s_symtable->stack[i]->name == ctok.name) {
            st->s_table->table[global_table_idx++] = MerCompiler_table_setup(st->s_symtable->stack[i]->value);
            return st;
        }
    }
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_CALL_FUNCTION(bytecode_token ctok) {
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_RETURN_VALUE(bytecode_token ctok) {
    return st;
}

stack *MerCompile_evaluate::MerCompiler_evaluate_bytecode_BINARY_ADD(bytecode_token ctok) {
    float c1 = st->s_table->table[global_table_idx - 1]->cval;
    float c2 = st->s_table->table[global_table_idx - 2]->cval;
    st->s_table->table[global_table_idx - 2]->cval = MERCURY_BINARY_ADD(c1, c2);
    st->s_table->table[global_table_idx - 1] = nullptr;
    global_table_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompiler_evaluate_bytecode_BINARY_SUB(bytecode_token ctok) {
    float c1 = st->s_table->table[global_table_idx - 1]->cval;
    float c2 = st->s_table->table[global_table_idx - 2]->cval;
    st->s_table->table[global_table_idx - 2]->cval = MERCURY_BINARY_SUB(c1, c2);
    st->s_table->table[global_table_idx - 1] = nullptr;
    global_table_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompiler_evaluate_bytecode_BINARY_MUL(bytecode_token ctok) {
    float c1 = st->s_table->table[global_table_idx - 1]->cval;
    float c2 = st->s_table->table[global_table_idx - 2]->cval;
    st->s_table->table[global_table_idx - 2]->cval = MERCURY_BINARY_MUL(c1, c2);
    st->s_table->table[global_table_idx - 1] = nullptr;
    global_table_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompiler_evaluate_bytecode_BINARY_DIV(bytecode_token ctok) {
    float c1 = st->s_table->table[global_table_idx - 1]->cval;
    float c2 = st->s_table->table[global_table_idx - 2]->cval;
    st->s_table->table[global_table_idx - 2]->cval = MERCURY_BINARY_DIV(c1, c2);
    st->s_table->table[global_table_idx - 1] = nullptr;
    global_table_idx--;
    return st;
}