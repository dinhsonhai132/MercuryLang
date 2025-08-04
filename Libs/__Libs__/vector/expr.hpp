#ifndef EXPR_HPP
#define EXPR_HPP

#include <string>
#include <stack>
#include <queue>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <sstream>

namespace Expr {

inline bool isNumberChar(char c) {
    return std::isdigit(c) || c == '.';
}

inline int precedence(const std::string &op) {
    if (op == "**") return 4;
    if (op == "*" || op == "/" || op == "//" || op == "%") return 3;
    if (op == "+" || op == "-") return 2;
    return 0;
}

inline bool isRightAssociative(const std::string &op) {
    return op == "**";
}

inline double applyOp(const std::string &op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "//") return std::floor(a / b);
    if (op == "%") return std::fmod(a, b);
    if (op == "**") return std::pow(a, b);
    throw std::runtime_error("Unknown operator: " + op);
}

inline std::vector<std::string> tokenize(const std::string &expr) {
    std::vector<std::string> tokens;
    for (size_t i = 0; i < expr.size();) {
        if (std::isspace(expr[i])) {
            ++i;
        } else if (isNumberChar(expr[i])) {
            std::string num;
            while (i < expr.size() && isNumberChar(expr[i])) {
                num.push_back(expr[i++]);
            }
            tokens.push_back(num);
        } else {
            if (i + 1 < expr.size()) {
                std::string two = expr.substr(i, 2);
                if (two == "**" || two == "//") {
                    tokens.push_back(two);
                    i += 2;
                    continue;
                }
            }
            tokens.push_back(std::string(1, expr[i++]));
        }
    }
    return tokens;
}

inline std::vector<std::string> toRPN(const std::vector<std::string> &tokens) {
    std::vector<std::string> output;
    std::stack<std::string> ops;

    for (auto &token : tokens) {
        if (std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1]))) {
            output.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else {
            while (!ops.empty() && ops.top() != "(" &&
                   (precedence(ops.top()) > precedence(token) ||
                    (precedence(ops.top()) == precedence(token) && !isRightAssociative(token)))) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

inline double evalRPN(const std::vector<std::string> &rpn) {
    std::stack<double> st;
    for (auto &token : rpn) {
        if (std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1]))) {
            st.push(std::stod(token));
        } else {
            if (st.size() < 2) throw std::runtime_error("Invalid expression");
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            st.push(applyOp(token, a, b));
        }
    }
    return st.top();
}

inline double eval(const std::string &expression) {
    auto tokens = tokenize(expression);
    auto rpn = toRPN(tokens);
    return evalRPN(rpn);
}

}

#endif
