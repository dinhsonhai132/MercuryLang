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

int MerObject_free(MerObject *obj) {
    if (obj) {
        obj->file_name.clear();
        obj->objtype.clear();
        obj->mom_name.clear();
        obj->mom_t.clear();
        obj->iden.clear();
        obj->svalue.clear();
        obj->args_type.clear();
        delete obj;
    }
    return _SUCCESS;    
}

MerCodeFObject MerCodeFObject_new(void) {
    MerCodeFObject obj = MerCodeFObject();
    obj.code.clear();
    obj.body.clear();
    obj.address = 0x0000;
    obj.funcv.clear();
    return obj;
}

int MerCodeFObject_free(MerCodeFObject *obj) {
    if (obj) {
        obj->code.clear();
        obj->body.clear();
        obj->funcv.clear();
        delete obj;
    }
    return _SUCCESS;    
}

MerCodeObject *MerCodeObject_new(void) {
    MerCodeObject *obj = new MerCodeObject();
    obj->buff.clear();
    obj->funcv = MerCodeFObject_new();
    return obj;
}

int MerCodeObject_free(MerCodeObject *obj) {
    if (obj) {
        obj->buff.clear();
        MerCodeFObject_free(&obj->funcv);
        delete obj;
    }
    return _SUCCESS;    
}