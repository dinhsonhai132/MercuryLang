#include "C:\MercuryLang-main\v2.0.1\parser\parser.h"
#include "C:\MercuryLang-main\v2.0.1\mercury\include\ceval.h"
#include <unordered_map>
#include <filesystem>

using namespace std;

void print_ast(mAST_T *ast) {
    if (!ast) return;

    cout << "Node Type: " << ast->type << endl;
    if (!ast->tok.empty()) {
        cout << "Token: " << ast->tok << endl;
    }
    if (!ast->string_iden.empty()) {
        cout << "Identifier: " << ast->string_iden << endl;
    }
    if (ast->value != 0.0) {
        cout << "Value: " << ast->value << endl;
    }
    if (ast->left) {
        cout << "Left:" << endl;
        print_ast(ast->left);
    }
    if (ast->right) {
        cout << "Right:" << endl;
        print_ast(ast->right);
    }
    if (!ast->children.empty()) {
        cout << "Children:" << endl;
        for (auto &child : ast->children) {
            print_ast(child);
        }
    }
}

namespace fs = std::filesystem;

#define MERCURY_VERSION "2.1.0"
#define AUTHOR "Dinh Son Hai"

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BOLD    "\033[1m"

enum class OptionFlags {
    NONE,
    VERSION,
    HELP,
    PROMPT,
    OUTPUT,
    COMPILE
};

void print_help() {
    cout << COLOR_BOLD << "MercuryLang CLI - Version " << MERCURY_VERSION << COLOR_RESET << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  " << COLOR_GREEN << "-v" << COLOR_RESET << "\t\tShow version information\n";
    cout << "  " << COLOR_YELLOW << "-p" << COLOR_RESET << "\t\tStart the Mercury REPL\n";
    cout << "  " << COLOR_CYAN << "-h" << COLOR_RESET << "\t\tShow this help message\n";
    cout << "  " << COLOR_BLUE << "-o <filename> <target>" << COLOR_RESET << "\tCompile to a specific output file\n";
    cout << "  " << COLOR_RED << "-m" << COLOR_RESET << "\t\tCompiled into readable mercury bytecode\n"; 
}

void print_logo() {
    cout << COLOR_BOLD << COLOR_CYAN;
    cout << " __       __                                                              __                                     \n";
    cout << "/  \\     /  |                                                            /  |                                    \n";
    cout << "$$  \\   /$$ |  ______    ______    _______  __    __   ______   __    __ $$ |        ______   _______    ______  \n";
    cout << "$$$  \\ /$$$ | /      \\  /      \\  /       |/  |  /  | /      \\ /  |  /  |$$ |       /      \\ /       \\  /      \\ \n";
    cout << "$$$$  /$$$$ |/$$$$$$  |/$$$$$$  |/$$$$$$$/ $$ |  $$ |/$$$$$$  |$$ |  $$ |$$ |       $$$$$$  |$$$$$$$  |/$$$$$$  | \n";
    cout << "$$ $$ $$/$$ |$$    $$ |$$ |  $$/ $$ |      $$ |  $$ |$$ |  $$/ $$ |  $$ |$$ |       /    $$ |$$ |  $$ |$$ |  $$ | \n";
    cout << "$$ |$$$/ $$ |$$$$$$$$/ $$ |      $$ \\_____ $$ \\__$$ |$$ |      $$ \\__$$ |$$ |_____ /$$$$$$$ |$$ |  $$ |$$ \\__$$ | \n";
    cout << "$$ | $/  $$ |$$       |$$ |      $$       |$$    $$/ $$ |      $$    $$ |$$       |$$    $$ |$$ |  $$ |$$    $$ | \n";
    cout << "$$/      $$/  $$$$$$$/ $$/        $$$$$$$/  $$$$$$/  $$/        $$$$$$$ |$$$$$$$$/  $$$$$$$/ $$/   $$/  $$$$$$$ | \n";
    cout << "                                                               /  \\__$$ |                              /  \\__$$ | \n";
    cout << "                                                               $$    $$/                               $$    $$/  \n";
    cout << "                                                                $$$$$$/                                 $$$$$$/   \n";
    cout << COLOR_RESET;
    cout << " MercuryLang version: " << MERCURY_VERSION << " - By " << AUTHOR << endl;
}

void prompt() {
    print_logo();
    cout << COLOR_BOLD << "MercuryLang REPL " << MERCURY_VERSION << COLOR_RESET << endl;
    cout << "Type " << COLOR_RED << "'exit'" << COLOR_RESET << " to quit\n";
    
    string input = "";
    string source = "";
    while (true) {
        cout << COLOR_YELLOW << ">>> " << COLOR_RESET;
        getline(cin, source);

        if (source == "exit") break;
        if (source == "cls") input = "";

        input += source + "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return EXIT_FAILURE;
    }

    unordered_map<string, OptionFlags> options = {
        {"-v", OptionFlags::VERSION},
        {"-h", OptionFlags::HELP},
        {"-p", OptionFlags::PROMPT},
        {"-o", OptionFlags::OUTPUT},
        {"-m", OptionFlags::COMPILE}
    };

    OptionFlags flag = OptionFlags::NONE;
    string inputFile, outputFile;
    bool customOutput = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

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
                    cerr << COLOR_RED << "Error: '-o' option requires both an input file and an output file." << COLOR_RESET << endl;
                    return EXIT_FAILURE;
                }
                inputFile = argv[++i];

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
                    cerr << COLOR_RED << "Error: Input file must have a .mer extension" << COLOR_RESET << endl;
                    return EXIT_FAILURE;
                }

                string v = ".merc-250.merc";
                outputFile = argv[++i] + v;
                customOutput = true;
            }
            if (flag == OptionFlags::COMPILE) {
                if (i + 1 >= argc) {
                    cerr << COLOR_RED << "Error: No input file specified." << COLOR_RESET << endl;
                    return EXIT_FAILURE;
                }
                inputFile = argv[++i];

                if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
                    cerr << COLOR_RED << "Error: Input file must have a .mer extension" << COLOR_RESET << endl;
                    return EXIT_FAILURE;
                }

                try {
                    string source = MerBuffer_read_file(inputFile);
                    char* source_copy = strdup(source.c_str());
                    mLexer_T *lexer = _MerLexer_init(source_copy);
                    free(source_copy);
                    mParser_T *parser = _MerParser_init(lexer);
                    mAST_T *ast = MerParser_parse_program(parser);
                    vector<uint8_t> code = MerCompiler_compile_ast_program(ast);

                    string folder_name = "__mercache__";
                    if (!fs::exists(folder_name)) fs::create_directory(folder_name);

                    string real_outputFile = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + ".merc-250.merc");
                    MerBuffer_make_and_write_file_bytecode(real_outputFile.c_str(), code);

                    cout << COLOR_BLUE << "Compiled successfully to: " << real_outputFile << COLOR_RESET << endl;
                    return EXIT_SUCCESS;
                } catch (exception &e) {
                    cerr << COLOR_RED << "Error: " << e.what() << COLOR_RESET << endl;
                    return EXIT_FAILURE;
                }
            }
        } else {
            inputFile = arg;
        }
    }

    if (inputFile.empty() || inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
        cerr << COLOR_RED << "Error: Input file must have a .mer extension" << COLOR_RESET << endl;
        return EXIT_FAILURE;
    }

    try {
        string source = MerBuffer_read_file(inputFile);
        char* source_copy = strdup(source.c_str());
        mLexer_T *lexer = _MerLexer_init(source_copy);
        free(source_copy);
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        vector<uint8_t> code = MerCompiler_compile_ast_program(ast);

        if (outputFile.empty()) {
            outputFile = fs::path(inputFile).stem().string() + ".merc-250.merc";
        }

        if (outputFile.substr(outputFile.find_last_of(".") + 1) != "mer") {
            cerr << COLOR_RED << "Error: Output file must have a .mer extension" << COLOR_RESET << endl;
            return EXIT_FAILURE;
        }

        string folder_name = "__mercache__";
        if (!fs::exists(folder_name)) fs::create_directory(folder_name);

        string real_outputFile = folder_name + "/" + (customOutput ? outputFile : fs::path(inputFile).stem().string() + ".merc-250.merc");
        MerBuffer_make_and_write_file_bytecode(real_outputFile.c_str(), code);

        cout << COLOR_BLUE << "Compiled successfully to: " << real_outputFile << COLOR_RESET << endl;
    } 
    catch (const std::exception &e) {
        cerr << COLOR_RED << "Compilation Error: " << e.what() << COLOR_RESET << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}