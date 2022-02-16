#ifndef CONSTANT_H
#define CONSTANT_H
#pragma once

#ifndef M_PI
#define M_PI (3.1415926535897)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237)
#endif

#define q (14)
#define scale14 (powf(2, q))

#define ACC_MAX 0x1FFFFFFF
#define ACC_MIN -0x20000000
#define ACC_REM 0x00003FFF

#define CLAMP(x, a, b) (x > a ? a : (x < b ? b : x))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#endif