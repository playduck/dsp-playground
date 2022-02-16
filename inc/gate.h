#ifndef GATE_H
#define GATE_H
#pragma once

#include <stdint.h>
#include <math.h>

#include "constant.h"

typedef struct
{
    float threshold;
    float gain;
    uint32_t hold;
    float alphaA;
    float alphaR;
    float OMalphaA;
    float OMalphaR;

    float gs;
    uint32_t Ca;
    
    int32_t state_error;
} dynamic_gate_t;

float gc;
float gs;

extern int32_t accumulator;

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate);
void dynamic_gate(int16_t *s, dynamic_gate_t *d);

#endif
