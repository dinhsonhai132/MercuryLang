#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "parser.h"
using namespace std;

class lexer {

private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
    
public:
    void advance();
    void advance_to(int a);
    vector<datatype> token();
    lexer(string input) : input(input), pos(0) {}
};

#endif