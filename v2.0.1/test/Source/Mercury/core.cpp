#include "C:\Users\dinhs\Documents\Program Language\Mercury-Langluage-main\Mercury-Langluage-main\v2.0.1\test\Source\Mercury\include\core.h"
#include "core.h"

RunTimeVal MerShell_repl(string source) {
    vector<token> tokens = MerLexer_tokenize(source);
    AST_node *ast = MerAST_make_ast(tokens);
    RunTimeVal result = MVM_evaluate_program(ast, nullptr);
    return result;
}

RunTimeVal MerShell_repl_file(string file_name);