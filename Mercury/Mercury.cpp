#include "vm.cpp"
#include <time.h>

const char* show_opcode_name(uint8_t x) {
    if (x == CPUSH_FLOAT)         return "PUSH_FLOAT";
    else if (x == CPUSH_NORMAL_MODE) return "PUSH_NORMAL_MODE";
    else if (x == CBUILD_LIST)    return "BUILD_LIST";
    else if (x == CGET_ITEM)      return "GET_ITEM";
    else if (x == CSTORE_INDEX)   return "STORE_INDEX";
    else if (x == CBINARY_SUBSCRIBE) return "BINARY_SUBSCRIBE";
    else if (x == CLOAD_GLOBAL)   return "LOAD_GLOBAL";
    else if (x == CSTORE_GLOBAL)  return "STORE_GLOBAL";
    else if (x == CBINARY_ADD)    return "BINARY_ADD";
    else if (x == CLOAD_ARGS)     return "LOAD_ARGS";
    else if (x == CBINARY_SUB)    return "BINARY_SUB";
    else if (x == CBINARY_MUL)    return "BINARY_MUL";
    else if (x == CBINARY_DIV)    return "BINARY_DIV";
    else if (x == CBINARY_MOD)    return "BINARY_MOD";
    else if (x == TRUE_ADDRESS)   return "TRUE_ADDRESS";
    else if (x == FALSE_ADDRESS)  return "FALSE_ADDRESS";
    else if (x == CLOAD_TRUE)     return "LOAD_TRUE";
    else if (x == CLOAD_FALSE)    return "LOAD_FALSE";
    else if (x == CEQUAL)         return "EQUAL";
    else if (x == CNOT_EQUAL)     return "NOT_EQUAL";
    else if (x == CEND_FUNCTION)  return "END_FUNCTION";
    else if (x == CCLASS_BEGIN)   return "CLASS_BEGIN";
    else if (x == CPOP_TOP)       return "POP_TOP";
    else if (x == CCLASS_END)     return "CLASS_END";
    else if (x == CLESS)          return "LESS";
    else if (x == CCALL_METHOD)   return "CALL_METHOD";
    else if (x == CLESS_EQUAL)    return "LESS_EQUAL";
    else if (x == CGREATER)       return "GREATER";
    else if (x == CLOAD_ATTR)     return "LOAD_ATTR";
    else if (x == CGREATER_EQUAL) return "GREATER_EQUAL";
    else if (x == CNOT)           return "NOT";
    else if (x == CLEN)           return "LEN";
    else if (x == CJUMP_IF_FALSE) return "JUMP_IF_FALSE";
    else if (x == CJUMP_IF_TRUE)  return "JUMP_IF_TRUE";
    else if (x == CPOP_JUMP_IF_FALSE) return "POP_JUMP_IF_FALSE";
    else if (x == CPOP_JUMP_IF_TRUE)  return "POP_JUMP_IF_TRUE";
    else if (x == CJUMP_TO)       return "JUMP_TO";
    else if (x == CSTORE_ATTR)    return "STORE_ATTR";
    else if (x == CPROGRAM_START) return "PROGRAM_START";
    else if (x == CPROGRAM_END)   return "PROGRAM_END";
    else if (x == CMAKE_FUNCTION) return "MAKE_FUNCTION";
    else if (x == CFUNCTION_CALL) return "FUNCTION_CALL";
    else if (x == CRETURN)        return "RETURN";
    else if (x == CADDRESS)       return "ADDRESS";
    else                          return "UNKNOWN_OPCODE";
}

void print_bytecode(vector<uint8_t> &bytecode) {
    int i = 0;
    int line = 1;
    while (i < bytecode.size()) {
        string c = show_opcode_name(bytecode[i]);
        cout << dec << line++ << ": ";
        if (c == "PUSH_FLOAT") {
            uint8_t c1 = bytecode[++i];
            uint8_t c2 = bytecode[++i];
            uint8_t c3 = bytecode[++i];
            uint8_t c4 = bytecode[++i];

            cout << "PUSH_FLOAT ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c1 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c2 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c3 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c4 << " ";
            cout << endl;
        } else if (c == "PUSH_NORMAL_MODE") {
            uint8_t mode = bytecode[++i];
            int size = mode;
            cout << "PUSH_NORMAL_MODE ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)mode << " ";

            while (i < bytecode.size() && size > 0) {
                cout << "0x" << hex << setfill('0') << setw(2) << (int)bytecode[i] << " ";
                ++i;
                --size;
            }
            cout << endl;
        } 
        else if (c == "STORE_GLOBAL" 
            || c == "LOAD_GLOBAL" 
            || c == "CALL_METHOD"
            || c == "STORE_ATTR"
            || c == "CLASS_BEGIN"
            || c == "LOAD_ARGS"
            || c == "POP_JUMP_IF_FALSE" 
            || c == "JUMP_IF_FALSE" 
            || c == "POP_JUMP_IF_TRUE" 
            || c == "JUMP_IF_TRUE"
            || c == "LOAD_ATTR"
            || c == "JUMP_TO" 
            || c == "ADDRESS"
            || c == "BUILD_LIST") {
            uint8_t address = bytecode[++i];
            cout << c << " 0x" << hex << setfill('0') << setw(2) << (int)address << endl;
        } else if (c == "STORE_INDEX" 
            || c == "GET_ITEM" 
            || c == "FUNCTION_CALL"
            || c == "POP_TOP"
            || c == "PROGRAM_START" 
            || c == "PROGRAM_END"
            || c == "RETURN"
            || c == "BINARY_ADD"
            || c == "BINARY_SUB"
            || c == "CLASS_END"
            || c == "END_FUNCTION"
            || c == "BINARY_MUL"
            || c == "LOAD_TRUE"
            || c == "LOAD_FALSE"
            || c == "BINARY_DIV"
            || c == "BINARY_MOD"
            || c == "LESS"
            || c == "EQUAL"
            || c == "NOT_EQUAL"
            || c == "GREATER"
            || c == "GREATER_EQUAL"
            || c == "LEN"
            || c == "STORE_INDEX"
            || c == ""
        ) {
            cout << c << endl;
        } else if (c == "MAKE_FUNCTION") {
            uint8_t address = bytecode[++i];
            uint8_t name_length = bytecode[++i];
            cout << c << " 0x" << hex << setfill('0') << setw(2) << (int)address << " " << "0x" << hex << setfill('0') << setw(2) << (int)name_length << endl;
        }
        ++i;
    }
}

void print_bytecode_index(vector<uint8_t> &bytecode) {
    cout << "Bytecode Index:" << endl;
    int index = 0;
    for (auto &item : bytecode) {
        cout << "0x" << hex << setfill('0') << setw(2) << (int)item << " ";
        if (index++ == 5) {
            cout << endl;
            index = 0;
        }
    }
}

void print_help() {
    cout << "MercuryLang CLI - Version " << CUSTOM_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: 'mer' or 'mer3' + [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -m\t\tCompiled into readable bytecode\n";
}

string time_date() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%c", &tstruct);
    return string(buf); 
}

void prompt() {
    cout << LANGUAGE << " " << CUSTOM_VERSION << " Copyright (C) 2025-present, " << AUTHOR << endl;
    Mer_real_string input = "";
    Mer_real_string source = "";

    __compiler_u glb = compiler_init();

    MerCore_initialize();
    
    while (true) {
        bool first = true;
        string line;
        string full_line = "";
        while (true) {

            if (first) {
                cout << "> ";
                first = false;
            } else {
                cout << "... ";
            }
            getline(cin, line);
   
            full_line += line + "\n";
            if (line.empty() || line.back() == ';') {
                break;
            }
        }

        char* c_line = (char*)full_line.c_str();
        mLexer_T *lexer = _MerLexer_init(c_line);
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MerCompiler_compile_ast_program(ast, glb);
        stack *stk = MerVM_evaluate_program(code);

        _MerParser_free(parser);
        MerAST_free(ast);
    }

    MerCore_Finalize();
}

void MercuryRunSimpleString(char* buff) {
    mLexer_T *lexer = _MerLexer_init(buff);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);
    stack *stk = MerVM_evaluate_program(code);
}

mCode_T MercuryCompileSimpleString(char* buff) {
    MerCore_initialize();
    mLexer_T *lexer = _MerLexer_init(buff);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);
    MerCore_Finalize();
    
    return code;
}