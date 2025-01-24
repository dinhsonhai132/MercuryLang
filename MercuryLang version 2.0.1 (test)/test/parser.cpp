#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <variant>
#include "lexer.cpp"
using namespace std;

class parser {
private:
    size_t tok_idx;
    datatype cur_idx;
    vector<datatype> tokenize;
    string var;
    int val;
public:
    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0) {}

    int get_tempotary_variable(string name) {
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

    auto get_variable(string name) {
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

    store_var get_variable_data(string name) {
        for (auto &variable: variables) {
            if (variable.name == name) {
                return variable;
            }
        }
        return {"", AUTO, 0};
    }

    vector<int> get_list(string name) {
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

    auto extract() {
        auto tok = get_next_tok();
        if (tok.type == LIST_NAME) {
            auto list = get_list(tok.name);
            tok = get_next_tok();
            if (tok.type == ARROW_TOKEN) {
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
            cout << "Error: can't ARROW_TOKEN the value from the list" << endl;
        }
        return 0;
    }

    vector<int> get_tempotary_list(string name) {
        bool found = false;
        for (auto &list : tempotary_list) {
            if (list.name == name) {
                found = true;
                return list.list;
            }
        } 
        if (!found) {
            cout << "Error: can't found the list" << endl;
        }
        return {};
    }

    auto extract_tempotary_list() {
        auto tok = get_next_tok();
        if (tok.type == PARAMATER_KWARGS) {
            auto list = get_tempotary_list(tok.name);
            tok = get_next_tok();
            if (tok.type == ARROW_TOKEN) {
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
            cout << "Error: can't ARROW_TOKEN the value from the list" << endl;
        }
        return 0;
    }

    datatype get_next_tok() {
        if (tok_idx < tokenize.size()) {
            return tokenize[tok_idx++];
        }
        return {NONE, 0, ""};
    }

    datatype get_next_tok_to(int s) {
        if (tok_idx < tokenize.size()) {
            tok_idx += s;
            return tokenize[tok_idx];
        }
        return {NONE, 0, ""};
    }

    void update_pp() {
        cur_idx = get_next_tok();
        if (cur_idx.type == TEMPORARY_MEMORY) {
            for (auto &variable: variables) {
                if (variable.name == cur_idx.name) {
                    switch (variable.type) {
                        case INT_TYPE: variable.val += 1; break;
                        case FLOAT_TYPE: variable.float_val += 1; break;
                    }
                }
            }
        } else if (cur_idx.type == INT) {
            cur_idx.value += 1;
        }
    }

    void update_mm() {
        cur_idx = get_next_tok();
        if (cur_idx.type == TEMPORARY_MEMORY) {
            for (auto &variable: variables) {
                if (variable.name == cur_idx.name) {
                    switch (variable.type) {
                        case INT_TYPE: variable.val += 1; break;
                        case FLOAT_TYPE: variable.float_val += 1; break;
                    }
                }
            }
        } else if (cur_idx.type == INT) {
            cur_idx.value -= 1;
        }
    }
    
    float factor() {
        cur_idx = get_next_tok();
        if (cur_idx.type == INT) {
            int left = cur_idx.value;
            if (tokenize[tok_idx].type == DOT) {
                tok_idx++;
                cur_idx = get_next_tok();
                if (cur_idx.type == INT) {
                    int right = cur_idx.value;
                    float result = left + right / pow(10, to_string(right).length());
                    return result;
                } else {
                    cout << "Error: Expected integer after dot" << endl;
                    return 0;
                }
            } else {
                return left;
            }
        } else if (cur_idx.type == INT && tokenize[tok_idx + 1].type != DOT) {
            return cur_idx.value;
        } else if (cur_idx.type == TEMPORARY_MEMORY) {
            auto variable = get_variable_data(cur_idx.name);
            if (variable.type == FLOAT_TYPE) {
                return variable.float_val;
            } else if (variable.type == DOUBLE_TYPE) {
                return variable.double_val;
            } else if (variable.type == AUTO) {
                return variable.val;
            } else if (variable.type == INT_TYPE) {
                return variable.val;
            }
        } else if (cur_idx.type == PARAMATER) {
            return get_tempotary_variable(cur_idx.name);
        } else if (cur_idx.type == PP) {
            update_pp();
        } else if (cur_idx.type == MM) {
            update_mm();
        } else if (cur_idx.type == LIST_NAME) {
            tok_idx--;
            return extract();
        } else if (cur_idx.type == PARAMATER_KWARGS) {
            tok_idx--;
            return extract_tempotary_list();
        } else if (cur_idx.type == NONE || cur_idx.type == COMMA) {
            tok_idx++;
        }
        return 0;
    }   

    float term() {
        float result = factor();
        while (true) {
            cur_idx = get_next_tok();
            if (cur_idx.type == DIV) {
                float divisor = factor();
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

    float expr() {
        float result = term();
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

    void make_list() {
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
                        while (tok_idx < tokenize.size() && tokenize[tok_idx].type != SPARE_RP) {
                            if (tokenize[tok_idx].type == INT) {
                                the_list.push_back(tokenize[tok_idx].value);
                                tok_idx++;
                            } else if (tokenize[tok_idx].type == COMMA) {
                                tok_idx++;
                            }
                        }
                    }
                } else {
                    cout << "Error: Expected '=' after list name" << endl;
                }
            } else {
                cout << "Error: Expected list name after 'LIST'" << endl;
            }
        }

        if (!name.empty()) {
            lists.push_back({name, the_list});
        } else {
            cout << "Error: can't create the list" << endl;
        }
    }

    void make_function() {
        cur_idx = get_next_tok();
        string name_func;
        vector<Parameter> paras;
        Parameter_kwargs paras_kwargs;
        vector<datatype> store_tokens;
        bool list_found = false;
        if (cur_idx.type == FUNCTION) {
            name_func = cur_idx.name;
            cur_idx = get_next_tok();
            if (cur_idx.type == LP) {
                auto next_tok = tokenize[tok_idx + 1];
                if (next_tok.type == PARAMATER_KWARGS) {
                    paras_kwargs = {next_tok.name, {}, AUTO};
                    cur_idx = get_next_tok_to(2);
                    if (cur_idx.type != RP) {
                        cout << "Error: Expected ')' after parameter" << endl;
                    }
                    list_found = true;
                } else if (next_tok.type == RP) {
                    cur_idx = get_next_tok();
                } else {
                    while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                        cur_idx = tokenize[tok_idx];
                        if (cur_idx.type == PARAMATER && tokenize[tok_idx + 1].type != PARAMATER) {
                            paras.push_back({cur_idx.name, 0, AUTO});
                            tok_idx++;
                        } else if (cur_idx.type == COMMA) {
                            tok_idx++;
                        }
                    }
                }

                cur_idx = get_next_tok();
                if (cur_idx.type == DO) {
                    while (tok_idx < tokenize.size()) {
                        store_tokens.push_back(cur_idx);
                        cur_idx = tokenize[tok_idx++];
                    }
                }

            } else {
                cout << "Error: Expected '(' after function name" << endl;
            }
        } else {
            cout << "Error: Expected 'FUNC' after function name" << endl;
        }

        if (list_found) {
            functions.push_back({name_func, AUTO, 0, {}, store_tokens, paras_kwargs, true});
        } else {
            functions.push_back({name_func, AUTO, 0, paras, store_tokens, {}, false});
        }
    }

    function_ get_function(string name) {
        for (auto &func : functions) {
            if (func.function_name == name) {
                return func;
            }
        }
        return {};
    }

    auto execute(string function_name) {
        auto func = get_function(function_name);
        auto paras = func.Parameters;
        auto tokens = func.store_tokens;
        auto paras_kwargs = func.parameter_kwargs;

        if (tokens.empty()) {
            cout << "Error: can't found the function" << endl;
            return 0;
        }

        int cur_tok_idx = tok_idx;
        auto cur_tokens = tokenize;

        if (!func.parameter_kwargs_found) {
            for (auto &para : paras) {
                tempotary_variables.push_back({para.name, NULL_TYPE, para.val});
            }
        } else {
            tempotary_list.push_back({paras_kwargs.name, paras_kwargs.vec});
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
            } else if (cur_idx.type == IMPORT) {
                cout << "Error: can't import the file in the function" << endl;
            } else {
                expr();
            }
        }
        tempotary_variables = {};
        tempotary_list = {};
        tokenize = cur_tokens;
        tok_idx = cur_tok_idx;
        return 0;
    }

    float call_function() {
        cur_idx = get_next_tok();
        string name;
        vector<int> values;
        vector<int> kwargs;
        vector<Parameter> paras;
        Parameter_kwargs paras_kwargs;
        bool check_kwarg_func;
        if (cur_idx.type == FUNCTION_CALL) {
            name = cur_idx.name;
            cur_idx = get_next_tok();
            if (cur_idx.type == LP) {
                function_ func = get_function(name);
                paras = func.Parameters;
                check_kwarg_func = func.parameter_kwargs_found;
                if (check_kwarg_func) {
                    while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                        if (cur_idx.type == INT) {
                            kwargs.push_back(cur_idx.value);
                        } else if (cur_idx.type == TEMPORARY_MEMORY) {
                            kwargs.push_back(get_variable(cur_idx.name));
                        } else if (cur_idx.type == PARAMATER) {
                            kwargs.push_back(get_tempotary_variable(cur_idx.name));
                        }
                        cur_idx = tokenize[tok_idx++];
                    }
                    func.parameter_kwargs = {func.parameter_kwargs.name, kwargs, AUTO};
                } else {
                    while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                        if (cur_idx.type == INT) {
                            values.push_back(cur_idx.value);
                        } else if (cur_idx.type == TEMPORARY_MEMORY) {
                            values.push_back(get_variable(cur_idx.name));
                        } else if (cur_idx.type == PARAMATER) {
                            values.push_back(get_tempotary_variable(cur_idx.name));
                        }
                        cur_idx = tokenize[tok_idx++];
                    }
                    for (int i = 0; i < paras.size(); i++) {
                        paras[i].val = values[i];
                    }

                    for (auto &func : functions) {
                        if (func.function_name == name) {
                            func.Parameters = paras;
                        }
                    }
                }

                int pos = tok_idx;
                execute(name);
                tok_idx = pos;

            } else {
                cout << "Error: Expected '(' after function name" << endl;
            }
        }
        return 0;
    }

    void for_loop() {
        cur_idx = get_next_tok();
        int left, right;
        string name;
        bool list_found = false;
        if (cur_idx.type == FOR_LOOP) {
            cur_idx = get_next_tok();
            if (cur_idx.type == TEMPORARY_MEMORY) {
                name = cur_idx.name;
                variables.push_back({name, INT_TYPE, 0});
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
                    } else if (cur_idx.type == PARAMATER_KWARGS) {
                        list_found = true;
                        vector<int> list = get_tempotary_list(cur_idx.name);
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
        if (!list_found) variables.push_back({name, INT_TYPE, right});
    }

    vector<store_var> store_variables() {
        vector<store_var> vars;
        Mercury_type type;
        bool found = false;
        int cur_tok_idx = tok_idx;
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == LET) {
                cur_idx = get_next_tok();
                if (cur_idx.type == FLOAT) {
                    type = FLOAT_TYPE;
                    found = true;
                } else if (cur_idx.type == INT) {
                    type = INT_TYPE;
                    found = true;
                } else if (cur_idx.type == STR) {
                    type = STRING_TYPE;
                    found = true;
                } else if (cur_idx.type == DOUBLE) {
                    type = DOUBLE_TYPE;
                    found = true;
                }
                
                if (found) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == TEMPORARY_MEMORY) {
                        string name = cur_idx.name;
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (type == STRING_TYPE) {
                                string string_val = cur_idx.name;
                                vars.push_back({name, type, 0, string_val});
                            } else if (type == INT_TYPE) {
                                tok_idx--;
                                int val = expr();
                                vars.push_back({name, type, val});
                            } else if (type == FLOAT_TYPE) {
                                tok_idx--;
                                float val = expr();
                                vars.push_back({name, type, 0, "", false, '\0', val});
                            } else if (type == DOUBLE_TYPE) {
                                tok_idx--;
                                double val = expr();
                                vars.push_back({name, type, 0, "", false, '\0', 0, val});
                            }
                        } else {
                            vars.push_back({name, type});
                        }
                    }
                }
            }
            cur_idx = tokenize[tok_idx++];
        }
        tok_idx = cur_tok_idx;
        return vars;
    }

    vector<store_list> store_lists() {
        vector<store_list> lists;
        string name;
        vector<int> the_list;
        int cur_tok_idx = tok_idx;
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == LIST) {
                cur_idx = get_next_tok();
                if (cur_idx.type == LIST_NAME) {
                    name = cur_idx.name;
                    cur_idx = get_next_tok();
                    if (cur_idx.type == ASSIGN) {
                        cur_idx = get_next_tok();
                        if (cur_idx.type == SPARE_LP) {
                            while (tok_idx < tokenize.size() && tokenize[tok_idx].type != SPARE_RP) {
                                if (tokenize[tok_idx].type == INT) {
                                    the_list.push_back(tokenize[tok_idx].value);
                                    tok_idx++;
                                } else if (tokenize[tok_idx].type == COMMA) {
                                    tok_idx++;
                                }
                            }
                        }
                    } else {
                        lists.push_back({name, the_list});
                    }
                }
            }
            cur_idx = tokenize[tok_idx++];
        }
        tok_idx = cur_tok_idx;
        return lists;
    }

    vector<function_> store_functions() {
        vector<function_> funcs;
        string name_func;
        vector<Parameter> paras;
        Parameter_kwargs paras_kwargs;
        vector<datatype> store_tokens;
        bool found = false;
        int cur_tok_idx = tok_idx;
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == FUNCTION) {
                name_func = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == LP) {
                    if (tokenize[tok_idx + 1].type == PARAMATER_KWARGS) {
                        paras_kwargs = {tokenize[tok_idx + 1].name, {}, AUTO};
                        found = true;
                    } else {
                        while (tok_idx < tokenize.size() && cur_idx.type != RP) {
                            if (cur_idx.type == PARAMATER) {
                                paras.push_back({cur_idx.name, 0, AUTO});
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
                    cout << "Error: Expected '(' after function name" << endl;
                }
            }
            else {
                cout << "Error: Expected 'FUNC' after function name" << endl;
            }
            funcs.push_back({name_func, AUTO, 0, paras, store_tokens, paras_kwargs, found});
            cur_idx = tokenize[tok_idx++];
        }
        tok_idx = cur_tok_idx;
        return funcs;
    }

    void make_class() {
        cur_idx = get_next_tok();
        vector<store_list> class_lists;
        vector<store_var> class_variables;
        vector<function_> class_functions;
        if (cur_idx.type == CLASS) {
            cur_idx = get_next_tok();
            if (cur_idx.type == TEMPORARY_MEMORY) {
                string name = cur_idx.name;
                user_datatype.push_back(name);
                cur_idx = get_next_tok();
                if (cur_idx.type == DO) {
                    class_lists = store_lists();
                    class_variables = store_variables();
                    class_functions = store_functions();
                }
            }
        }
        moms.push_back({cur_idx.name, class_variables, class_lists, class_functions});
    }

    void make_struct() {
        cur_idx = get_next_tok();
        vector<store_list> struct_lists;
        vector<store_var> struct_variables;
        string struct_name;
        Mercury_type type;
        if (cur_idx.type == STRUCT) {
            cur_idx = get_next_tok();
            if (cur_idx.type == TEMPORARY_MEMORY) {
                struct_name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == DO) {
                    
                }
            }   
        }
        moms.push_back({struct_name, struct_variables, struct_lists});
    }

    function_ get_func_in_mom(string name_func, string name_mom) {
        for (auto &mom : moms) {
            if (mom.class_name == name_mom) {
                for (auto &func : mom.functions) {
                    if (func.function_name == name_func) {
                        return func;
                    }
                }
            }
        }
        return {};
    }

    auto execute_in_mom(string name_func, string name_mom) {
        function_ func = get_func_in_mom(name_func, name_mom);
        vector<datatype> tokens = func.store_tokens;
        vector<Parameter> paras = func.Parameters;
        Parameter_kwargs paras_kwargs = func.parameter_kwargs;

        if (tokens.empty()) {
            cout << "Error: can't found the function" << endl;
            return 0;
        }
        int cur_tok_idx = tok_idx;
        vector<datatype> cur_tokens = tokenize;

        if (!paras.empty()) {
            for (auto &para : paras) {
                tempotary_variables.push_back({para.name, NULL_TYPE, para.val});
            }
        } else {
            tempotary_list.push_back({paras_kwargs.name, paras_kwargs.vec});
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
            } else if (cur_idx.type == IMPORT) {
                cout << "Error: can't import the file in the function" << endl;
            } else {
                expr();
            }
        }
        tempotary_variables = {};
        tempotary_list = {};
        tokenize = cur_tokens;
        tok_idx = cur_tok_idx;
        return 0;
    }

    mom_type get_mom(string name) {
        for (auto &son : moms) {
            if (son.class_name == name) {
                return son;
            }
        }
        return {};
    }

    int take_value() {
        cur_idx = get_next_tok();
        if (cur_idx.type == USER_TYPE) {
            auto son = get_mom(cur_idx.name);
            cur_idx = get_next_tok();
            if (cur_idx.type == ARROW_TOKEN) {
                cur_idx = get_next_tok();
                if (cur_idx.type == TEMPORARY_MEMORY) {
                    string name = cur_idx.name;
                    for (auto &var : son.variables) {
                        if (var.name == name) {
                            switch (var.type) {
                                case INT_TYPE: return static_cast<float>(var.val);
                                case FLOAT_TYPE: return var.float_val;
                                case DOUBLE_TYPE: return var.double_val;
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }

    void make_enum() {
        cur_idx = get_next_tok();
        vector<enumerate> enummerates;
        if (cur_idx.type == ENUM) {
            cur_idx = get_next_tok();
            if (cur_idx.type == TEMPORARY_MEMORY) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == DO) {
                    int orders = 0;
                    while (tok_idx < tokenize.size() && tokenize[tok_idx].type != END) {
                        cur_idx = tokenize[tok_idx];
                        if (cur_idx.type == TEMPORARY_MEMORY && tokenize[tok_idx + 1].type != ASSIGN) {
                            enummerates.push_back({cur_idx.name, orders});
                            orders++;
                        } else if (cur_idx.type == TEMPORARY_MEMORY && tokenize[tok_idx + 1].type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == ASSIGN) {
                                cur_idx = get_next_tok();
                                if (cur_idx.type == INT) {
                                    enummerates.push_back({cur_idx.name, orders, cur_idx.value});
                                    orders++;
                                } else {
                                    cout << "Error: can't found the value of the enum" << endl;
                                }
                            }
                        }
                        tok_idx++;
                    }
                } else {
                    cout << "Error: can't found the token 'DO' in enum" << endl;
                }
            } else {
                cout << "Error: can't found the name of the enum" << endl;
            }
        }
        the_enums.push_back({cur_idx.name, enummerates});
    }

    int while_loop() {
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

    void make_var() {
        string var_name;
        Mercury_type type;
        bool found = false;
        auto tok = get_next_tok();
        if (tok.type == LET) {
            cur_idx = get_next_tok();
            if (cur_idx.type == NUM_TYPE) {
                type = INT_TYPE;
                found = true;
            } else if (cur_idx.type == FLOAT) {
                type = FLOAT_TYPE;
                found = true;
            } else if (cur_idx.type == STR) {
                type = STRING_TYPE;
                found = true;
            } else if (cur_idx.type == DOUBLE) {
                type = DOUBLE_TYPE;
                found = true;
            }
            
            if (found) {
                cur_idx = get_next_tok();
                if (cur_idx.type == TEMPORARY_MEMORY) {
                    var_name = cur_idx.name;
                    cur_idx = get_next_tok();
                    if (cur_idx.type == ASSIGN) {
                        cur_idx = get_next_tok();
                        if (type == STRING_TYPE) {
                            string string_val = cur_idx.name;
                            variables.push_back({var_name, type, 0, string_val});
                        } else if (type == INT_TYPE) {
                            tok_idx--;
                            int val = expr();
                            variables.push_back({var_name, type, val});
                        } else if (type == FLOAT_TYPE) {
                            tok_idx--;
                            float val = expr();
                            variables.push_back({var_name, type, 0, "", false, '\0', val});
                        } else if (type == DOUBLE_TYPE) {
                            tok_idx--;
                            double val = expr();
                            variables.push_back({var_name, type, 0, "", false, '\0', 0, val});
                        }
                    } else {
                        variables.push_back({var_name, type});
                    }
                } else {
                    cout << "Error: can't found the variable name" << endl;
                }
            } else {
                cout << "Error: can't found the type" << endl;
            }
        }
    }

    int comparison() {
        auto left_token = get_next_tok();
        auto OP = get_next_tok().type;
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

    int condition() {
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

    string string_print_output() {
        string string_output = "";
        while (tok_idx < tokenize.size()) {
            cur_idx = tokenize[tok_idx];
            if (cur_idx.type == STRING) {
                string_output += cur_idx.name;
            } else if (cur_idx.type == PLUS) {
                continue;
            } else {
                break;
            }
            tok_idx++;
        }
        return string_output;
    }

    void print_func() {
        auto tok = get_next_tok();
        if (tok.type == PRINT) {
            auto next_tok = get_next_tok();
            if (next_tok.type == STRING) {
                tok_idx--;
                cout << string_print_output() << endl;
            } else {
                tok_idx--;
                cout << expr() << endl;
            }
        }
    }

    void do_block() {
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
            } else if (cur_idx.type == POP) {
                pop();
                tok_idx++;
            } else if (cur_idx.type == PUSH) {
                push();
                tok_idx++;
            } else if (cur_idx.type == REPAIR) {
                repair();
                tok_idx++;
            } else {
                expr();
            }
        }
    }

    void pop() {
        cur_idx = get_next_tok();
        if (cur_idx.type == POP) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int order = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    }
                } else if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int erase_element = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int erase_element = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int erase_element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (cur_idx.type == PARAMATER_KWARGS) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int order = get_tempotary_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.erase(list.list.begin() + order - 1);
                            }
                        }
                    }
                } else if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int erase_element = cur_idx.value;
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int erase_element = get_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int erase_element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                for (int i = 0; i < list.list.size(); i++) {
                                    if (list.list[i] == erase_element) {
                                        list.list.erase(list.list.begin() + i);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void push() {
        cur_idx = get_next_tok();
        if (cur_idx.type == PUSH) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int element = cur_idx.value;
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int element = get_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : lists) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    }
                }
            } else if (cur_idx.type == PARAMATER_KWARGS) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == ARROW_TOKEN) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int element = cur_idx.value;
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int element = get_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    } else if (cur_idx.type == PARAMATER) {
                        int element = get_tempotary_variable(cur_idx.name);
                        for (auto &list : tempotary_list) {
                            if (list.name == name) {
                                list.list.push_back(element);
                            }
                        }
                    }
                }
            }
        }
    }

    void repair() {
        cur_idx = get_next_tok();
        if (cur_idx.type == REPAIR) {
            cur_idx = get_next_tok();
            if (cur_idx.type == LIST_NAME) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : lists) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (cur_idx.type == PARAMATER_KWARGS) {
                string name = cur_idx.name;
                cur_idx = get_next_tok();
                if (cur_idx.type == AT) {
                    cur_idx = get_next_tok();
                    if (cur_idx.type == INT) {
                        int order = cur_idx.value;
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    } else if (cur_idx.type == TEMPORARY_MEMORY) {
                        int order = get_variable(cur_idx.name);
                        cur_idx = get_next_tok();
                        if (cur_idx.type == ASSIGN) {
                            cur_idx = get_next_tok();
                            if (cur_idx.type == INT) {
                                int element = cur_idx.value;
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == TEMPORARY_MEMORY) {
                                int element = get_variable(cur_idx.name);
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            } else if (cur_idx.type == PARAMATER) {
                                int element = get_tempotary_variable(cur_idx.name);
                                for (auto &list : tempotary_list) {
                                    if (list.name == name) {
                                        list.list[order - 1] = element;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void run_code() {
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
            } else if (tokenize[tok_idx].type == PUSH) {
                push();
                break;
            } else if (tokenize[tok_idx].type == POP) {
                pop();
                break;
            }  else if (cur_idx.type == REPAIR) {
                repair();
                break;
            } else if (cur_idx.type == CLASS) {
                make_class();
                break;
            }  else if (cur_idx.type == STRUCT) {
                make_struct();
                break;
            } else if (cur_idx.type == ENUM) {
                make_enum();
                break;
            } else if (cur_idx.type == USER_TYPE) {
                take_value();
                break;
            } else {
                expr();
                break;
            }
        }
    }
};