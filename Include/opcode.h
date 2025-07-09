#ifndef MERCURY_OPCODE_H
#define MERCURY_OPCODE_H

#define CPUSH_FLOAT                             0x01
#define CPUSH_NORMAL_MODE                       0x02
#define CSTORE_GLOBAL                           0x03
#define CLOAD_GLOBAL                            0x04
#define CLOAD_ARGS                              0x05

#define CBINARY_ADD                             0x10
#define CBINARY_SUB                             0x11
#define CBINARY_MUL                             0x12
#define CBINARY_DIV                             0x13
#define CBINARY_MOD                             0x14
#define CBINARY_POW                             0xF1
#define CBINARY_SUBSCRIBE                       0x15

#define TRUE_ADDRESS                            0x20
#define FALSE_ADDRESS                           0x21
#define CEQUAL                                  0x22
#define CNOT_EQUAL                              0x23
#define CLESS                                   0x24
#define CLESS_EQUAL                             0x25
#define CGREATER                                0x26
#define CGREATER_EQUAL                          0x27
#define CNOT                                    0x28
#define CLEN                                    0x29

#define CFUNCTION_CALL_WITH_ARGS                0x30
#define CMAKE_FUNCTION_WITH_ARGS                0x31
#define CMAKE_FUNCTION                          0x32
#define CFUNCTION_CALL                          0x33
#define CRETURN                                 0x34

#define CJUMP_IF_FALSE                          0x40
#define CJUMP_IF_TRUE                           0x41
#define CPOP_JUMP_IF_FALSE                      0x42
#define CPOP_JUMP_IF_TRUE                       0x43
#define CJUMP_TO                                0x44

#define CBUILD_LIST                             0x50
#define CGET_ITEM                               0x51
#define CSTORE_INDEX                            0x52

#define CPROGRAM_START                          0x60
#define CPROGRAM_END                            0x8D
#define CADDRESS                                0x9D

#define CLOAD_TRUE                              0x63
#define CLOAD_FALSE                             0x64

#define CINC                                    0x9A
#define CDEC                                    0x9B

#define CAND                                    0x9C
#define COR                                     0x62

#define CCLASS_BEGIN                            0x9E // CLASS_BEGIN <class_name>
#define CCLASS_END                              0x9F // CLASS_END

#define CSTORE_ATTR                             0xA0 // STORE_ATTR <class_name> <attr_name>
#define CLOAD_ATTR                              0xA1 // LOAD_ATTR <class_name> <attr_name>

#define CDELETE                                 0xA2

#define CIS                                     0xA3

#define CEND_FUNCTION                           0xFF


#define NUMBER_0 {0x00, 0x00, 0x00, 0x00}
#define NUMBER_1 {0x00, 0x00, 0x80, 0x3F}
#define NUMBER_2 {0x00, 0x00, 0x00, 0x40}
#define NUMBER_3 {0x00, 0x00, 0x40, 0x40}

#endif // MERCURY_OPCODE_H
