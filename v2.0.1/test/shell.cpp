#include "./parser/lexer/lexer.h"
#include "./parser/lexer/ast.h"
#include "./parser/parser.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main(int argc, char **argv) {
    string source = "1 + 1";
    vector<token> tokens = MerLexer_tokenize(source);
    for (token t : tokens) {
        cout << t.tok << endl;
    }
    return 0;
}