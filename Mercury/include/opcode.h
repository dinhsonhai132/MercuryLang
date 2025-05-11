#ifndef MERCURY_OPCODE_H
#define MERCURY_OPCODE_H
#define CPUSH_FLOAT                             0x01 // push float (only push float to stack)
#define CPUSH_NORMAL_MODE                       0x02 // push normal (any type to stack)
#define CPUSH_TEMP_MODE                         0x03 // push temp (push temp val to stack will be free when call other opcode)
#define CLOAD_GLOBAL                            0x04 // load global (push global val to stack)
#define CSTORE_GLOBAL                           0x05 // store global (store stack val to global)
#define CEQUAL                                  0xE3 // compair equal (==)
#define CNOT_EQUAL                              0xE4 // compair not equal (!=)
#define CLESS                                   0xE5 // compair less (<)
#define CLESS_EQUAL                             0xE6 // compair less equal (<=)
#define CGREATER                                0xE7 // compair greater (>)
#define CGREATER_EQUAL                          0xE8 // compair greater equal (>=)
#define CNOT                                    0xE9 // compair not
#define CAND                                    0xEA // and (not in use)
#define COR                                     0xEC // or (not in use)
#define CNOT_OR                                 0xED // not or (not in use)
#define CBINARY_MOD                             0xEB // mod
#define CAND_OR                                 0xEE // and or (not in use)
#define CNOT_AND_OR                             0xEF // not and or (not in use)
#define CPOP_NORMAL_MODE                        0x06 // pop normal any type
#define CPOP_TEMP_MODE                          0x07 // pop temp
#define CPOP_GLOBAL                             0x09 // pop global
#define CPRINT                                  0x0F // print
#define CJUMP_IF_FALSE                          0xB3 // jump if false
#define CJUMP_IF_TRUE                           0xB0 // jump if false
#define CPOINT_TO                               0x10 // point to idx of code
#define CFREE                                   0x11 // free stack
#define CPOP_LOCAL                              0x0A // pop local
#define CPOP_TEMP                               0x0B // pop temp
#define CPOP_NORMAL                             0x0C // pop normal
#define CPOP_STRING                             0x0D // pop string
#define CPOP_FLOAT                              0x08 // pop float
#define CADDRESS                                0x0E // push address
#define CPOP_JUMP_IF_FALSE                      0xB8 // pop and jump if false
#define CPROGRAM_START                          0xA1 // program start told the vm that this is the main program
#define CPROGRAM_END                            0xFF // flag end of program told the vm that this is the end of main program
#define CBINARY_ADD                             0xB1 // binary add, add two number of the bottom stack
#define CBINARY_SUB                             0xB9 // binary sub, sub two number of the bottom stack
#define CBINARY_MUL                             0xB2 // binary mul, mul two number of the bottom stack
#define CBINARY_DIV                             0xB4 // binary div, div two number of the bottom stack
#define CNONE                                   0x00 // none
#define CPOP_JUMP_IF_TRUE                       0xB7 // pop and jump if true
#define CJUMP_TO                                0xB6 // jump to
#define CMAKE_BLOCK                             0xC0 // make block
#define CEND_BLOCK                              0xC3 // end block
#define CMAKE_FUNCTION                          0xC1 // make function
#define CFUNCTION_CALL                          0xC2 // function call
#define CRETURN                                 0xF1 // return
#endif // MERCURY_OPCODE_H