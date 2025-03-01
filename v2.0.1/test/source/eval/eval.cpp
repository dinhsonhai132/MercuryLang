#include "./source/include/eval.h"


RunTimeVal MVM_valuelize(string type, float value) {
    RunTimeVal val;
    val.type = type;
    val.value = value;
    return val;
}

RunTimeVal MVM_evaluate(AST_node *node) {
    if (node->type == Literal) {
        return MVM_valuelize(_Number, node->value);
    } else if (node->type == Program) {
        return MVM_evaluate_program(node);
    } else if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node);
    } else if (node->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node);
    }
    else {
        return MVM_valuelize(_Null, 0.0);
    }
}

RunTimeVal MVM_evaluate_program(AST_node *node) {
    vector<AST_node*> statements = node->children;
    RunTimeVal result = MVM_valuelize(_Null, 0.0);
    for (auto &statement : statements) {
        result = MVM_evaluate(statement);
    }
    return result;
}

RunTimeVal MVM_evaluate_total_expression(AST_node *node) {
    if (node->type == ExpressionStatement) {
        return MVM_evaluate_expression_statement(node);
    } 
    return MVM_valuelize(_Null, 0.0);
}

RunTimeVal MVM_evaluate_expression_statement(AST_node *node) {
    if (node->children[0]->type == BinaryExpression) {
        return MVM_evaluate_binary_expression(node->children[0]);
    } else {
        return MVM_evaluate_total_expression(node->children[0]);
    }
    return MVM_valuelize(_Null, 0.0);
}

RunTimeVal MVM_evaluate_binary_expression(AST_node *expr) {
    RunTimeVal left = MVM_evaluate(expr->left);
    RunTimeVal right = MVM_evaluate(expr->right);

    if (left.type != _Number || right.type != _Number) {
        return MVM_valuelize(_Null, 0.0);
    }

    if (expr->op == PLUS) {
        return MVM_valuelize(_Number, left.value + right.value);
    } else if (expr->op == MINUS) {
        return MVM_valuelize(_Number, left.value - right.value);
    } else if (expr->op == TIME) {
        return MVM_valuelize(_Number, left.value * right.value);
    } else if (expr->op == DIV) {
        return MVM_valuelize(_Number, left.value / right.value);
    }
    return MVM_valuelize(_Null, 0.0);
}

RunTimeVal MVM_evaluate_AST(AST_node *node) {
    return MVM_evaluate_program(node);
}