#include "./scr/compile.cpp"

void print_ast(AST_node *node, int indent = 0) {
    if (!node) return;

    for (int i = 0; i < indent; ++i) cout << "  ";
    cout << "Node Type: " << node->type << endl;

    if (node->type == BinaryExpression) {
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << "Operator: " << node->op << endl;
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << "Left:" << endl;
        print_ast(node->left, indent + 1);
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << "Right:" << endl;
        print_ast(node->right, indent + 1);
    } else if (node->type == FunctionStatement) {
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << "Function Name: " << node->func_name << endl;
    } else if (node->type == LetStatement) {
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << "Variable Name: " << node->var_name << endl;
    }

    for (AST_node *child : node->children) {
        print_ast(child, indent + 1);
    }
}

int main(int argc, char *argv[]) {
    for (;;) {
        string input;
        cout << ">> ";
        getline(cin, input);
        if (input == "exit") break;

        vector<token> tokens = MerLexer_tokenize(input);
        AST_node *ast = MerAST_make_AST(tokens);
        char *bytecode = MVM_compile_program(ast);
        print_ast(ast);
        delete[] bytecode;
    }
}