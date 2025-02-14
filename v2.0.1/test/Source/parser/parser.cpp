#include "parser.h"

token Parser::get_ctok() {
    return cur_tok = tokens[idx];
}

token Parser::get_ntok() {
    return cur_tok = tokens[idx++];
}

token Parser::jump_tok(int n) {
    return cur_tok = tokens[idx += n];
}

bool Parser::look_ahead(string tok, int n) {
    cur_tok = tokens[idx + n];
    return cur_tok.tok == tok;
}

AST_node *Parser::MerParser_program() {
    program = MerAST_make_parent(Program);
    while (Is_tok_eof(get_ctok())) {
        program->children.push_back(MerParser_statement());
    }
    return program;
}

AST_node *Parser::MerParser_statement() {
    AST_node *state = MerAST_make_parent(ExpressionStatement);
    cur_tok = get_ctok();
    if (cur_tok.type == PRINT) {
        state->children.push_back(MerParser_print_statement());
    } else if (cur_tok.type == LET) {
        state->children.push_back(MerParser_let_statement());
    } else {
        state->children.push_back(MerParser_additive_expression());
    }
    return state;
}

AST_node *Parser::MerParser_print_statement() {
    AST_node *state = MerAST_make_parent(PrintStatement);
    cur_tok = get_ctok();
    state->children.push_back(MerParser_additive_expression());
    return state;
}

AST_node *Parser::MerParser_let_statement() {
    cur_tok = get_ntok();
    string name;
    AST_node *value;
    if (cur_tok.tok == VARIABLE) {
        name = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == ASSIGN) {
            cur_tok = get_ntok();
            value = MerParser_additive_expression();
        }
    }

    AST_node *state = MerAST_make_parent(LetStatement);
    state->var_name = name;
    state->var_value = value;
    return state;
}



AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier, cur_tok.tok, cur_tok.value, cur_tok.type);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type);
    }
}

AST_node *Parser::MerParser_additive_expression() {
    AST_node *left = MerParser_multiplicative_expression();
    AST_node *right;

    cur_tok = get_ctok();
    while (cur_tok.tok != PLUS || cur_tok.tok != MINUS) {
        string op = get_ntok().tok;
        get_ntok();
        right = MerParser_multiplicative_expression();
        left = MerParser_binary_expression(left, right, op);
    }   
    return left;
}

AST_node *Parser::MerParser_multiplicative_expression() {
    AST_node *left = MerParser_primary();
    AST_node *right;

    cur_tok = get_ctok();
    while (cur_tok.tok != TIME || cur_tok.tok != DIV || cur_tok.tok != MOD) {
        string op = get_ntok().tok;
        get_ntok();
        right = MerParser_primary();
        left = MerParser_binary_expression(left, right, op);
    }   
    return left;
}

AST_node *Parser::MerParser_binary_expression(AST_node *left, AST_node *right, string op) {
    AST_node *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->right = right;
    node->op = op;
    return node;
}

