#include "parser.h"

using namespace std;

mParser_T *_MerParser_new(void)
{
    mParser_T *parser = (mParser_T *)malloc(sizeof(mParser_T));
    parser->lexer = _MerLexer_new();
    parser->token = _MerToken_new();
    parser->next = _MerToken_new();
    return parser;
}

mParser_T *_MerParser_init(mLexer_T *lexer)
{
    mParser_T *parser = _MerParser_new();
    parser->lexer = lexer;
    return parser;
}

int _MerParser_free(mParser_T *parser)
{
    _MerLexer_free(parser->lexer);
    _MerToken_free(parser->token);
    free(parser);
    return 0;
}

mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right)
{
    mAST_T *node = _MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

mAST_T *MerParser_parse_program(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(Program);
    node->children.push_back(MerParser_parse_expression_statement(parser));
    free(parser);
    return node;
}

mAST_T *MerParser_parse_expression_statement(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(ExpressionStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != EOF_T)
        node->children.push_back(MerParser_parse(parser));
    return node;
}

mAST_T *MerParser_parse(mParser_T *parser)
{
    ;
    if (parser->token->tok == LET)
        return MerParser_parse_let_statement(parser);
    if (parser->token->tok == FUNCTION)
        return MerParser_parse_function_statement(parser);
    if (parser->token->tok == FUNCTION_CALL)
        return MerParser_parse_function_call_expression(parser);
    if (parser->token->tok == RETURN)
        return MerParser_parse_return_statement(parser);
    if (parser->token->tok == IF)
        return MerParser_parse_if_statement(parser);
    if (parser->token->tok == PRINT)
        return MerParser_parse_print_statement(parser);
    if (parser->token->tok == WHILE)
        return MerParser_parse_while_statement(parser);
    if (parser->token->tok == VARIABLE)
        return MerParser_parse_assignment_statement(parser);
    if (parser->token->tok == STRING)
        return MerParser_parse_string_expression(parser);
    if (parser->token->tok == LIST)
        return MerParser_parse_list_statement(parser);

    return MerParser_parse_comparison_expression(parser);
}

mAST_T *parser_string_identifier_primary(mToken_T *token) {
    mAST_T *node = _MerAST_make_parent(StringIdentifier);

    node->str_v = token->string_iden;
    node->is_string = true;
    return node;
}

mAST_T *MerParser_parse_string_expression(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(StringIdentifier);

    node->str_v = parser->token->name;
    node->is_string = true;
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    return node;
}

mAST_T *MerParser_parse_print_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(PrintStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == STRING) {
        node->is_print = true;
        node->str_print_v = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    } else {
        node->is_print = false;
        node->print_v = MerParser_parse_additive_expression(parser);
        return node;
    }

    return node;
}

mAST_T *MerParser_parse_return_statement(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(ReturnStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->return_v = MerParser_parse_additive_expression(parser);
    return node;
}

mAST_T *MerParser_parse_comparison_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_additive_expression(parser);
    if (parser->token->tok == EQUAL || parser->token->tok == NOT_EQUAL ||
        parser->token->tok == LESS || parser->token->tok == LESS_EQUAL ||
        parser->token->tok == GREATER || parser->token->tok == GREATER_EQUAL)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_additive_expression(parser);

        if (!right)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected comparison expression", "stdin", parser->lexer->row);
        }
        return MerParser_parse_compair(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right)
{
    mAST_T *node = _MerAST_make_parent(ComparisonExpression);
    node->comp_left = left;
    node->comp_op = op;
    node->comp_right = right;
    return node;
}

mAST_T *MerParser_parse_if_statement(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(IfStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse_comparison_expression(parser);
    if (!comp)
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after if", "stdin", parser->lexer->row);
        return NULL;
    }
    node->comp = comp;

    if (parser->token->tok == THEN)
    {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", "stdin", parser->lexer->row);
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->then_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Unexpected statement", "stdin", parser->lexer->row);
            }
        }
    }
    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected then", "stdin", parser->lexer->row);
        return NULL;
    }


    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == ELSE) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", "stdin", parser->lexer->row);
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->else_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement", "stdin", parser->lexer->row);
            }

        }

        node->has_else = true;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    }

    return node;
}

mAST_T *MerParser_parse_let_statement(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(LetStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE)
    {
        node->var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->var_value = MerParser_parse_additive_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment", "stdin", parser->lexer->row);
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", "stdin", parser->lexer->row);
    }

    return NULL;
}

mAST_T *MerParser_parse_while_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(WhileStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse_comparison_expression(parser);
    if (!comp)
    {
        return NULL;
    }
    node->while_cond = comp;

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", "stdin", parser->lexer->row);
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->while_body.push_back(body);
            }
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'do'", "stdin", parser->lexer->row);
        return NULL;
    }
}

mAST_T *MerParser_parse_list_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(ListStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->list_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            if (parser->token->tok == LEFT_BRACKET) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                while (parser->token->tok != RIGHT_BRACKET)
                {
                    if (parser->token->tok == COMMA)
                    {
                        parser->token = _MerLexer_get_next_tok(parser->lexer);
                        continue;
                    }

                    if (parser->token->tok == EOF_T) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression, can not see the end in the list", "stdin", parser->lexer->row);
                    }

                    mAST_T *item = MerParser_parse_additive_expression(parser);
                    if (item)
                    {
                        node->list.push_back(item);
                    } else {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", "stdin", parser->lexer->row);
                    }
                }
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected '[' in list", "stdin", parser->lexer->row);
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in list", "stdin", parser->lexer->row);
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", "stdin", parser->lexer->row);
    }
}

mAST_T *MerParser_parse_assignment_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(AssignStatement);

    if (parser->token->tok == VARIABLE) {
        node->assign_iden = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);

            node->assign_value = MerParser_parse_additive_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in assignment", "stdin", parser->lexer->row);
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name in assignment", "stdin", parser->lexer->row);
    }

    return NULL;
}

mAST_T *MerParser_parse_function_statement(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(FunctionStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE)
    {
        if (!parser->token->name)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected function name", "stdin", parser->lexer->row);
            return NULL;
        }
        node->func_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == LEFT_PAREN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != RIGHT_PAREN)
            {
                if (parser->token->tok == ARG)
                {
                    node->args_idens.push_back(parser->token->name);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected argument in function definition", "stdin", parser->lexer->row);
                }

                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing end of the function definition", "stdin", parser->lexer->row);
                }    

                parser->token = _MerLexer_get_next_tok(parser->lexer);
                if (parser->token->tok == COMMA)
                {
                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                }
            }
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            int idex_amount = 0;
            if (parser->token->tok == DO_T)
            {
                parser->token = _MerLexer_get_next_tok(parser->lexer);

                while (parser->token->tok != END_T)
                {
                    if (parser->token->tok == EOF_T) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", "stdin", parser->lexer->row);
                    }
        
                    node->body.push_back(MerParser_parse(parser));
                }
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected DO", "stdin", parser->lexer->row);
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected LEFT_PAREN", "stdin", parser->lexer->row);
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected function name", "stdin", parser->lexer->row);
    }

    return NULL;
}

mAST_T *MerParser_parse_function_call_expression(mParser_T *parser)
{
    mAST_T *node = _MerAST_make_parent(FunctionCallExpression);

    if (!parser->token->name)
    {
        return NULL;
    }

    node->func_call = parser->token->name;
    
    if (node->func_call == "print") {
        node->is_built_in_func = true;
        node->built_in_func_name = node->func_call;
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == LEFT_PAREN)
    {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != RIGHT_PAREN)
        {
            if (parser->token->tok == COMMA)
            {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                continue;
            }

            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression, can not see the end in the function call arguments", "stdin", parser->lexer->row);
            }

            if (parser->token->tok != RIGHT_PAREN) {
                node->is_having_args = true;
            }

            if (parser->token->tok == STRING) {
                node->args.push_back(MerParser_parse_string_expression(parser));
            } else {
                mAST_T *arg = MerParser_parse_additive_expression(parser);
                if (arg)
                {
                    node->args.push_back(arg);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call", "stdin", parser->lexer->row);
                }
            }
        }

        parser->token = _MerLexer_get_next_tok(parser->lexer);
    }
    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected '('", "stdin", parser->lexer->row);
        return NULL;
    }

    return node;
}

mAST_T *MerParser_parse_multiplicative_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_primary_expression(parser);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok == TIME || parser->token->tok == DIV || parser->token->tok == MOD)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_primary_expression(parser);
        if (!right) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", "stdin", parser->lexer->row);
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        left = MerParser_parse_binary_expression(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_additive_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_multiplicative_expression(parser);
    while (parser->token->tok == PLUS || parser->token->tok == MINUS)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_multiplicative_expression(parser);
        if (!right) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", "stdin", parser->lexer->row);
        }
        left = MerParser_parse_binary_expression(left, op, right);
    }
    return left;
}

mAST_T *MerParser_parse_primary_expression(mParser_T *parser)
{
    if (is_tok_identifier(parser->token->tok)) return _MerAST_make(Identifier_, parser->token->tok, 0, "AUTO_T", parser->token->string_iden);
    if (is_tok_literal(parser->token->tok)) return _MerAST_make(Literal, parser->token->tok, parser->token->value, "AUTO_T", "");
    if (parser->token->tok == EOF_T 
        || parser->token->tok == DO_T 
        || parser->token->tok == EOL_T 
        || parser->token->tok == LESS 
        || parser->token->tok == GREATER 
        || parser->token->tok == STRING 
        || parser->token->tok == COMMA
        || parser->token->tok == COLON
        || parser->token->tok == SEMICOLON
        || parser->token->tok == LEFT_PAREN
        || parser->token->tok == RIGHT_PAREN
        || parser->token->tok == LEFT_BRACKET
        || parser->token->tok == RIGHT_BRACKET
        || parser->token->tok == LEFT_BRACE
        || parser->token->tok == RIGHT_BRACE
        || parser->token->tok == FUNCTION_CALL) return NULL;
    
    string sym = parser->token->string_iden;
    string msg = "Unexpected primary expression near '" + sym + "'";
    MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), "stdin", parser->lexer->row);
    return NULL;
}