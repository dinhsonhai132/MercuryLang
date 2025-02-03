/*
------------------------------------------------------------
-- Mercury Language - Core Header File              --------
------------------------------------------------------------
-- Repository: https://github.com/dinhsonhai132/Mercury-Langluage
-- Author: dinhsonhai132
------------------------------------------------------------
-- This is the heart of the Mercury interpreter
-- This take all the ast token from parser.h and execute it
-- This file also store variables, functions, etc...
------------------------------------------------------------
*/

#ifndef CORE_H
#define CORE_H

#include "ast.h"
#include "run.h"

using namespace std;    

#define _Null "_Null"
#define _Auto "_Auto"
#define _Number "_Number"

struct RunTimeVal {
    string type;
};

struct NullVal : RunTimeVal {
    string type = _Null;
    float value = NULL;
};

struct NumberVal : RunTimeVal {
    string type = _Number;
    float value;
};

RunTimeVal evaluate(statement stmt);

#endif