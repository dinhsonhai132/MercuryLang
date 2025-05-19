#ifndef MERCURY_PORT_HEADER_FILE
#define MERCURY_PORT_HEADER_FILE

using namespace std;

typedef unsigned int hash_t;

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
#ifndef MER_UINT8_LIB
#define MER_UINT8_LIB 1
#endif
#ifdef MER_UINT8_LIB
#include <stdint.h>
typedef uint8_t Mer_uint8_t;
typedef int8_t Mer_int8_t;
#else
typedef unsigned char Mer_uint8_t;
typedef char Mer_int8_t;
#endif
#endif

#ifndef MER_UINT16_T
#ifndef MER_UINT16_LIB
#define MER_UINT16_LIB 1
#endif
#ifdef MER_UINT16_LIB
#include <stdint.h>
typedef uint16_t Mer_uint16_t;
#else
typedef unsigned short Mer_uint16_t;
#endif
#endif

#ifndef MER_UINT32_T
#ifndef MER_UINT32_LIB
#define MER_UINT32_LIB 1
#endif
#ifdef MER_UINT32_LIB
#include <stdint.h>
typedef uint32_t Mer_uint32_t;
#else
typedef unsigned int Mer_uint32_t;
#endif
#endif

#ifndef MER_UINT64_T
#ifndef MER_UINT64_LIB
#define MER_UINT64_LIB 1
#endif
#ifdef MER_UINT64_LIB
#include <stdint.h>
typedef uint64_t Mer_uint64_t;
#else
typedef unsigned long long Mer_uint64_t;
#endif
#endif

#ifndef MER_BOOL
typedef bool Mer_bool;
#endif

#ifndef MER_VOID
typedef void Mer_void;
#endif

#ifndef MER_SSIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
typedef ssize_t Mer_ssize_t;
#endif

#ifndef MER_SIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SIZE_T size_t;
#endif
typedef unsigned long long Mer_size_t;
#endif

#ifndef MER_NULL
#define MER_NULL nullptr
#endif

#ifndef MER_UNUSED
#define MER_UNUSED(x) (void)(x)
#endif

#ifndef MER_CONST_CHAR
typedef const char *Mer_string;
#define REAL_STRING 1
#ifdef REAL_STRING
#include <string>
typedef string Mer_real_string;
#else
typedef const char *Mer_real_string;
#endif
#endif

#endif // MERCURY_PORT_HEADER_FILE