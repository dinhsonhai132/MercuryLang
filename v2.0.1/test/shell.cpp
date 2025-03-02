#include "source/include/eval.h"
#include "shell.h"

int main() {
    for (;;) {
        string input;
        getline(cin, input);
        if (input == "exit") {
            break;
        }
        
        vector<token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_ast(tokens);
        RunTimeVal result = MVM_evaluate_program(ast, NULL);
    }
    return 0;
}