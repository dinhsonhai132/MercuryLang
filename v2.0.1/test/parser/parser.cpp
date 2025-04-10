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

mParser_T *_MerParser_free(mParser_T *parser) {
    free(parser->lexer);
    free(parser->token);
    free(parser);
    return NULL;
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
    return node;
}

mAST_T *MerParser_parse_expression_statement(mParser_T *parser) {
    mAST_T *node = _MerAST_make_parent(ExpressionStatement);
    while (parser->token->tok != EOF_T)
        node->children.push_back(MerParser_parse(parser));
    return node;
}

mAST_T *MerParser_parse(mParser_T *parser) {
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == LET) return MerParser_parse_let_statement(parser);
    if (parser->token->tok == FUNCTION) return MerParser_parse_function_statement(parser);
    return MerParser_parse_additive_expression(parser);
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
    mToken_T *token = _MerLexer_get_next_tok(parser->lexer);
    if (token->tok == FUNCTION) token = _MerLexer_get_next_tok(parser->lexer);
    if (token->tok == VARIABLE) {
        node->func_name = token->name;
        if ((token = _MerLexer_get_next_tok(parser->lexer))->tok == LEFT_PAREN) {
            while ((token = _MerLexer_get_next_tok(parser->lexer))->tok != RIGHT_PAREN)
                if (token->tok == VARIABLE) node->args_idens.push_back(token->name);
            if ((token = _MerLexer_get_next_tok(parser->lexer))->tok == DO_T) {
                while ((token = _MerLexer_get_next_tok(parser->lexer))->tok != END_T)
                    node->children.push_back(MerParser_parse(parser));
                _MerLexer_get_next_tok(parser->lexer);
                return node;
            }
        }
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
    mToken_T *token = _MerLexer_get_next_tok(parser->lexer);
    if (token->tok == LEFT_PAREN) {
        for (int i = 0; (token = _MerLexer_get_next_tok(parser->lexer))->tok != RIGHT_PAREN;) {
            if (++i >= 10)
                mer_run_time_error(to_string(parser->lexer->line), "Runtime error: loop failed", parser->lexer->inp, "main.mer");
        }
        _MerLexer_get_next_tok(parser->lexer);
    } else {
        mer_run_time_error(to_string(parser->lexer->line), "Syntax error: Missing left parent", parser->lexer->inp, "main.mer");
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
// crystalcheese
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
    if (parser->token->tok == EOF_T) return NULL;
    string token = parser->token->tok;
    mer_run_time_error(to_string(parser->lexer->line), "Invalid token: Parser can not parse this token: " + token, parser->lexer->inp, "main.mer");
    return NULL;
}