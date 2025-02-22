#ifndef MERCURY_STACK_HEADER_FILE
#define MERCURY_STACK_HEADER_FILE

#include <iostream>
#include <string>
#include "oobject.h"

using namespace std;

#define PUSH "PUSH"
#define POP "POP"
#define ADD "ADD"
#define SUB "SUB"
#define MUL "MUL"   
#define DIV "DIV"
#define MOD "MOD"
#define POW "POW"
#define START "START"
#define END "END"

#define STACK_SIZE 100
#define SYMBOL_SIZE 100

#define SUCCESS 0
#define FAILURE 1

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYMBOL_OVERFLOW "SYMBOL_OVERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"
#define RUNTIME_ERROR "RUNTIME_ERROR"

struct table {
    string *code;
    string *next;
    string *buf;
    string *err;
    
    int idx;
    int size;

    const string *cstart;
    const string *cend;

    string name;
    Object *value;

    Object *stack[STACK_SIZE];
};

struct symtable {
    Object *vname;
    Object *vvalue;
    string *err;

    int idx;
    int size;

    Object *symstack[STACK_SIZE];
};

struct Stack {
    table *p;
    symtable *s;

    Object *stack[STACK_SIZE];
    Object *symstack[STACK_SIZE];
};

Stack *MVM_make_new_stack(void);
int MVM_stack_setup(Stack *stk, table *p, symtable *s);
int MVM_stack_free(Stack *stk);
int MVM_table_free(table *p);
int MVM_symtable_free(symtable *s);


#endif