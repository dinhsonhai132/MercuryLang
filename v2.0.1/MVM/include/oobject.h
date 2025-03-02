#ifndef MERCURY_OBJECT_HEADER_FILE
#define MERCURY_OBJECT_HEADER_FILE
#include <string>
using namespace std;

#define SUCCESS 0
#define FAILURE 1
#define NNONE 100;

struct Object {
    string file_name;
    string objtype;
    int ovalue;

    bool is_mom;
    string mom_name;
    string mom_t;

    string iden;
    string type;
    string vname;

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

    Object *objv;
    int something_missing;
};

Object *MerOobject_new(void);
int Mer_free_oobject(Object *obj);

#endif