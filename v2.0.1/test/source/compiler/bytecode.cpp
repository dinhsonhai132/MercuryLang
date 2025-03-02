#ifndef BYTECODE_H
#define BYTECODE_H

#include <iostream>
#include <vector>
using namespace std;

#define PUSH 0
#define POP 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define PRINT 7
#define RETURN 8
#define START 9
#define END 10

typedef struct MERCURY_BYTE_CODE {
    char* tem;
    char* code;
    int line;
} bytecode;

#endif