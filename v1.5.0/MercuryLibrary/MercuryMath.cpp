#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cctype>
using namespace std;

enum Math_type {
    PLUS, MINUS, TIME, DIV, MOD, POW, SQRT, CBRT, EXP, LOG, LOG10, LOG2, SIN, COS, TAN, 
    ASIN, ACOS, ATAN, SINH, COSH, TANH, ASINH, ACOSH, ATANH, CEIL, FLOOR, ROUND, TRUNC, 
    FMOD, REMAINDER, MIN, MAX, ABS, POW2, POW3, ROOT2, ROOT3, EXP2, EXP3, RAD, DEG, VARIABLE, NONE, 
    EPSILON, INF, SOLVE_EQUATION, LIMIT, DIFFERENTIATE, INTEGRATE, SUM, PRODUCT, FACTORIAL, NUM, LP, RP
};

struct math_variable {
    string name;
    double value;
};

struct data_type {
    Math_type type;
    double value;
    string name;
};

struct Math_const {
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double E = 2.71828182845904523536;
    static constexpr double RAD = 180.0 / PI;
    static constexpr double DEG = PI / 180.0;
    static constexpr double EPSILON = 1e-10;
    static constexpr double INF = 1e9;
    static constexpr double MY_NAN = std::numeric_limits<double>::quiet_NaN();
};

class MercuryMath {
public:
    static double abs(double x) {
        return x < 0 ? -x : x;
    }

    static double pow(double x, double y) {
        return std::pow(x, y);
    }

    static double sqrt(double x) {
        return std::sqrt(x);
    }

    static double cbrt(double x) {
        return std::cbrt(x);
    }

    static double exp(double x) {
        return std::exp(x);
    }

    static double log(double x) {
        return std::log(x);
    }

    static double log10(double x) {
        return std::log10(x);
    }

    static double log2(double x) {
        return std::log2(x);
    }

    static double sin(double x) {
        return std::sin(x);
    }

    static double cos(double x) {
        return std::cos(x);
    }

    static double tan(double x) {
        return std::tan(x);
    }

    static double asin(double x) {
        return std::asin(x);
    }

    static double acos(double x) {
        return std::acos(x);
    }

    static double atan(double x) {
        return std::atan(x);
    }

    static double sinh(double x) {
        return std::sinh(x);
    }

    static double cosh(double x) {
        return std::cosh(x);
    }

    static double tanh(double x) {
        return std::tanh(x);
    }

    static double asinh(double x) {
        return std::asinh(x);
    }

    static double acosh(double x) {
        return std::acosh(x);
    }

    static double atanh(double x) {
        return std::atanh(x);
    }

    static double ceil(double x) {
        return std::ceil(x);
    }

    static double floor(double x) {
        return std::floor(x);
    }

    static double round(double x) {
        return std::round(x);
    }

    static double trunc(double x) {
        return std::trunc(x);
    }

    static double fmod(double x, double y) {
        return std::fmod(x, y);
    }

    static double remainder(double x, double y) {
        return std::remainder(x, y);
    }

    static double min(double x, double y) {
        return std::min(x, y);
    }

    static double solve_equation_power_2(double a, double b, double c) {
        double delta = b * b - 4 * a * c;
        if (delta < 0) {
            return Math_const::MY_NAN;
        } else if (delta == 0) {
            return -b / (2 * a);
        } else {
            double x1 = (-b + sqrt(delta)) / (2 * a);
            double x2 = (-b - sqrt(delta)) / (2 * a);
            return x1, x2;
        }
    }
};

class MercuryMath_SOLVE_EQUATION_lexer {
private:
    string equation;
    int pos;
    char cur;
public:
    MercuryMath_SOLVE_EQUATION_lexer(string equation) : equation(equation), pos(0), cur(equation[pos]) {}

    void advance() {
        if (pos < equation.size()) {
            pos++;
            cur = equation[pos];
        } else {
            cur = '\0';
        }
    }

    void advance_to(int a) {
        if (pos < equation.size()) {
            pos += a;
            cur = equation[pos];
        } else {
            cur = '\0';
        }
    }

    vector<data_type> token() {
        vector<data_type> tokens;
        while (pos < equation.size()) {
            cur = equation[pos];
            if (cur == 'x') {
                tokens.push_back({VARIABLE, 0, "x"});
                advance();
            } else if (cur == '^') {
                tokens.push_back({POW, 0, "^"});
                advance();
            } else if (cur == '+') {
                tokens.push_back({PLUS, 0, "+"});
                advance();
            } else if (cur == '-') {
                tokens.push_back({MINUS, 0, "-"});
                advance();
            } else if (cur == '*') {
                tokens.push_back({TIME, 0, "*"});
                advance();
            } else if (cur == '/') {
                tokens.push_back({DIV, 0, "/"});
                advance();
            } else if (cur == '(') {
                tokens.push_back({LP, 0, "("});
                advance();
            } else if (cur == ')') {
                tokens.push_back({RP, 0, ")"});
                advance();
            } else if (isdigit(cur)) {
                int num = 0;
                while (isdigit(equation[pos]) && pos < equation.size()) {
                    num = num * 10 + (equation[pos] - '0');
                    advance();
                }
                tokens.push_back({NUM, static_cast<double>(num), to_string(num)});
            } else if (cur == ' ') {
                advance();
            } else {
                advance();
            }
        }
        return tokens;
    }
};

class MercuryMath_SOLVE_EQUATION_parser {
private:
    size_t tok_idx;
    data_type cur_idx;
    vector<data_type> tokenize;
    string var;
    double val;
public:
    MercuryMath_SOLVE_EQUATION_parser(vector<data_type> tokenize) : tokenize(tokenize), tok_idx(0) {}

    data_type get_next_tok() {
        if (tok_idx < tokenize.size()) {
            return tokenize[tok_idx++];
        }
        return {NONE, 0, ""};
    }

    double factor() {
        cur_idx = get_next_tok();
        if (cur_idx.type == NUM) {
            return cur_idx.value;
        } else if (cur_idx.type == VARIABLE) {
            return val;
        } else if (cur_idx.type == LP) {
            double result = expr();
            cur_idx = get_next_tok();
            return result;
        }
        return 0;
    }

    double term() {
        double result = factor();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == DIV) {
                double divisor = factor();
                if (divisor == 0) {
                    cout << "Error: Division by zero" << endl;
                    return 0;
                }
                result /= divisor;
            } else if (cur_idx.type == TIME) {
                result *= factor();
            } else {
                tok_idx--;
                break;
            }
        }
        return result;
    }

    double expr() {
        double result = term();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == PLUS) {
                result += term();
            } else if (cur_idx.type == MINUS) {
                result -= term();
            } else {
                tok_idx--;
                break;
            }
        }
        return result;
    }
};
