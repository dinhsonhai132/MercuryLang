#include "./scr/bceval.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#define VERSION "2.0.1"

vector <char*> code_address = vector<char*>();
void print_help() {
    cout << "Usage: mercury [options] <filename>.mer" << endl;
    cout << "Options:" << endl;
    cout << "  --version\t\tPrint version information" << endl;
    cout << "  --prompt\t\tStart the Mercury REPL" << endl;
    cout << "  --help\t\tShow this help message" << endl;
    cout << "  --output <filename>\tMake output file" << endl;
}

void print_code(vector<uint8_t> code) {
    int idx = 0;
    while (idx < code.size()) {
        uint8_t byte = code[idx++];
        if (byte == PUSH_FLOAT) {
            cout << "PUSH_FLOAT ";
            uint32_t int_repr;
            memcpy(&int_repr, &code[idx], sizeof(uint32_t));
            idx += 4;

            float rval;
            memcpy(&rval, &int_repr, sizeof(float));
            cout << rval << endl;
        } else if (byte == BINARY_ADD || byte == BINARY_SUB || byte == BINARY_DIV || byte == BINARY_MUL) {
            switch (byte) {
                case BINARY_ADD: cout << "BINARY_ADD "; break;
                case BINARY_SUB: cout << "BINARY_SUB "; break;
                case BINARY_DIV: cout << "BINARY_DIV "; break;
                case BINARY_MUL: cout << "BINARY_MUL "; break;
            }
            cout << endl;
        } else if (byte == PROGRAM_END) {
            cout << "PROGRAM_END" << endl;
        } else if (byte == PROGRAM_START) {
            cout << "PROGRAM_START" << endl;
        }
    }
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

    if (ast->type == FunctionStatement) {
        cout << indent << "  Function Statement Body:\n";
        for (auto &child : ast->body) {
            print_ast(child, depth + 1);
        }
    }

    if (ast->type == FunctionCallExpression) {
        cout << indent << "  Function Call Arguments:\n";
        for (auto &arg : ast->args) {
            print_ast(arg, depth + 1);
        }
    }

    if (ast->type == LetStatement) {
        cout << indent << "  Let Statement Value:\n";
        print_ast(ast->var_value, depth + 1);
    }

    if (!ast->children.empty()) {
        cout << indent << "  Children:\n";
        for (auto &child : ast->children) {
            print_ast(child, depth + 1);
        }
    }

    cout << indent << "}\n";
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
        vector<uint8_t> code = MerCompiler_compile_ast_program(ast);
        stack *stk = MerCompilerBytecode_evaluate_program(code);
        for (int i = 0; i < stk->s_table->table.size(); i++) {
            cout << stk->s_table->table[i]->cval << endl;
        }
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
    string source = MerBuffer_read_file(inputFile);
    string outputFile;
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_AST(tokens);
    vector<uint8_t> code = MerCompiler_compile_ast_program(ast);
    print_code(code);
    

    if (!output) {
        outputFile = inputFile.substr(0, inputFile.find_last_of(".")) + ".merc-250.merc";
    } else {
        outputFile = output_file_name + ".merc-250.merc";
    }
    string folder_name = "__mercache__";
    string real_outputFile = folder_name + "/" + outputFile;
    MerBuffer_create_folder(folder_name);
    MerBuffer_make_and_write_file_bytecode(real_outputFile.c_str(), code);
    return 0;
}
