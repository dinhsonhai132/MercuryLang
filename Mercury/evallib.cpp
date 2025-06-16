#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../include/evallib.h"

double number(const char*& expr) {
    double result = 0.0;
    while (isdigit(*expr)) result = result * 10 + (*expr++ - '0');
    if (*expr == '.') {
        ++expr;
        double frac = 0.1;
        while (isdigit(*expr)) {
            result += (*expr++ - '0') * frac;
            frac *= 0.1;
        }
    }
    return result;
}

double factor(const char*& expr) {
    while (isspace(*expr)) ++expr;
    return number(expr);
}

double term(const char*& expr) {
    double result = factor(expr);
    while (true) {
        while (isspace(*expr)) ++expr;
        if (*expr == '*') {
            ++expr;
            result *= factor(expr);
        } else if (*expr == '/') {
            ++expr;
            double denom = factor(expr);
            result /= denom;
        } else break;
    }
    return result;
}

double expression(const char*& expr) {
    double result = term(expr);
    while (true) {
        while (isspace(*expr)) ++expr;
        if (*expr == '+') {
            ++expr;
            result += term(expr);
        } else if (*expr == '-') {
            ++expr;
            result -= term(expr);
        } else break;
    }
    return result;
}

double eval(const string& input) {
    const char* expr = input.c_str();
    double result = expression(expr);
    while (isspace(*expr)) ++expr;
    return result;
}

