#include "include/eval.h"
#include "eval.h"

RunTimeVal valuelize(string type, float value) {
    return RunTimeVal {
        .type = type, 
        .value = value
    };
}

RunTimeVal MVM_evaluate(AST_node *node, Envi *envi) {
    if (node->type == Literal) {
        return valuelize(Number, node->value);
    } else if (node->type == Identifier) {
        return MVM_evaluate_identifier(node, envi);
    } else if (node->type == Program) {
        return MVM_evaluate_program(node, envi);
    } else if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node, envi);
    } else if (node->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node, envi);
    } else {
        return valuelize(Null, 0.0);
    }
}

RunTimeVal MVM_evaluate_identifier(AST_node *node, Envi *envi) {
    return *envi->MerEnvi_evaluate_identifier(node->string_iden);
}

RunTimeVal MVM_evaluate_program(AST_node *node, Envi *envi) {
    vector<AST_node*> statements = node->children;
    RunTimeVal result = valuelize(Null, 0.0);
    for (auto &statement : statements) {
        result = MVM_evaluate(statement, envi);
    }
    return result;
}

RunTimeVal MVM_evaluate_expression_statement(AST_node *node, Envi *envi) {
    if (node->children[0]->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node->children[0], envi);
    } else {
        return valuelize(Null, 0.0);
    }
}

RunTimeVal MVM_evaluate_binary_expression(AST_node *expr, Envi *envi) {
    RunTimeVal left = MVM_evaluate(expr->left, envi);
    RunTimeVal right = MVM_evaluate(expr->right, envi);

    if (left.type != Number || right.type != Number) {
        return valuelize(Null, 0.0);
    }

    if (expr->op == PLUS) {
        return valuelize(Number, left.value + right.value);
    } else if (expr->op == MINUS) {
        return valuelize(Number, left.value - right.value);
    } else if (expr->op == TIME) {
        return valuelize(Number, left.value * right.value);
    } else if (expr->op == DIV) {
        return valuelize(Number, left.value / right.value);
    }
}