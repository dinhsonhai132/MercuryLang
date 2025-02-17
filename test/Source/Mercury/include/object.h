#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <vector>
using namespace std;

struct MerObject {
    AST_node *node;
    
    string file_name;
    string objtype;

    bool is_mom;
    string mom_name;
    string mom_t;

    string iden;
    float rvalue;
    float fvalue;
    string svalue;
    double dvalue;
    bool bvalue;

    float args_value;
    string args_type;
    bool is_func_v;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
};

#endif