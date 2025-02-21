#include "stack.h"

Stack *MVM_make_new_stack(void) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->p = (table *)malloc(sizeof(table));
    s->s = (symtable *)malloc(sizeof(symtable));

    s->p->code = NULL;
    s->p->next = NULL;
    s->p->buf = NULL;
    s->p->err = NULL;
    s->p->idx = 0;
    s->p->size = 0;
    s->p->cstart = NULL;
    s->p->cend = NULL;
    s->p->name = "";
    s->p->value = NULL;
    s->p->stack[0] = NULL;
    s->s->vname = NULL;
    s->s->vvalue = NULL;
    s->s->err = NULL;
    s->s->idx = 0;
    s->s->size = 0;
    s->s->symstack[0] = NULL;
    return s;
};

int MVM_stack_setup(Stack *stk, table *p, symtable *s) {
    if (!stk || !p || !s) {
        return FAILURE;
    }

    if (stk->p == NULL || stk->s == NULL) {
        return FAILURE;
    }

    stk->p = p;
    stk->s = s;
    return SUCCESS;
};

int MVM_stack_free(Stack *stk) {
    if (!stk) {
        return FAILURE;
    }
    free(stk);
    return SUCCESS;
};

int MVM_table_free(table *p) {
    if (!p) {
        return FAILURE;
    }
    free(p);
    return SUCCESS;
};

int MVM_symtable_free(symtable *s) {
    if (!s) {
        return FAILURE;
    }
    free(s);
    return SUCCESS;
};