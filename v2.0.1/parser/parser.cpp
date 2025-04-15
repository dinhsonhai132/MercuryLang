#include "parser.h"

using namespace std;

mParser_T *_MerParser_new(void) {
    mParser_T *parser = (mParser_T *)malloc(sizeof(mParser_T));
    parser->lexer = _MerLexer_new();
    parser->token = _MerToken_new();
    return parser;
}

mParser_T *_MerParser_init(mLexer_T *lexer) {
    mParser_T *parser = _MerParser_new();
    parser->lexer = lexer;
    return parser;
}

int _MerParser_free(mParser_T *parser) {
    _MerLexer_free(parser->lexer);
    _MerToken_free(parser->token);
    free(parser);
    return 0;
}

mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right) {
    mAST_T *node = _MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

mAST_T *MerParser_parse_program(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(Program);
    node->children.push_back(MerParser_parse_expression_statement(parser));
    free(parser);
    return node;
}

mAST_T *MerParser_parse_expression_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(ExpressionStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != EOF_T) node->children.push_back(MerParser_parse(parser));
    return node;
}

mAST_T *MerParser_parse(mParser_T *parser) {;
    if (parser->token->tok == LET) return MerParser_parse_let_statement(parser);
    if (parser->token->tok == FUNCTION) return MerParser_parse_function_statement(parser);
    if (parser->token->tok == FUNCTION_CALL) return MerParser_parse_function_call_expression(parser);
    if (parser->token->tok == RETURN) return MerParser_parse_return_statement(parser);
    return MerParser_parse_comparison_expression(parser);
}

mAST_T *MerParser_parse_return_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(ReturnStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->return_v = MerParser_parse_additive_expression(parser);
    return node;
}

mAST_T *MerParser_parse_comparison_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_additive_expression(parser);
    if (parser->token->tok == EQUAL || parser->token->tok == NOT_EQUAL ||
        parser->token->tok == LESS || parser->token->tok == LESS_EQUAL ||
        parser->token->tok == GREATER || parser->token->tok == GREATER_EQUAL) {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_additive_expression(parser);

        if (!right) {
            mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing right operand", parser->lexer->inp, "main.mer");
        }
        return MerParser_parse_compair(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right) {
   mAST_T *node = _MerAST_make_parent(ComparisonExpression);
   node->comp_left = left;
   node->comp_op = op;
   node->comp_right = right;
   return node;
}

mAST_T *MerParser_parse_let_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(LetStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        node->var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->var_value = MerParser_parse_additive_expression(parser);
            return node;
        } else {
            mer_run_time_error(to_string(parser->lexer->line), "Syntax error: no assignment", parser->lexer->inp, "main.mer");
        }
    } else {
        mer_run_time_error(to_string(parser->lexer->line), "Syntax error: no variable name", parser->lexer->inp, "main.mer");
    }

    mer_run_time_error(to_string(parser->lexer->line), "Structure error: parser.cpp can not compile let statement", parser->lexer->inp, "main.mer");
    return NULL;
}

mAST_T *MerParser_parse_function_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(FunctionStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        if (!parser->token->name) {
            mer_run_time_error(to_string(parser->lexer->line), "Function name is null", parser->lexer->inp, "main.mer");
            return NULL;
        }
        node->func_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == LEFT_PAREN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != RIGHT_PAREN) {
                if (parser->token->tok == ARG) {
                    node->args_idens.push_back(parser->token->name);
                }
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                if (parser->token->tok == COMMA) {
                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                }
            }
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            int error_index_ammount = 0;
            if (parser->token->tok == DO_T) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                
                while (parser->token->tok != END_T) {
                    error_index_ammount++;
                    if (error_index_ammount > 1024) {
                        mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing 'END", parser->lexer->inp, "main.mer");
                    }
                    node->body.push_back(MerParser_parse(parser));
                }
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                return node;
            } else {
                mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing 'DO' keyword in function body", parser->lexer->inp, "main.mer");
            }
        } else {
            mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing '(' after function name", parser->lexer->inp, "main.mer");
        }
    } else {
        mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing function name", parser->lexer->inp, "main.mer");
    }

    return NULL;
}

mAST_T *MerParser_parse_function_call_expression(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(FunctionCallExpression);

    if (!parser->token->name) {
        mer_run_time_error(to_string(parser->lexer->line), "Function call name is null", parser->lexer->inp, "main.mer");
        return NULL;
    }

    node->func_call = parser->token->name;

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == LEFT_PAREN) {
        parser->token = _MerLexer_get_next_tok(parser->lexer); 

        while (parser->token->tok != RIGHT_PAREN) {
            if (parser->token->tok == COMMA) {
                parser->token = _MerLexer_get_next_tok(parser->lexer); 
                continue;
            }

            mAST_T *arg = MerParser_parse_additive_expression(parser);
            if (arg) {
                node->args.push_back(arg);
            }

            parser->token = _MerLexer_get_next_tok(parser->lexer); 
        }

        parser->token = _MerLexer_get_next_tok(parser->lexer);
    } else {
        mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing left parenthesis in function call", parser->lexer->inp, "main.mer");
        return NULL;
    }

    return node;
}

mAST_T *MerParser_parse_multiplicative_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_primary_expression(parser);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok == TIME || parser->token->tok == DIV) {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_primary_expression(parser);
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        left = MerParser_parse_binary_expression(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_additive_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_multiplicative_expression(parser);
    while (parser->token->tok == PLUS || parser->token->tok == MINUS) {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_multiplicative_expression(parser);
        left = MerParser_parse_binary_expression(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_primary_expression(mParser_T *parser) {
    if (is_tok_identifier(parser->token->tok)) return _MerAST_make(Identifier_, parser->token->tok, 0, "AUTO_T", parser->token->string_iden);
    if (is_tok_literal(parser->token->tok)) return _MerAST_make(Literal, parser->token->tok, parser->token->value, "AUTO_T", "");
    if (parser->token->tok == EOF_T || 
        parser->token->tok == END_T || 
        parser->token->tok == DO_T  || 
        parser->token->tok == EOL_T ||
        parser->token->tok == LESS  ||
        parser->token->tok == GREATER) return NULL;
    string token = parser->token->tok;
    mer_run_time_error(to_string(parser->lexer->line), "Invalid token: Parser can not parse this token: " + token, parser->lexer->inp, "main.mer");
    return NULL;
}