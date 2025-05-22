#ifndef MERCURY_CODE_HEADER_FILE
#define MERCURY_CODE_HEADER_FILE
#include "object.h"

int _MerCode_push_opcode(mCode_T &code, Mer_uint8_t op);
int _MerCode_insert_opcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size);
int _MerCode_insert_vec_code(mCode_T &code, mCode_T &ins);
int _MerCode_push_opcode_to_outcode(mCode_T &code, Mer_uint8_t op);
int _MerCode_insert_opcode_to_outcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size);
int _MerCode_insert_vec_code_to_outcode(mCode_T &code, mCode_T &ins);

#endif // MERCURY_CODE_HEADER_FILE