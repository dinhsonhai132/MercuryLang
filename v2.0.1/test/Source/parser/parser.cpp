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
    } else {
        state->children.push_back(MerParser_primary());
    }
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

AST_node *Parser::MerParser_binary_expression(AST_node *left, AST_node *right, string op) {
    AST_node *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->right = right;
    node->op = op;
    return node;
}

