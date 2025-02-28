#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <iostream>

#include "eval.h"
#include "envi.h"
#include "object.h"
#include "C:\Users\dinhs\Documents\Program Language\Mercury-Langluage-main\Mercury-Langluage-main\v2.0.1\test\Source\Parser\parser.h"

using namespace std;

#define MAX_LINE 1024
#define MAX_ELEMENTS 1024

struct ListObject {
    MerObject *name;
    MerObject *eles[MAX_ELEMENTS];
    string dt;
};

RunTimeVal MerShell_repl(string source);
RunTimeVal MerShell_repl_file(string file_name);

#endif