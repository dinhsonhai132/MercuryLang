#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"

MERCURY_API double __builtin_sin(double _Var);
MERCURY_API double __builtin_cos(double _Var);
MERCURY_API double __builtin_tan(double _Var);
MERCURY_API double __builtin_atan(double _Var);
MERCURY_API long long __builtin_abs(long long _Var);
MERCURY_API long long __builtin_pow(long long _Number, long long _Power);
MERCURY_API long long __builtin_factorial(long long _Number);
MERCURY_API int mer_to_string(Mer_uint8_t _Var);
MERCURY_API void __builtin_print(mObject_T *str);

#endif // MERCURY_BUILTIN_HEADER_FILE