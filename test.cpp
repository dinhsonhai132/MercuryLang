#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, VAR
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

vector<store_var> varibles;

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
public:
    lexer(string input) : input(input), pos(0) {}
    
    vector<datatype> token() {

        bool error_num = false;
        bool error_iden = false;
        bool error_string = false;
        bool error_var = false;

        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '+') {
                tokens.push_back({PLUS, 0, ""});
            } else if (cur == '-') {
                tokens.push_back({MINUS, 0, ""});
            } else if (cur == '*') {
                tokens.push_back({TIME, 0, ""});
            } else if (cur == '/') {
                tokens.push_back({DIV, 0, ""});
            } else if (isdigit(cur)) {
                int num = 0;
                while (isdigit(input[pos]) && pos < input.size()) {
                    num = num * 10 + (input[pos] - '0');
                    pos++;
                    if (isalpha(cur)) {
                        error_num = true;
                        break;
                    }
                }
                if (!error_num) tokens.push_back({INT, num, ""});
                continue;
            } else if (cur == ';') {
                tokens.push_back({NONE, 0});
            } else if (cur == '@') {
                string name = "";
                int value = 0;
                pos++;
                while (pos < input.size() && isalpha(input[pos])) {
                    name += input[pos];
                    pos++;
                }
                if (input[pos] == '=') {
                    pos++;
                    while (pos < input.size() && isdigit(input[pos])) {
                        value = value * 10 + (input[pos] - '0');
                        pos++;
                    }
                }
                if (!name.empty()) {
                    varibles.push_back({name, value});
                } else {
                    error_var = true;
                }
            } else if (cur == ' ' || cur == '\t' || cur == '\n') {
                pos++;
            } else if (isalpha(cur)) {
                string name = "";
                while (isalpha(input[pos]) && pos < input.size()) {
                    name += input[pos];
                    pos++;
                }
                tokens.push_back({VAR, 0, name});
            } else {
                if (error_num) {
                    cout << "Number error cant evalulate";
                    error_num = false;
                } else if (error_string) {
                    cout << "Error string cannot in number";
                    error_string = false;
                } else if (error_iden) {
                    cout << "Error identifier";
                    error_iden = false;
                } else {
                    continue;
                }
            }
            pos++;
        }
        return tokens;
    }
};


class parser {
private:
    size_t tok_idx;
    vector<datatype> tokenize;
    datatype cur_idx;
public:
    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0), cur_idx(tokenize[tok_idx]) {}
    int eval() {
        auto get_next_tok = [&]() -> datatype {
            if (tok_idx < tokenize.size()) return tokenize[tok_idx++];
            return {NONE, 0};
        };

        auto factor = [&]() -> int {
            cur_idx = get_next_tok();
            if (cur_idx.type == INT) {
                return cur_idx.value;
            } else if (cur_idx.type == VAR) {
                for (const auto &varible: varibles) {
                    if (varible.name == cur_idx.name) {
                        return varible.val;
                    }
                }
                cout << "Error: Undefined variable '" << cur_idx.name << "'" << endl;
                throw runtime_error("Undefined variable");
            }
            return 0;
        };

        auto term = [&]() -> int {
            int result = factor();
            while (true) {
                cur_idx = get_next_tok();
                if (cur_idx.type == DIV) {
                    result /= factor();
                } else if (cur_idx.type == TIME) {
                    result *= factor();
                } else {
                    tok_idx--;
                    break;
                }
            }
            return result;
        };

        auto expr = [&]() -> int {
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
        };
        
        return expr();
    }

    void print_varibles() {
        for (auto &var: varibles) {
            cout << var.name << "=" << var.val << endl;
        }
    }
};

void run() {
    cout << "fslang2 [Version 0.0.2] \n(c) (this is test version) All rights reserved.\n type 'help?' for help" << endl;
    while (true) {
        string input;
        cout << ">>> ";
        getline(cin, input);
        lexer lex = lexer(input);
        vector<datatype> tok = lex.token();
        parser par = parser(tok);
        if (input.empty()) {
            cout << endl;
        } else if (input == "help?") {
            cout << "visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "var") {
            par.print_varibles();
        }
        else {
            cout << par.eval() << endl;
        }
    }
}

int main() {
    run();
}
