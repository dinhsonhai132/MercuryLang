#include "./include/compiler.h"

int push(Stack *stk, Object *value) {
    if (!stk || !value) {
        return FAILURE;
    }

    stk->p->stack[stk->p->idx++] = value;
    stk->stack[stk->p->idx] = value;
    return 0;
}

int pop(Stack *stk) {
    if (!stk) {
        return FAILURE;
    }

    stk->p->stack[stk->p->idx--] = NULL;
    stk->stack[stk->p->idx] = NULL;
    return SUCCESS;
}

int eval(Stack *stk, string code) {
    if (!stk) {
        return FAILURE;
    }

    Object *a = stk->stack[stk->p->idx - 1];
    Object *b = stk->stack[stk->p->idx - 2];

    if (!a || !b) {
        return FAILURE;
    }

    pop(stk);
    pop(stk);

    Object *c;    
    
    if (code == ADD) {
        c->ovalue = a->ovalue + b->ovalue;
    } else if (code == SUB) {
        c->ovalue = a->ovalue - b->ovalue;
    } else if (code == MUL) {
        c->ovalue = a->ovalue * b->ovalue;
    } else if (code == DIV) {
        c->ovalue = a->ovalue / b->ovalue;
    } else if (code == MOD) {
        c->ovalue = a->ovalue % b->ovalue;
    }

    push(stk, c);
    return 0;
}

int main(int argc, char *argv[]) {
    return 0;
}
