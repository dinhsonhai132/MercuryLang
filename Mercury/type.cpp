#include "./include/type.h"

_val *MerCompiler_val_new(void) {
    _val *v = new _val;
    v->value_t.int_value = 0;
    v->value_t.float_value = 0.0;
    v->value_t.bool_value = false;
    v->value_t.char_value = '\0';
    v->value_t.string_value = "";
    v->value_t.long_value = 0;
    v->value_t.byte_value = 0x00;
    v->value_t.sbyte_value = 0x00;
    v->value_t.longlong_value = 0x00;
    return v;
}

_code MerCompiler_code_new(void) {
    _code c = {};
    c.code = 0x00;
    c.byte = 0x00;
    c.address = 0x00;
    c.cvalue = 0x00;
    c.name = "";
    c.buff.clear();
    c.raw.clear();
    return c;
}

_code *MerCompiler_code_new_as_ptr(void) {
    _code *c = new _code;
    c->code = 0x00;
    c->byte = 0x00;
    c->address = 0x00;
    c->cvalue = 0x00;
    c->name = "";
    c->buff.clear();
    c->raw.clear();
    return c;
}


_string *MerCompiler_string_new(void) {
    _string *s = new _string;
    s->size = 0;
    s->hash = 0x00;
    s->contents[0] = '\0';
    s->buff.clear();
    return s;
}

_pcode *MerCompiler_pcode_new(void) {
    _pcode *p = new _pcode;
    p->prg_code = MerCompiler_code_new();
    p->out_code = MerCompiler_code_new();

    p->scode = nullptr;
    p->cfile = nullptr;
    p->csize = 0;
    p->raw.clear();
    p->raw_in_buff[0] = 0x00;
    p->raw_out_buff[0] = 0x00;

    return p;
}

_func_object *MerCompiler_func_object_new(void) {
    _func_object *f = new _func_object;
    f->ui8_address = 0x00;
    f->ui32_address = 0x00;
    f->ui16_address = 0x00;
    f->sf = nullptr;
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
    f->o = nullptr;
    f->f_builtin = false;
    return f;
}

_list_object *MerCompiler_list_object_new(void) {
    _list_object *l = new _list_object;
    l->ui8_address = 0x00;
    l->ui32_address = 0x00;
    l->ui16_address = 0x00;
    l->size = 0;
    l->args.clear();
    return l;
}

_variable *MerCompiler_variable_new(void) {
    _variable *v = new _variable;
    v->name = "";
    v->type = "";
    v->val = MerCompiler_val_new();
    v->ui8_address = 0x00;
    v->ui32_address = 0x00;
    v->ui16_address = 0x00;
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
    t->o_ptr = nullptr;
    t->is_builtin = false;
    t->builtin_name = "";
    t->builtin_ptr = nullptr;
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
    t->o_ptr = nullptr;
    t->is_builtin = false;
    t->builtin_name = "";
    t->builtin_ptr = nullptr;
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
    p->scode = nullptr;
    p->cfile = nullptr;
    p->csize = 0;
    p->raw.clear();
    p->raw_in_buff[0] = 0x00;
    p->raw_out_buff[0] = 0x00;
    delete p;
    return 1;
}

int MerCompiler_free_string(_string *s) {
    if (!s) return 0;
    s->size = 0;
    s->hash = 0x00;
    s->contents[0] = '\0';
    s->buff.clear();
    delete s;
    return 1;
}

int MerCompiler_free_variable(_variable *v) {
    if (!v) return 0;
    v->name = "";
    v->type = "";
    MerCompiler_free_val(v->val);
    v->ui8_address = 0x00;
    v->ui32_address = 0x00;
    v->ui16_address = 0x00;
    v->_is_constant = false;
    v->_is_local = false;
    v->_is_global = false;
    delete v;
    return 1;
}

int MerCompiler_free_func_object(_func_object *f) {
    if (!f) return 0;
    f->ui8_address = 0x00;
    f->ui32_address = 0x00;
    f->ui16_address = 0x00;
    f->sf = nullptr;
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
    f->o = nullptr;
    f->f_builtin = false;
    delete f;
    return 1;
}

int MerCompiler_free_code(_code *c) {
    if (!c) return 0;
    c->code = 0x00;
    c->byte = 0x00;
    c->address = 0x00;
    c->cvalue = 0x00;
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
    v->value_t.char_value = '\0';
    v->value_t.string_value = "";
    v->value_t.long_value = 0;
    v->value_t.byte_value = 0x00;
    v->value_t.sbyte_value = 0x00;
    v->value_t.longlong_value = 0x00;
    delete v;
    return 1;
}

int MerCompiler_free_list_object(_list_object *l) {
    if (!l) return 0;
    l->ui8_address = 0x00;
    l->ui32_address = 0x00;
    l->ui16_address = 0x00;
    l->size = 0;
    l->args.clear();
    delete l;
    return 1;
}
