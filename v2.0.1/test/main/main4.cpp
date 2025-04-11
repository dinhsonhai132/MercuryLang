#include "C:\MercuryLang-main\v2.0.1\mercury\ceval.cpp"

#include <cstring>

using namespace std;

void print_ast(mAST_T *ast, int depth = 0) {
    if (!ast) return;

    string indent(depth * 2, ' ');
    cout << indent << "{" << endl;

    cout << indent << "  Node Type: " << ast->type << endl;

    if (!ast->tok.empty()) {
        cout << indent << "  Token: " << ast->tok << endl;
    }
    if (!ast->string_iden.empty()) {
        cout << indent << "  Identifier: " << ast->string_iden << endl;
    }
    if (ast->value != 0.0) {
        cout << indent << "  Value: " << ast->value << endl;
    }

    if (ast->type == LetStatement) {
        cout << indent << "  Variable Name: " << ast->var_name << endl;
        if (ast->var_value) {
            cout << indent << "  Variable Value:" << endl;
            print_ast(ast->var_value, depth + 1);
        }
    } else if (ast->type == FunctionStatement) {
        cout << indent << "  Function Name: " << ast->func_name << endl;
        cout << indent << "  Arguments:" << endl;
        for (const auto &arg : ast->args_idens) {
            cout << indent << "    " << arg << endl;
        }
        cout << indent << "  Body:" << endl;
        for (auto &child : ast->body) {
            print_ast(child, depth + 1);
        }
    } else if (ast->type == BinaryExpression) {
        cout << indent << "  Operator: " << ast->op << endl;
        cout << indent << "  Left:" << endl;
        print_ast(ast->left, depth + 1);
        cout << indent << "  Right:" << endl;
        print_ast(ast->right, depth + 1);
    }

    if (!ast->children.empty()) {
        cout << indent << "  Children:" << endl;
        for (auto &child : ast->children) {
            print_ast(child, depth + 1);
        }
    }

    cout << indent << "}" << endl;
}

int main() {
    const char* buff = "LET a = 2";
    mLexer_T *lexer = _MerLexer_init(buff);
    // mToken_T *token = _MerLexer_get_next_tok(lexer);
    // cout << "Token: " << token->tok << ", Value: " << token->value << ", Index: " << lexer->id << endl;
    // token = _MerLexer_get_next_tok(lexer);
    // cout << "Token: " << token->tok << ", Value: " << token->value << ", Index: " << lexer->id << endl;
    // token = _MerLexer_get_next_tok(lexer);
    // cout << "Token: " << token->tok << ", Value: " << token->value << ", Index: " << lexer->id << endl;
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    print_ast(ast);

    vector<uint8_t> code = MerCompiler_compile_ast_program(ast);
    stack *stk = MerCompilerBytecode_evaluate_program(code);

    for (auto &item : stk->s_table->table) {
        cout << item->cval << endl;
    }
    return 0;
}