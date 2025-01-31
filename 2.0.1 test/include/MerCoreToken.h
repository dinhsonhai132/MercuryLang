#ifndef MER_CORE_H
#define MER_CORE_H

#define UNIDEN      0
#define PLUS        1
#define MINUS       2
#define TIME        3
#define DIV         4
#define NUM         5
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
#define NONE        18
#define EOF         19
#define ENDMARKER   20
#define NEW_LINE    21

#define ISSTRING(x) (x == STRING)

#define ISNUM(x) (x == NUM)

#define ISSPACE(x) (x == SPACE)

#define ISEOF(x) ((x == EOF) || \
(x == ENDMARKER) || \
(x == NEW_LINE))

#endif