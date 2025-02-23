#include "./Mercury/include/core.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void MercuryLang(string source) {
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_ast(tokens);
    RunTimeVal result = MVM_evaluate_program(ast, nullptr);
    cout << "{ type: " << result.type << ", value: " << result.value << " }" << endl;
}