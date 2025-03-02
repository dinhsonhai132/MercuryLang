#include "../include/eval.h"

int main(int argc, char **argv) {
    for (;;) {
        cout << ">> ";
        string line;
        getline(cin, line);
        if (line == "exit") break;
        
        vector<token> tokens = MerLexer_tokenize(line);
        AST_node *ast = MerAST_make_AST(tokens);
        RunTimeVal result = MVM_evaluate_AST(ast, NULL);
        cout << "{ type: " << result.type << ", value: " << result.value << " }" << endl;
    }
}