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
        parse::next_token();
    }
}

statement parse::AST_statement() {
    return parse::AST_exprstatement();
};

AST_ExprStatement parse::AST_exprstatement() {
    return parse::AST_primary_expr();
};

AST_ExprStatement parse::AST_primary_expr() {
    const token tok = parse::current_token();
    switch (tok.tok) {
        case parse::is_CurTok_identifier(): {
            return (AST_Identifier) {
                .kind = Identifier,
                .name = tok.tok
            };
        } case parse::is_CurTok_Literal(): {
            return (AST_Literal) {
                .kind = Literal,
                .value = tok.value
            };
        } default: {
            return (statement) {};
        }
    }
};

AST_Literal parse::AST_parse_literal() {};