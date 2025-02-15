#include "eval.h"

RunTimeVal MVM_valuelize(string type, float value) {
    return RunTimeVal {
        .type = type, 
        .value = value
    };
}

RunTimeVal MVM_evaluate(AST_node *node) {
    if (node->type == Literal) {
        return MVM_valuelize(Number, node->value);
    } else if (node->type == Program) {
        return MVM_evaluate_program(node);
    } else if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node);
    } else if (node->type == LetStatement) {
        return MVM_evaluate_let_statement(node);
    } else if (node->type == PrintStatement) {
        return MVM_evaluate_print_statement(node);
    } else if (node->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node);
    }
    else {
        return MVM_valuelize(Null, 0.0);
    }
}

RunTimeVal MVM_evaluate_program(AST_node *node) {
    vector<AST_node*> statements = node->children;
    RunTimeVal result = MVM_valuelize(Null, 0.0);
    for (auto &statement : statements) {
        result = MVM_evaluate(statement);
    }
    return result;
}

RunTimeVal MVM_evaluate_expression_statement(AST_node *node) {}

RunTimeVal MVM_evaluate_let_statement(AST_node *node) {}

RunTimeVal MVM_evaluate_print_statement(AST_node *node) {}

RunTimeVal MVM_evaluate_binary_expression(AST_node *expr) {
    RunTimeVal left = MVM_evaluate(expr->left);
    RunTimeVal right = MVM_evaluate(expr->right);

    if (left.type != Number || right.type != Number) {
        return MVM_valuelize(Null, 0.0);
    }

    if (expr->op == "+") {
        return MVM_valuelize(Number, left.value + right.value);
    } else if (expr->op == "-") {
        return MVM_valuelize(Number, left.value - right.value);
    } else if (expr->op == "*") {
        return MVM_valuelize(Number, left.value * right.value);
    } else if (expr->op == "/") {
        return MVM_valuelize(Number, left.value / right.value);
    }
}