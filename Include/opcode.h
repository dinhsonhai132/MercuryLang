#ifndef MERCURY_OPCODE_H
#define MERCURY_OPCODE_H

#define CPUSH_FLOAT                             0xAB
#define CPUSH_NORMAL_MODE                       0xAA
#define CFREE                                   0x18

#define CBUILD_LIST                             0x1A
#define CGET_ITEM                               0xF2
#define CGET_ITER                               0xF3
#define CSTORE_INDEX                            0xF1
#define CBINARY_SUBSCRIBE                       0xF4

#define CLOAD_GLOBAL                            0x9F
#define CSTORE_GLOBAL                           0xFF

#define CBINARY_ADD                             0x1F
#define CBINARY_SUB                             0x2F
#define CBINARY_MUL                             0x3F
#define CBINARY_DIV                             0x4F
#define CBINARY_MOD                             0x5F

#define TRUE_ADDRESS                            0x1A
#define FALSE_ADDRESS                           0x2A

#define CEQUAL                                  0x1B
#define CNOT_EQUAL                              0x2B
#define CLESS                                   0x3B
#define CLESS_EQUAL                             0x4B
#define CGREATER                                0x5B
#define CGREATER_EQUAL                          0x6B
#define CNOT                                    0x7B

#define CAND                                    0x1C
#define COR                                     0x2C
#define CNOT_OR                                 0x3C
#define CAND_OR                                 0x4C
#define CNOT_AND_OR                             0x5C

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

#define CPRINT                                  0xFC
#define CADDRESS                                0xFA
#define CNONE                                   0xFD

#endif // MERCURY_OPCODE_H
