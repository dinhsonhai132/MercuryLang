#include "../source/include/shell.h"

RunTimeVal MerShell_compile(string source) {
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_AST(tokens);
    RunTimeVal result = MVM_evaluate_AST(ast, nullptr);
    return result;
}

int MerShell_run_check(string source) {
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_AST(tokens);
    RunTimeVal result = MVM_evaluate_AST(ast, nullptr);
    if (result.type == _Null) {
        return _FAILURE
    }

    return _SUCCESS;
}

int main(int argc, char **argv) {
    for (;;) {
        cout << ">> ";
        string line;
        getline(cin, line);
        if (line == "exit") break;
        
        RunTimeVal result = MerShell_compile(line);
        int check = MerShell_run_check(line);
        cout << "{ type: " << result.type << ", value: " << result.value << " }" << endl;

        if (check == 1) {
            cout << "SUCCESS\n";
        } else {
            cout << "FAILURE\n";
        }
    }
}