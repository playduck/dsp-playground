#ifndef IIR_H
#define IIR_H
#pragma once

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "constant.h"

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

extern int32_t accumulator;

void biquad_filter(int16_t *s, biquad_t *b);
biquad_t generate_biquad(filter_type_t type, float Fc, float Fs, float Q, float peakGain);

#endif
