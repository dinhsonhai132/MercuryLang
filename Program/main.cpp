#include "..\Mercury\Mercury.cpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        prompt();
        return 0;
    }

    std::string inputFile = argv[1];
    std::string mode;

    if (inputFile == "-v") {
        std::cout << LANGUAGE << " " << CUSTOM_VERSION << " 2025 " << AUTHOR << '\n';
        return 0;
    }

    if (inputFile == "-h") {
        print_help();
        return 0;
    }

    if (inputFile == "-p") {
        prompt();
        return 0;
    }

    if (inputFile == "-ast" || inputFile == "-c" || inputFile == "-m") {
        mode = inputFile;
        inputFile = argv[2];
    }

    if (inputFile == "-info" || inputFile == "-i") {
        std::cout << "More info at http://dinhsonhai132.github.io/main.html\n";
        return 0;
    }

    if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
        std::cerr << "Error: file must have .mer extension\n";
        return 1;
    }

    std::string sourceCode = MerBuffer_read_file(inputFile);
    MerCore_initialize();

    mLexer_T* lexer = _MerLexer_init(sourceCode.c_str());
    lexer->file = inputFile.c_str();

    mParser_T* parser = _MerParser_init(lexer);
    mAST_T* ast = MerParser_parse_program(parser);

    __compiler_u compiler = compiler_init();
    compiler.file = inputFile.c_str();

    mCode_T compiledCode = MerCompiler_compile_ast_program(ast, compiler);

    if (mode == "-m") {
        print_bytecode(compiledCode.prg_code.buff);
        return 0;
    }

    if (mode == "-ast") {
        MerAST_print_ast(ast, 0);
    }

    if (mode == "-c") {
        std::string outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + ".o";
        MerBuffer_make_and_write_file_bytecode(outputFile, compiledCode.prg_code.buff);
    }

    stack* result = MerVM_evaluate_program(compiledCode);
    MerCore_Finalize();

    return 0;
}
