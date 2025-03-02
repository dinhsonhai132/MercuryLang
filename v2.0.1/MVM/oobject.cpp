#include "./include/oobject.h"

Object *MerOobject_new(void) {
    Object *obj = (Object *)malloc(sizeof(Object));
    obj->file_name = "";
    obj->objtype = "";
    obj->ovalue = 0;
    obj->is_mom = false;
    obj->mom_name = "";
    obj->mom_t = "";
    obj->iden = "";
    obj->type = "";
    obj->vname = "";
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
    obj->objv = NULL;
}

int Mer_free_oobject(Object *obj) {
    free(obj);
    return 0;
}