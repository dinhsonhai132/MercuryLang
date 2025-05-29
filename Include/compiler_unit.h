#ifndef MERCURY_COMPILER_UNIT_H
#define MERCURY_COMPILER_UNIT_H

#include "Mercury.h"

struct __program_bytecode {
    mCode_T &code;
    Mer_size_t lid;             // id of label
    hash_t hash;
    Mer_size_t glb_id;
    Mer_size_t lc_id;
    Mer_size_t iid;             // id of prg_code
    Mer_size_t oid;             // id of out_code
    Mer_uint8_t icode;          // cur code in prg_code
    Mer_uint8_t ocode;          // cur code in out_code
    unordered_map<Mer_uint8_t, Mer_size_t> label_map;
    Mer_size_t loop_size;
    bool is_in_func;
    const char *file;
};

#endif // MERCURY_COMPILER_UNIT_H