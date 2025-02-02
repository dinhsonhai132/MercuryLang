/*
------------------------------------------------------------
-- Mercury Language - Shell File                          --
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This is the terminal of Mercury Language
-- This is file you use to run code
------------------------------------------------------------
*/

#include "parse.h"
#include "lexer.h"
#include "ast.h"
#include "core.h"
#include "run.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "MercuryLang v2.0.1" << endl;
    while (true) {
        cout << ">> ";
        string input;
        getline(cin, input);
        parser program = parse(input).AST_tokenize();
        if (input == "exit") break;
    }
    return 0;
}