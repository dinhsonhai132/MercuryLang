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
};

struct var {
    string name;
    int val;
};

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
    vector<var> vars;
    size_t tok_idx;
    datatype cur_idx;
public:
    lexer(string input) : input(input), pos(0), cur(input[pos]), tok_idx(0) {}

    vector<datatype> token() {
        datatype datatoken;
        int num = 0;
        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '+') {
                tokens.push_back({PLUS, 0});
            } else if (cur == '-') {
                tokens.push_back({MINUS, 0});
            } else if (cur == '*') {
                tokens.push_back({TIME, 0});
            } else if (cur == '/') {
                tokens.push_back({DIV, 0});
            } else if (isdigit(cur)) {
                num = 0;
                while (isdigit(input[pos]) && pos < input.size()) {
                    num = num * 10 + (input[pos] - '0');
                    pos++;
                }
                tokens.push_back({INT, num});
                continue;
            } else if (cur == ';') {
                tokens.push_back({NONE, 0});
            }
            pos++;
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
            }
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
};

int main() {
    cout << "Mercury [Version 0.0.1] \n(c) All rights reserved." << endl;
    while (true) {
        string input;
        cout << ">>> ";
        getline(cin, input);
        lexer lex = lexer(input);
        vector<datatype> tok = lex.token();
        parser par = parser(tok);
        int result = par.eval();
        cout << result << endl;
    }
}
