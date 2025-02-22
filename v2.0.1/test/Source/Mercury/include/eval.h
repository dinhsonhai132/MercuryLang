#ifndef EVAL_H
#define EVAL_H

#include <string>
#include <vector>

#include "parser.h"
#include "lexer.h"
#include "ast.h"

#include "envi.h"

using namespace std;

#define Number "number"
#define Null "null"
#define String "string"

struct RunTimeVal {
    string type;
    float value;

    MerObject *ovalue;
    string string_iden;
};

RunTimeVal MVM_valuelize(string type, float value);
RunTimeVal MVM_evaluate(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_binary_expression(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_let_statement(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_print_statement(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_program(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_expression_statement(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_identifier(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_total_expression(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_AST(AST_node *node, Envi *envi);

#endif