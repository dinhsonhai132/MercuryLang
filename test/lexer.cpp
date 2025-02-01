#include "lexer.h"

using namespace std;

vector<token> lexer::tokenize() {
    while (idx < source.length()) {
        char c = source[idx];

        if (isalpha(c)) {
            string iden = "";
            bool found = false;

            while (is_potential_identifier(c)) {
                c = source[idx];
                iden += c;
                idx++;

                if (iden == "LET") {
                    tokens.push_back(token(LET, NULL_T, 0.0, ""));
                    found = true;
                    break;
                } else if (iden == "PRINT") {
                    tokens.push_back(token(PRINT, NULL_T, 0.0, ""));
                    found = true;
                    break;
                } else if (iden == "IF") {
                    tokens.push_back(token(IF, NULL_T, 0.0, ""));
                    found = true;
                    break;
                } else if (iden == "ELSE") {
                    tokens.push_back(token(ELSE, NULL_T, 0.0, ""));
                    found = true;
                    break;
                } else if (iden == "FOR") {
                    tokens.push_back(token(FOR, NULL_T, 0.0, ""));
                    found = true;
                    break;
                } else if (iden == "WHILE") {
                    tokens.push_back(token(WHILE, NULL_T, 0.0, ""));
                    found = true;
                    break;
                }
            }

            if (!found) {
                tokens.push_back(token(VARIABLE, AUTO_T, 0.0, iden));
            }
        } else if (isdigit(c)) {
            string num = "";
            int dot_count = 0;
            while (isdigit(c) || c == '.') {
                if (c == '.') {
                    dot_count++;
                    if (dot_count > 1) {
                        break;
                    }
                }
                num += c;
                idx++;
                c = source[idx];
            }

            float num_value = atof(num.c_str());
            tokens.push_back(token(dot_count == 0 ? INT : FLOAT, dot_count == 0 ? INT_T : FLOAT_T, num_value, ""));
        } else if (c == '"') {
            string str = "";
            idx++;
            while (source[idx] != '"') {
                str += source[idx];
                idx++;
            }
            tokens.push_back(token(STRING, STRING_T, 0.0, str));
            idx++;
        } else if (is_keyword(c)) {
            char c2 = source[idx + 1];
            if (is_keyword(c2)) {
                tokens.push_back(token(get_2_char(c, c2), NULL_T, 0.0, ""));
                idx += 2;
            } else {
                tokens.push_back(token(get_1_char(c), NULL_T, 0.0, ""));
            }
        } else if (isskippable(c)) {
            idx++;
        } else {
            idx++;
        }
    }
    return tokens;
}