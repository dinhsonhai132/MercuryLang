//test version
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
    
    void skip_whitespace() {
        while (cur == ' ' || cur == '\t' || cur == '\n') {
            advance();
        }
    }

    void advance() {
        pos++;

        if (pos < input.size()) {
            cur = input[pos];
        } else {
            cur = '\0';
        }
    }

    int make_int() {
        int num = 0;

        while (isdigit(cur)) {
            num = num * 10 + (cur - '0');
            advance();
        }

        tokens.push_back({INT, num});
    }

public:
    lexer(string input) : input(input), pos(0), cur(input[pos]) {}

    vector<datatype> token() {
        while (pos < input.size()) {
            cur = input[pos];
            if (cur == '+') {
                tokens.push_back({PLUS, 0});
            } 
            else if (cur == '-') {
                tokens.push_back({MINUS, 0});
            } 
            else if (cur == '*') {
                tokens.push_back({TIME, 0});
            } 
            else if (cur == '/') {
                tokens.push_back({DIV, 0});
            } 
            else if (isdigit(cur)) {
                make_int();
            } 
            else if (cur == ';') {
                advance();
            } 
            else if (isalpha(cur)) {
                string name = "";
                int val = 0;
                while (pos < input.size()) {
                    if (isalpha(input[pos])) {
                        name += input[pos];
                    } else if (isdigit(input[pos])) {
                        val = val * 10 + (input[pos] - '0');
                    }
                    pos++;
                }
                varibles.push_back({name, val});
                tokens.push_back({VAR, 0, name});
                
            } 
            else if (cur == ' ' || cur == '\t' || cur == '\n') {
                skip_whitespace();
            } 
            else {
                cout << "Error: Invalid character '" << cur << "' at position " << pos << endl;
                break;
                exit(1);
            }

            advance();
        }

        return tokens;
    }
};


class parser {
    
private:

    size_t tok_idx;
    vector<datatype> tokenize;

public:

    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0) {}

    int eval() {

        auto get_next_tok = [&]() -> datatype {
            return tokenize[tok_idx++];
        };

        auto factor = [&]() -> int {
            datatype cur_idx = get_next_tok();
            if (cur_idx.type == INT) {
                return cur_idx.value;
            } 
            else if (cur_idx.type == VAR) {
                bool found = false;
                for (auto& varible : varibles) {
                    if (varible.name == cur_idx.name) {
                        found = true;
                        return varible.val;
                    }
                }
                if (!found) {
                    cout << "Error: Undefined variable '" << cur_idx.name << "'" << endl;
                    exit(1);
                }
            }
            return 0;
        };

        auto term = [&]() -> int {

            int result = factor();

            while (true) {
                datatype cur_idx = get_next_tok();

                if (cur_idx.type == DIV) {
                    result /= factor();
                } 
                else if (cur_idx.type == TIME) {
                    result *= factor();
                }
                else {
                    tok_idx--;
                    break;
                }
            }
            return result;
        };

        auto expr = [&]() -> int {

            int result = term();

            while (true) {
                datatype cur_idx = get_next_tok();
                if (cur_idx.type == PLUS) {
                    result += term();
                }
                 else if (cur_idx.type == MINUS) {
                    result -= term();
                }
                else {
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
        cout << ">>> ";
        getline(cin, input);
        lexer lex = lexer(input);
        vector<datatype> tok = lex.token();
        cout << endl;
        parser par = parser(tok);
        cout << "Result: " << par.eval() << endl;
    }
}

