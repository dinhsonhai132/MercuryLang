#include "..\Mercury\Mercury.cpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        prompt();
        return EXIT_SUCCESS;
    }

    string file = argv[1];
    string tags;

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

    if (file == "-ast") {
        tags = file;
        file = argv[2];
    }

    if (file == "-c") {
        tags = file;
        file = argv[2];
    }

    if (file == "-m") {
        tags = file;
        file = argv[2];
    }

    if (file == "-info" || file == "-i") {
        cout << "More info at http://dinhsonhai132.github.io/main.html" << endl;
        return EXIT_SUCCESS;
    }
    
    if (file.substr(file.find_last_of(".") + 1) != "mer") {
        cerr << "Error: The file must have a .mer extension." << endl;
        return EXIT_FAILURE;
    }

    string input = MerBuffer_read_file(file);


    MerCore_initialize();
    
    mLexer_T *lexer = _MerLexer_init(input.c_str());
    lexer->file = file.c_str();
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    u.file = file.c_str();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);

    if (tags == "-m") {
        print_bytecode(code.prg_code.buff);
    }

    if (tags == "-ast") {
        MerAST_print_ast(ast, 0);
    }
    
    if (tags == "-c") {
        string bytefile = file.substr(0, file.find_last_of(".")) + ".o";
        MerBuffer_make_and_write_file_bytecode(bytefile, code.prg_code.buff);
    }
  
    stack *stk = MerVM_evaluate_program(code);

    MerCore_Finalize();

    return EXIT_SUCCESS;
}