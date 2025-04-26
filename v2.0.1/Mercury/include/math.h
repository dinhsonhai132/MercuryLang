#ifndef MATH_HEADER_FILE
#define MATH_HEADER_FILE

// for that one evil subject


#define PI 3.1415926535897932384626433832795
#define TAU 6.283185307179586476925286766559
#define GOLDEN_RATIO 1.6180339887498948482045868343656
#define EULER 2.7182818284590452353602874713527

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define CLAMP01(x) CLAMP(x, 0.0, 1.0)

#define DEG_TO_RAD(x) ((x) * (PI / 180.0))
#define RAD_TO_DEG(x) ((x) * (180.0 / PI))

#define SQ(x) ((x) * (x))


#endif // MATH_HEADER_FILE