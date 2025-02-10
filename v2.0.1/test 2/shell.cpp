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

#include <iostream>
#include "error.h"
using namespace std;

int main(int argc, char *argv[])
{
    throw Mer_RuntimeError("Hello World!");
    return 0;
}