#include "olexer.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#ifndef COMPILE_TOKEN_NEW
#define COMPILE_TOKEN_NEW
ctok_state ctok_state_new() {
    ctok_state cs = ctok_state();
    cs.ctok = "";
    cs.cval = 0;
    cs.ciden = "";
    cs.is_iden = false;
    cs.is_addr = false;
    cs.address = nullptr;
    return cs;
};
#endif

#ifndef BYTECODE_TOKEN_NEW
#define BYTECODE_TOKEN_NEW
bytecode_token bytecode_token_new() {
    bytecode_token ctok;
    ctok.ctype = "";
    ctok.name = "";
    ctok.value = 0.0;
    ctok.line = 0;
    ctok.err = "";
    ctok.cbuff = "";
    ctok.vval = 0.0;
    ctok.is_iden = false;
    ctok.address = nullptr;
    ctok.global_address = nullptr;
    return ctok;
}
#endif

#ifndef MERCOMPILE_LEXER_DEFINED
#define MERCOMPILE_LEXER_DEFINED
vector<ctok_state> tokenize_ctok_state(char* source) {
    vector<ctok_state> ctokens;
    ctok_state ctok;
    int idx = 0;
    char c;
    string cc;
    size_t length = strlen(source);

    while (idx < length) {
        c = source[idx];

        if (IS_WHITE_SPACE(c)) {
            idx++;
            continue;
        } 
        
        if (IS_POTENTIAL_IDENTIFIER_CHAR(c)) {
            while (idx < length && IS_POTENTIAL_IDENTIFIER_CHAR(source[idx])) {
                cc += source[idx++];
            }

            ctok = ctok_state_new();
            if (IS_BYTECODE_POTENTIONAL_IDENIFIER(cc)) {
                ctok.ctok = cc;
            } else {
                ctok.ciden = cc;
                ctok.is_iden = true;
            }
            ctokens.push_back(ctok);
            cc.clear();
        } else if (IS_TOK_DIGITS_CHAR(c)) {
            bool hasDot = false;
            while (idx < length && (isdigit(source[idx]) || source[idx] == '.')) {
                if (source[idx] == '.') {
                    if (hasDot) break;
                    hasDot = true;
                }
                cc += source[idx++];
            }

            ctok = ctok_state_new();
            ctok.cval = stof(cc);
            ctokens.push_back(ctok);
            cc.clear();
        } else if (c == ';') {
            ctok = ctok_state_new();
            ctok.ctok = ";";
            ctokens.push_back(ctok);
            idx++;
        } else if (c == '<') {
            idx++;
            cc = "";

            while (idx < length && source[idx] != '>') {
                cc += source[idx++];
            }
            idx++;

            if (cc.find("address of global") == 0) {
                size_t name_start = cc.find(" ", 17);
                size_t at_pos = cc.find(" at ", name_start);

                if (name_start != string::npos && at_pos != string::npos) {
                    char* global_address_name = strdup(cc.substr(name_start + 1, at_pos - name_start - 1).c_str());
                    char* address = strdup(cc.substr(at_pos + 4).c_str());

                    ctok = ctok_state_new();
                    ctok.global_address = global_address_name;
                    ctok.address = address;
                    ctok.is_addr = true;
                    ctokens.push_back(ctok);
                }
            }
        } else {
            idx++;
        }
    }

    return ctokens;
}
#endif

#ifndef MERCOMPILE_BYTECODE_LEXER_DEFINED
#define MERCOMPILE_BYTECODE_LEXER_DEFINED
vector<bytecode_token> MerCompile_bytecode_tokenizer(char* source) {
    vector<bytecode_token> cctoks;
    vector<ctok_state> ctoks = tokenize_ctok_state(source);
    ctok_state ctok = ctok_state_new();
    int cline = 0;
    int idx = 0;
    int table_idx = 0;
    int symtable_idx = 0;
    string cc;
    bool check_start = false;
    bool check_end = false;
    if (ctoks[0].ctok == PROGRAM_START) {
        check_start = true;
    }

    while (idx < ctoks.size()) {
        ctok = ctoks[idx];
        if (ctok.ctok == PUSH_FLOAT) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = PUSH_FLOAT;
            idx++;
            ctok = ctoks[idx];
            cctok.value = ctok.cval;
            idx++;
            ctok = ctoks[idx];
            if (ctok.ctok == ";") {
                cctok.line = cline++;
                cctoks.push_back(cctok);
                idx++;
            }
        } else if (ctok.ctok == LOAD_GLOBAL) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = ctok.ctok;
            idx++;
            ctok = ctoks[idx];
            cctok.name = ctok.ciden;
            idx++;
            ctok = ctoks[idx];
            if (ctok.ctok == ";") {
                cctok.line = cline++;
                cctoks.push_back(cctok);
                idx++;
            }
        } else if (ctok.ctok == STORE_GLOBAL) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = ctok.ctok;
            idx++;
            ctok = ctoks[idx];
            cctok.name = ctok.ciden;
            idx++;
            ctok = ctoks[idx];
            if (ctok.ctok == ";") {
                cctok.line = cline++;
                cctoks.push_back(cctok);
                idx++;
            }
        } else if (ctok.ctok == BINARY_ADD || ctok.ctok == BINARY_SUB || ctok.ctok == BINARY_MUL || ctok.ctok == BINARY_DIV) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = ctok.ctok;
            idx++;
            ctok = ctoks[idx];
            if (ctok.ctok == ";") {
                cctok.line = cline++;
                cctoks.push_back(cctok);
                idx++;
            }
        } else if (ctok.ctok == POP_NORMAL_MODE) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = ctok.ctok;
            idx++;
            ctok = ctoks[idx];
            if (ctok.ctok == ";") {
                cctok.line = cline++;
                cctoks.push_back(cctok);
                idx++;
            }
        } else if (ctok.ctok == PROGRAM_END) {
            check_end = true;
            break;
        } else if (ctok.is_addr) {
            bytecode_token cctok = bytecode_token_new();
            cctok.ctype = GLOBAL_ADDRESS;
            cctok.global_address = ctok.global_address;
            cctok.address = ctok.address;
            cctok.line = cline++;
            idx++;
            cctoks.push_back(cctok);
        } else {
            idx++;
        }
    }
    if (check_start && check_end) {
        return cctoks;
    }
    cerr << "Error: Invalid bytecode" << endl;
    return vector<bytecode_token>();
}

#endif
