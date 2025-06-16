#include "../include/math.h"

float fcos(float x) { return cos(RAD_TO_DEG(x)); }
float fsin(float x) { return sin(RAD_TO_DEG(x)); }
float ftan(float x) { return tan(RAD_TO_DEG(x)); }
float fcot(float x) { return 1 / tan(RAD_TO_DEG(x)); }
float fexp(float x) { return exp(x); }
float flog(float x) { return log(x); }
float fsqrt(float x) { return sqrt(x); }