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

_code *MerCompiler_code_new_as_ptr(void) {
    _code *c = new _code;
    c->code = NULL_UINT_8_T;
    c->byte = NULL_UINT_8_T;
    c->address = NULL_UINT_8_T;
    c->cvalue = NULL_UINT_8_T;
    c->name = "";
    c->buff.clear();
    c->raw.clear();
    return c;
}


_string *MerCompiler_string_new(void) {
    _string *s = new _string;
    s->size = 0;
    s->hash = NULL_UINT_8_T;
    s->contents[0] = NULL_CHAR;
    s->buff.clear();
    return s;
}

_pcode *MerCompiler_pcode_new(void) {
    _pcode *p = new _pcode;
    p->prg_code = MerCompiler_code_new();
    p->out_code = MerCompiler_code_new();

    p->scode = NULL_PTR;
    p->cfile = "stdin";
    p->csize = 0;
    p->raw.clear();
    p->raw_in_buff[0] = NULL_UINT_8_T;
    p->raw_out_buff[0] = NULL_UINT_8_T;

    return p;
}

_func_object *MerCompiler_func_object_new(void) {
    _func_object *f = new _func_object;
    f->ui8_address = NULL_UINT_8_T;
    f->ui32_address = NULL_UINT_8_T;
    f->ui16_address = NULL_UINT_8_T;
    f->sf = NULL_PTR;
    f->f_bc = MerCompiler_code_new_as_ptr();
    f->fs_bc = MerCompiler_code_new_as_ptr();
    f->raw_body.clear();
    f->body_size = 0;
    f->args_size = 0;
    f->f_value = 0.0;
    f->args.clear();
    f->is_return = false;
    f->is_local = false;
    f->is_global = false;
    f->o = NULL_PTR;
    f->f_builtin = false;
    return f;
}

_list_object *MerCompiler_list_object_new(void) {
    _list_object *l = new _list_object;
    l->ui8_address = NULL_UINT_8_T;
    l->ui32_address = NULL_UINT_8_T;
    l->ui16_address = NULL_UINT_8_T;
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

_type *MerCompiler_type_new(void) {
    _type *t = new _type;
    t->func = MerCompiler_func_object_new();
    t->variable = MerCompiler_variable_new();
    t->str = MerCompiler_string_new();
    t->pcode = MerCompiler_pcode_new();
    t->code = MerCompiler_code_new_as_ptr();
    t->o_ptr = NULL_PTR;
    t->is_builtin = false;
    t->builtin_name = "";
    t->builtin_ptr = NULL_PTR;
    t->name = "";
    t->type = "";
    t->file_name = "";
    return t;
}

_object *MerCompiler_object_new(void) {
    _object *o = new _object;
    o->attributes.clear();
    o->type = MerCompiler_type_new();
    o->data_type = MerCompiler_type_new();
    o->value = MerCompiler_type_new();
    o->name = MerCompiler_type_new();
    o->file_name = MerCompiler_type_new();
    o->code = MerCompiler_pcode_new();
    return o;
}

int MerCompiler_free_object(_object *o) {
    if (!o) return 0;
    MerCompiler_free_type(o->type);
    MerCompiler_free_type(o->data_type);
    MerCompiler_free_type(o->value);
    MerCompiler_free_type(o->file_name);
    MerCompiler_free_pcode(o->code);
    o->attributes.clear();
    delete o;
    return 1;
}

int MerCompiler_free_type(_type *t) {
    if (!t) return 0;
    MerCompiler_free_func_object(t->func);
    MerCompiler_free_variable(t->variable);
    MerCompiler_free_string(t->str);
    MerCompiler_free_pcode(t->pcode);
    MerCompiler_free_code(t->code);
    t->o_ptr = NULL_PTR;
    t->is_builtin = false;
    t->builtin_name = "";
    t->builtin_ptr = NULL_PTR;
    t->name = "";
    t->type = "";
    t->file_name = "";
    delete t;
    return 1;
}

int MerCompiler_free_pcode(_pcode *p) {
    if (!p) return 0;
    MerCompiler_free_code(&p->prg_code);
    MerCompiler_free_code(&p->out_code);
    p->scode = NULL_PTR;
    p->cfile = NULL_PTR;
    p->csize = 0;
    p->raw.clear();
    p->raw_in_buff[0] = NULL_UINT_8_T;
    p->raw_out_buff[0] = NULL_UINT_8_T;
    delete p;
    return 1;
}

int MerCompiler_free_string(_string *s) {
    if (!s) return 0;
    s->size = 0;
    s->hash = NULL_UINT_8_T;
    s->contents[0] = NULL_CHAR;
    s->buff.clear();
    delete s;
    return 1;
}

int MerCompiler_free_variable(_variable *v) {
    if (!v) return 0;
    v->name = "";
    v->type = "";
    MerCompiler_free_val(v->val);
    v->ui8_address = NULL_UINT_8_T;
    v->ui32_address = NULL_UINT_8_T;
    v->ui16_address = NULL_UINT_8_T;
    v->_is_constant = false;
    v->_is_local = false;
    v->_is_global = false;
    delete v;
    return 1;
}

int MerCompiler_free_func_object(_func_object *f) {
    if (!f) return 0;
    f->ui8_address = NULL_UINT_8_T;
    f->ui32_address = NULL_UINT_8_T;
    f->ui16_address = NULL_UINT_8_T;
    f->sf = NULL_PTR;
    MerCompiler_free_code(f->f_bc);
    MerCompiler_free_code(f->fs_bc);
    f->raw_body.clear();
    f->body_size = 0;
    f->args_size = 0;
    f->f_value = 0.0;
    f->args.clear();
    f->is_return = false;
    f->is_local = false;
    f->is_global = false;
    f->o = NULL_PTR;
    f->f_builtin = false;
    delete f;
    return 1;
}

int MerCompiler_free_code(_code *c) {
    if (!c) return 0;
    c->code = NULL_UINT_8_T;
    c->byte = NULL_UINT_8_T;
    c->address = NULL_UINT_8_T;
    c->cvalue = NULL_UINT_8_T;
    c->name = "";
    c->buff.clear();
    c->raw.clear();
    delete c;
    return 1;
}

int MerCompiler_free_val(_val *v) {
    if (!v) return 0;
    v->value_t.int_value = 0;
    v->value_t.float_value = 0.0;
    v->value_t.bool_value = false;
    v->value_t.char_value = NULL_CHAR;
    v->value_t.string_value = "";
    v->value_t.long_value = 0;
    v->value_t.byte_value = NULL_UINT_8_T;
    v->value_t.sbyte_value = NULL_UINT_8_T;
    v->value_t.longlong_value = NULL_UINT_8_T;
    delete v;
    return 1;
}

int MerCompiler_free_list_object(_list_object *l) {
    if (!l) return 0;
    l->ui8_address = NULL_UINT_8_T;
    l->ui32_address = NULL_UINT_8_T;
    l->ui16_address = NULL_UINT_8_T;
    l->size = 0;
    l->args.clear();
    delete l;
    return 1;
}