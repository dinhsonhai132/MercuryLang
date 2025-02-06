#include "parse.h"

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
    const token tok = parse::get_current_token();
    if (tok.tok == LET) {
        return parse::AST_varDeclaraion();
    } else if (tok.tok == PRINT) {
        return parse::AST_printstatement();
    }
    return parse::AST_exprstatement();
};

AST_ExprStatement parse::AST_exprstatement() {
    return parse::AST_Multiplicative_Expression();
};

statement parse::AST_printstatement() {
    const token tok = parse::get_current_token();
    if (tok.tok != PRINT) {
        throw runtime_error("Unexpected token: " + tok.tok);
    }
    parse::jump_ntok();
    AST_ExprStatement expr = parse::AST_Multiplicative_Expression();
    return (AST_PrintStatement) {
        .type = PrintStatement,
        .output = expr
    };
}

statement parse::AST_varDeclaraion() {
    const bool isLet = parse::get_current_token().tok == LET;
    if (isLet) {
        const token var_name = parse::get_next_token();
        if (!is_Tok_identifier(var_name.tok)) {
            throw runtime_error("Unexpected token: " + var_name.tok);
        }

        const token tok = parse::get_current_token();
        const token isAssign = tok.tok != LET || tok.tok == SEMICOLON;
        if (isAssign) {
            return (AST_VarDeclaraion) {
                .type = VarDeclaraion,
                .constants = isConst,
                .var_identifier = var_name.name,
                .value = 0
            };
        }

        AST_ExprStatement value = parse::AST_Multiplicative_Expression();
        return (AST_VarDeclaraion) {
            .type = VarDeclaraion,
            .constants = isConst,
            .var_identifier = var_name.name,
            .value = value
        };
    } else {
        throw runtime_error("Unexpected token: " + tok.tok);
    }

    return {};
}

AST_ExprStatement parse::AST_primary_expr() {
    const token tok = parse::get_current_token();
    if (is_Tok_identifier(tok.tok)) {
        return (AST_Identifier) {
            .type = Identifier,
            .name = tok.name
        };
    } else if (is_Tok_Literal(tok.tok)) {
        return (AST_Literal) {
            .type = Literal,
            .value = tok.value
        };
    } else if (is_Tok_Null(tok.tok)) {
        return (AST_NullExpression) {};
    } else {
        throw runtime_error("Unexpected token: " + tok.tok);
    }
}

AST_ExprStatement parse::AST_Additive_Expression() {
    AST_ExprStatement left = parse::AST_primary_expr();
    auto tok = parse::get_next_token();
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
        tok = parse::get_next_token();
    }

    return left;
}

AST_ExprStatement parse::AST_Multiplicative_Expression() {
    AST_ExprStatement left = parse::AST_Additive_Expression();
    auto tok = parse::get_next_token();
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
        tok = parse::get_next_token();
    }

    return left;
}