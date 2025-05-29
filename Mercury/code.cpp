#include "../include/code.h"

int _MerCode_push_opcode(mCode_T &code, Mer_uint8_t op) {
    code.prg_code.buff.push_back(op);
    return 0;
}
int _MerCode_insert_opcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size) {
    code.prg_code.buff.insert(code.prg_code.buff.end() , op, op + size);
    return 0;
}
int _MerCode_insert_vec_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    return 0;
}

int _MerCode_super_insert_vec_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    code.out_code.buff.insert(code.out_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}

int _MerCode_push_opcode_to_outcode(mCode_T &code, Mer_uint8_t op) {
    code.out_code.buff.push_back(op);
    return 0;
}
int _MerCode_insert_opcode_to_outcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size) {
    code.out_code.buff.insert(code.out_code.buff.end() , op, op + size);
    return 0;
}
int _MerCode_insert_vec_code_to_outcode(mCode_T &code, mCode_T &ins) {
    code.out_code.buff.insert(code.out_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}

int _MerCode_insert_vec_code_to_outcode_by_prog_code(mCode_T &code, mCode_T &ins) {
    code.out_code.buff.insert(code.out_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    return 0;
}

int _MerCode_insert_vec_code_to_prg_code_by_out_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}