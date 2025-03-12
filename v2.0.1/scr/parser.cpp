#include <iostream>
#include <vector>
#include <string>
#include "parser.h"

token Parser::get_ctok() {
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::get_ntok() {
    idx++;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::jump_tok(int n) {
    idx += n;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }

    return cur_tok = tokens[idx];
}

bool Parser::look_ahead(string tok, int n) {
    return tokens[idx + n].tok == tok;
}

AST_node *Parser::MerParser_program() {
    program = MerAST_make_parent(Program);
    cur_tok = get_ctok();
    program->children.push_back(MerParser_statement());
    return program;
}

AST_node *Parser::MerParser_statement() {
    AST_node *node = MerAST_make_parent(ExpressionStatement);
    cur_tok = get_ctok();
    while (!Is_tok_eof(cur_tok)) {
        if (cur_tok.tok == LET) {
            node->children.push_back(MerParser_let_statement());
        } else if (cur_tok.tok == RETURN) {
            node->children.push_back(MerParser_return_statement());
        } else if (cur_tok.tok == FUNCTION_CALL) {
            node->children.push_back(MerParser_function_call_statement());
        } else if (cur_tok.tok == FUNCTION) {
            node->children.push_back(MerParser_function_expression_statement());
        } else {
            node->children.push_back(MerParser_additive_expression());
        }
        cur_tok = get_ctok();
    }
    return node;
}

AST_node *Parser::MerParser_function_body_expression() {
    AST_node *node = MerAST_make_parent(ExpressionStatement);
    cur_tok = get_ctok();
    while (cur_tok.tok != END) {
        if (cur_tok.tok == LET) {
            node->children.push_back(MerParser_let_statement());
        } else if (cur_tok.tok == RETURN) {
            node->children.push_back(MerParser_return_statement());
        } else if (cur_tok.tok == FUNCTION_CALL) {
            node->children.push_back(MerParser_function_call_statement());
        } else if (cur_tok.tok == FUNCTION) {
            node->children.push_back(MerParser_function_expression_statement());
        } else {
            node->children.push_back(MerParser_additive_expression());
        }
        cur_tok = get_ctok();
    }
    return node;
}

AST_node *Parser::MerParser_return_statement() {
    return nullptr;
}

AST_node *Parser::MerParser_function_expression_statement() {
    AST_node *func = MerAST_make_parent(FunctionStatement);

    cur_tok = get_ntok();
    if (cur_tok.tok == VARIABLE) {
        func->func_name = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == LEFT_PAREN) {
            cur_tok = get_ntok();
            while (cur_tok.tok != RIGHT_PAREN) {
                if (cur_tok.tok == COMMA) {
                    cur_tok = get_ntok();
                } else {
                    if (cur_tok.tok == ARG) {
                        func->args_idens.push_back(cur_tok.name);
                    }
                    cur_tok = get_ntok();
                }
            }
            
            cur_tok = get_ntok();
            func->children.push_back(MerParser_function_body_expression());
        } else {
            cout << "Error: function ast make failed, missing '('!\n";
            return nullptr;
        }
    } else {
        cout << "Error: function ast make failed, missing name!\n";
        return nullptr;
    }

    return func;
}

AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier_, cur_tok.tok, cur_tok.value, cur_tok.type, cur_tok.string_iden);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type, cur_tok.string_iden);
    }
    cout << "Error: primary ast make failed!\n";
    return nullptr;
}

AST_node *Parser::MerParser_let_statement() {
    AST_node *node = MerAST_make_parent(LetStatement);
    cur_tok = get_ntok();
    if (Is_tok_identifier(cur_tok.tok)) {
        node->var_name = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == ASSIGN) {
            cur_tok = get_ntok();
            if (cur_tok.tok == LEFT_BRACE) {
                node->is_list = true;
                while (cur_tok.tok != RIGHT_BRACE) {
                    if (cur_tok.tok == COMMA) {
                        cur_tok = get_ntok();
                    } else {
                        node->elements.push_back(MerParser_additive_expression());
                        cur_tok = get_ntok();
                    }
                }
            } else {
                node->var_value = MerParser_additive_expression();
            }
        } else {
            node->is_None = true;
            node->var_value = nullptr;
        }
    }
    node->data_type = AUTO_T;
    return node;
}

AST_node *Parser::MerParser_function_call_statement() {
    AST_node *node = MerAST_make_parent(FunctionCallExpression);
    node->func_call = cur_tok.name;
    cur_tok = get_ntok();
    if (cur_tok.tok == LEFT_PAREN) {
        cur_tok = get_ntok();
        while (cur_tok.tok != RIGHT_PAREN) {
            if (cur_tok.tok == COMMA) {
                cur_tok = get_ntok();
            } else {
                node->args.push_back(MerParser_additive_expression());
            }
        }
    }
    cur_tok = get_ntok();
    return node;
}

AST_node *Parser::MerParser_additive_expression() {
    AST_node *left = MerParser_multiplicative_expression();

    while (cur_tok.tok == PLUS || cur_tok.tok == MINUS) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_multiplicative_expression();
        left = MerParser_binary_expression(left, right, op);
    }
    return left;
}

AST_node *Parser::MerParser_multiplicative_expression() {
    AST_node *left = MerParser_primary();

    cur_tok = get_ntok();
    while (cur_tok.tok == TIME || cur_tok.tok == DIV || cur_tok.tok == MOD) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_primary();
        left = MerParser_binary_expression(left, right, op);
        cur_tok = get_ntok();
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

AST_node *MerAST_make_AST(vector<token> tokens) {
    Parser parser(tokens);
    return parser.MerParser_program();
}