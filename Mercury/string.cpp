#include "../include/string.h"

hash_t __hash(mString_T *str) {
    hash_t hash = 0x00;
    for (Mer_size_t i = 0; i < str->size; ++i) {
        hash += str->buff[i] * i;
    }
    
    return hash;
}