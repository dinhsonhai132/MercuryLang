#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, 
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL
};

struct datatype {
    VerType type;
    int value;
    string name;
};

struct store_var {
    string name;
    int val;
};

vector<store_var> variables;
vector<vector<store_var>> memory;

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
public:
    lexer(string input) : input(input), pos(0) {}

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
            if (cur == '+') {
                tokens.push_back({PLUS, 0, ""});
                advance();

            } else if (cur == '-') {
                tokens.push_back({MINUS, 0, ""});
                advance();

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

            } else if (cur == 'L' && input.substr(pos, 3) == "LET") {
                int val = 0;
                string name = "";
                advance_to(3);

                while (isspace(input[pos])) {
                    advance();
                }
                
                while (isalpha(input[pos]) && pos < input.size()) {
                    name += input[pos];
                    advance();
                }

                while (isspace(cur)) {
                    advance();
                }
                
                if (input[pos] == '=') {
                    advance();
                    while (isspace(cur)) {
                        advance();
                    }
                    while (isdigit(input[pos]) && pos < input.size()) {
                        val = val * 10 + (input[pos] - '0');
                        advance();
                    }
                }

                variables.push_back({name, val});
            } else if (isalpha(cur)) {
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({TEMPORARY_MEMORY, 0, name});
            } else if (isspace(cur)) {
                advance();
            } else if (cur == 'P' && input.substr(pos, 5) == "PRINT") {
                tokens.push_back({PRINT, 0, ""});
                advance_to(5);
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
                if (!name.empty()) {
                    tokens.push_back({STRING, 0, name});
                }
            } else if (cur == '=' && input[pos + 1] == '=') {
                tokens.push_back({EQUAL, 0, ""});
                advance_to(2);
            }
            else {
                advance();
            }
        }
        return tokens;
    }
};


class parser {
private:
    size_t tok_idx;
    datatype cur_idx;
    vector<datatype> tokenize;
    string var;
    int val;
public:
    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0) {}

    datatype get_next_tok() {
        if (tok_idx < tokenize.size()) {
            return tokenize[tok_idx++];
        }
        return {NONE, 0, ""};
    }

    int factor() {
        cur_idx = get_next_tok();
        datatype next_cur_idx = get_next_tok();
        tok_idx--;
        if (cur_idx.type == INT) {
            return cur_idx.value;
        } else if (cur_idx.type == TEMPORARY_MEMORY) {
            string var_name = cur_idx.name;
            for (auto &variable : variables) {
                if (variable.name == var_name) {
                    return variable.val;
                }
            }
        }
        return 0;
    }

    int term() {
        int result = factor();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == DIV) {
                int divisor = factor();
                if (divisor == 0) {
                    cerr << "Error: Division by zero" << endl;
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

    int expr() {
        int result = term();
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

    int comparison() {
        tok_idx = 0;
        auto left_number = get_next_tok();
        VerType op = get_next_tok().type;
        auto right_number = get_next_tok();
        int left; int right;
        if (left_number.type == TEMPORARY_MEMORY) {
            for (auto &variable : variables) {
                string name = left_number.name;
                if (variable.name == name) {
                    left = variable.val;
                    break;
                }
            }
        } else if (left_number.type == INT) {
            left = left_number.value;
        }
        if (right_number.type == TEMPORARY_MEMORY) {
            for (auto &variable : variables) {
                string name = right_number.name;
                if (variable.name == name) {
                    right = variable.val;
                    break;
                }
            }
        } else if (right_number.type == INT) {
            right = right_number.value;
        }

        switch (op) {
            case BIGGER: return left > right ? 1 : 0;
            case SMALLER: return left < right ? 1 : 0;
            case EQUAL: return left == right ? 1 : 0;
        }
        return 0;
    }

    void print_func() {
        auto tok = get_next_tok();
        if (tok.type == PRINT) {
            int result = expr();
            cout << result << endl;
        } else {
            cerr << "Error: Invalid token for PRINT command." << endl;
        }
    }

    void run() {
        while (tok_idx < tokenize.size()) {
            if (tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BIGGER 
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SMALLER
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == EQUAL) {
                cout << comparison() << endl;
                break;
            } else if (tokenize[tok_idx].type == PRINT) {
                print_func();
                break;
            } else if (tokenize[tok_idx].type == STRING) {
                cout << tokenize[tok_idx].name << endl;
                break;
            } else {
                cout << expr() << endl;
                break;
            }
        }
    }

    void print_var() {
        for (auto &variable: variables) {
            cout << variable.name << " = " << variable.val << endl;
        }
    }

    void printstring() {
        int idx = 0;
        while (idx < tokenize.size()) {
            if (tokenize[idx].type == STRING) {
                cout << tokenize[idx].name << endl;
            }
            idx++;
        }
        
    }
};

void info() {
    cout << "copy right (c) dinhsonhai132" << endl;
}

void run() {
    cout << "MercuryLang [Version 0.0.2] \n(c) (this is test version) All rights reserved.\n type 'help?' for help, 'info' for info, 'exit' to leave" << endl;
    while (true) {
        string input;
        cout << ">>> ";
        getline(cin, input);
        if (input.empty()) {
            cout << endl;
            continue;
        }

        lexer lex(input);
        vector<datatype> tok = lex.token();
        parser par(tok);

        if (input == "help?") {
            cout << "Visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "var") {
            par.print_var();
        } else if (input == "exit") {
            cout << "Goodbye :)" << endl;
            break;  
        } else if (input == "info") {
            info();
        } else if (input == "str") {
            par.printstring();
        }
        else {
            par.run();
        }
    }
}

int main() {
    run();
    system("pause");
}
