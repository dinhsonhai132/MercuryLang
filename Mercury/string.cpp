#include "../include/string.h"
#include "../include/math.h"

float __uint8_to_float(Mer_uint8_t c) {
    return static_cast<float>(c);
}

float __hash(mString_T *str) {
    vector<uint8_t> data = str->buff;
    float result = 0.0f;
    int size = data.size();
    for (auto &item : data) {
        result += __uint8_to_float(item) * POWER(31, size - 1);
        size--;
    }
    
    return result;
}

mString_T *creat_string_obj(string str) {
    mString_T *str_obj;
    str_obj->buff.insert(str_obj->buff.end(), str.begin(), str.end());
    str_obj->size = str.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}