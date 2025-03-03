#ifndef STACK_H
#define STACK_H

#define BYTECODE_STACK_SIZE 1024
#define BYTECODE_SYMTABLE_SIZE 1024
#define BYTECODE_TABLE_SIZE 1024

#define __SUCCESS__ 0
#define __FAILURE__ 1

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYMTABLE_OVERFLOW "SYMTABLE_OVERFLOW"
#define SYMTABLE_UNDERFLOW "SYMTABLE_UNDERFLOW"
#define TABLE_OVERFLOW "TABLE_OVERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"

using namespace std;

typedef struct MERCURY_BYTECODE_TABLE {
    int cval;
    int cidx;
    int cbuf;
    char *err;

    table *table[BYTECODE_TABLE_SIZE];
} table;

typedef struct MERCURY_BYTECODE_SYMBOL_TABLE {
    char *name;
    int value;
    char *type;
    char *err;

    symtable *next;
    symtable *buf;
    symtable *stack[BYTECODE_SYMTABLE_SIZE];
} symtable;

typedef struct MERCURY_BYTECODE_STACK {
    char *code;
    char *ncode;
    char *bcode;
    int cidx;
    int cvalue;
    char *iden;
    char *err;

    table *p;
    symtable *s;
} stack;

stack *MerCompiler_Stack_new(void);
table *MerCompiler_Table_new(void);
symtable *MerCompiler_SymbolTable_new(void);

int MerCompiler_free_stack(stack *s);
int MerCompiler_free_table(table *t);
int MerCompiler_free_symboltable(symtable *s);

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy);

#endif // STACK_H