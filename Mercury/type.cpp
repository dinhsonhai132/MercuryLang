#include "./include/type.h"

int MerType_free(_type *type) {MER_PASS;}
int MerFunc_free(_func_object *func) {MER_PASS;}
int MerCode_free(_code *code) {MER_PASS;}
int MerObject_free(_object *obj) {MER_PASS;}
int MerPCode_free(_pcode *pcode) {MER_PASS;}
int MerVariable_free(_variable *var) {MER_PASS;}
int MerString_free(_string *str) {MER_PASS;}


_object *Merfunc_new(void) {
    _object *obj = Merobject_new();
    obj->type->func->args = vector<void*>(0);
    obj->type->func->size = 0;
    obj->type->func->ui8_address = 0;
    obj->type->func->ui16_address = 0;
    obj->type->func->ui32_address = 0;
    obj->type->func->f_bc = NULL_OPCODE_PTR;
    obj->type->func->fs_bc = NULL_OPCODE_PTR;
    obj->type->func->args_size = 0;
    obj->type->func->name = NULL_MER_STRING;
    obj->type->func->real_name = NULL_MER_STRING;
    obj->type->func->sf = NULL_PTR;
    obj->type->func->_is_global = 0;
    obj->type->func->_is_local = 0;
    obj->type->func->_return = 0;
    return obj;
}
_object *Merobject_new(void) {
    _object *obj = new _object();
    obj->type = NULL_PTR;
    obj->data_type = NULL_PTR;
    obj->value = NULL_PTR;
    obj->file_name = NULL_PTR;
    obj->name = NULL_PTR;
    obj->code = NULL_PTR;
    return obj;
}
_object *Mercode_new(void) {
    _object *obj = new _object();
    obj->type = NULL_PTR;
    obj->data_type = NULL_PTR;
    obj->value = NULL_PTR;
    obj->file_name = NULL_PTR;
    obj->name = NULL_PTR;
    obj->code = NULL_PTR;
    return obj;
}
_object *Merpcode_new(void) {MER_PASS;}
_object *Merstring_new(void) {MER_PASS;}
_object *Mervariable_new(void) {MER_PASS;}
_object *Mertype_new(void) {MER_PASS;}