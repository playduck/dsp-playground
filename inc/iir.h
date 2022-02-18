#ifndef IIR_H
#define IIR_H
#pragma once

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
    float a[3];
    float b[3];
    float d[2];
} biquad_t;

void biquad_filter(sample_t *s, biquad_t *b);
biquad_t generate_biquad(filter_type_t type, float Fc, float Q, float peakGain, float Fs);

#endif
