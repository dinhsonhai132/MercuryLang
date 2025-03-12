#include "./scr/compile.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>.mer" << endl;
        return 1;
    }

    string inputFile = argv[1];
    if (inputFile.substr(inputFile.find_last_of(".") + 1) != "mer") {
        cerr << "Error: Input file must have a .mer extension" << endl;
        return 1;
    }

    string outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + ".merc";

    string source = MerBuffer_read_file(inputFile);
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_AST(tokens);
    print_ast(ast);
    cout << "\n\n\n";
    print_token(tokens);
    char* code = MVM_compile_program(ast);
    MerBuffer_make_and_write_file(outputFile.c_str(), code);

    return 0;
}
