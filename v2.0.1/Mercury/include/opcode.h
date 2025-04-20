#ifndef MERCURY_OPCODE_H
#define MERCURY_OPCODE_H


#define CPUSH_FLOAT 0x01
#define CPUSH_NORMAL_MODE 0x02
#define CPUSH_TEMP_MODE 0x03

#define CLOAD_GLOBAL 0x04
#define CSTORE_GLOBAL 0x05

#define CEQUAL 0xE3
#define CNOT_EQUAL 0xE4
#define CLESS 0xE5
#define CLESS_EQUAL 0xE6
#define CGREATER 0xE7
#define CGREATER_EQUAL 0xE8
#define CNOT 0xE9
#define CAND 0xEA
#define COR 0xEC
#define CNOT_OR 0xED
#define CAND_OR 0xEE
#define CNOT_AND_OR 0xEF

#define CPOP_NORMAL_MODE 0x06
#define CPOP_TEMP_MODE 0x07

#define CPROGRAM_START 0xA1
#define CPROGRAM_END 0xFF

#define CBINARY_ADD 0xB1
#define CBINARY_SUB 0xB2
#define CBINARY_MUL 0xB3
#define CBINARY_DIV 0xB4

#define JUMP_IF_TRUE 0xB5
#define JUMP_TO 0xB6

#define CMAKE_FUNCTION 0xC1
#define CFUNCTION_CALL 0xC2

#define CRETURN 0xF1

#endif // MERCURY_OPCODE_H