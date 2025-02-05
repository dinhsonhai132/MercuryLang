#include "core.h"
#include "ast.h"

RunTimeVal evaluate_program(AST_Program prog) {
    RunTimeVal last_eval;

    for (const auto &state : prog.statements) {
        last_eval = evaluate(state);
    }
}

RunTimeVal evaluate_binary_expr(AST_BinaryExpression binexpr) {
    RunTimeVal lhs = evaluate(binexpr.left);
    RunTimeVal rhs = evaluate(binexpr.right);
    if (lhs.type == _Number && rhs.type == _Number) {
        return eval_num_expr(lhs, rhs, binexpr.op);
    }
    return NullVal {};
}

RunTimeVal eval_num_expr(RunTimeVal left, RunTimeVal right, string op_tok) {
    if (op_tok == "+") {
        NumberVal left = left;
        NumberVal right = right;
        return NumberVal {
            .type = _Number,
            .value = left.value + right.value
        };
    } else if (op_tok == "-") {
        NumberVal left = left;
        NumberVal right = right;
        return NumberVal {
            .type = _Number,
            .value = left.value - right.value
        };
    } else if (op_tok == "*") {
        NumberVal left = left;
        NumberVal right = right;
        return NumberVal {
            .type = _Number,
            .value = left.value * right.value
        };
    } else if (op_tok == "/") {
        NumberVal left = left;
        NumberVal right = right;
        return NumberVal {
            .type = _Number,
            .value = left.value / right.value
        };
    }
}

RunTimeVal evaluate(statement state) {
    if (state.type == Literal) {
        AST_Literal state = state;
        return NumberVal {
            .type = _Number,
            .value = state.value
        };
    } else if (state.type == BinaryExpression) {
        AST_BinaryExpression state = state;
        return evaluate_binary_expr(state);
    } else if (state.type == Program) {
        AST_Program state = state;
        return evaluate_program(state);
    } else {
        return NullVal {
            .type = _Null,
            .value = NULL
        };
    }
}