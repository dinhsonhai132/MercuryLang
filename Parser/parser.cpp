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
    mAST_T *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

mAST_T *MerParser_parse_program(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(Program);
    node->file = parser->lexer->file;
    node->children.push_back(MerParser_parse_expression_statement(parser));
    return node;
}

mAST_T *MerParser_parse_expression_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(ExpressionStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != EOF_T)
        node->children.push_back(MerParser_parse(parser));

    return node;
}

mAST_T *MerParser_parse(mParser_T *parser)
{
    if (parser->token->tok == LET)
        return MerParser_parse_let_statement(parser);
    if (parser->token->tok == FUNCTION)
        return MerParser_parse_function_statement(parser);
    if (parser->token->tok == RETURN)
        return MerParser_parse_return_statement(parser);
    if (parser->token->tok == IF)
        return MerParser_parse_if_statement(parser);
    if (parser->token->tok == WHILE)
        return MerParser_parse_while_statement(parser);
    if (parser->token->tok == VARIABLE) {
        parser->next = _MerLexer_look_ahead(parser->lexer);
        if (parser->next->tok == ASSIGN 
            || parser->next->tok == PLUS_EQUAL 
            || parser->next->tok == MINUS_EQUAL 
            || parser->next->tok == TIMES_EQUAL 
            || parser->next->tok == DIV_EQUAL 
            || parser->next->tok == MOD_EQUAL) {
            return MerParser_parse_assignment_statement(parser);
        } else {
            return MerParser_parse_logical_expression(parser);
        }
    }

    if (parser->token->tok == LOOP) {
        return MerParser_parse_loop_statement(parser);
    }
    if (parser->token->tok == LIST)
        return MerParser_parse_list_statement(parser);
    if (parser->token->tok == STR)
        return MerParser_parse_variable_statement(parser);
    if (parser->token->tok == FOR)
        return MerParser_parse_for_statement(parser);
    if (parser->token->tok == CONTINUE) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *node = MerAST_make_parent(ContinueStatement);
        node->true_line = TRUE_LINE(parser);
        return node;
    } if (parser->token->tok == BREAK) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *node = MerAST_make_parent(BreakStatement);
        node->true_line = TRUE_LINE(parser);
        return node;
    } if (parser->token->tok == IMPORT) {
        return MerParser_parse_import_statement(parser);
    } if (parser->token->tok == DEFINE_STA) {
        return MerParser_parse_define_statement(parser);
    } if (parser->token->tok == INCLUDE) {
        return MerParser_parse_include_statement(parser);
    }

    return MerParser_parse_logical_expression(parser);
}

mAST_T *MerParser_parse_include_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(IncludeStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    
    if (parser->token->tok == STRING) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in import, import \"<file>\" ", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

mAST_T *MerParser_parse_define_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(DefineStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Missing name in define, 'define <name> {<code>}' ", parser->lexer->file, TRUE_LINE(parser));
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->define_val = MerParser_parse(parser);
    if (!node) {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in define", parser->lexer->file, TRUE_LINE(parser));
    }

    if (!is_ast_expression(node->define_val->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in define", parser->lexer->file, TRUE_LINE(parser));
    }

    
    return node;
}

mAST_T *MerParser_parse_import_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ImportStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    
    if (parser->token->tok == STRING) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in import, import \"<file>\" ", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

mAST_T *MerParser_parse_loop_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(LoopStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    while (parser->token->tok != END_T) {
        node->do_body.push_back(MerParser_parse(parser));
    }
    
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    return node;
}

mAST_T *MerParser_parse_array_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ArrayExpression);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != RIGHT_BRACKET) {

        if (parser->token->tok == EOF_T) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF> in the end of list", parser->lexer->file, TRUE_LINE(parser));
        }

        mAST_T *item = MerParser_parse(parser);

        if (!is_ast_expression(item->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!item) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        node->list.push_back(item);

        if (parser->token->tok == COMMA)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            continue;
        }
    }

    node->is_list = true;
    node->is_alone_val = true;

    return node;
}

mAST_T *MerParser_parse_for_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ForInStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->in_iden = parser->token->string_iden;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok == IN_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->in_value = MerParser_parse(parser);

        if (node->in_value->type == Literal || node->in_value->type == BinaryExpression || node->in_value->type == ComparisonExpression) {
            MerDebug_print_error(SYNTAX_ERROR, "'int' object is not iterable", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!node->in_value) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!is_ast_expression(node->in_value->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "'null' object is not iterable", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'IN' keyword in for in statement", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T) {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END' keyword in the for loop", parser->lexer->file, TRUE_LINE(parser));
                return NULL;
            }

            mAST_T *body = MerParser_parse(parser);
            if (body) {
                node->in_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Unexpected statement", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'DO' keyword in for in statement", parser->lexer->file, TRUE_LINE(parser));
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *MerParser_parse_store_index_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StoreIndexStatement);

    node->extract_assign = MerParser_parse(parser);

    if (!is_ast_expression(node->extract_assign->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }
    
    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *parser_string_identifier_primary(mToken_T *token) {
    mAST_T *node = MerAST_make_parent(StringIdentifier);

    node->str_v = token->string_iden;
    node->is_string = true;
    return node;
}

mAST_T *MerParser_parse_string_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringIdentifier);

    node->str_v = parser->token->name;
    node->is_string = true;
    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *MerParser_parse_return_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(ReturnStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    node->return_v = MerParser_parse(parser);
    if (!is_ast_expression(node->return_v->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *MerParser_parse_string_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringVariableStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        node->str_var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->str_var_value = MerParser_parse_string_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

mAST_T *MerParser_parse_if_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(IfStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse(parser);
    if (!is_ast_expression(comp->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }
    
    if (!comp)
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'IF'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
    node->comp = comp;

    if (parser->token->tok == THEN)
    {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END'", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->then_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Unexpected statement", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    }    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Missing 'THEN'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    elif:
    if (parser->token->tok == ELIF) {
        mAST_T *elif_node = MerAST_make_parent(IfStatement);
        node->has_elif = true;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        elif_node->comp = MerParser_parse(parser);

        if (!is_ast_expression(elif_node->comp->type) || !elif_node->comp) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == THEN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != END_T)
            {
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'end'", parser->lexer->file, TRUE_LINE(parser));
                }

                mAST_T *body = MerParser_parse(parser);
                if (body)
                {
                    elif_node->then_body.push_back(body);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement", parser->lexer->file, TRUE_LINE(parser));
                }
            }

            node->elif_body.push_back(elif_node);
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            goto elif;
        }    
        else
        {
            MerDebug_print_error(SYNTAX_ERROR, "Missing 'then'", parser->lexer->file, TRUE_LINE(parser));
        }
    }
    
    
    if (parser->token->tok == ELSE) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->else_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement", parser->lexer->file, TRUE_LINE(parser));
            }

        }

        node->has_else = true;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    }

    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *MerParser_parse_let_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(LetStatement);
    node->true_line = TRUE_LINE(parser);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    string var_name;
    if (parser->token->tok == VARIABLE)
    {
        node->var_name = parser->token->name;
        var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }

            node->var_value = MerParser_parse(parser);

            if (!node->var_value) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }   

            if (!is_ast_expression(node->var_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        } else if (parser->token->tok == LEFT_PAREN) {
            node = MerAST_make_parent(FunctionStatement);
            node->true_line = TRUE_LINE(parser);
            node->func_name = var_name;

            parser->token = _MerLexer_get_next_tok(parser->lexer);

            while (parser->token->tok != RIGHT_PAREN) {
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
                }
                if (parser->token->tok == COMMA) {
                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                    continue;
                }

                if (parser->token->tok == VARIABLE) {
                    node->args_idens.push_back(parser->token->string_iden);
                    node->args_size++;
                    node->is_having_args = true;
                    para_temp.push_back(parser->token->string_iden);

                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected variable name in function arguments", parser->lexer->file, TRUE_LINE(parser));
                }
            }

            parser->token = _MerLexer_get_next_tok(parser->lexer);
            parser->next = _MerLexer_look_ahead(parser->lexer);

            if (parser->token->tok == ASSIGN) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected <EOF> after lambda function", parser->lexer->file, TRUE_LINE(parser));
                }

                mAST_T *return_v = MerAST_make_parent(ReturnStatement);
                return_v->true_line = TRUE_LINE(parser);
                return_v->return_v = MerParser_parse(parser);
                if (!return_v->return_v || !is_ast_expression(return_v->return_v->type)) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression in lambda function", parser->lexer->file, TRUE_LINE(parser));
                }

                node->body.push_back(return_v);
                para_temp.clear();
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Missing '=' in lambda function", parser->lexer->file, TRUE_LINE(parser));
            }
        }
        
        else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment, missing '='", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name, the token after 'LET' is not a variable", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_while_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(WhileStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse(parser);

    if (!is_ast_expression(comp->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'WHILE'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    if (!comp) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'WHILE'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
    node->while_cond = comp;

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END' keyword in the while loop", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->while_body.push_back(body);
            } else if (body->type == BreakStatement) {
                node->while_body.push_back(body);
                node->is_break = true;
            } else if (body->type == ContinueStatement) {
                node->while_body.push_back(body);
                node->is_continue = true;
            }
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'DO', while loop body must start with keyword 'DO'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
}

mAST_T *MerParser_parse_variable_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringVariableStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        node->str_var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->str_var_value = MerParser_parse_string_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_list_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ListStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->list_name = parser->token->string_iden;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            if (parser->token->tok == LEFT_BRACKET) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                node->is_list = true;
                node->list_type = "list";
                while (parser->token->tok != RIGHT_BRACKET)
                {
                    if (parser->token->tok == COMMA)
                    {
                        parser->token = _MerLexer_get_next_tok(parser->lexer);
                        continue;
                    }

                    if (parser->token->tok == EOF_T) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF>", parser->lexer->file, TRUE_LINE(parser));
                    }

                    mAST_T *item = MerParser_parse(parser);

                    if (!is_ast_expression(item->type)) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
                    }

                    if (item)
                    {
                        node->list.push_back(item);
                        node->list_size++;
                    } else {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
                    }
                }
                
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected '[' in list", parser->lexer->file, TRUE_LINE(parser));
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in list", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name, in list", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_assignment_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(AssignStatement);
    node->true_line = TRUE_LINE(parser);

    if (parser->token->tok == VARIABLE) {
        node->assign_iden = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);

            node->assign_value = MerParser_parse(parser);

            if (!is_ast_expression(node->assign_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in assignment", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        } 

        else if (parser->token->tok == PLUS_EQUAL || parser->token->tok == MINUS_EQUAL || parser->token->tok == TIMES_EQUAL || parser->token->tok == DIV_EQUAL || parser->token->tok == MOD_EQUAL) {

            if (parser->token->tok == PLUS_EQUAL) {
                node->is_plus_assign = true;
            } else if (parser->token->tok == MINUS_EQUAL) {
                node->is_minus_assign = true;
            } else if (parser->token->tok == TIMES_EQUAL) {
                node->is_mul_assign = true;
            } else if (parser->token->tok == DIV_EQUAL) {
                node->is_div_assign = true;
            } else if (parser->token->tok == MOD_EQUAL) {
                node->is_mod_assign = true;
            }

            node->is_assign_operator = true;

            parser->token = _MerLexer_get_next_tok(parser->lexer);

            node->assign_value = MerParser_parse(parser);

            if (!is_ast_expression(node->assign_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in assignment", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        }
        
        else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name in assignment", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_function_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(FunctionStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE)
    {
        if (!parser->token->name)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected function name", parser->lexer->file, TRUE_LINE(parser));
            return NULL;
        }
        node->func_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == LEFT_PAREN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != RIGHT_PAREN)
            {
                if (parser->token->tok == VARIABLE)
                {
                    node->args_idens.push_back(parser->token->name);
                    para_temp.push_back(parser->token->name);
                    node->is_having_args = true;
                    node->args_size++;
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected argument in function definition", parser->lexer->file, TRUE_LINE(parser));
                }

                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'end' of the function definition", parser->lexer->file, TRUE_LINE(parser));
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
                        MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END'", parser->lexer->file, TRUE_LINE(parser));
                    }
        
                    node->body.push_back(MerParser_parse(parser));
                }
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                para_temp.clear();
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "missing 'DO' in function definition", parser->lexer->file, TRUE_LINE(parser));
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '(' in function definition", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected function name", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_function_call_expression(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(FunctionCallExpression);
    node->true_line = TRUE_LINE(parser);

    if (!parser->token->name)
    {
        return NULL;
    }

    node->func_call = parser->token->name;
    
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
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF>", parser->lexer->file, TRUE_LINE(parser));
            }

            if (parser->token->tok != RIGHT_PAREN) {
                node->is_having_args = true;
            }

            mAST_T *arg = MerParser_parse(parser);

            if (!is_ast_expression(arg->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call, not an expression", parser->lexer->file, TRUE_LINE(parser));
            }

            if (arg)
            {
                node->args.push_back(arg);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    }
    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected '('", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    return node;
}

mAST_T *MerParser_parse_comparison_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_additive_expression(parser);

    while (parser->token->tok == EQUAL || parser->token->tok == NOT_EQUAL ||
           parser->token->tok == LESS || parser->token->tok == LESS_EQUAL ||
           parser->token->tok == GREATER || parser->token->tok == GREATER_EQUAL || parser->token->tok == IS)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_additive_expression(parser);

        if (!right)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected comparison expression", parser->lexer->file, TRUE_LINE(parser));
        }
        left = MerParser_parse_compair(left, op, right);
    }

    left->true_line = TRUE_LINE(parser);
    return left;
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
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        left = MerParser_parse_binary_expression(left, op, right);
    }
    left->true_line = TRUE_LINE(parser);
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
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }
        left = MerParser_parse_binary_expression(left, op, right);
        left->true_line = TRUE_LINE(parser);
    }

    left->true_line = TRUE_LINE(parser);
    return left;
}

mAST_T *MerParser_parse_extract_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ExtractExpression);
    node->extract_name = parser->token->string_iden;
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == LEFT_BRACKET) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->is_extract = true;
        node->extract_value = MerParser_parse(parser);
        if (!node->extract_value || !is_ast_expression(node->extract_value->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected extract expressuin", parser->lexer->file, TRUE_LINE(parser));
        }

        if (node->extract_value->type == ArrayExpression) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected extract expression, can not be list", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == RIGHT_BRACKET) {
            parser->next = _MerLexer_look_ahead(parser->lexer);
            if (parser->next->tok == ASSIGN) {
                mAST_T *assign = MerAST_make_parent(StoreIndexStatement);
                assign->extract_name = node->extract_name;
                assign->array_store = node->extract_value;

                parser->token = _MerLexer_get_next_tok(parser->lexer);
                parser->token = _MerLexer_get_next_tok(parser->lexer);

                assign->array_store_value = MerParser_parse(parser);

                if (!assign->array_store_value || !is_ast_expression(assign->array_store_value->type)) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
                }

                return assign;
            }
            return node;
        } else {
            string msg = "Expected ']' in expression, name: " + node->extract_name;
            MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        string msg = "Expected '[' in expression, name: " + node->extract_name;
        MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right)
{
    mAST_T *node = MerAST_make_parent(ComparisonExpression);
    node->comp_left = left;
    node->comp_op = op;
    node->comp_right = right;
    return node;
}

mAST_T *MerParser_parse_or_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_and_expression(parser);
    while (parser->token->tok == OR) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_and_expression(parser);
        left = MerParser_parse_operator_expression(left, OR, right, OrExpression);
    }

    return left;
}

mAST_T *MerParser_parse_and_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_not_expression(parser);
    while (parser->token->tok == AND) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_not_expression(parser);
        left = MerParser_parse_operator_expression(left, AND, right, AndExpression);
    }
    
    return left;
}

mAST_T *MerParser_parse_not_expression(mParser_T *parser) {
    if (parser->token->tok == NOT) {
        mAST_T *node = MerAST_make_parent(NotExpression);
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->not_expr = MerParser_parse_not_expression(parser);
        if (!node->not_expr) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'not'", parser->lexer->file, TRUE_LINE(parser));
        }
        return node;
    }
    
    return MerParser_parse_comparison_expression(parser);
}

mAST_T *MerParser_parse_dictionary_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(DictionaryExpression);

    while (parser->token->tok != RIGHT_BRACE) {
        mAST_T *dict_key = MerAST_make_parent(DictionaryExpression);
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        mAST_T *key = MerParser_parse(parser);

        if (!key || !is_ast_expression(key->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

        dict_key->dict_key = key;

        if (parser->token->tok == COLON) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);

            mAST_T *value = MerParser_parse(parser);

            if (!value || !is_ast_expression(value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in dictionary", parser->lexer->file, TRUE_LINE(parser));
            }

            dict_key->dict_value = value;
            node->dict_list.push_back(dict_key);
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Missing ':' in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == COMMA) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
        } else if (parser->token->tok != RIGHT_BRACE) {
            MerDebug_print_error(SYNTAX_ERROR, "Missing ',' in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

    }

    return node;
}

mAST_T *MerParser_parse_parent_expression(mParser_T *parser) {
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    mAST_T *left = MerParser_parse_logical_expression(parser);
    if (!left) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok != RIGHT_PAREN) {
        MerDebug_print_error(SYNTAX_ERROR, "Missing ')' at the end of expression", parser->lexer->file, TRUE_LINE(parser));
    }

    return left;
}

mAST_T *MerParser_parse_logical_expression(mParser_T *parser) {
    mAST_T *value = MerParser_parse_or_expression(parser);
    if (!value) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    value->true_line = TRUE_LINE(parser);
    return value;
}

mAST_T *MerParser_parse_primary_expression(mParser_T *parser)
{
    if (parser->token->tok == TRUE_T) return MerAST_make(TrueExpression, TRUE_T, 1, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == FALSE_T) return MerAST_make(FalseExpression, FALSE_T, 0, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == DEFINE_VAL) return MerAST_make(DefineExpression, parser->token->tok, 0, "AUTO_T", parser->token->string_iden, TRUE_LINE(parser));
    if (parser->token->tok == STRING) return MerParser_parse_string_expression(parser);
    if (parser->token->tok == LEFT_BRACKET) return MerParser_parse_array_expression(parser);
    if (parser->token->tok == LEFT_BRACE) return MerParser_parse_dictionary_expression(parser);
    if (parser->token->tok == LEFT_PAREN) return MerParser_parse_parent_expression(parser);
    if (parser->token->tok == VARIABLE) {
        parser->next = _MerLexer_look_ahead(parser->lexer);
        if (parser->next->tok == LEFT_BRACKET) {
            return MerParser_parse_extract_expression(parser);
        } else if (parser->next->tok == LEFT_PAREN) {
            return MerParser_parse_function_call_expression(parser);
        }
    }
    if (is_tok_identifier(parser->token->tok)) return MerAST_make(Identifier_, parser->token->tok, 0, "AUTO_T", parser->token->string_iden, TRUE_LINE(parser));
    if (is_tok_literal(parser->token->tok)) return MerAST_make(Literal, parser->token->tok, parser->token->value, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == EOF_T 
        || parser->token->tok == DO_T
        || parser->token->tok == COLON) return NULL;
    
    string sym = parser->token->string_iden;
    string msg = "Unexpected primary expression near '" + sym + "'";
    MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
    return NULL;
}

mAST_T *MerParser_parse_operator_expression(mAST_T *left, string op, mAST_T *right, string type) {
    mAST_T *node = MerAST_make_parent(type);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}