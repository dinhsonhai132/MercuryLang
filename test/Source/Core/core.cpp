#include "core.h"

RunTimeVal evaluate(statement stmt) {
    if (stmt.type == Identifier) {
        return RunTimeVal{.type = _Auto, .value = 0};
    } else if (stmt.type == Literal) {
        return RunTimeVal{.type = _Number, .value = stmt.value};
    } else if (stmt.type == Program) {
        return program_eval(stmt);
    } else if (stmt.type == BinaryExpression) {
        return evaluate_binary_expression(stmt);
    }
}

RunTimeVal program_eval(AST_Program stmt) {
    vector<statement> statements = stmt.statements;
    RunTimeVal last_eval = RunTimeVal{.type = _Auto, .value = 0};
    for (auto &statement : statements) {
        last_eval = evaluate(statement);
    }
    return last_eval;
}

RunTimeVal evaluate_binary_expression(AST_BinaryExpression expr) {
    RunTimeVal left = evaluate(expr.left);
    RunTimeVal right = evaluate(expr.right);
    string op = expr.op;
    if (left.type == _Number && right.type == _Number) {
        return evaluate_binary_numerical_expression(left, right, op);
    }
}

RunTimeVal evaluate_binary_numerical_expression(RunTimeVal left, RunTimeVal right, string op) {
    float result = 0;
    if (op == PLUS) {
        result = left.value + right.value;
    } else if (op == MINUS) {
        result = left.value - right.value;
    } else if (op == TIME) {
        result = left.value * right.value;
    } else if (op == DIV) {
        if (right.value == 0) {
            return RunTimeVal{.type = _Null, .value = NULL};
        }
        result = left.value / right.value;
    } else {
        return RunTimeVal{.type = _Null, .value = NULL};
    }

    return RunTimeVal{.type = _Number, .value = result};
}
