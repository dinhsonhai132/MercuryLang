#ifndef EVAL_H
#define EVAL_H
#include <iostream>
#include <string>
#include <vector>
#include "envi.h"
#include "parser.h"

using namespace std;

RunTimeVal MVM_valuelize(string type, float value);
RunTimeVal MVM_evaluate(AST_node *node);
RunTimeVal MVM_evaluate_binary_expression(AST_node *node);
RunTimeVal MVM_evaluate_program(AST_node *node);
RunTimeVal MVM_evaluate_expression_statement(AST_node *node);
RunTimeVal MVM_evaluate_total_expression(AST_node *node);
RunTimeVal MVM_evaluate_AST(AST_node *node);

#endif // EVAL_H