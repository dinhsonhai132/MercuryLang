#include "../include/string.h"
#include "../include/math.h"

float __uint8_to_float(Mer_uint8_t c) {
    return static_cast<float>(c);
}

float __hash(mString_T *str) {
    float result = 0.0f;
    float power = 1.0f;
    
    for (int i = (int)str->buff.size() - 1; i >= 0; --i) {
        result += (float)str->buff[i] * power;
        power *= 31.0f;
    }
    
    return result;
}

__mer_core_api__ mString_T *__mer_core_api__ add_string(mString_T *a, mString_T *b) {
    mString_T *result = MerCompiler_string_new();
    result->buff.insert(result->buff.end(), a->buff.begin(), a->buff.end());
    result->buff.insert(result->buff.end(), b->buff.begin(), b->buff.end());
    result->size = a->size + b->size;
    result->hash = __hash(result);
    return result;
}

__mer_core_api__ mString_T *__mer_core_api__ mul_string(mString_T *a, int times) {
    mString_T *result = MerCompiler_string_new();

    for (int i = 0; i < times; i++) {
        result->buff.insert(result->buff.end(), a->buff.begin(), a->buff.end());
    }

    result->size = a->size * times;
    result->hash = __hash(result);
    return result;
}

__mer_core_lib_api__ string __convert_to_string(mString_T *__string) {
    string value = "";
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        value += static_cast<char>(item);
    }

    return value;
}

char* from_mstring_to_char(mString_T *str) {
    char* result = new char[str->size];
    vector<Mer_uint8_t> code = str->buff;
    for (Mer_size_t i = 0; i < str->size; i++) {
        result[i] = code[i];
    }
    return result;
}

mString_T *creat_string_obj_with_code(vector<Mer_uint8_t> code) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.insert(str_obj->buff.end(), code.begin(), code.end());
    str_obj->size = code.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

mString_T *creat_char_obj(Mer_uint8_t c) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.push_back(c);
    str_obj->size = size(str_obj->buff);
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

mString_T *creat_string_obj(string str) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.insert(str_obj->buff.end(), str.begin(), str.end());
    str_obj->size = str.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}