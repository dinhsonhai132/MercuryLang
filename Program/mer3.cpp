#include "..\Mercury\Mercury.cpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        prompt();
        return EXIT_SUCCESS;
    }

    string file = argv[1];

    if (file == "-v") {
        cout << LANGUAGE << " " << CUSTOM_VERSION << " Copyright (c) 2025-present, " << AUTHOR << endl;
        return EXIT_SUCCESS;
    }

    if (file == "-h") {
        print_help();
        return EXIT_SUCCESS;
    }

    if (file == "-p") {
        prompt();
        return EXIT_SUCCESS;
    }

    if (file == "-info" || file == "-i") {
        cout << "More info at http://dinhsonhai132.github.io/main.html" << endl;
        return EXIT_SUCCESS;
    }

    string input = MerBuffer_read_file(file);

    MerCore_initialize();

    mLexer_T *lexer = _MerLexer_init(input.c_str());
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);
    stack *stk = MerVM_evaluate_program(code);

    MerCore_Finalize();
    
    return EXIT_SUCCESS;
}