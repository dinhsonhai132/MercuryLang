#include "olexer.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#ifndef MERCOMPILE_BYTECODE_NEW_DEFINED
#define MERCOMPILE_BYTECODE_NEW_DEFINED
bytecode_token* MerCompile_bytecode_new() {
    bytecode_token* token = new bytecode_token;
    token->ctype = NULL;
    token->value = 0.0;
    token->line = 0;
    token->name = NULL;
    token->vval = 0.0;
    token->table_idx = 0;
    token->symtable_idx = 0;
    token->cbuff = NULL;
    token->err = NULL;
    return token;
}
#endif

#ifndef MERCOMPILE_LEXER_DEFINED
#define MERCOMPILE_LEXER_DEFINED
vector<bytecode_token> MerCompile_lexer(const char *code) {
    vector<bytecode_token> ctokens;
    bytecode_token *token = MerCompile_bytecode_new();
    int idx = 0;
    int curl;
    char *cc;
    bool found = false;
    bool cn;
    while (idx < strlen(code)) {
        char c = code[idx];
        if (IS_POTENTIAL_IDENTIFIER_CHAR(c)) {
            while (IS_POTENTIAL_IDENTIFIER_CHAR(c)) {
                c = code[idx];
                cc += c;
                if (IS_BYTECODE_POTENTIONAL_IDENIFIER(cc)) {
                    found = true;
                    break; 
                }
                idx++;
            }

            if (found) {
                token->ctype = cc;
            } else {
                token->name = cc;
            }
        } else if (IS_TOK_DIGITS_CHAR(c)) {
            while (IS_TOK_DIGITS_CHAR(c)) {
                c = code[idx];
                cc += c;
                idx++;
            }
            if (IS_DIGIT_STR(cc)) {
                token->value = atof(cc);
            }
        } else if (c == ';') {
            curl++;
            token->line = curl;
            token->cbuff = code;
            ctokens.push_back(*token);
            token = MerCompile_bytecode_new();
            idx += 2;
        } else if (IS_WHITE_SPACE(c)) {
            while (IS_WHITE_SPACE(c)) {
                c = code[idx];
                idx++;
            }
        } else {
            idx++;
        }
    }
    return ctokens;
}
#endif