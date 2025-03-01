#include "./source/include/eval.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

RunTimeVal MerCompiler_compile(string source) {
    vector <token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_ast(tokens);
    RunTimeVal result = MVM_evaluate_AST(ast);
    return result;
}

int main() {
    cout << "MercuryLang v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        }
        RunTimeVal result = MerCompiler_compile(source);
        cout << result.value << endl;
    }
    return 0;
}