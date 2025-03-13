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
        return MerCompile_evaluate_bytecode_BINARY_ADD(ctok);
    } else if (ctok.ctype == BINARY_SUB) {
        return MerCompile_evaluate_bytecode_BINARY_SUB(ctok);
    } else if (ctok.ctype == BINARY_MUL) {
        return MerCompile_evaluate_bytecode_BINARY_MUL(ctok);
    } else if (ctok.ctype == BINARY_DIV) {
        return MerCompile_evaluate_bytecode_BINARY_DIV(ctok);
    }
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_RETURN_VALUE(bytecode_token ctok) {
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_CALL_FUNCTION(bytecode_token ctok) {
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_PUSH_FLOAT(bytecode_token ctok) {
    st->s_table->table[table_global_idx++] = MerCompiler_table_setup(ctok.value);
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_LOAD_GLOBAL(bytecode_token ctok) {
    string iden = ctok.name;
    for (auto &sym : st->s_symtable->stack) {
        if (sym->name == iden) {
            st->s_table->table[table_global_idx++] = MerCompiler_table_setup(sym->value);
            return st;
        }
    }
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_STORE_GLOBAL(bytecode_token ctok) {
    string iden = ctok.name;
    st->s_symtable->stack[symtable_global_idx++] = MerCompiler_symboltable_setup(iden, st->s_table->table[table_global_idx]->cval, "AUTO_T");
    st->s_table->table[table_global_idx] = nullptr;
    table_global_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_POP(bytecode_token ctok) {
    st->s_table->table[table_global_idx--] = nullptr;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_BINARY_ADD(bytecode_token ctok) {
    auto left = st->s_table->table[table_global_idx - 1]->cval; 
    auto right = st->s_table->table[table_global_idx]->cval;
    auto val = MERCURY_BINARY_ADD(left, right);
    st->s_table->table[table_global_idx] = nullptr;
    st->s_table->table[table_global_idx - 1] = MerCompiler_table_setup(val);
    table_global_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_BINARY_SUB(bytecode_token ctok) {
    auto left = st->s_table->table[table_global_idx - 1]->cval; 
    auto right = st->s_table->table[table_global_idx]->cval;
    auto val = MERCURY_BINARY_SUB(left, right);
    st->s_table->table[table_global_idx] = nullptr;
    st->s_table->table[table_global_idx - 1] = MerCompiler_table_setup(val);
    table_global_idx--;
    return st;
} 

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_BINARY_MUL(bytecode_token ctok) {
    auto left = st->s_table->table[table_global_idx - 1]->cval; 
    auto right = st->s_table->table[table_global_idx]->cval;
    auto val = MERCURY_BINARY_MUL(left, right);
    st->s_table->table[table_global_idx] = nullptr;
    st->s_table->table[table_global_idx - 1] = MerCompiler_table_setup(val);
    table_global_idx--;
    return st;
}

stack *MerCompile_evaluate::MerCompile_evaluate_bytecode_BINARY_DIV(bytecode_token ctok) {
    auto left = st->s_table->table[table_global_idx - 1]->cval; 
    auto right = st->s_table->table[table_global_idx]->cval;
    auto val = MERCURY_BINARY_DIV(left, right);
    st->s_table->table[table_global_idx] = nullptr;
    st->s_table->table[table_global_idx - 1] = MerCompiler_table_setup(val);
    table_global_idx--;
    return st;
}

stack *MerCompiler_evaluate_program(char *code) {
    MerCompile_evaluate *eval = new MerCompile_evaluate(code);
    return eval->MerCompile_evaluate_statement();
}