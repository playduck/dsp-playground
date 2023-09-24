#ifndef GATE_H
#define GATE_H
#pragma once

#include "constant.h"

typedef struct
{
    float threshold;
    float gain;
    float hold;
    float alphaA;
    float alphaR;
    float OMalphaA;
    float OMalphaR;

    float gs;
    uint32_t Ca;
} dynamic_gate_t;

dynamic_gate_t generate_gate(
    float thresshold,
    float attack,
    float hold,
    float release,
    float gain,
    uint16_t samplerate);
void dynamic_gate(float *s, dynamic_gate_t *d);

#endif
