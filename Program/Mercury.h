#include "C:\MercuryLang\Mercury\Mercury.cpp"

#define     START_DLL                   extern "C" {

#define     END_DLL                     }   

#define     DLL_EXPORT                  __declspec(dllexport)

#define     DLL_IMPORT                  __declspec(dllimport)

#define     ARGS                        table* args[]
#define     GET_ARGS        (x)         args[x - 1]
