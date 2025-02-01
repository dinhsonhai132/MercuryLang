#include "ast.h"
#include "lexer.h"
#ifndef PARSE
#define PARSE

using namespace std;
class parse {
private:
    vector<token> tokens;
    lexer lex;
public:
    parse(string source) : source(source), lex(lex) {}

    program ast_tokenize() {
        vector<token> tokens = lex.tokenize(source);
        
    }
}

#endif