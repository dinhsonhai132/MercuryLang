#include "../include/type.h"

_val *MerCompiler_val_new(void) {
    _val *v = new _val;
    v->value_t.int_value = 0;
    v->value_t.float_value = 0.0;
    v->value_t.bool_value = false;
    v->value_t.char_value = NULL_CHAR;
    v->value_t.string_value = "";
    v->value_t.long_value = 0;
    v->value_t.byte_value = NULL_UINT_8_T;
    v->value_t.sbyte_value = NULL_UINT_8_T;
    v->value_t.longlong_value = NULL_UINT_8_T;
    return v;
}

_bool *MerCompiler_bool_new(void) {
    _bool *b = new _bool;
    b->value = false;
    return b;
}

_code MerCompiler_code_new(void) {
    _code c = {};
    c.code = NULL_UINT_8_T;
    c.byte = NULL_UINT_8_T;
    c.address = NULL_UINT_8_T;
    c.cvalue = NULL_UINT_8_T;
    c.name = "";
    c.buff.clear();
    c.raw.clear();
    return c;
}

__iter *MerCompiler_iter_new(void) {
    __iter *it = new __iter();

    it->index = 0;
    it->size = 0;
    it->ui8_address = NULL_UINT_8_T;
    it->ui16_address = NULL_UINT_16_T;
    it->ui32_address = NULL_UINT_32_T;

    it->loop_obj.list = NULL_PTR;
    it->loop_obj.list = NULL_PTR;

    return it;
}

_class *MerCompiler_class_new(void) {
    _class *c = new _class;
    c->address = NULL_UINT_8_T;
    c->super_class = NULL_PTR;
    c->inheritance = NULL_PTR;
    c->members.clear();
    c->methods.clear();
    return c;
}

_code *MerCompiler_code_new_as_ptr(void) {
    _code *c = new _code;
    c->buff.clear();
    c->raw.clear();
    return c;
}


_string *MerCompiler_string_new(void) {
    _string *s = new _string;
    s->size = 0;
    s->buff.clear();
    return s;
}

_pcode *MerCompiler_pcode_new(void) {
    _pcode *p = new _pcode;
    p->prg_code = MerCompiler_code_new();
    p->cfile = "stdin";
    return p;
}

_func_object *MerCompiler_func_object_new(void) {
    _func_object *f = new _func_object;
    f->f_bc = MerCompiler_code_new_as_ptr();
    f->body_size = 0;
    f->args_size = 0;
    f->f_value = 0.0;
    return f;
}

_list_object *MerCompiler_list_object_new(void) {
    _list_object *l = new _list_object;
    l->size = 0;
    l->args.clear();
    return l;
}

_variable *MerCompiler_variable_new(void) {
    _variable *v = new _variable;
    v->name = "";
    v->type = "";
    v->val = MerCompiler_val_new();
    v->ui8_address = NULL_UINT_8_T;
    v->ui32_address = NULL_UINT_8_T;
    v->ui16_address = NULL_UINT_8_T;
    v->_is_constant = false;
    v->_is_local = false;
    v->_is_global = false;
    return v;
}

_object *MerCompiler_object_new(void) {
    _object *o = new _object;
    o->attributes.clear();
    o->obj_size = 0;
    o->obj_val;

    return o;
}

_type_obj *MerCompiler_type_obj_new(void) {
    _type_obj *obj = new _type_obj();

    obj->func = NULL_PTR;
    obj->variable = NULL_PTR;
    obj->str = NULL_PTR;
    obj->pcode = NULL_PTR;
    obj->code = NULL_PTR;
    obj->list = NULL_PTR;
    obj->bool_obj = NULL_PTR;
    obj->block = NULL_PTR;
    obj->val = NULL_PTR;
    obj->reg = NULL_PTR;
    obj->str_entry = NULL_PTR;

    return obj;
}
int MerCompiler_free_object(_object *o) {
    if (!o) return 0;

    o->attributes.clear();
    o->attributes.rehash(0);

    delete o;
    return 1;
}

int MerCompiler_free_code(_code *c) {
    if (!c) return 0;

    std::vector<Mer_uint8_t>().swap(c->buff);
    std::vector<Mer_uint8_t>().swap(c->raw);

    delete c;
    return 1;
}

int MerCompiler_free_string(_string *s) {
    if (!s) return 0;

    // std::vector<Mer_uint8_t>().swap(s->buff);
    
    delete s;
    return 1;
}

int MerCompiler_free_list_object(_list_object *l) {
    if (!l) return 0;

    std::vector<void*>().swap(l->args);
    delete l;
    return 1;
}

int MerCompiler_free_bool(_bool *b) {
    if (!b) return 0;
    delete b;
    return 1;
}

int MerCompiler_free_func_object(_func_object *f) {
    if (!f) return 0;

    MerCompiler_free_code(f->f_bc);
    std::vector<void*>().swap(f->args);

    delete f;
    return 1;
}

int MerCompiler_free_variable(_variable *v) {
    if (!v) return 0;

    MerCompiler_free_val(v->val);
    delete v;
    return 1;
}

int MerCompiler_free_val(_val *v) {
    if (!v) return 0;
    delete v;
    return 1;
}

int MerCompiler_free_pcode(_pcode *p) {
    if (!p) return 0;

    MerCompiler_free_code(&p->prg_code);
    MerCompiler_free_code(&p->out_code);
    std::vector<Mer_uint8_t>().swap(p->raw);

    delete p;
    return 1;
}