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

#include "C:\MercuryLang\Mercury\ceval.cpp"
#include <filesystem>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#define MERCURY_VERSION "2.1.0"
#define AUTHOR "Dinh Son Hai"

enum class OptionFlags {
    NONE,
    VERSION,
    HELP,
    PROMPT,
    OUTPUT,
    COMPILE
};

void print_help() {
    cout << "MercuryLang CLI - Version " << MERCURY_VERSION << endl;
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
    strftime(buf, sizeof(buf), "%a %b %d %H:%M:%S %Y", ltm); // không có \n
    return Mer_real_string(buf);
}

void prompt() {
    cout << "MercuryLang v2.1.1a (tags v2.1.1-alpha " << get_time() << ") [Mercury-Virtal-Machine-v2.0 64-bit (x86_64)] on win32\n";
    cout << "'help' for help, 'cls' for reset stack, 'exit' for exit\n";

    Mer_real_string input = "";
    Mer_real_string source = "";
    while (true) {
        cout << ">>> ";
        getline(cin, source);

        if (source == "exit") break;
        if (source == "cls") input = "";
        if (source == "help") print_help();
        if (source == "version") cout << "MercuryLang version: " << MERCURY_VERSION << " - By " << AUTHOR << endl;

        input += source + "\n";

        mLexer_T *lexer = _MerLexer_init(input.c_str());
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MVM_program(ast);
        stack *stk = eval_program(code);

        if (!ast) {
            cerr << "Syntax Error!" << endl;
            continue;
        }

        if (stk->s_table->table.size() == 0) {
            continue;
        } else {
            cout << "Register: [0";
            for (auto &item : stk->s_table->table) {
                cout << ", ";
                cout << item->cval;
            }
            cout << "]" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        prompt();
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
                cout << "MercuryLang Version " << MERCURY_VERSION << " by " << AUTHOR << endl;
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

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
                    cerr << "Error: Input file must have a .mer extension" << endl;
                    return EXIT_FAILURE;
                }

                Mer_real_string v = ".merc-250.merc";
                outputFile = argv[++i] + v;
                customOutput = true;
            }
            if (flag == OptionFlags::COMPILE) {
                if (i + 1 >= argc) {
                    cerr << "Error: No input file specified." << endl;
                    return EXIT_FAILURE;
                }
                inputFile = argv[++i];

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
                    cerr << "Error: Input file must have a .mer extension" << endl;
                    return EXIT_FAILURE;
                }

                try {
                    Mer_real_string input = MerBuffer_read_file(inputFile);
                    mLexer_T *lexer = _MerLexer_init(input.c_str());
                    mParser_T *parser = _MerParser_init(lexer);
                    mAST_T *ast = MerParser_parse_program(parser);
                    mCode_T code = MVM_program(ast);
                    vector<Mer_uint8_t> buff = code.prg_code.buff;
                    vector<Mer_uint8_t> out_buff = code.out_code.buff;
                    stack *stk = eval_program(code);
                    outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + ".merc";
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

    if (inputFile.empty() || inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
        cerr << "Error: Input file must have a .mer extension" << endl;
        return EXIT_FAILURE;
    }

    try {
        Mer_real_string input = MerBuffer_read_file(inputFile);
        mLexer_T *lexer = _MerLexer_init(input.c_str());
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MVM_program(ast);
        stack *stk = eval_program(code);
        vector<Mer_uint8_t> buff = code.prg_code.buff;
        vector<Mer_uint8_t> out_buff = code.out_code.buff;

        if (!ast) {
            cerr << "Error: Failed to parse the AST!" << endl;
            return EXIT_FAILURE;
        }

        cout << "Register: [0";
        for (auto &item : stk->s_table->table) {
            cout << ", ";
            cout << item->cval;
        }

        cout << "]" << endl;

        Mer_real_string folder_name = "__mercache__";
        if (!fs::exists(folder_name)) fs::create_directory(folder_name);

        Mer_real_string real_outputFile = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + ".merc-250.merc");
        Mer_real_string real_outputFile_out_code = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + ".merc-250.out.merc");
        MerBuffer_make_and_write_file_bytecode(real_outputFile.c_str(), buff);
        MerBuffer_make_and_write_file_bytecode(real_outputFile_out_code.c_str(), out_buff);
        
        cout << "Compiled successfully to: " << real_outputFile << endl;
    } 
    catch (const std::exception &e) {
        cerr << "Compilation Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}