#ifndef EVAL_H
#define EVAL_H

#include <string>
#include <vector>

#include "runtime.h"
#include "envi.h"

using namespace std;

RunTimeVal MVM_evaluate(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_binary_expression(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_program(AST_node *node, Envi *envi);
RunTimeVal MVM_evaluate_identifier(AST_node *node, Envi *envi);

#endif