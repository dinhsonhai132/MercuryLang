// Copyright (c) 2025-present Dinh Son Hai

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MERCURY_STACK_CORE_HEADER
#define MERCURY_STACK_CORE_HEADER

#include <cstddef>
#include <string>
#include <vector>
#include <cstdint>

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
