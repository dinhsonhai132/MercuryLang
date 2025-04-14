#ifndef MERCURY_OBJECT_HEADER_FILE
#define MERCURY_OBJECT_HEADER_FILE

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdint>

using namespace std;

#define SUCCESS 0;
#define FAILURE 1;

struct MerObject {
    
    string file_name;
    string objtype;
    int ovalue;

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
    string func_name;
    bool is_func_v;
    bool is_return;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
    bool iserrt;
    MerObject *objv;
};

struct MerCodeFObject {
    vector<uint8_t> code;
    vector<uint8_t> body;
    MerObject objv;
    uint32_t address;
    vector<MerCodeFObject> funcv;
};

struct MerCodeObject {
    vector<uint8_t> buff;
    MerCodeFObject funcv;
};

MerObject MerObject_new(void);
MerCodeFObject MerCodeFObject_new(void);
MerCodeObject *MerCodeObject_new(void);

struct mObject_T {
    string file_name;

    string objtype;
    int ovalue;      // the main value of object like true will be 1 and false will be 0

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
    string func_name;
    bool is_func_v;
    bool is_return;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
    bool iserrt;

    mObject_T *objv;
};

struct mCodeF_T {
    vector<uint8_t> body;
    mObject_T objv;
    uint32_t address;
    vector<mCodeF_T*> funcv;
};

struct mCode_T {
    vector<uint8_t> buff;
    uint8_t c;
    uint8_t nc;
    uint8_t add;
    uint8_t byte;
    vector<mCodeF_T*> funcv;
    vector<mCode_T*> code;
};

#endif // MERCURY_OBJECT_HEADER_FILE