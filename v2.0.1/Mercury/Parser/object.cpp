#include <iostream>
#include <string>

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
    bool is_func_v;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
    bool iserrt;
    MerObject *objv;
};

MerObject *MerObject_new(void) {
    MerObject *obj = (MerObject *)malloc(sizeof(MerObject));
    obj->objtype = "";
    obj->file_name = "";
    obj->ovalue = 0;
    obj->is_mom = false;
    obj->mom_name = "";
    obj->mom_t = "";
    obj->iden = "";
    obj->rvalue = 0.0;
    obj->fvalue = 0.0;
    obj->svalue = "";
    obj->dvalue = 0.0;
    obj->bvalue = false;
    obj->args_value = 0.0;
    obj->args_type = "";
    obj->is_func_v = false;
    obj->is_constant = false;
    obj->is_args = false;
    obj->is_kwargs = false;
    obj->is_global = false;
    obj->iserrt = false;
    obj->objv = NULL;
    return obj;
}

int MerObject_free(MerObject *obj) {
    if (obj->iserrt) {
        return FAILURE
    }

    free(obj);
    return SUCCESS;
}