#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <variant>
#include "token.cpp"
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, STRUCT, ENUM, BLOCK, PORT, DOT, TRUE, FALSE,
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL, BE, SE, DIFFERENCES, IF, ELSE, ELIF, PARAMATER_KWARGS, GLOBAL_VAR,
    THEN, LP, RP, FOR, PP, MM, WHILE, LET, ASSIGN, GOTO, INPUT, LIST, RETURN_FUNC, POP, PUSH, AT, REPAIR,
    FUNCTION, PARAMATER, FUNCTION_CALL, COMMA, DOUBLE_COLON, COMMAND, CIN, CLASS, LAMBDA, MAXTRIX, IMPORT, 
    DO, VECTOR, SPARE_LP, SPARE_RP, LIST_NAME, ARROW_TOKEN, RANGE, FOR_LOOP, IN, TO, END, NUM_TYPE, USER_TYPE,
    NULL_TOK, LOCAL, GLOBAL, HEAP, STACK, REGISTER, CONSTANT, LOCAL_VAR, HEAP_VAR, STACK_VAR, VOID_TOK, AUTO_TOK, 
    CONST_VAR, VOLATILE_TOK, STATIC_TOK, FLOAT, DOUBLE, CHAR, BOOL, LONG, SHORT, UNSIGNED, SIGNED, STR, F_STRING
};

enum VerLibrary_type {
    MERCURY_MATH, MERCURY_FILE, MERCURY_TIME, 
    MERCURY_RANDOM, MERCURY_INPUT_OUTPUT,
};

enum Mercury_type {
    FLOAT_TYPE, DOUBLE_TYPE, CHAR_TYPE, BOOL_TYPE, LONG_TYPE, SHORT_TYPE, UNSIGNED_TYPE, SIGNED_TYPE, 
    VOID, AUTO, CONST, VOLATILE, STATIC, EXTERN, REGISTER_, MUTABLE, STRING_TYPE, INT_TYPE, NULL_TYPE
};

enum port_address {
    PORT_1, PORT_2, PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, PORT_8, PORT_9, PORT_10, PORT_NULL
};

struct port {
    string name = "";
    int value = 0;
    vector<int> values = {};
    port_address address = PORT_NULL;
};

struct enumerate {
    string name;
    int order;
    int value;
};

struct Mer_enum {
    string name;
    vector<enumerate> the_enums;
};

struct store_var {
    string name;
    Mercury_type type;
    int val;
    string string_val;
    bool bool_val;
    char char_val;
    float float_val;
    double double_val;
    long long_val;
    short short_val;
    unsigned unsigned_val;
    signed signed_val;
};

struct store_list {
    string name;
    vector<int> list;
    Mercury_type type = AUTO;
};

struct Parameter {
    string name;
    int val;
    Mercury_type type = AUTO;
};

struct Parameter_kwargs {
    string name;
    vector<int> vec;
    Mercury_type type = AUTO;
};

struct datatype {
    VerType type;
    int value;
    string name;
};

struct function_ {
    string function_name;
    Mercury_type type = AUTO;
    int value = 0;
    vector<Parameter> Parameters;
    vector<datatype> store_tokens;
    Parameter_kwargs parameter_kwargs;
    bool parameter_kwargs_found = false;
};

struct mom_type {
    string class_name;
    vector<store_var> variables;
    vector<store_list> lists;
    vector<function_> functions;
};

vector<store_var> variables;
vector<store_var> tempotary_variables;
vector<store_list> tempotary_list;
vector<store_list> lists;
vector<function_> functions;
vector<VerLibrary_type> libraries;
vector<Mer_enum> the_enums;
vector<mom_type> moms;
vector<string> user_datatype;

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
public:
    lexer(string input) : input(input), pos(0), cur('\0') {}

    void advance() {
        if (pos < input.size()) {
            pos++;
            cur = input[pos];
        } else {
            cur = '\0';
        }
    }

    void advance_to(int a) {
        if (pos < input.size()) {
            pos += a;
            cur = input[pos];
        } else {
            cur = '\0';
        }
    }

    vector<datatype> token() {

        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '/' && input[pos + 1] == '*') {
                advance_to(2);
                while (pos < input.size() && !(cur == '*' && input[pos + 1] == '/')) {
                    advance();
                }
                advance_to(2);
            } else if (cur == '-' && input.substr(pos, 2) == "->") {
                tokens.push_back({ARROW_TOKEN, 0, ""});
                advance_to(2);
            } else if (cur == '*') {
                tokens.push_back({TIME, 0, ""});
                advance();
            } else if (cur == '/') {
                tokens.push_back({DIV, 0, ""});
                advance();
            } else if (isdigit(cur)) {
                int num = 0;
                while (isdigit(input[pos]) && pos < input.size()) {
                    num = num * 10 + (input[pos] - '0');
                    advance();
                }
                tokens.push_back({INT, num, ""});
            } else if (cur == ';') {
                tokens.push_back({NONE, 0, ""});
                advance();
            } else if (cur == '+' && input.substr(pos, 2) == "++") {
                tokens.push_back({PP, 0, ""});
                advance_to(2);
            } else if (cur == '-' && input.substr(pos, 2) == "--") {
                tokens.push_back({MM, 0, ""});
                advance_to(2);
            } else if (cur == '+') {
                tokens.push_back({PLUS, 0, ""});
                advance();
            } else if (cur == '-') {
                tokens.push_back({MINUS, 0, ""});
                advance();
            } else if (cur == 'L' && input.substr(pos, 3) == "LET") {
                tokens.push_back({LET, 0, ""});
                advance_to(3);
            } else if (cur == 'D' && input.substr(pos, 6) == "DOUBLE") {
                advance_to(6);
                tokens.push_back({DOUBLE, 0, ""});
            } else if (cur == 'P' && input.substr(pos, 5) == "PRINT") {
                tokens.push_back({PRINT, 0, ""});
                advance_to(5);
                token();
            } else if (cur == 'E' && input.substr(pos, 3) == "END") {
                tokens.push_back({END, 0, ""});
                advance_to(3);
            } else if (cur == 'F' && input.substr(pos, 5) == "FLOAT") {
                tokens.push_back({FLOAT, 0, ""});
                advance_to(5);
            } else if (cur == 'R' && input.substr(pos, 6) == "RETURN") {
                tokens.push_back({RETURN_FUNC, 0, ""});
                advance_to(6);
            } else if (isspace(cur)) {
                advance();
            } else if (cur == '<') {
                tokens.push_back({SMALLER, 0, ""});
                advance();
            } else if (cur == '>') {
                tokens.push_back({BIGGER, 0, ""});
                advance();
            } else if (cur == '"') {
                string name = "";
                advance();
                while (cur != '"' && cur != '\0' && cur != '\n') {
                    name += input[pos];
                    advance();
                }
                if (!name.empty() && cur == '"') {
                    tokens.push_back({STRING, 0, name});
                }
                advance();
            } else if (cur == '=' && input[pos + 1] == '=') {
                tokens.push_back({EQUAL, 0, ""});
                advance_to(2);
            } else if (cur == '>' && input[pos + 1] == '=') {
                tokens.push_back({BE, 0, ""});
                advance_to(2);
            } else if (cur == '<' && input[pos + 1] == '=') {
                tokens.push_back({SE, 0, ""});
                advance_to(2);
            } else if (cur == '!' && input[pos + 1] == '=') {
                tokens.push_back({DIFFERENCES, 0, ""});
                advance_to(2);
            } else if (cur == 'I' && input.substr(pos, 2) == "IF") {
                tokens.push_back({IF, 0, ""});
                advance_to(2);
            } else if (cur == '(') {
                tokens.push_back({LP, 0, ""}); 
                advance();
            } else if (cur == ')') {
                tokens.push_back({RP, 0, ""});
                advance();
            } else if (cur == ']') {
                tokens.push_back({SPARE_RP, 0, ""});
                advance();
            } else if (cur == '[') {
                tokens.push_back({SPARE_LP, 0, ""});
                advance();
            } else if (cur == 'T' && input.substr(pos, 2) == "TO") {
                tokens.push_back({TO, 0, ""});
                advance_to(2);
            } else if (cur == 'I' && input.substr(pos, 3) == "INT") {
                advance_to(3);
                tokens.push_back({NUM_TYPE, 0, ""});
            } else if (cur == 'F' && input.substr(pos, 3) == "FOR") {
                tokens.push_back({FOR_LOOP, 0, ""});
                advance_to(3);
            } else if (cur == 'I' && input.substr(pos, 2) == "IN") {
                tokens.push_back({IN, 0, ""});
                advance_to(2);
            } else if (cur == 'L' && input.substr(pos, 4) == "LIST") {
                tokens.push_back({LIST, 0, ""});
                advance_to(4);
            } else if (cur == 'T' && input.substr(pos, 4) == "THEN") {
                 tokens.push_back({THEN, 0, ""});
                 advance_to(4);
            } else if (cur == 'E' && input.substr(pos, 4) == "ELSE") {
                tokens.push_back({ELSE, 0, ""});
                advance_to(4);
            } else if (cur == 'E' && input.substr(pos, 4) == "ELIF") {
                tokens.push_back({ELIF, 0, ""});
                advance_to(4);
            } else if (cur == 'F' && input.substr(pos, 4) == "FUNC") {
                advance_to(5);
                string name = "";
                while (isspace(cur)) {
                    advance();
                }
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({FUNCTION, 0, name});
            } else if (cur == 'P' && input.substr(pos, 3) == "POP") {
                advance_to(3);
                tokens.push_back({POP, 0, ""});
            } else if (cur == 'P' && input.substr(pos, 4) == "PUSH") {
                advance_to(4);
                tokens.push_back({PUSH, 0, ""});
            } else if (cur == 'A' && input.substr(pos, 2) == "AT") {
                advance_to(2);  
                tokens.push_back({AT, 0, ""});
            } else if (cur == 'R' && input.substr(pos, 5) == "REPAIR") {
                advance_to(5);
                tokens.push_back({REPAIR, 0, ""});
            } else if (cur == 'C' && input.substr(pos, 3) == "CIN") {
                advance_to(3);
                tokens.push_back({CIN, 0, ""});
            } else if (cur == 'C' && input.substr(pos, 5) == "CLASS") {
                advance_to(5);
                tokens.push_back({CLASS, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 3) == "STR") {
                advance_to(3);
                tokens.push_back({STR, 0, ""});
            } else if (cur == 'N' && input.substr(pos, 4) == "NULL") {
                advance_to(4);
                tokens.push_back({NULL_TOK, 0, ""});
            } else if (cur == 'I' && input.substr(pos, 6) == "IMPORT") {
                advance_to(6);
                tokens.push_back({IMPORT, 0, ""});
            } else if (cur == 'V' && input.substr(pos, 6) == "VECTOR") {
                advance_to(6);
                tokens.push_back({VECTOR, 0, ""});
            } else if (cur == 'M' && input.substr(pos, 6) == "MAXTRIX") {
                advance_to(6);
                tokens.push_back({MAXTRIX, 0, ""});
            } else if (cur == 'E' && input.substr(pos, 4) == "ENUM") {
                advance_to(4);
                tokens.push_back({ENUM, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 6) == "STRUCT") {
                advance_to(6);
                tokens.push_back({STRUCT, 0, ""});
            } else if (cur == 'B' && input.substr(pos, 4) == "BLOCK") {
                advance_to(4);
                tokens.push_back({BLOCK, 0, ""});
            } else if (cur == 'P' && input.substr(pos, 4) == "PORT") {
                advance_to(4);  
                tokens.push_back({PORT, 0, ""});
            } else if (cur == 'C' && input.substr(pos, 4) == "CHAR") {
                advance_to(4);
                tokens.push_back({CHAR, 0, ""});
            } else if (cur == 'B' && input.substr(pos, 4) == "BOOL") {
                advance_to(4);
                tokens.push_back({BOOL, 0, ""});
            } else if (cur == 'L' && input.substr(pos, 4) == "LONG") {
                advance_to(4);
                tokens.push_back({LONG, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 5) == "SHORT") {
                advance_to(5);
                tokens.push_back({SHORT, 0, ""});
            } else if (cur == 'U' && input.substr(pos, 8) == "UNSIGNED") {
                advance_to(8);
                tokens.push_back({UNSIGNED, 0, ""});
            } else if (cur == 'S' && input.substr(pos, 6) == "SIGNED") {
                advance_to(6);
                tokens.push_back({SIGNED, 0, ""});
            } else if (cur == 'T' && input.substr(pos, 4) == "TRUE") {
                advance_to(4);
                tokens.push_back({TRUE, 0, ""});
            } else if (cur == 'F' && input.substr(pos, 5) == "FALSE") {
                advance_to(5);
                tokens.push_back({FALSE, 0, ""});
            } else if (cur == 'G' && input.substr(pos, 6) == "GLOBAL") {
                advance_to(6);
                tokens.push_back({GLOBAL_VAR, 0, ""});
            } else if (cur == 'G' && input.substr(pos, 6) == "GLOBAL") {
                advance_to(6);
                tokens.push_back({GLOBAL_VAR, 0, ""});
            } else if (cur == 'f') {
                tokens.push_back({F_STRING, 0, ""});
                advance();
            } else if (cur == '.') {
                advance();
                tokens.push_back({DOT, 0, ""});
            } else if (cur == '&') {
                advance();
                string name;
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({PARAMATER, 0, name});
            } else if (cur == '%') {
                advance();
                string name;
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({PARAMATER_KWARGS, 0, name});
            } else if (cur == '$') {
                string name;
                advance();
                while (isalpha(cur)) {
                    name += cur;
                    advance();
                }
                tokens.push_back({USER_TYPE, 0, name});
            } 
            else if (cur == ',') {
                tokens.push_back({COMMA, 0, ""});
                advance();
            } else if (cur == ':') {
                tokens.push_back({DOUBLE_COLON, 0, ""});
                advance();
            } else if (cur == '!') {
                advance();
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({FUNCTION_CALL, 0, name});
            } else if (cur == 'D' && input.substr(pos, 2) == "DO") {
                tokens.push_back({DO, 0, ""});
                advance_to(2);
            } else if (cur == 'W' && input.substr(pos, 5) == "WHILE") {
                advance_to(5);
                tokens.push_back({WHILE, 0, ""});
            } else if (cur == '@') {
                advance();
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({LIST_NAME, 0, name});
            } else if (isalpha(cur)) {
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({TEMPORARY_MEMORY, 0, name});
            } else if (cur == '=') {
                tokens.push_back({ASSIGN, 0, ""});
                advance();
            } else {
                advance();
            }
        }
        return tokens;
    }
};