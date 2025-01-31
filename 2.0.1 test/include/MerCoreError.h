#ifndef MER_CORE_ERROR_H
#define MER_CORE_ERROR_H
#include "MerErrorIden.h"

#define     EOK                     1
#define     EOF                     2
#define     E_TOK                   3
#define     E_SYNTAX                4
#define     E_FACTO                 5
#define     E_OUT                   6
#define     E_OVER_F                7
#define     E_UNIDEN                8

static int *MerCoreError_set_error_mode(char_state cur, int error_type);
#endif