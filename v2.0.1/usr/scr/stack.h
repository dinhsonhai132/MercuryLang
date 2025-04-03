#ifndef MERCURY_STACK_CORE_HEADER
#define MERCURY_STACK_CORE_HEADER

#include <cstddef>
#include <string>
#include <vector>
#include <cstdint>
#include "object.cpp"

#define BYTECODE_STACK_SIZE 10
#define BYTECODE_SYMTABLE_SIZE 10
#define BYTECODE_TABLE_SIZE 10

#define __SUCCESS__ 0
#define __FAILURE__ 1

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYMTABLE_OVERFLOW "SYMTABLE_OVERFLOW"
#define SYMTABLE_UNDERFLOW "SYMTABLE_UNDERFLOW"
#define TABLE_OVERFLOW "TABLE_OVERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"

using namespace std;

typedef struct MERCURY_BYTECODE_TABLE
{
    float cval;
    int cidx;
    float cbuf;
    uint8_t address;
    string err;
    MerObject *objv;

    vector<MERCURY_BYTECODE_TABLE *> table;
} table;

typedef struct MERCURY_BYTECODE_SYMBOL_TABLE
{
    string name;
    int value;
    int cidx;
    uint8_t address;
    table *pval;
    string type;
    string err;
    vector<uint8_t> tbody;
    MerCodeObject *cobjv;
    MerObject *objv;
    vector<MERCURY_BYTECODE_SYMBOL_TABLE *> stack;
} symtable;

typedef struct MERCURY_BYTECODE_STACK
{
    string code;
    string bcode;
    int cvalue;
    string iden;
    string err;

    table *s_table;
    symtable *s_symtable;
} stack;

stack *MerCompiler_Stack_new(void);
table *MerCompiler_Table_new(void);
symtable *MerCompiler_SymbolTable_new(void);

int MerCompiler_free_stack(stack *s);
int MerCompiler_free_table(table *t);
int MerCompiler_free_symboltable(symtable *s);

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy);
table *MerCompiler_table_setup(float cval, uint8_t address = 0x00);
symtable *MerCompiler_symboltable_setup(string name, int value, string type, uint8_t address);

#endif // MERCURY_STACK_CORE_HEADER
