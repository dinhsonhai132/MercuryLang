#include "./scr/compile.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void print_token(vector<token> tokens) {
    for (auto &token : tokens) {
        cout << "{ type: " << token.tok << ", value: " << token.value << ", name: " << token.name << ", symbol: " << token.symbol << ", string_iden: " << token.string_iden << " },\n";
    }
}

void print_ast(AST_node *node, int indent = 0) {
    if (!node) return;

    cout << string(indent, ' ') << "{ type: " << node->type;

    if (node->type == LetStatement) {
        cout << ", var_name: " << node->var_name << "\n";
        cout << ", data_type: " << node->data_type << "\n"; 
        cout << ", is_list: " << node->is_list << "\n";
        cout << ", is_None: " << node->is_None << "\n";
        cout << ", is_global: " << node->is_global << "\n";
        cout << ", is_const: " << node->is_constant << "\n";
    } else if (node->type == FunctionCallExpression) {
        cout << ", func_name: " << node->func_call << "\n";
    }

    cout << ", value: " << node->value << ", tok: " << node->tok << " }\n";

    if (node->type == BinaryExpression) {
        cout << string(indent + 2, ' ') << "left: ";
        print_ast(node->left, indent + 2);
        cout << string(indent + 2, ' ') << "right: ";
        print_ast(node->right, indent + 2);
    } else if (node->type == LetStatement) {
        cout << string(indent + 2, ' ') << "value: ";
        print_ast(node->var_value, indent + 2);
    } else if (node->type == FunctionCallExpression) {
        cout << string(indent + 2, ' ') << "args: [\n";
        for (auto &arg : node->args) {
            print_ast(arg, indent + 4);
        }
        cout << string(indent + 2, ' ') << "]\n";
    }

    for (auto &child : node->children) {
        print_ast(child, indent + 2);
    }
}

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