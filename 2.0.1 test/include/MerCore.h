#include <iostream>

#include "MerCoreDataType.h"
#include "MerCoreError.h"
#include "MerCoreToken.h"

typedef ssize_t Mer_ssize_t;
typedef int Mer_int;
typedef float Mer_float;

#define Mer_CHARMASK(c) ((unsigned char)(c) & 0xff) // change char into int
#define MAX_INDEX 1250000;
#define TRUE 1;
#define FALSE 0;