#include "parse.h"

using namespace std;

AST_Program parse::AST_tokenize() {
    tokens = lex.tokenize(source);
    AST_Program program = {
        .kind = AST_Program,
        .statements = vector<statement>{}
    };

    while (!parse::is_CurTokEOF()) {
        program.statements.push_back(parse::AST_statement());
    }

    return program;
}

statement parse::AST_statement() {
    return parse::AST_exprstatement();
};

AST_ExprStatement parse::AST_exprstatement() {
    return parse::AST_Additive_Expression();
};

AST_ExprStatement parse::AST_primary_expr() {
    const token tok = parse::get_current_token();
    switch (tok.tok) {
        case parse::is_CurTok_identifier(): {
            parse::jump_ntok();
            return (AST_Identifier) {
                .kind = Identifier,
                .name = tok.tok
            };
        } case parse::is_CurTok_Literal(): {
            parse::jump_ntok();
            return (AST_Literal) {
                .kind = Literal,
                .value = tok.value
            };
        } default: {
            cout << "Unexpected token: " << tok.tok << endl;
            return (statement) {};
        }
    }
}

AST_ExprStatement parse::AST_Additive_Expression() {
    auto left = parse::AST_primary_expr();
    while (parse::get_current_token().tok == PLUS || parse::get_current_token().tok == MINUS) {
        string op = parse::get_current_token().tok;
        parse::jump_ntok();
        auto right = parse::AST_primary_expr();
        left = (AST_BinaryExpression) {
            .kind = BinaryExpression,
            .left = left,
            .right = right,
            .op = op
        }
    }
    return left;
};