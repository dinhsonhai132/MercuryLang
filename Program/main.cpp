#include "../Mercury/Mercury.cpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        prompt();
        return 0;
    }

    std::string inputFile = argv[1];
    std::string mode;

    if (inputFile == "-v") {
        std::cout << LANGUAGE << " " << CUSTOM_VERSION << " Copyright (C) 2025-present, " << AUTHOR << '\n';
        return 0;
    }

    if (inputFile == "-h") {
        print_help();
        return 0;
    }

    if (inputFile == "-dll") {
        if (argc < 3) {
            std::cerr << "Usage: 'mer -dll <source.cpp> [-o output.dll]'\n";
            return 1;
        }

        std::string dllPath = argv[2];
        std::string outputFile = "init.dll";

        for (int i = 3; i < argc; i++) {
            if (std::string(argv[i]) == "-o" && i + 1 < argc) {
                outputFile = argv[i + 1];
                break;
            }
        }

        std::string command = "g++ -shared -o " + outputFile + " " + dllPath +
            " -static -static-libgcc -static-libstdc++"
            " -luser32 -lgdi32 -limm32 -lole32 -loleaut32"
            " -lversion -luuid -ldxguid -lwinmm -lsetupapi -lcfgmgr32";

        if (system(command.c_str()) != 0) {
            std::cerr << "Error: Failed to compile DLL\n";
            return 1;
        }

        return 0;
    }

    if (inputFile == "-p") {
        prompt();
        return 0;
    }

    if (inputFile == "-ast" || inputFile == "-c" || inputFile == "-m") {
        if (argc < 3) {
            std::cerr << "Error: Missing file argument for mode " << inputFile << "\n";
            return 1;
        }
        mode = inputFile;
        inputFile = argv[2];
    }

    if (inputFile == "-info" || inputFile == "-i") {
        std::cout << "More info at http://dinhsonhai132.github.io/main.html";
        std::cout << "\n";
        return 0;
    }

    size_t dotPos = inputFile.find_last_of('.');

    if (inputFile.substr(dotPos + 1) == "merc" || inputFile.substr(dotPos + 1) == "o") {
        vector<uint8_t> bytecode = MerBuffer_read_file_bytecode(inputFile);
        mCode_T compiledCode;
        compiledCode.prg_code.buff = bytecode;
        stack* result = MerVM_evaluate_program(compiledCode);
        return 0;
    }

    if (dotPos == std::string::npos || inputFile.substr(dotPos + 1) != "mer") {
        std::cerr << "Error: file must have .mer extension\n";
        return 1;
    }

    char* sourceCode = MerBuffer_read_file_source(inputFile);
    char* sourceCodeChar = sourceCode;

    MerCore_initialize();

    mLexer_T* lexer = _MerLexer_init(sourceCodeChar);
    lexer->file = const_cast<char*>(inputFile.c_str());

    mParser_T* parser = _MerParser_init(lexer);
    mAST_T* ast = MerParser_parse_program(parser);

    if (mode == "-ast") {
        MerAST_print_ast(ast);
        return 0;
    }

    __compiler_u compiler = compiler_init();
    compiler.file = inputFile.c_str();

    mCode_T compiledCode = MerCompiler_compile_ast_program(ast, compiler);

    free(ast);
    free(lexer);
    free(parser);
    
    if (mode == "-m") {
        print_bytecode(compiledCode.prg_code.buff);
        return 0;
    }

    stack* result = MerVM_evaluate_program(compiledCode);

    if (mode == "-c") {
        std::string OutputByteCode = "__mercache__\\" + inputFile.substr(0, dotPos) + ".merc-320.merc";
        MerBuffer_create_folder("__mercache__");
        MerBuffer_make_and_write_file_bytecode(OutputByteCode, compiledCode.prg_code.buff);
    }
    
    MerCore_Finalize();

    return 0;
}
