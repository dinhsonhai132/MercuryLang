#include "./scr/compile.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#define VERSION "2.0.1"

void print_help() {
    cout << "Usage: mercury [options] <filename>.mer" << endl;
    cout << "Options:" << endl;
    cout << "  --version\t\tPrint version information" << endl;
    cout << "  --prompt\t\tStart the Mercury REPL" << endl;
    cout << "  --help\t\tShow this help message" << endl;
    cout << "  --output <filename>\tMake output file" << endl;
}

void prompt() {
    cout << "Repl " << VERSION << endl;
    cout << "Type 'exit' to exit" << endl;
    string input;
    while (true) {
        cout << ">>> ";
        getline(cin, input);
        if (input == "exit") break;

        vector<token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_AST(tokens);
        char* code = MVM_compile_program(ast);
        cout << code << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    string arg = argv[1];

    bool output = false;
    string output_file_name;
    if (arg == "--version") {
        cout << "MercuryLang Version " << VERSION << endl;
        cout << "Written by Dinh Son Hai" << endl;
        return 0;
    } 
    if (arg == "--prompt") {
        prompt();
        return 0;
    } 
    if (arg == "--help") {
        print_help();
        return 0;
    } 
    if (arg == "--output") {
        if (argc < 3) {
            cerr << "Error: Output file not specified" << endl;
            return 1;
        }
        arg = argv[2];
        output_file_name = argv[3];
        output = true;
    }

    string inputFile = arg;
    if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
        cerr << "Error: Input file must have a .mer extension" << endl;
        return 1;
    }
    string outputFile;
    if (!output) {
        outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + ".merc";
    } else {
        outputFile = output_file_name + ".merc";
    }
    string source = MerBuffer_read_file(inputFile);
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_AST(tokens);
    char* code = MVM_compile_program(ast);
    MerBuffer_make_and_write_file(outputFile.c_str(), code);

    return 0;
}
