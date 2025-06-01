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

void prompt() {
    cout << LANGUAGE << " " << CUSTOM_VERSION << " Copyright (c) 2025-present, " << AUTHOR << endl;

    Mer_real_string input = "";
    Mer_real_string source = "";

    __compiler_u glb = compiler_init();

    MerCore_initialize();
    
    while (true) {
        cout << "> ";
        getline(cin, source);
        input = source + "\n";

        mLexer_T *lexer = _MerLexer_init(input.c_str());
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MerCompiler_compile_ast_program(ast, glb);
        stack *stk = eval_program(code);
    }

    MerCore_Finalize();
}