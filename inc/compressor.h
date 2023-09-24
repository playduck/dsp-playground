#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#pragma once

#include "constant.h"
#include "pow.h"

typedef struct
{
    float threshold;
    float ratio;
    float width;
    float gain;
    float alphaA;
    float alphaR;
    float OMalphaA;
    float OMalphaR;

    float gs;
} dynamic_compressor_t;

extern int32_t accumulator;

dynamic_compressor_t generate_compressor(
    float threshold,
    float ratio,
    float width,
    float attack,
    float release,
    float gain,
    uint16_t samplerate);
void dynamic_compressor(sample_t *s, dynamic_compressor_t *c);

#endif
