#ifndef IIR_H
#define IIR_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI (3.1415926535897)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237)
#endif

typedef enum
{
    lowpass,
    highpass,
    bandpass,
    notch,
    peak,
    lowshelf,
    highshelf,
    none
} filter_type_t;

typedef struct
{
    filter_type_t type;
    int32_t a[3];
    int32_t b[3];
    int32_t z[3];
    int32_t x[3];
    int32_t y[3];
    int32_t state_error;
} biquad_t;

int16_t biquad_filter(int16_t s, biquad_t *b);
biquad_t generate_biquad(filter_type_t type, float Fc, float Fs, float Q, float peakGain);

#endif
