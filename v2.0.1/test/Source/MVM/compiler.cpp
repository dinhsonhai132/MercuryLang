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

struct bytecode {
    string code;
    Object* value;
    Object* load;
};

bool is_binary_operator(string code) {
    if (code == ADD || code == SUB || code == MUL || code == DIV || code == MOD) {
        return true;
    }
    return false;
}

int MVM_compiler(vector<bytecode> bytecodes, Stack *stk) {
    int line;
    while (line < bytecodes.size()) {
        if (bytecodes[line].code == PUSH) {
            push(stk, bytecodes[line].value);
        } else if (bytecodes[line].code == POP) {
            pop(stk);
        } else if (is_binary_operator(bytecodes[line].code)) {
            eval(stk, bytecodes[line].code);
        }
        line++;
    }
}

int main() {
    return 0;
}

int main(int argc, char *argv[]) {
    return 0;
}
