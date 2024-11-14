#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE
};

struct datatype {
    VerType type;
    int value;
};

class lexer {
private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
    size_t tok_idx;
    datatype cur_idx;
public:
    lexer(string input) : input(input), pos(0), cur(input[pos]), tok_idx(0) {}

    vector<datatype> token() {
        datatype datatoken;
        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '+') {
                datatoken.type = PLUS;
                datatoken.value = 0;
                tokens.push_back(datatoken);
            } else if (cur == '-') {
                datatoken.type = MINUS;
                datatoken.value = 0;
                tokens.push_back(datatoken);
            } else if (cur == '*') {
                datatoken.type = TIME;
                datatoken.value = 0;
                tokens.push_back(datatoken);
            } else if (cur == '/') {
                datatoken.type = DIV;
                datatoken.value = 0;
                tokens.push_back(datatoken);
            } else if (isdigit(cur)) {
                datatoken.type = INT;
                datatoken.value = cur - '0';
                tokens.push_back(datatoken);
            }
            pos++;
        }
        datatoken.type = NONE;
        datatoken.value = 0;
        tokens.push_back(datatoken);
        return tokens;
    }
};

class parser {
private:
    size_t tok_idx;
    datatype cur_idx;
    vector<datatype> tokenize;
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
    cout << "fslang2 [Version 0.0.1] \n(c) Haidinhson company. All rights reserved." << endl;
    while (true) {
        string input;
        cout << "enter: ";
        getline(cin, input);
        lexer lex = lexer(input);
        vector<datatype> tok = lex.token();
        parser par = parser(tok);
        int result = par.eval();
        cout << "result: " << result << endl;
    }
}
