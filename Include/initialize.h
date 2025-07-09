#ifndef MERCURY_INITIALIZE_HEADER_FILE
#define MERCURY_INITIALIZE_HEADER_FILE
#include "../Mercury/register.cpp"

MERCURY_API void MerCore_initialize(void);   
MERCURY_API void MerCore_Finalize(void);

MERCURY_API __mer_core_api__ void __initialize__(void);

#endif // MERCURY_INITIALIZE_HEADER_FILE
