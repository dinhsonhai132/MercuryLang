#ifndef MERCURY_COMPILER_HEADER_FILE
#define MERCURY_COMPILER_HEADER_FILE

#include <string>
#include <vector>
#include <iostream>

#include "stack.h"

using namespace std;

int push(Stack *stk, Object *value);
int pop(Stack *stk);
int eval(Stack *stk, string code);

#endif