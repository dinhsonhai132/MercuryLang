#include "./scr/compile.cpp"
#include "./scr/ceval.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#define VERSION "2.0.1"
#define AUTHOR  "Dinh Son Hai"

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BOLD    "\033[1m"

vector<char*> code_address;

void print_help() {
    cout << COLOR_BOLD << "MercuryLang CLI - " << VERSION << COLOR_RESET << endl;
    cout << "Usage: " << COLOR_YELLOW << "mercury [options] <filename>.mer" << COLOR_RESET << endl;
    cout << "Options:\n";
    cout << "  " << COLOR_GREEN << "--version" << COLOR_RESET << "\t\tShow version information\n";
    cout << "  " << COLOR_BLUE << "--prompt" << COLOR_RESET << "\t\tStart the Mercury REPL\n";
    cout << "  " << COLOR_CYAN << "--help" << COLOR_RESET << "\t\tShow this help message\n";
    cout << "  " << COLOR_RED << "--output <filename>" << COLOR_RESET << "\tCompile to specific output file\n";
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
    cout << " MercuryLang v" << VERSION << " - By " << AUTHOR << endl;
}


void prompt() {
    print_logo();
    cout << COLOR_BOLD << "Type 'exit' to quit\n" << COLOR_RESET;

    string input;
    while (true) {
        cout << COLOR_YELLOW << ">>> " << COLOR_RESET;
        getline(cin, input);
        if (input == "exit") break;

        vector<token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_AST(tokens);
        char* code = MVM_compile_program(ast, code_address);
        stack *stk = MerCompiler_Stack_new();
        stk = MerCompiler_evaluate_program(code, stk);

        for (auto &item : stk->s_table->table) {
            cout << COLOR_GREEN << item->cval << COLOR_RESET << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return EXIT_FAILURE;
    }

    string arg = argv[1];
    bool output = false;
    string output_file_name;

    if (arg == "--version") {
        cout << "MercuryLang Version " << VERSION << " by " << AUTHOR << endl;
        return EXIT_SUCCESS;
    } 
    if (arg == "--prompt") {
        prompt();
        return EXIT_SUCCESS;
    }
    if (arg == "--help") {
        print_help();
        return EXIT_SUCCESS;
    } 
    if (arg == "--output") {
        if (argc < 4) {
            cerr << COLOR_RED << "Error: Output file not specified!" << COLOR_RESET << endl;
            return EXIT_FAILURE;
        }
        arg = argv[2];
        output_file_name = argv[3];
        output = true;
    }

    size_t dot_pos = arg.find_last_of(".");
    if (dot_pos == string::npos || arg.substr(dot_pos + 1) != "mer") {
        cerr << COLOR_RED << "Error: Input file must have a .mer extension!" << COLOR_RESET << endl;
        return EXIT_FAILURE;
    }

    string inputFile = arg;
    string outputFile = output ? output_file_name + ".merc" : inputFile.substr(0, dot_pos) + ".merc";

    try {
        string source = MerBuffer_read_file(inputFile);
        vector<token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_AST(tokens);
        char* code = MVM_compile_program(ast, code_address);
        MerBuffer_make_and_write_file(outputFile.c_str(), code);
        
        cout << COLOR_GREEN << "✅ Compilation successful! Output: " << outputFile << COLOR_RESET << endl;
    } catch (const exception &e) {
        cerr << COLOR_RED << "Compilation Error: " << e.what() << COLOR_RESET << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
