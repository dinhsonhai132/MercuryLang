/// Copyright (c) 2025-present Dinh Son Hai

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "..\Mercury\out.cpp"

using namespace std;
namespace fs = std::filesystem;

enum class OptionFlags {
    NONE,
    VERSION,
    HELP,
    PROMPT,
    OUTPUT,
    COMPILE
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        prompt();
        return 0;
    }

    unordered_map<Mer_real_string, OptionFlags> options = {
        {"-v", OptionFlags::VERSION},
        {"-h", OptionFlags::HELP},
        {"-p", OptionFlags::PROMPT},
        {"-o", OptionFlags::OUTPUT},
        {"-m", OptionFlags::COMPILE}
    };

    OptionFlags flag = OptionFlags::NONE;
    Mer_real_string inputFile, outputFile;
    bool customOutput = false;

    for (int i = 1; i < argc; ++i) {
        Mer_real_string arg = argv[i];

        if (options.find(arg) != options.end()) {
            flag = options[arg];
            if (flag == OptionFlags::VERSION) {
                cout << LANGUAGE << " Version " << CUSTOM_VERSION << " by " << AUTHOR << endl;
                return EXIT_SUCCESS;
            }
            if (flag == OptionFlags::HELP) {
                print_help();
                return EXIT_SUCCESS;
            }
            if (flag == OptionFlags::PROMPT) {
                prompt();
                return EXIT_SUCCESS;
            }
            if (flag == OptionFlags::OUTPUT) {
                if (i + 2 >= argc) {
                    cerr << "Error: '-o' option requires both an input file and an output file." << endl;
                    return EXIT_FAILURE;
                }
                inputFile = argv[++i];

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != CUSTOM_INPUT) {
                    cerr << "Error: Input file must have a ." << CUSTOM_INPUT << " extension" << endl;
                    return EXIT_FAILURE;
                }

                Mer_real_string v = CUSTOM_BINARY_OUTPUT;
                outputFile = argv[++i] + v;
                customOutput = true;
            }
            if (flag == OptionFlags::COMPILE) {
                if (i + 1 >= argc) {
                    cerr << "Error: No input file specified." << endl;
                    return EXIT_FAILURE;
                }
                inputFile = argv[++i];

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != CUSTOM_INPUT) {
                    cerr << "Error: Input file must have a ." << CUSTOM_INPUT << " extension" << endl;
                    return EXIT_FAILURE;
                }

                try {
                    Mer_real_string input = MerBuffer_read_file(inputFile);
                    mLexer_T *lexer = _MerLexer_init(input.c_str());
                    lexer->file = inputFile.c_str();
                    mParser_T *parser = _MerParser_init(lexer);
                    sign_in_mer_libs();
                    __compiler_u glb = compiler_init();
                    glb.file = inputFile.c_str();
                    mAST_T *ast = MerParser_parse_program(parser);
                    mCode_T code = MerCompiler_compile_ast_program(ast, glb);
                    vector<Mer_uint8_t> buff = code.prg_code.buff;
                    vector<Mer_uint8_t> out_buff = code.out_code.buff;
                    stack *stk = eval_program(code);
                    outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + CUSTOM_INPUT;
                    MerBuffer_make_and_write_file_bytecode(outputFile, buff);
                    return EXIT_SUCCESS;
                } catch (exception &e) {
                    cerr << "Error: " << e.what() << endl;
                    return EXIT_FAILURE;
                }
            }
        } else {
            inputFile = arg;
        }
    }

    if (inputFile.empty() || inputFile.substr(inputFile.find_last_of(".") + 1) != CUSTOM_INPUT) {
        cerr << "Error: Input file must have a ." << CUSTOM_INPUT << " extension" << endl;
        return EXIT_FAILURE;
    }

    try {
        __compiler_u glb = compiler_init();
        glb.file = inputFile.c_str();
        Mer_real_string input = MerBuffer_read_file(inputFile);
        mLexer_T *lexer = _MerLexer_init(input.c_str());
        lexer->file = inputFile.c_str();
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MerCompiler_compile_ast_program(ast, glb);
        sign_in_mer_libs();
        stack *stk = eval_program(code);
        vector<Mer_uint8_t> buff = code.prg_code.buff;
        vector<Mer_uint8_t> out_buff = code.out_code.buff;

        if (!ast) {
            cerr << "Error: Failed to parse the AST!" << endl;
            return EXIT_FAILURE;
        }

        Mer_real_string folder_name = CUSTOME_BINARY_FOLDER;
        if (!fs::exists(folder_name)) fs::create_directory(folder_name);

        Mer_real_string real_outputFile = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + "." + CUSTOM_BINARY_OUTPUT);
        Mer_real_string real_outputFile_out_code = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + "." + CUSTOM_BINARY_OUT_OUTPUT);
        MerBuffer_make_and_write_file_bytecode(real_outputFile.c_str(), buff);
        MerBuffer_make_and_write_file_bytecode(real_outputFile_out_code.c_str(), out_buff);
    } 
    catch (const std::exception &e) {
        cerr << "Compilation Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}