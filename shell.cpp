#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, NONE
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
        vector<VerType> ops;
        vector<int> nums;
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == INT) {
                nums.push_back(cur_idx.value);
            } else if (cur_idx.type == PLUS || cur_idx.type == MINUS) {
                ops.push_back(cur_idx.type);
            }
            tok_idx++;
        }

        int result = nums[0];
        for(size_t index = 1; index < nums.size(); index++) {
            if (ops[index - 1] == PLUS) {
                result += nums[index];
            } else if (ops[index - 1] == MINUS) {
                result -= nums[index];
            }
        }
        return result;
    }
};

int main() {
    cout << "fslang2 [Version 0.0.1] \n(c) Haidinhson company. All rights reserved." << endl;
    while (true) {
        string input;
        cin >> input;
        cout << endl;
        lexer lex = lexer(input);
        vector<datatype> tok = lex.token();
        parser par = parser(tok);
        int result = par.eval();
        cout << "result: " << result << endl;
    }
    
}