#ifndef MER_CORE_H
#define MER_CORE_H

#define PLUS        1
#define MINUS       2
#define TIME        3
#define DIV         4
#define DIGIT       5
#define BIGGER      6
#define SMALLER     7
#define EQUAL       8
#define NOT_EQUAL   9
#define BE          10
#define SE          11
#define VARIABLE    12
#define PRINT       13
#define ASSIGN      14
#define SPACE       15
#define ALPHA       16
#define STRING      17

#define ISSPACE(x) (x == SPACE)
#define ISDIGIT(x) (x == DIGIT)
#define ISALPHA(x) (x == ALPHA)
#define ISALPHA_DIGIT(x) (x == ALPHA || \ x == DIGIT)
#define ISSTRING(x) (x == STRING)

int MerToken_1_char(char c1);
int MerToken_2_char(char c1, char c2);
int MerToken_3_char(char c1, char c2, char c3);

#endif