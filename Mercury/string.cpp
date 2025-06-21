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