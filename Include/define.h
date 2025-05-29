#ifndef MERCURY_TYPEDEF_HEADER_FILE
#define MERCURY_TYPEDEF_HEADER_FILE
#include "..\Mercury\code.cpp"

#define GLOBAL_TABLE(address, name) create_global_table(address, name)
#define GLOBAL_TABLE_PTR(address, name) create_global_table_ptr(address, name)
#define PUSH(code, opcode) _MerCode_push_opcode(code, opcode)
#define INSERT(code, opcode, size) _MerCode_insert_opcode(code, opcode, size)
#define INSERT_VEC(code, ins) _MerCode_insert_vec_code(code, ins)
#define INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, ins) _MerCode_super_insert_vec_code(code, ins)
#define PUSH_TO_OUTCODE(code, opcode) _MerCode_push_opcode_to_outcode(code, opcode)
#define INSERT_TO_OUTCODE(code, opcode, size) _MerCode_insert_opcode_to_outcode(code, opcode, size)
#define INSERT_VEC_TO_OUTCODE(code, ins) _MerCode_insert_vec_code_to_outcode(code, ins)
#define INSERT_OUT_BY_PRG(code, ins) _MerCode_insert_vec_code_to_outcode_by_prog_code(code, ins)
#define INSERT_PRG_BY_OUT(code, ins) _MerCode_insert_vec_code_to_prg_code_by_out_code(code, ins)

#define __do_not_change const

#define __Mer_return_Void void
#define __Mer_return_Object mObject_T
#define __Mer_return_Code mCode_T
#define __Mer_return_Type mType_T
#define __Mer_return_Void_ptr void *
#define __Mer_return_Object_ptr mObject_T *
#define __Mer_return_Code_ptr mCode_T *
#define __Mer_return_Type_ptr mType_T *
#define __Mer_return_Void_ptr_ptr void **
#define __Mer_return_Object_ptr_ptr mObject_T **
#define __Mer_return_Code_ptr_ptr mCode_T **
#define __Mer_return_Type_ptr_ptr mType_T **
#define __Mer_return_Mer_uint8_t Mer_uint8_t
#define __Mer_return_Mer_uint8_t_ptr Mer_uint8_t *
#define __Mer_return_Mer_int8_t Mer_int8_t
#define __Mer_return_Mer_int8_t_ptr Mer_int8_t *
#define __Mer_return_Mer_uint16_t Mer_uint16_t
#define __Mer_return_Mer_uint16_t_ptr Mer_uint16_t *
#define __Mer_return_Mer_int16_t Mer_int16_t
#define __Mer_return_Mer_int16_t_ptr Mer_int16_t *
#define __Mer_return_Mer_uint32_t Mer_uint32_t
#define __Mer_return_Mer_uint32_t_ptr Mer_uint32_t *
#define __Mer_return_Mer_int32_t Mer_int32_t
#define __Mer_return_Mer_int32_t_ptr Mer_int32_t *
#define __Mer_return_Mer_uint64_t Mer_uint64_t
#define __Mer_return_Mer_uint64_t_ptr Mer_uint64_t *
#define __Mer_return_Mer_int64_t Mer_int64_t
#define __Mer_return_Mer_int64_t_ptr Mer_int64_t *
#define __Mer_return_Mer_float_t Mer_float_t
#define __Mer_return_Mer_float_t_ptr Mer_float_t *
#define __Mer_return_Mer_double_t Mer_double_t
#define __Mer_return_Mer_double_t_ptr Mer_double_t *
#define __Mer_return_Mer_long_t Mer_long_t
#define __Mer_return_Mer_long_t_ptr Mer_long_t *
#define __Mer_return_Mer_bool_t Mer_bool_t
#define __Mer_return_Mer_bool_t_ptr Mer_bool_t *
#define __Mer_return_Mer_string Mer_string
#define __Mer_return_Mer_string_ptr Mer_string *
#define __Mer_return_Mer_char_t Mer_char_t
#define __Mer_return_Mer_char_t_ptr Mer_char_t *

#endif // MERCURY_TYPEDEF_HEADER_FILE