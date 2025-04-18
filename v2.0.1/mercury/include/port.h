#ifndef MERCURY_PORT_HEADER_FILE
#define MERCURY_PORT_HEADER_FILE

#ifndef MER_LONG_LONG
typedef long long Mer_longlong;
#endif

#ifndef MER_LONG
typedef long Mer_long;
#endif

#ifndef MER_INT
typedef int Mer_int;
#endif

#ifndef MER_SHORT
typedef short Mer_short;
#endif

#ifndef MER_CHAR
typedef char Mer_char;
#endif

#ifndef MER_BYTE
typedef unsigned char Mer_byte;
#endif

#ifndef MER_FLOAT
typedef float Mer_float;
#endif

#ifndef MER_DOUBLE
typedef double Mer_double;
#endif

#ifndef MER_UINT8_T
typedef unsigned char Mer_uint8_t;
typedef char Mer_int8_t;
#endif

#ifndef MER_BOOL
typedef bool Mer_bool;
#endif

#ifndef MER_VOID
typedef void Mer_void;
#endif

#ifndef MER_SIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
typedef ssize_t Mer_ssize_t;
#endif

#ifndef MER_SSIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
typedef ssize_t Mer_ssize_t;
#endif

#ifndef MER_NULL
#define MER_NULL nullptr
#endif

#ifndef MER_UNUSED
#define MER_UNUSED(x) (void)x
#endif

#ifndef MER_CONST_CHAR
typedef const char* Mer_string;
#endif

#endif // MERCURY_PORT_HEADER_FILE