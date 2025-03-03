#include "../include/stack.h"
#include <cstddef>

table *MerCompiler_Table_new(void) { 
    table *t = new table;
    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->err = NULL;
    t->table[0] = NULL;
    return t;
}

symtable *MerCompiler_SymbolTable_new(void) {
    symtable *s = new symtable;
    s->name = NULL;
    s->value = 0;
    s->type = NULL;
    s->err = NULL;

    s->next = NULL;
    s->buf = NULL;
    s->stack[0] = NULL;
    return s;
}

stack *MerCompiler_Stack_new(void) { 
    stack *s = new stack;
    s->code = NULL;
    s->ncode = NULL;
    s->bcode = NULL;
    s->cidx = 0;
    s->cvalue = 0;
    s->iden = NULL;
    s->err = NULL;
    s->p = MerCompiler_Table_new();
    s->s = MerCompiler_SymbolTable_new();
    return s;
}

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy) {
    if (!s || !t || !sy) return NULL;
    s = MerCompiler_Stack_new();
    s->p = t;
    s->s = sy;
    return s;
}

int MerCompiler_free_table(table *t) {
    if (!t) return __FAILURE__;
    delete[] t;
    return __SUCCESS__;
}

int MerCompiler_free_symboltable(symtable *s) { 
    if (!s) return __FAILURE__;
    delete[] s;
    return __SUCCESS__;
}

int MerCompiler_free_stack(stack *s) { 
    if (!s) return __FAILURE__;
    delete[] s;
    return __SUCCESS__;
}