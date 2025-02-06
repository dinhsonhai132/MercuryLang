#include "core.h"
#include "ast.h"
#include "envi.cpp"

RunTimeVal evaluate_program(AST_Program prog, Environment envi) {
    RunTimeVal last_eval;

    for (const auto &state : prog.statements) {
        last_eval = evaluate(state, envi);
    }
}

RunTimeVal evaluate_binary_expr(AST_BinaryExpression binexpr, Environment envi) {
    RunTimeVal lhs = evaluate(binexpr.left, envi);
    RunTimeVal rhs = evaluate(binexpr.right, envi);
    if (lhs.type == _Number && rhs.type == _Number) 
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

RunTimeVal evaluate_identifier(AST_Identifier iden, Environment envi) {
    return envi.lookupVar(iden.name);
}

RunTimeVal evaluate(statement state, Environment envi) {
    if (state.type == Literal) {
        AST_Literal state = state;
        return NumberVal {
            .type = _Number,
            .value = state.value
        };
    } else if (state.type == BinaryExpression) {
        AST_BinaryExpression state = state;
        return evaluate_binary_expr(state, envi);
    } else if (state.type == Program) {
        AST_Program state = state;
        return evaluate_program(state, envi);
    } else if (state.type == Identifier)  {
        AST_Identifier state = state;
        return evaluate_identifier(state, envi);
    } else if (state.type == NullExpression) {
        return NullVal {
            .type = _Null,
            .value = NULL
        }
    } else if (state.type == VarDeclaraion) {
        return eval_var_declaraion(state, envi);
    } else {
        return NullVal {
            .type = _Null,
            .value = NULL
        };
    }
}

RunTimeVal eval_var_declaraion(AST_VarDeclaraion var, Environment envi) {
    throw new Error("Unimplemented");
}