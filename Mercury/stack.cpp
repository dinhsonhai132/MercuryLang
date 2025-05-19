#include "./include/stack.h"

stack *MerCompiler_Stack_new(void) {
    stack *s = new stack;
    s->code = "";
    s->cvalue = 0;
    s->iden = "";
    s->bcode = "";
    s->err = "";
    s->s_table = MerCompiler_Table_new();
    s->s_symtable = MerCompiler_SymbolTable_new();
    s->s_global = MerCompiler_SymbolTable_new();
    s->s_local = MerCompiler_SymbolTable_new();
    return s;
}

table *MerCompiler_Table_new(void) {
    table *t = new table;
    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->err = "";
    t->is_list = false;
    t->is_str = false;
    t->is_code = false;
    t->is_builtin = false;
    t->is_same = false;
    t->is_local = false;
    t->is_obj = false;
    t->is_func = false;
    t->is_type = false;
    t->is_opcode = false;
    t->is_same = false;
    t->is_var = false;
    t->name = "";
    t->value = 0;
    t->type = "";
    t->address = 0x01;
    t->size = 0;
    t->str_v = "";
    t->list_v = nullptr;
    t->f_str_v = nullptr;
    t->code_v = nullptr;
    t->type_v = nullptr;
    t->func_v = nullptr;
    t->obj_v = nullptr;
    t->opcode_v = nullptr;
    t->table = vector<table*>();
    t->tbody = vector<uint8_t>();
    t->f_value = 0;

    t->table = vector<table*>();
    return t;
}

symtable *MerCompiler_SymbolTable_new(void) {
    symtable *s = new symtable;
    s->name = "";
    s->value = 0;
    s->type = "";
    s->is_str = false;
    s->is_code = false;
    s->is_list = false;
    s->is_obj = false;
    s->is_func = false;
    s->is_type = false;
    s->is_opcode = false;
    s->is_same = false;
    s->is_var = false;
    s->is_builtin = false;
    s->is_local = false;
    s->list_v = nullptr;
    s->var_v = nullptr;
    s->f_str_v = nullptr;
    s->code_v = nullptr;
    s->type_v = nullptr;
    s->func_v = nullptr;
    s->obj_v = nullptr;
    s->opcode_v = nullptr;
    s->tab = MerCompiler_Table_new();
    s->err = "";
    s->tbody = vector<uint8_t>();
    s->cidx = 0;
    s->address = 0x01;
    return s;
}

int MerCompiler_free_stack(stack *s) {
    if (!s) return __FAILURE__;
    MerCompiler_free_table(s->s_table);
    MerCompiler_free_symboltable(s->s_symtable);
    s->code.clear();
    s->iden.clear();
    delete[] s;
    return __SUCCESS__;
}
int MerCompiler_free_table(table *t) {
    if (!t) return __FAILURE__;
    t->table.clear();
    delete[] t;
    return __SUCCESS__;
}
int MerCompiler_free_symboltable(symtable *s) {
    if (!s) return __FAILURE__;
    delete[] s;
    return __SUCCESS__;
}

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy) {
    if (!s || !t || !sy) return NULL;
    s = MerCompiler_Stack_new();
    s->s_table = t;
    s->s_symtable = sy;
    return s;
}

table *MerCompiler_table_setup(float cval, uint8_t address) {
    table *t = MerCompiler_Table_new();
    t->cval = cval;
    t->address = address;
    return t;
}

symtable *MerCompiler_symboltable_setup(string name, float value, string type, uint8_t address) {
    symtable *s = MerCompiler_SymbolTable_new();
    s->name = name;
    s->value = value;
    s->type = type;
    s->address = address;
    return s;
}

table *pop_stack(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [start]" << endl;
    #endif

    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack underflow in pop_stack" << endl;
        break_point();
        return nullptr;
    }
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [pass]" << endl;
    #endif

    return top;
}

table *eat_stack(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [start]" << endl;
    #endif
    
    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack underflow in eat_stack" << endl;
        cerr << "eat_stack" << endl;
        return nullptr;
    }
    table *top = stk->s_table->table.back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [pass]" << endl;
    #endif

    return top;
}

