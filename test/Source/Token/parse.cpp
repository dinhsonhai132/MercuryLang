#include "parse.h"
#include "ast.h"

using namespace std;

AST_Program parse::AST_tokenize() {
    tokens = lexer(parse::source).tokenize();
    AST_Program program = {
        .type = Program,
        .statements = vector<statement>{}
    };

    while (!parse::is_CurTokEOF(tokens[tok_idx].tok)) {
        program.statements.push_back(parse::AST_statement());
    }

    return program;
}

statement parse::AST_statement() {
    return parse::AST_exprstatement();
};

AST_ExprStatement parse::AST_exprstatement() {
    return parse::AST_Multiplicative_Expression();
};

AST_ExprStatement parse::AST_primary_expr() {
    const token tok = parse::get_current_token();
    if (is_Tok_identifier(tok.tok)) {
        parse::jump_ntok();
        return (AST_Identifier) {
            .type = Identifier,
            .name = tok.name
        };
    } else if (is_Tok_Literal(tok.tok)) {
        parse::jump_ntok();
        return (AST_Literal) {
            .type = Literal,
            .value = tok.value
        };
    } else if (is_Tok_Null(tok.tok)) {
        parse::jump_ntok();
        return (AST_NullExpression) {};
    } else {
        throw runtime_error("Unexpected token: " + tok.tok);
    }
}

AST_ExprStatement parse::AST_Additive_Expression() {
    AST_ExprStatement left = parse::AST_primary_expr();
    auto tok = parse::get_current_token();
    parse::jump_ntok();
    while (tok.tok == PLUS || tok.tok == MINUS) {
        string op = tok.tok;
        parse::jump_ntok();
        AST_ExprStatement right = parse::AST_primary_expr();
        left = (AST_BinaryExpression) {
            .type = BinaryExpression,
            .op = op,
            .left = left,
            .right = right,
        };
        tok = parse::get_current_token();
    }

    return left;
}

AST_ExprStatement parse::AST_Multiplicative_Expression() {
    AST_ExprStatement left = parse::AST_Additive_Expression();
    auto tok = parse::get_current_token();
    parse::jump_ntok();
    while (tok.tok == TIME || tok.tok == DIV) {
        string op = tok.tok;
        parse::jump_ntok();
        AST_ExprStatement right = parse::AST_Additive_Expression();
        left = (AST_BinaryExpression) {
            .type = BinaryExpression,
            .op = op,
            .left = left,
            .right = right,
        };
        tok = parse::get_current_token();
    }

    return left;
}

AST_ExprStatement parse::AST_ParentLitive() {}