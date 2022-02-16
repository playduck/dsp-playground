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
    float u1;
    float y1;

    int32_t state_error;
} virtual_bass_t;

extern int32_t accumulator;

virtual_bass_t generate_virtual_bass(float Lcutoff, float Ecutoff, float gain, uint16_t samplerate);
void virtual_bass(int16_t* s, virtual_bass_t* vb);

#endif