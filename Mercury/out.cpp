#include "ceval.cpp"

void print_help() {
    cout << "MercuryLang CLI - Version " << CUSTOM_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -o <filename> <target>\tCompile to a specific output file\n";
    cout << "  -m\t\tCompiled into readable mercury bytecode\n";
}

Mer_real_string get_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Y", ltm);
    return Mer_real_string(buf);
}

void prompt() {
    cout << LANGUAGE << " " << CUSTOM_VERSION << " (main, " << get_time() << ") [Mercury-Virtal-Machine-v4.0 64-bit]\n";
    cout << "'!help()' for help, '!cls()' for reset stack, '!exit()' for exit\n";

    Mer_real_string input = "";
    Mer_real_string source = "";
    sign_in_mer_libs();

    __compiler_u glb = compiler_init();
    
    while (true) {
        cout << ">>> ";
        getline(cin, source);
        input = source + "\n";

        mLexer_T *lexer = _MerLexer_init(input.c_str());
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MerCompiler_compile_ast_program(ast, glb);
        stack *stk = eval_program(code);
    }
}