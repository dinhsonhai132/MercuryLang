#include "./scr/compile.cpp"
#include "./scr/ceval.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#define MERCURY_VERSION "2.0.1"
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
    cout << COLOR_BOLD << "MercuryLang CLI - Version " << MERCURY_VERSION << COLOR_RESET << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  " << COLOR_BLUE << "-o <filename>" << COLOR_RESET << "\tCompile to a specific output file\n";
}

void print_ast(AST_node *ast, int depth = 0) {
    if (!ast) return;

    string indent(depth * 2, ' ');
    cout << indent << "{\n";
    cout << indent << "  Node Type: " << ast->type << endl;

    if (!ast->var_name.empty()) cout << indent << "  Variable Name: " << ast->var_name << endl;
    if (!ast->func_name.empty()) cout << indent << "  Function Name: " << ast->func_name << endl;
    if (!ast->string_iden.empty()) cout << indent << "  Identifier: " << ast->string_iden << endl;
    if (ast->value != 0.0) cout << indent << "  Value: " << ast->value << endl;
    if (!ast->op.empty()) cout << indent << "  Operator: " << ast->op << endl;

    if (ast->left) {
        cout << indent << "  Left Node:\n";
        print_ast(ast->left, depth + 1);
    }

    if (ast->right) {
        cout << indent << "  Right Node:\n";
        print_ast(ast->right, depth + 1);
    }

    if (!ast->children.empty()) {
        cout << indent << "  Children:\n";
        for (auto &child : ast->children) {
            print_ast(child, depth + 1);
        }
    }
    cout << indent << "}\n";
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
    cout << COLOR_CYAN << "MercuryLang REPL - v" << MERCURY_VERSION << COLOR_RESET << endl;
    cout << "Type " << COLOR_YELLOW << "'exit'" << COLOR_RESET << " to quit\n" << endl;
    
    string input;
    while (true) {
        cout << COLOR_YELLOW << ">>> " << COLOR_RESET;
        getline(cin, input);
        if (input == "exit") break;
        
        vector<token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_AST(tokens);
        if (!ast) {
            cerr << COLOR_RED << "Syntax Error!" << COLOR_RESET << endl;
            continue;
        }

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

    if (arg == "-o") {
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
    string outputFile = output ? output_file_name + "merc-250.merc" : inputFile.substr(0, dot_pos) + "merc-250.merc";

    try {
        string source = MerBuffer_read_file(inputFile);
        vector<token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_AST(tokens);
        if (!ast) {
            cerr << COLOR_RED << "Error: Failed to parse the AST!" << COLOR_RESET << endl;
            return EXIT_FAILURE;
        }
        char* code = MVM_compile_program(ast, code_address);
        MerBuffer_make_and_write_file(outputFile.c_str(), code);
        print_ast(ast);
        cout << COLOR_GREEN << "Compilation successful! Output: " << outputFile << COLOR_RESET << endl;
    } catch (const exception &e) {
        cerr << COLOR_RED << "Compilation Error: " << e.what() << COLOR_RESET << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
