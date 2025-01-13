#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
using namespace std;

int parser::get_tempotary_variable(string name) {
    bool found = false;

    for (auto &variable: tempotary_variables) {
        if (variable.name == name) {
            found = true;
            return variable.val;
        }
    }

    if (!found) {
        cout << "Error: can't found the paramater name" << endl;
    }

    return 0;
}

int parser::get_variable(string name) {
    bool found = false;
    for (auto &variable: variables) {
        if (variable.name == name) {
            found = true;
            return variable.val;
        }
    }
    if (!found) {
        cout << "Error: can't found the variable name" << endl;
    }
    return 0;
}

vector<int> parser::get_list(string name) {
    bool found = false;
    for (auto &list : lists) {
        if (list.name == name) {
            found = true;
            return list.list;
        }
    }
    if (!found) {
        cout << "Error: can't found the list" << endl;
    }
    return {0};
}

int parser::extract() {
    datatype tok = parser::get_next_tok();
    if (tok.type == LIST_NAME) {
        auto list = get_list(tok.name);
        tok = get_next_tok();
        if (tok.type == EXTRACT) {
            tok = get_next_tok();
            if (tok.type == INT) {
                int order = tok.value;
                if (order > list.size()) {
                    cout << "Error: index out of range" << endl;
                    return 0;
                } else if (order < 1) {
                    cout << "Error: order can't below 1" << endl;
                    return 0;
                }
                auto element = list[tok.value - 1];
                return element;
            } else if (tok.type == TEMPORARY_MEMORY) {
                int val = get_variable(tok.name);
                if (val > list.size()) {
                    cout << "Error: index out of range, please change the another variable" << endl;
                    return 0;
                } else if (val < 1) {
                    cout << "Error: order can't below 1, please change the another variable" << endl;
                    return 0;
                }
                int element = list[val - 1];
                return element;
            }
        }
    } else {
        cout << "Error: can't extract the value from the list" << endl;
    }
    return 0;
}

datatype parser::get_next_tok() {
    if (tok_idx < tokenize.size()) {
        return tokenize[tok_idx++];
    }
    return {NONE, 0, ""};
}

datatype parser::get_next_tok_to(int s) {
    if (tok_idx < tokenize.size()) {
        tok_idx += s;
        return tokenize[tok_idx];
    }
    return {NONE, 0, ""};
}

int parser::factor() {
    cur_idx = get_next_tok();
    if (cur_idx.type == INT) {
        return cur_idx.value;
    } else if (cur_idx.type == TEMPORARY_MEMORY) {
        string var_name = cur_idx.name;
        int value = get_variable(var_name);
        return value;
    } else if (cur_idx.type == PARAMATER) {
        string var_name = cur_idx.name;
        int value = get_tempotary_variable(var_name);
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
    } else if (cur_idx.type == LIST_NAME) {
        tok_idx--;
        return extract();
    } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
        tok_idx++;
    }
    return 0;
}

int parser::term() {
    int result = factor();
    while (true) {
        cur_idx = get_next_tok();
        if (cur_idx.type == DIV) {
            int divisor = factor();
            if (divisor == 0) {
                cout << "Error: Division by zero" << endl;
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

int parser::expr() {
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

void parser::make_list() {
    string name;
    vector<int> the_list;
    auto tok = get_next_tok();
    if (tok.type == LIST) {
        tok = get_next_tok();
        if (tok.type == TEMPORARY_MEMORY) {
            name = tok.name;
            tok = get_next_tok();
            if (tok.type == ASSIGN) {
                tok = get_next_tok();
                if (tok.type == SPARE_LP) {
                    while (tok_idx < tokenize.size() && tok.type != SPARE_RP) {
                        if (tok.type == INT) {
                            the_list.push_back(tok.value);
                            tok = get_next_tok();
                        } else if (tok.type == COMMA) {
                            tok = get_next_tok();
                        }
                    }
                }
            } else {
                cout << "Error: '=' not found" << endl;
            }
        } else {
            cout << "Error: Expected list name after 'LIST'" << endl;
        }
    }

    if (!name.empty()) {
        lists.push_back({name, the_list});
    } else {
        cout << "Error: name not found" << endl;
    }
}

void parser::make_function() {
    cur_idx = get_next_tok();
    string name_func;
    vector<Parameter> paras;
    vector<Parameter_kwargs> paras_kwargs;
    vector<datatype> store_tokens;
    if (cur_idx.type == FUNCTION) {
        name_func = cur_idx.name;
        cur_idx = get_next_tok();
        if (cur_idx.type == LP) {

            bool found = false;
            if (tokenize[tok_idx + 1].type == PARAMATER_KWARGS) {
                paras_kwargs.push_back({tokenize[tok_idx + 1].name, {}});
                found = true;
            } else {
                while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                    if (cur_idx.type == PARAMATER) {
                        paras.push_back({cur_idx.name, 0});
                    }
                    cur_idx = tokenize[tok_idx++];
                }
            }

            if (found) {
                cur_idx = get_next_tok_to(3);
            } else {
                cur_idx = get_next_tok();
            }

            if (cur_idx.type == DO) {
                while (tok_idx < tokenize.size() && cur_idx.type != END
                || tok_idx < tokenize.size()) {
                    store_tokens.push_back(cur_idx);
                    cur_idx = tokenize[tok_idx++];
                }
            }

        } else {
            cout << "Error: missing left parent" << endl;
        }
    }
    else {
        cout << "Error: function name failed" << endl;
    }
    
    if (paras_kwargs.empty()) {
        functions.push_back({name_func, paras, store_tokens});
    } else {
        functions.push_back({name_func, {}, store_tokens, paras_kwargs});
    }
}

vector<datatype> parser::get_tokens(string name) {
    for (auto &func : functions) {
        if (func.function_name == name) {
            return func.store_tokens;
        }
    }
    return {};
}

vector<Parameter> parser::get_para(string name) {
    for (auto &func : functions) {
        if (func.function_name == name) {
            return func.Parameters;
        }
    }
    return {};
} 

auto parser::make_return() {
    cur_idx = get_next_tok();
    if (cur_idx.type == RETURN_FUNC) {
        cur_idx = get_next_tok();
    }
}

void parser::execute(vector<datatype> tokens, vector<Parameter> paras) {

    if (!paras.empty()) {
        for (auto &para : paras) {
            tempotary_variables.push_back({para.name, para.val});
        }
    }

    tok_idx = 0;
    tokenize = tokens;
    cur_idx = tokenize[tok_idx];

    while (tok_idx < tokenize.size()) {
        cur_idx = tokenize[tok_idx];
        if (cur_idx.type == PRINT) {
            print_func();
            tok_idx++;
        } else if (cur_idx.type == LET) {
            make_var();
            tok_idx++;
        } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
            tok_idx++;
        } else if (cur_idx.type == IF) {
            condition();
            tok_idx++;
        } else if (cur_idx.type == LIST) {
            make_list();
            tok_idx++;
        } else if (cur_idx.type == FOR_LOOP) {
            for_loop();
        } else if (cur_idx.type == WHILE) {
            while_loop();
        } else if (cur_idx.type == FUNCTION_CALL) {
            call_function();
            tok_idx++;
        } else if (cur_idx.type == FUNCTION) {
            make_function();
            tok_idx++;
        } else if (cur_idx.type == RETURN_FUNC) {
            make_return();
            break;
        } else {
            expr();
        }
    }
    tempotary_variables = {};
}

void parser::call_function() {
    cur_idx = get_next_tok();
    string name;
    vector<int> values;
    vector<datatype> func_tokens;
    vector<Parameter> paras;
    if (cur_idx.type == FUNCTION_CALL) {
        name = cur_idx.name;
        cur_idx = get_next_tok();
        if (cur_idx.type == LP) {
            func_tokens = parser::get_tokens(name);
            paras = get_para(name);
            int orders = 0;
            while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                if (cur_idx.type == INT) {
                    values.push_back(cur_idx.value);
                } else if (cur_idx.type == TEMPORARY_MEMORY) {
                    values.push_back(get_variable(cur_idx.name));
                }
                cur_idx = tokenize[tok_idx++];
            }

            for (int i = 0; i < paras.size(); i++) {
                paras[i].val = values[i];
            }
            int pos = tok_idx;
            execute(func_tokens, paras);
            tok_idx = pos;
        } else {
            cout << "Error: missing left parent" << endl;
        }
    }
}

void parser::for_loop() {
    cur_idx = get_next_tok();
    int left, right;
    string name;
    bool list_found = false;
    if (cur_idx.type == FOR_LOOP) {
        cur_idx = get_next_tok();
        if (cur_idx.type == TEMPORARY_MEMORY) {
            name = cur_idx.name;
            variables.push_back({name, 0});
            cur_idx = get_next_tok();
            if (cur_idx.type == IN) {
                cur_idx = get_next_tok();
                if (cur_idx.type == INT) {
                    int left = cur_idx.value;
                    cur_idx = get_next_tok();
                    if (cur_idx.type == TO) {
                        cur_idx = get_next_tok();
                        if (cur_idx.type == INT) {
                            right = cur_idx.value;
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == TEMPORARY_MEMORY) {
                            right = get_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == PARAMATER) {
                            right = get_tempotary_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else {
                            cout << "Error: unexpected factor" << endl;
                        }
                    } else {
                        cout << "Error: can't found token 'TO'" << endl;
                    }
                } else if (cur_idx.type == TEMPORARY_MEMORY) {
                    int left = get_variable(cur_idx.name);
                    cur_idx = get_next_tok();
                    if (cur_idx.type == TO) {
                        cur_idx = get_next_tok();
                        if (cur_idx.type == INT) {
                            right = cur_idx.value;
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == TEMPORARY_MEMORY) {
                            right = get_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == PARAMATER) {
                            right = get_tempotary_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else {
                            cout << "Error: unexpected factor" << endl;
                        }
                    } else {
                        cout << "Error: can't found token 'TO'" << endl;
                    }
                } else if (cur_idx.type == PARAMATER) {
                    int left = get_tempotary_variable(cur_idx.name);
                    cur_idx = get_next_tok();
                    if (cur_idx.type == TO) {
                        cur_idx = get_next_tok();
                        if (cur_idx.type == INT) {
                            right = cur_idx.value;
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == TEMPORARY_MEMORY) {
                            right = get_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else if (cur_idx.type == PARAMATER) {
                            right = get_tempotary_variable(cur_idx.name);
                            cur_idx = get_next_tok();
                            if (cur_idx.type == DO) {
                                int cur_tok_idx = tok_idx;
                                for (;left < right; left++) {
                                    for (auto &variable : variables) {
                                        if (variable.name == name) {
                                            variable.val = left;
                                        }
                                    }
                                    do_block();
                                    tok_idx = cur_tok_idx;
                                }
                            }
                        } else {
                            cout << "Error: unexpected factor" << endl;
                        }
                    } else {
                        cout << "Error: can't found token 'TO'" << endl;
                    }
                }
                else if (cur_idx.type == LIST_NAME) {
                    list_found = true;
                    vector<int> list = get_list(cur_idx.name);
                    int cur_tok_idx = tok_idx;
                    for (int i : list) {
                        for (auto &variable : variables) {
                            if (variable.name == name) {
                                variable.val = i;
                            }
                        }
                        do_block();
                        tok_idx = cur_tok_idx;
                    }
                } else {
                    cout << "Error: unexpected factor" << endl;
                }
            } else {
                cout << "Error: can't found token 'IN'" << endl;
            }
        } else {
            cout << "Error: name variable failed" << endl;
        }
    } else {
        cout << "Error: can't found token 'FOR'" << endl;
    }
    if (!list_found) variables.push_back({name, right});
}

int parser::while_loop() {
    cur_idx = get_next_tok();
    if (cur_idx.type == WHILE) {
        int condition = comparison();
        if (condition == 1) {
            cur_idx = get_next_tok();
            if (cur_idx.type == DO) {
                do_block();
                tok_idx = 0;
                while_loop();
            } else {
                cout << "Error: can't not found the token 'DO' in while loop" << endl;
            }
        }
    }
    return 0;
}

void parser::make_var() {
    datatype name;
    int val;
    string var_name;
    auto tok = get_next_tok();
    if (tok.type == LET) {
        name = get_next_tok();
        if (name.type == TEMPORARY_MEMORY) {
            var_name = name.name;
        } else {
            cout << "Error: name variable failed" << endl;
        }
        tok = get_next_tok();
        if (tok.type == ASSIGN) {
            tok = get_next_tok();
            if (tok.type == INT) {
                tok_idx--;
                val = expr();
            } else if (tok.type == STRING) {
                cout << "Error: not support 'string' type in variable" << endl;
            } else {
                cout << "Error: type not found" << endl;
            }
        }
    }
    variables.push_back({var_name, val});
}

int parser::comparison() {
    auto left_token = get_next_tok();
    VerType OP = get_next_tok().type;
    auto right_token = get_next_tok();
    int left = 0;
    int right = 0;
    if (left_token.type == TEMPORARY_MEMORY) {
        string name = left_token.name;
        left = get_variable(name);
    } else if (left_token.type == INT) {
        left = left_token.value;
    } else if (left_token.type == PARAMATER) {
        left = get_tempotary_variable(left_token.name);
    } 
    else {
        cout << "Error: error type" << endl;
    }
    if (right_token.type == TEMPORARY_MEMORY) {
        string name = right_token.name;
        right = get_variable(name);
    } else if (right_token.type == INT) {
        right = right_token.value;
    } else if (right_token.type == PARAMATER) {
        right = get_tempotary_variable(right_token.name);
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
        case DIFFERENCES:
            return left != right ? 1 : 0;
    }
    return 0;
}

bool found_else = false;
bool found_elif = false;

int parser::condition() {
    int pos = tok_idx;
    cur_idx = get_next_tok();
    if (cur_idx.type == IF) {
        int check = comparison();
        if (check == 1 && get_next_tok().type == THEN) {
            do_block();
        } else if (check == 0 && get_next_tok().type == THEN) {
            while (tok_idx < tokenize.size()) {
                cur_idx = tokenize[tok_idx];
                if (cur_idx.type == ELSE) {
                    found_else = true;
                    break;
                } else if (cur_idx.type == ELIF) {
                    found_elif = true;
                    break;
                }
                tok_idx++;
            }
            if (found_elif) {
                tok_idx++;
                int elif_check = comparison();
                if (elif_check == 1 && get_next_tok().type == THEN) {
                    do_block();
                } else {
                    while (tok_idx < tokenize.size() && tokenize[tok_idx].type != ELSE && tokenize[tok_idx].type != ELIF) {
                        tok_idx++;
                    }
                    if (tokenize[tok_idx].type == ELSE) {
                        found_else = true;
                    }
                }
            }
            if (found_else) {
                tok_idx++;
                do_block();
            }
        } else {
            cout << "Error: condition failed" << endl;
        }
    }
    return 0;
}

void parser::print_func() {
    auto tok = get_next_tok();
    if (tok.type == PRINT) {
        auto next_tok = get_next_tok();
        if (next_tok.type == STRING) {
            cout << next_tok.name << endl;
        } else {
            tok_idx--;
            cout << expr() << endl;
        }
    }
}

void parser::do_block() {
    while (tok_idx < tokenize.size()) {
        cur_idx = tokenize[tok_idx];
        if (cur_idx.type == PRINT) {
            print_func();
            tok_idx++;
        } else if (cur_idx.type == LET) {
            make_var();
            tok_idx++;
        } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
            tok_idx++;
        } else if (cur_idx.type == IF) {
            condition();
            tok_idx++;
        } else if (cur_idx.type == LIST) {
            make_list();
            tok_idx++;
        } else if (cur_idx.type == FOR_LOOP) {
            for_loop();
            tok_idx++;
        } else if (cur_idx.type == WHILE) {
            while_loop();
            tok_idx++;
        } else if (cur_idx.type == FUNCTION_CALL) {
            call_function();
            tok_idx++;
        } else if (cur_idx.type == FUNCTION) {
            make_function();
            tok_idx++;
        } else {
            expr();
        }
    }
}

void parser::run_code() {
    while (tok_idx < tokenize.size()) {
        if (tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BIGGER 
        || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SMALLER
        || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == EQUAL
        || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == BE
        || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == SE
        || tokenize[tok_idx].type == INT && tokenize[tok_idx + 1].type == DIFFERENCES) {
            tok_idx = 0;
            cout << comparison() << endl;
            break;
        } else if (tokenize[tok_idx].type == PRINT) {
            print_func();
            break;
        } else if (tokenize[tok_idx].type == IF) {
            condition();
            break;
        } else if (tokenize[tok_idx].type == LET) {
            make_var();
            break;
        } else if (tokenize.empty()) {
            continue;
        } else if (tokenize[tok_idx].type == WHILE) {
            while_loop();
            break;
        } else if (tokenize[tok_idx].type == LIST) {
            make_list();
            break;
        } else if (tokenize[tok_idx].type == FOR_LOOP) {
            for_loop();
            break;
        } else if (tokenize[tok_idx].type == FUNCTION) {
            make_function();
            break;
        } else if (tokenize[tok_idx].type == FUNCTION_CALL) {
            call_function();
            break;
        } else {
            expr();
            break;
        }
    }
}