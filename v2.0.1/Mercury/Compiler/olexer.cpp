#include <string>
#include <iostream>
#include <vector>
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

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYMTABLE_OVERFLOW "SYMTABLE_OVERFLOW"
#define SYMTABLE_UNDERFLOW "SYMTABLE_UNDERFLOW"
#define TABLE_OVERFLOW "TABLE_OVERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"

#define IS_TOK_DIGITS(c) (c >= '0' && c <= '9' || c == '.')
#define IS_POTENTIAL_IDENTIFIER(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
#define IS_WHITE_SPACE(c) (c == ' ')
#define IS_BYTECODE_POTENTIONAL_IDENIFIER_CHAR(s) ( \
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

bytecode_token bytecode_new(void) {
    bytecode_token b = bytecode_token();
    b.ctype = NULL;
    b.value = 0.0f;
    b.name = NULL;
    b.vval = 0.0f;
    b.line = 0;
    b.table_idx = 0;
    b.symtable_idx = 0;
    b.cbuff = NULL;
    b.err = NULL;
    return b;
}

const char *return_bytecode_identifier(const char *s) {
    if (s == PUSH_FLOAT) return PUSH_FLOAT;
    if (s == PUSH_INT) return PUSH_INT;
    if (s == PUSH_NORMAL_MODE) return PUSH_NORMAL_MODE;
    if (s == PUSH_TEMP_MODE) return PUSH_TEMP_MODE;

    if (s == POP_FLOAT) return POP_FLOAT;
    if (s == POP_NORMAL_MODE) return POP_NORMAL_MODE;
    if (s == POP_TEMP_MODE) return POP_TEMP_MODE;   

    if (s == BINARY_ADD) return BINARY_ADD;
    if (s == BINARY_SUB) return BINARY_SUB;
    if (s == BINARY_MUL) return BINARY_MUL;
    if (s == BINARY_DIV) return BINARY_DIV;
    if (s == BINARY_MOD) return BINARY_MOD;
    if (s == BINARY_POW) return BINARY_POW;
    if (s == BINARY_INCREMENT) return BINARY_INCREMENT;
    if (s == BINARY_DECREMENT) return BINARY_DECREMENT;

    if (s == BINARY_ASSIGN_ADD) return BINARY_ASSIGN_ADD;
    if (s == BINARY_ASSIGN_SUB) return BINARY_ASSIGN_SUB;
    if (s == BINARY_ASSIGN_MUL) return BINARY_ASSIGN_MUL;
    if (s == BINARY_ASSIGN_DIV) return BINARY_ASSIGN_DIV;
    if (s == BINARY_ASSIGN_MOD) return BINARY_ASSIGN_MOD;
    if (s == BINARY_ASSIGN_POW) return BINARY_ASSIGN_POW;

    if (s == LOAD_GLOBAL) return LOAD_GLOBAL;
    if (s == STORE_GLOBAL) return STORE_GLOBAL;
    if (s == LOAD_LOCAL) return LOAD_LOCAL;
    if (s == STORE_LOCAL) return STORE_LOCAL;
    return NULL;
}

vector<bytecode_token> MerCompile_bytecode_token_tokenize(char *code) {
    vector<bytecode_token> tokens;
    bytecode_token token;
    int line = 0;
    int idx = 0;
    char *l;
    while (code[idx] != '\0') {
        char c = code[idx];
        if (IS_POTENTIAL_IDENTIFIER(c)) {
            bool is_bytecode = false;
            while (IS_POTENTIAL_IDENTIFIER(c)) {
                l += c;
                idx++;
                if (code[idx] == '\0') {
                    break;
                } else if (IS_BYTECODE_POTENTIONAL_IDENIFIER_CHAR(l)) {
                    token.ctype = return_bytecode_identifier(l);
                    is_bytecode = true;
                    break;
                }
                c = code[idx];
            }
            if (!is_bytecode) {
                token.name = l;
            }
            l = NULL;
        } else if (IS_TOK_DIGITS(c)) {
            while (IS_TOK_DIGITS(c)) {
                l += c;
                idx++;
                if (code[idx] == '\0') {
                    break;
                }
                c = code[idx];
            }

            token.value = stof(l);
            l = NULL;
        } else if (c == '(') {
            idx++;
            c = code[idx];
            while (c != ')') {
                if (!IS_TOK_DIGITS(c)) {
                    cerr << "Error: Unexpected value '" << c << "' at line " << line << endl;
                    exit(1);
                }

                l += c;
                idx++;
                if (code[idx] == '\0') {
                    break;
                }
                c = code[idx];
            }
            token.vval = stof(l);
            l = NULL;
        } else if (IS_WHITE_SPACE(c)) {
            while (IS_WHITE_SPACE(c)) {
                idx++;
                if (code[idx] == '\0') {
                    break;
                }
                c = code[idx];
            }
        } else if (c == '%') {
            idx++;
            c = code[idx];
            while (IS_TOK_DIGITS(c)) {
                l += c;
                idx++;
                if (code[idx] == '\0') {
                    break;
                }
                c = code[idx];
            }
            token.table_idx = stof(l);
            l = NULL;
        }
        else if (c == '\n') {
            line++;
            token.line = line;
            tokens.push_back(token);
            token = bytecode_new();
            l = NULL;
        } else {
            cerr << "Error: Unexpected character '" << c << "' at line " << line << endl;
            exit(1);
        }
    }

    token.cbuff = code;
    return tokens;
}