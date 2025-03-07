#include "olexer.h"
#include <cstring>

bytecode_token MerCompile_bytecode_new(void) {
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

const char *return_bytecode_identifier(const char *s)
{
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

vector<char*> make_buff(char* code) {
    int idx = 0;
    char c;
    char *cc;
    vector<char*> buf;
    idx = 0;
    while (true) {
        c = code[idx];
        if (IS_BYTECODE_POTENTIONAL_IDENIFIER(cc)) {
            const char* code = return_bytecode_identifier(cc);
            buf.push_back((char*)code);
            if (code == "PROGRAM_END") break;
            cc = NULL;
        } else if (IS_TOK_DIGITS_CHAR(c)) {
            char nc = code[idx + 1];
            if (nc == 'f' || nc == 'i') {
                buf.push_back((char*)cc);
            } else if (c == '.' && (nc == 'f' || nc == 'i')) {
                cout << "Error: Invalid number in ./scr/lexer.cpp line\n";
                cout << "| 71\n";
                cout << "|\n";
            } else {
                continue;
            }
        } else if (IS_POTENTIAL_IDENTIFIER_CHAR(c)) {
            char nc = code[idx + 1];
            if ((!IS_POTENTIAL_IDENTIFIER_CHAR(nc) || IS_WHITE_SPACE(nc)) && !IS_BYTECODE_POTENTIONAL_IDENIFIER(cc)) {
                buf.push_back((char*)cc);
            }
        } else if (IS_WHITE_SPACE(c)) {
            while (IS_WHITE_SPACE(c)) {
                c = code[idx];
                idx++;
            }
        } else {
            continue;
        }

        cc += c;
        idx++;
    }

    return buf;
}

vector<bytecode_token> MerCompile_bytecode_token_tokenize(char* buff) {
    vector<char*> cbuff = make_buff(buff);
    vector<bytecode_token> ctokens;
    bytecode_token ctoken;


    for (int i = 0; i < cbuff.size(); i++) {
        char* c = cbuff[i];
        if (c == PUSH_FLOAT) {
            char* nc = cbuff[i + 1];
            if (IS_DIGIT_STR(nc)) {
                ctoken.value = atof(nc);
                ctoken.ctype = "PUSH_FLOAT";
                ctokens.push_back(ctoken);
            }
        } else if (c == LOAD_GLOBAL) {
            char* nc = cbuff[i + 1];
        }
    }
}
   
