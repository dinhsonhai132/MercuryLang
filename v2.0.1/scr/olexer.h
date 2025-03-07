#ifndef MERCURY_BYTECODE_LEXER_HEADER_FILE
#define MERCURY_BYTECODE_LEXER_HEADER_FILE

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define PUSH_FLOAT "PUSH_FLOAT"
#define PUSH_INT "PUSH_INT"
#define PUSH_NORMAL_MODE "PUSH_NORMAL_MODE"
#define PUSH_TEMP_MODE "PUSH_TEMP_MODE"

#define POP_FLOAT "POP_FLOAT"
#define POP_NORMAL_MODE "POP_NORMAL_MODE"
#define POP_TEMP_MODE "POP_TEMP_MODE"

#define BINARY_ADD "BINARY_ADD"
#define BINARY_SUB "BINARY_SUB"
#define BINARY_MUL "BINARY_MUL"
#define BINARY_DIV "BINARY_DIV"
#define BINARY_MOD "BINARY_MOD"
#define BINARY_POW "BINARY_POW"
#define BINARY_INCREMENT "BINARY_INCREMENT"
#define BINARY_DECREMENT "BINARY_DECREMENT"
#define BINARY_ASSIGN_ADD "BINARY_ASSIGN_ADD"
#define BINARY_ASSIGN_SUB "BINARY_ASSIGN_SUB"
#define BINARY_ASSIGN_MUL "BINARY_ASSIGN_MUL"
#define BINARY_ASSIGN_DIV "BINARY_ASSIGN_DIV"
#define BINARY_ASSIGN_MOD "BINARY_ASSIGN_MOD"
#define BINARY_ASSIGN_POW "BINARY_ASSIGN_POW"

#define LOAD_GLOBAL "LOAD_GLOBAL"
#define STORE_GLOBAL "STORE_GLOBAL"
#define LOAD_LOCAL "LOAD_LOCAL"
#define STORE_LOCAL "STORE_LOCAL"
#define LOAD_IDENTIFIER "LOAD_IDENTIFIER"
#define STORE_IDENTIFIER "LOAD_IDENTIFIER"

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYMTABLE_OVERFLOW "SYMTABLE_OVERFLOW"
#define SYMTABLE_UNDERFLOW "SYMTABLE_UNDERFLOW"
#define TABLE_OVERFLOW "TABLE_OVERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"

#define IS_TOK_DIGITS_CHAR(c) (c >= '0' && c <= '9' || c == '.')
#define IS_POTENTIAL_IDENTIFIER_CHAR(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
#define IS_WHITE_SPACE(c) (c == ' ')
#define IS_BYTECODE_POTENTIONAL_IDENIFIER(s) ( \
    (s == PUSH_FLOAT) || \
    (s == PUSH_INT) || \
    (s == PUSH_NORMAL_MODE) || \
    (s == PUSH_TEMP_MODE) || \
    (s == POP_FLOAT) || \
    (s == POP_NORMAL_MODE) || \
    (s == POP_TEMP_MODE) || \
    (s == BINARY_ADD) || \
    (s == BINARY_SUB) || \
    (s == BINARY_MUL) || \
    (s == BINARY_DIV) || \
    (s == BINARY_MOD) || \
    (s == BINARY_POW) || \
    (s == BINARY_INCREMENT) || \
    (s == BINARY_DECREMENT) || \
    (s == BINARY_ASSIGN_ADD) || \
    (s == BINARY_ASSIGN_SUB) || \
    (s == BINARY_ASSIGN_MUL) || \
    (s == BINARY_ASSIGN_DIV) || \
    (s == BINARY_ASSIGN_MOD) || \
    (s == BINARY_ASSIGN_POW) || \
    (s == LOAD_GLOBAL) || \
    (s == STORE_GLOBAL) || \
    (s == LOAD_LOCAL) || \
    (s == STORE_LOCAL) \
)

typedef struct MERCURY_BYTECODE_TOKEN {
    const char *ctype;
    float value;
    const char *name;
    float vval;

    int line;
    int table_idx;
    int symtable_idx;

    const char *cbuff;
    const char *err;
} bytecode_token;

bytecode_token MerCompile_bytecode_new(void);
const char *return_bytecode_identifier(const char *s);
bytecode_token MerCompile_bytecode_token_tokenize(char *line_code);
vector<bytecode_token> MerCompile_program_bytecode_token_tokenize(char *byte_code);

#endif // MERCURY_BYTECODE_LEXER_HEADER_FILE