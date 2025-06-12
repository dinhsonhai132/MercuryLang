#ifndef MERCURY_OPCODE_H
#define MERCURY_OPCODE_H

#define CPUSH_FLOAT                             0xAB
#define CPUSH_NORMAL_MODE                       0xAA
#define CFREE                                   0x18

#define CBUILD_LIST                             0x1A
#define CGET_ITEM                               0xF2
#define CSTORE_INDEX                            0xF1
#define CBINARY_SUBSCRIBE                       0xF4

#define CLOAD_GLOBAL                            0x9F
#define CSTORE_GLOBAL                           0xFF

#define CBINARY_ADD                             0xE1
#define CBINARY_SUB                             0xE2
#define CBINARY_MUL                             0xE3
#define CBINARY_DIV                             0xE4
#define CBINARY_MOD                             0xE5

#define CGET_ITERATOR                           0x19
#define CFOR_ITERATOR                           0x20

#define TRUE_ADDRESS                            0x1A
#define FALSE_ADDRESS                           0x2A

#define CEQUAL                                  0x1B
#define CNOT_EQUAL                              0x2B
#define CLESS                                   0x8B
#define CLESS_EQUAL                             0x4B
#define CGREATER                                0x5B
#define CGREATER_EQUAL                          0x9B
#define CNOT                                    0xE1

#define CAND                                    0x1C
#define COR                                     0x2C
#define CNOT_OR                                 0x3C
#define CAND_OR                                 0x4C
#define CNOT_AND_OR                             0x5C
#define CLEN                                    0x6C

#define CJUMP_IF_FALSE                          0x1D
#define CJUMP_IF_TRUE                           0x2D
#define CPOP_JUMP_IF_FALSE                      0x3D
#define CPOP_JUMP_IF_TRUE                       0x4D
#define CJUMP_TO                                0x5D

#define CPROGRAM_START                          0x1E
#define CPROGRAM_END                            0x2E
#define CMAKE_BLOCK                             0x3E
#define CEND_BLOCK                              0x4E
#define CMAKE_FUNCTION                          0x5E
#define CFUNCTION_CALL                          0x6E
#define CRETURN                                 0x9E

#define CADDRESS                                0xFA
#define CNONE                                   0xFD

#define NUMBER_0 {0x00, 0x00, 0x00, 0x00}
#define NUMBER_1 {0x00, 0x00, 0x80, 0x3F}
#define NUMBER_2 {0x00, 0x00, 0x00, 0x40}
#define NUMBER_3 {0x00, 0x00, 0x40, 0x40}

#endif // MERCURY_OPCODE_H
