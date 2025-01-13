#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"
using namespace std;

void lexer::advance() {
    if (pos < input.size()) {
        pos++;
        cur = input[pos];
    } else {
        cur = '\0';
    }
}

void lexer::advance_to(int a) {
    if (pos < input.size()) {
        pos += a;
        cur = input[pos];
    } else {
        cur = '\0';
    }
}

vector<datatype> lexer::token() {

    while (pos < input.size()) {
        cur = input[pos];
        if (cur == '/' && input[pos + 1] == '*') {
            advance_to(2);
            while (pos < input.size() && !(cur == '*' && input[pos + 1] == '/')) {
                advance();
            }
            advance_to(2);
        } else if (cur == '-' && input.substr(pos, 2) == "->") {
            tokens.push_back({EXTRACT, 0, ""});
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
        } else if (cur == 'E' && input.substr(pos, 3) == "END") {
            tokens.push_back({END, 0, ""});
            advance_to(3);
        } else if (cur == 'L' && input.substr(pos, 3) == "LET") {
            tokens.push_back({LET, 0, ""});
            advance_to(3);
        } else if (cur == 'P' && input.substr(pos, 5) == "PRINT") {
            tokens.push_back({PRINT, 0, ""});
            advance_to(5);
            token();
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
            advance_to(2);
            tokens.push_back({DO, 0, ""});
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
