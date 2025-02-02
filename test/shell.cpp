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

#include "./Source/Token/parse.cpp"
#include "./Source/Token/lexer.cpp"
#include "./Source/Token/ast.cpp"
#include "./Source/Core/core.cpp"
#include "./Source/Core/run.cpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "MercuryLang v2.0.1" << endl;
    while (true) {
        cout << ">> ";
        string input;
        getline(cin, input);
        if (input == "exit") break;
    }
    return 0;
}