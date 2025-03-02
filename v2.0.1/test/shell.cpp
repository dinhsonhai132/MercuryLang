#include "./source/include/eval.h"

int main(int argc, char *argv[]) {
    for (;;) {
        cout << ">> ";
        string input;
        getline(cin, input);
        if (input == "exit") {
            break;
        }
        vector <token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_ast(tokens);
        RunTimeVal result = MVM_evaluate_AST(ast, NULL);
        cout << result.value << endl;
    }
}