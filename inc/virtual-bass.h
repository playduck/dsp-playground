#ifndef VIRTUAL_BASS_H
#define VIRTUAL_BASS_H
#pragma once

#include "constant.h"
#include "iir.h"

typedef struct {
    biquad_t lr_highpass[2];
    biquad_t lr_lowpass[2];
    biquad_t nld_bandpass[2];

    float gain;
    sample_t u1;
    sample_t y1;
} virtual_bass_t;

extern int32_t accumulator;

virtual_bass_t generate_virtual_bass(float Lcutoff, float Ecutoff, float gain, uint16_t samplerate);
void virtual_bass(sample_t* s, virtual_bass_t* vb);

#endif
