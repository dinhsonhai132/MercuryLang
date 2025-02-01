#define Program "Program";
#define NumericLiteral "NumericLiteral";
#define Identifier "Identifier";
#define BinaryExpression "BinaryExpression";
#include <string>

using namespace std;

#ifndef AST
#define AST

struct stmt {
    string kind;
}
struct program : stmt {
    string type = Program;
    vector<stmt> body;
}

struct expr : stmt {}
struct binary_expr : expr {
    string type = BinaryExpression;
    string op;
    expr left;
    expr right;
}

struct identifier : expr {
    string type = Identifier;
}
struct 

#endif