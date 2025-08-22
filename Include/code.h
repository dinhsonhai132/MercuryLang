#ifndef MERCURY_CODE_HEADER_FILE
#define MERCURY_CODE_HEADER_FILE

#include "../include/object.h"
#include "../include/port.h"

int _MerCode_push_opcode(mCode_T &code, Mer_uint8_t op);
int _MerCode_insert_opcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size);
int _MerCode_insert_vec_code(mCode_T &code, mCode_T &ins);
int _MerCode_super_insert_vec_code(mCode_T &code, mCode_T &ins);
int _MerCode_push_opcode_to_outcode(mCode_T &code, Mer_uint8_t op);
int _MerCode_insert_opcode_to_outcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size);
int _MerCode_insert_vec_code_to_outcode(mCode_T &code, mCode_T &ins);
int _MerCode_insert_vec_code_to_outcode_by_prog_code(mCode_T &code, mCode_T &ins);
int _MerCode_insert_vec_code_to_prg_code_by_out_code(mCode_T &code, mCode_T &ins);

#endif // MERCURY_CODE_HEADER_FILE