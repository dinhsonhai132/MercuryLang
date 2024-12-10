#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, 
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL, BE, SE, DIFFERENCE, IF, ELSE,
    THEN, LP, RP, FOR, PP, MM, WHILE, LET, ASSIGN, GOTO, INPUT, LIST
};

struct store_var {
    string name;
    int val;
};

struct PORT_NAME {
    string port_1 = "rx10001";
    string port_2 = "rx20001";
    string port_3 = "rx30001";
    string port_4 = "rx40001";
    string port_5 = "rx50001";
    string port_6 = "rx60001";
    string port_7 = "rx70001";
    string port_8 = "rx80001";
    string port_9 = "rx90001";
    string port_10 = "rx1A0002";
};

struct PORT_STORE {
    vector<store_var> port_1;
    vector<store_var> port_2;
    vector<store_var> port_3;
    vector<store_var> port_4;
    vector<store_var> port_5;
    vector<store_var> port_6;
    vector<store_var> port_7;
    vector<store_var> port_8;
    vector<store_var> port_9;
    vector<store_var> port_10;
};

struct datatype {
    VerType type;
    int value;
    string name;
};

class Port {
private:
    PORT_NAME name;
    PORT_STORE store;
public:
    Port(PORT_NAME name, PORT_STORE store) : name(name), store(store) {}
};

#define make_port(name, store) = Port(name, store);
#define make_error();

vector<store_var> variables;
vector<Port> memory;

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
            if (cur == '+' && isalnum(input[pos + 1])) {
                tokens.push_back({PLUS, 0, ""});
                advance();
            } else if (cur == '-' && isalnum(input[pos + 1])) {
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
            } else if (cur == '+' && input.substr(pos, 2) == "++") {
                tokens.push_back({PP, 0, ""});
                advance_to(2);
            } else if (cur == '-' && input.substr(pos, 2) == "--") {
                tokens.push_back({MM, 0, ""});
                advance_to(2);
            } else if (cur == 'L' && input.substr(pos, 3) == "LET") {
                tokens.push_back({LET, 0, ""});
                advance_to(3);
            } else if (cur == 'P' && input.substr(pos, 5) == "PRINT") {
                tokens.push_back({PRINT, 0, ""});
                advance_to(5);
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
                if (!name.empty()) {
                    tokens.push_back({STRING, 0, name});
                }
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
                tokens.push_back({DIFFERENCE, 0, ""});
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
            } else if (cur == 'T' && input.substr(pos, 4) == "THEN") {
                 tokens.push_back({THEN, 0, ""});
                 advance_to(4);
            } else if (cur == 'E' && input.substr(pos, 4) == "ELSE") {
                tokens.push_back({ELSE, 0, ""});
                advance_to(4);
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

    int get_variable(string name) {
        for (auto &variable: variables) {
            if (variable.name == name) {
                return variable.val;
            }
        }
        return 0;
    }

    datatype get_next_tok() {
        if (tok_idx < tokenize.size()) {
            return tokenize[tok_idx++];
        }
        return {NONE, 0, ""};
    }

    int factor() {
        cur_idx = get_next_tok();
        if (cur_idx.type == INT) {
            return cur_idx.value;
        } else if (cur_idx.type == TEMPORARY_MEMORY) {
            string var_name = cur_idx.name;
            int value = get_variable(var_name);
            return value;
        } else if (cur_idx.type == PP) {
            auto next_tok = get_next_tok();
            if (next_tok.type == TEMPORARY_MEMORY) {
                int val;
                for (auto &variable: variables) {
                    if (variable.name == next_tok.name) {
                        variable.val += 1;
                        val = variable.val;
                        break;
                    }
                }
                return val;
            } else if (next_tok.type == INT) {
                return ++next_tok.value;
            }
        } else if (cur_idx.type == MM) {
            auto next_tok = get_next_tok();
            if (next_tok.type == TEMPORARY_MEMORY) {
                int val;
                for (auto &variable: variables) {
                    if (variable.name == next_tok.name) {
                        variable.val -= 1;
                        val = variable.val;
                        break;
                    }
                }
                return val;
            } else if (next_tok.type == INT) {
                return --next_tok.value;
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
            }
            else {
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

    int while_loop() {
        cur_idx = get_next_tok();
        if (cur_idx.type == WHILE) {
            int condition = comparison();
            if (condition == 1) {
                expr();
                tok_idx = 0;
                while_loop();
            } else {
                return 0;
            }
        }
        return 0;
    }

    void make_var() {
        datatype name;
        int val;
        string var_name;
        auto tok = get_next_tok();
        if (tok.type == LET) {
            name = get_next_tok();
            if (name.type = TEMPORARY_MEMORY) {
                var_name = name.name;
            }
            tok = get_next_tok();
            if (tok.type == ASSIGN) {
                tok = get_next_tok();
                if (tok.type == INT) {
                    tok_idx--;
                    val = expr();
                }
            }
        }
        variables.push_back({var_name, val});
    }

    int comparison() {
        auto left_token = get_next_tok();
        VerType OP = get_next_tok().type;
        auto right_token = get_next_tok();
        int left = 0;
        int right = 0;
        if (left_token.type == TEMPORARY_MEMORY) {
            left = get_variable(left_token.name);
        } else if (left_token.type == INT) {
            left = left_token.value;
        }
        if (right_token.type == TEMPORARY_MEMORY) {
            right = get_variable(right_token.name);
        } else if (right_token.type == INT) {
            right = right_token.value;
        }
        switch (OP) {
            case BIGGER:
                return left > right ? 1 : 0;
            case SMALLER:
                return left < right ? 1 : 0;
            case EQUAL:
                return left == right ? 1 : 0;
            case BE:
                return left >= right ? 1 : 0;
            case SE:
                return left <= right ? 1 : 0;
            case DIFFERENCE:
                return left != right ? 1 : 0;
            default:
                return 0;
        }
        return 0;
    }
    
    auto condition() {
        tok_idx = 0;
        cur_idx = get_next_tok();
        if (cur_idx.type == IF) {
            int check = comparison();
            if (check == 1 && get_next_tok().type == THEN) {
                auto next_tok = get_next_tok();
                if (next_tok.type == STRING) {
                    cout << next_tok.name << endl;
                } else if (next_tok.type == INT) {
                    tok_idx--;
                    cout << expr() << endl;
                }
            } else if (check == 0 && get_next_tok().type == THEN) {
                while (cur_idx.type != ELSE && tok_idx < tokenize.size()) {
                    cur_idx = tokenize[tok_idx];
                    tok_idx++;
                }
                tok_idx--;
                auto tok = get_next_tok();
                if (tok.type == STRING) {
                    cout << tok.name << endl;
                } else if (tok.type == INT || tok.type == TEMPORARY_MEMORY) {
                    tok_idx--;
                    cout << expr() << endl;
                }
            }
        }
    }

    void print_func() {
        tok_idx = 0;
        auto tok = get_next_tok();
        if (tok.type == PRINT) {
            auto next_tok = get_next_tok();
            if (next_tok.type == INT || next_tok.type == TEMPORARY_MEMORY) {
                tok_idx--;
                cout << expr() << endl;
            } else if (next_tok.type == STRING) {
                cout << next_tok.name << endl;
            } else {
                cout << "Invalid PRINT token" << endl;
            }
        }
    }

    void run() {
        while (tok_idx < tokenize.size()) {
            if (tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BIGGER 
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SMALLER
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == EQUAL
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BE
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SE
            || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == DIFFERENCE) {
                tok_idx = 0;
                cout << comparison() << endl;
                break;
            } else if (tokenize[tok_idx].type == STRING) {
                cout << tokenize[tok_idx].name << endl;
                break;
            } else if (tokenize[tok_idx].type == PRINT) {
                tok_idx--;
                print_func();
                break;
            } else if (tokenize[tok_idx].type == IF) {
                condition();
                break;
            } else if (tokenize[tok_idx].type == LET) {
                make_var();
                break;
            } else if (tokenize.empty()) {
                break;
            }
            else {
                expr();
                break;
            }
        }
    }
};

void info() {
    cout << "copy right (c) dinhsonhai132" << endl;
}

void print_var() {
    for (auto &var: variables) {
        cout << "Name: " << var.name << " Value: " << var.val << endl;
    }
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
        vector<datatype> tokens = lex.token();
        parser par(tokens);

        if (input == "help?") {
            cout << "Visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "exit") {
            cout << "Goodbye :)" << endl;
            break;  
        } else if (input == "info") {
            info();
        } else if (input == "var") {
            print_var();
        } else if (input.empty()) {
            continue;
        } else {
            par.run();
        }
        tokens = {};
    }
}

void debug() {
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
        vector<datatype> tokens = lex.token();
        parser par(tokens);

        if (input == "help?") {
            cout << "Visit https://dinhsonhai132.github.io/fslang.github.io/fslang.html for more info" << endl;
        } else if (input == "exit") {
            cout << "Goodbye :)" << endl;
            break;  
        } else if (input == "info") {
            info();
        } else if (input == "var") {
            print_var();
        } else if (input.empty()) {
            continue;
        } else {
            par.run();
            string token_type;
            for (auto &token : tokens) {
                switch(token.type) {
                    case PLUS: token_type = "PLUS"; break; 
                    case INT: token_type = "INT"; break; 
                    case IF: token_type = "IF"; break; 
                    case THEN: token_type = "THEN"; break; 
                    case ELSE: token_type = "ELSE"; break;
                    case DIV: token_type = "DIV"; break; 
                    case MINUS: token_type = "MINUS"; break; 
                    case TIME: token_type = "TIME"; break; 
                    case PRINT: token_type = "PRINT"; break; 
                    case STRING: token_type = "STRING"; break;
                    case MEMORY: token_type = "MEMORY"; break;
                    case TEMPORARY_MEMORY: token_type = "TEMPORARY_MEMORY"; break;
                    case NONE: token_type = "NONE"; break;
                    case BIGGER: token_type = "BIGGER"; break;
                    case SMALLER: token_type = "SMALLER"; break;
                    case PP: token_type = "PP"; break;
                    case MM: token_type = "MM"; break;
                    case LET: token_type = "LET"; break;
                    case ASSIGN: token_type = "ASSIGN"; break;
                }
                cout << "Type: " << token_type << " Value: " << token.value << " Name: " << token.name << endl;
            }
        }
        tokens = {};
    }
}

int interpreter(string file_name) {
    std::ifstream inputFile(file_name);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        lexer lex(line);
        vector<datatype> tokens = lex.token();
        parser par(tokens);
        par.run();
    }

    inputFile.close();
    return 0;
}

int main() {
    cout << "enter 'debug' to debug, 'run' to run, or file name to run file" << endl;
    cout << "mode> ";
    string mode;
    getline(cin, mode);
    if (mode == "debug") {
        debug();
    } else if (mode == "run") {
        run();
    } else {
        interpreter(mode);
    }
    system("pause");
}
