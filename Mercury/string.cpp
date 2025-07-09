#include "../include/string.h"

float __hash(mString_T *str) {
    vector<uint8_t> data = str->buff;
    uint32_t hash = 2166136261u;
    for (uint8_t byte : data) {
        hash ^= byte;
        hash *= 16777619u;
    }
    
    float result;
    memcpy(&result, &hash, sizeof(float));
    return result;
}

mString_T *creat_string_obj(string str) {
    mString_T *str_obj;
    str_obj->buff.insert(str_obj->buff.end(), str.begin(), str.end());
    str_obj->size = str.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}