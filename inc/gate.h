#ifndef GATE_H
#define GATE_H
#include <stdint.h>
#include <math.h>

typedef struct
{
    float threshhold;
    float gain;
    uint32_t hold;
    float alphaA;
    float alphaR;
    float OMalphaA;
    float OMalphaR;

    float gs;
    uint32_t Ca;
} dynamic_gate_t;

float gc;
float gs;

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate);
void dynamic_gate(float *s, dynamic_gate_t *d);

#endif
