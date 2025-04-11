#include "./include/object.h"

MerObject MerObject_new(void) {
    MerObject obj = MerObject();
    obj.objtype = "";
    obj.file_name = "";
    obj.ovalue = 0;
    obj.is_mom = false;
    obj.mom_name = "";
    obj.mom_t = "";
    obj.iden = "";
    obj.rvalue = 0.0;
    obj.fvalue = 0.0;
    obj.svalue = "";
    obj.dvalue = 0.0;
    obj.bvalue = false;
    obj.args_value = 0.0;
    obj.args_type = "";
    obj.is_func_v = false;
    obj.is_constant = false;
    obj.is_args = false;
    obj.is_kwargs = false;
    obj.is_global = false;
    obj.iserrt = false;
    obj.objv = NULL;
    return obj;
}

MerCodeFObject MerCodeFObject_new(void) {
    MerCodeFObject obj = MerCodeFObject();
    obj.code.clear();
    obj.body.clear();
    obj.address = 0x0001;
    return obj;
}

MerCodeObject *MerCodeObject_new(void) {
    MerCodeObject *obj = (MerCodeObject *)malloc(sizeof(MerCodeObject));
    obj->buff.clear();
    obj->funcv = MerCodeFObject_new();
    return obj;
}