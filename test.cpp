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
    
    void advance() {
        if (pos < input.size() - 1) {
            pos++;
            cur = input[pos];
        } else {
            pos = 0;
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
                    if (isalpha(cur) || cur == ';') {
                        break;
                    }
                }
                tokens.push_back({INT, num, ""});
                continue;
            } else if (cur == ';') {
                tokens.push_back({NONE, 0, ""});
                advance();
            } else if (cur == '@') {
                int val = 0;
                string name = "";
                while (pos < input.size()) {
                    if (isalpha(input[pos])) {
                        name += input[pos];
                    } else if (input[pos] == '=') {
                        break;
                    }
                    advance();
                }
                while (pos < input.size()) {
                    if (isdigit(input[pos])) {
                        val = val * 10 + (input[pos] - '0');
                    } else if (input[pos] == ';') {
                        break;
                    }
                    advance();
                }
                varibles.push_back({name, val});
            } else if (isalpha(cur)) {
                string name = "";
                while (isalpha(cur)) {
                    name += input[pos];
                    advance();
                }
                tokens.push_back({VAR, 0, name});
            } else if (isspace(cur)) {
                advance();
            } else {
                cerr << "Unrecognized character: '" << cur << "' at position: " << pos << endl;
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

    int eval() {
        auto get_next_tok = [&]() -> datatype {
            return tokenize[tok_idx++];
        };

        auto factor = [&]() -> int {
            cur_idx = get_next_tok();
            if (cur_idx.type == INT) {
                return cur_idx.value;
            } else if (cur_idx.type == VAR) {
                string var_name = cur_idx.name;
                for (auto &varible : varibles) {
                    if (varible.name == var_name) {
                        return varible.val;
                    }
                }
                return 0;
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
    void print_var() {
        for (auto &varible: varibles) {
            cout << varible.name << "=" << varible.val << endl;
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
        } else {
            cout << par.eval() << endl;
        }
    }
}

int main() {
    run();
}
