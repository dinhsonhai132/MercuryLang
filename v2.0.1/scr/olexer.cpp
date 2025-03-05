#include "olexer.h"

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
        } else if (c == '\n') {
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