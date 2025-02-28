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
    while (!Is_tok_eof(get_ctok())) {
        program->children.push_back(MerParser_statement());
    }
    return program;
}

AST_node *Parser::MerParser_statement() {
    AST_node *state = MerAST_make_parent(ExpressionStatement);
    state->children.push_back(MerParser_additive_expression());
    return state;
}

AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier_, cur_tok.tok, cur_tok.value, cur_tok.type);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type);
    }
    return NULL;
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
        cur_tok = get_ntok();
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

AST_node *Parser::MerParser_expression() {
    AST_node *node = MerAST_make_parent(Expression);
    cur_tok = get_ctok();
    if (cur_tok.tok == STRING) {
        node->string_iden = cur_tok.string_iden;
    } else if (cur_tok.tok == FUNCTION_CALL) {
        node = MerParser_function_call();
    } else {
        node->children.push_back(MerParser_additive_expression());
    }
    return node;
}

AST_node *Parser::MerParser_function_call() {
    AST_node *node = MerAST_make_parent(FunctionCallExpression);
    cur_tok = get_ctok();
    if (cur_tok.tok == FUNCTION_CALL) {
        node->func_name = cur_tok.string_iden;
        cur_tok = get_ntok();
        if (cur_tok.tok == LEFT_PAREN) {
            cur_tok = get_ntok();
            AST_node *calle;
            while (cur_tok.tok != RIGHT_PAREN) {
                AST_node *value = MerParser_expression();
                calle->children.push_back(value);
                cur_tok = get_ntok();
            }
        }
    }
}

AST_node *MerAST_make_ast(vector<token> tokens) {
    Parser parser(tokens);
    return parser.MerParser_program();
}


