#ifndef CONSTANT_H
#define CONSTANT_H
#pragma once

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (3.1415926535897)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237)
#endif

#define M_SQRT2_H (0.7071067812f)

#define ACC_MAX 0x1FFFFFFF
#define ACC_MIN -0x20000000
#define ACC_REM 0x00003FFF

#define CLAMP(x, a, b) (x > a ? a : (x < b ? b : x))
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#
typedef float sample_t;

#endif
