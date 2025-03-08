#include "olexer.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#ifndef STRIP_FUNCTION_DEFINED
#define STRIP_FUNCTION_DEFINED
vector<string> strip(const char *str) {
    vector<string> tokens;
    string current;
    
    for (size_t i = 0; i < strlen(str); i++) {
        if (IS_WHITE_SPACE(str[i])) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += str[i];
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}
#endif

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

#ifndef MERCOMPILE_BYTECODE_LEXER
#define MERCOMPILE_BYTECODE_LEXER
vector<bytecode_token> MerCompiler_lexer(const char *code) {
    vector<string> tokens = strip(code);
    vector<bytecode_token> bytecode_tokens;
    bytecode_token* token = MerCompile_bytecode_new();

    bool started = false;
    size_t i = 0;

    while (i < tokens.size()) {
        if (tokens[i] == "PROGRAM_START") {
            started = true;
            break;
        }
        i++;
    }

    if (!started) return bytecode_tokens; 

    i++;
    int curl = 0;

    while (i < tokens.size() && tokens[i] != "PROGRAM_END") {
        string ccur = tokens[i];

        if (ccur == "PUSH_FLOAT") {
            if (++i < tokens.size()) {
                token->ctype = strdup("PUSH_FLOAT");
                token->value = stof(tokens[i]);
                token->line = ++curl;
                bytecode_tokens.push_back(*token);
                delete token;
                token = MerCompile_bytecode_new();
            }
        } else if (ccur == "LOAD_GLOBAL") {
            if (++i < tokens.size()) {
                token->ctype = strdup("LOAD_GLOBAL");
                token->name = strdup(tokens[i].c_str());
                token->line = ++curl;
                bytecode_tokens.push_back(*token);
                delete token;
                token = MerCompile_bytecode_new();
            }
        } else if (ccur == "STORE_GLOBAL") {
            if (++i < tokens.size()) {
                token->ctype = strdup("STORE_GLOBAL");
                token->name = strdup(tokens[i].c_str());
                token->line = ++curl;
                bytecode_tokens.push_back(*token);
                delete token;
                token = MerCompile_bytecode_new();
            }
        } else if (ccur == "CALL_FUNCTION" || ccur == "BINARY_DIV" ||
                   ccur == "BINARY_MUL" || ccur == "BINARY_ADD" || ccur == "BINARY_SUB") {
            token->ctype = strdup(ccur.c_str());
            token->line = ++curl;
            bytecode_tokens.push_back(*token);
            delete token;
            token = MerCompile_bytecode_new();
        }

        i++;
    }

    delete token;

    for (auto &tok : bytecode_tokens) {
        if (tok.ctype) delete[] tok.ctype;
        if (tok.name) delete[] tok.name;
    }

    return bytecode_tokens;
}
#endif
