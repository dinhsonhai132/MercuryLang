#include <iostream>
#include <cassert>
#include "MerCoreDataType.h"
#include "MerCoreError.h"
#include "MerCoreToken.h"

typedef ssize_t Mer_ssize_t;
typedef int Mer_int;
typedef float Mer_float;

#define Mer_CHARMASK(c) ((unsigned char)(c) & 0xff)