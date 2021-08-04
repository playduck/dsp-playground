#ifndef GATE_H
#define GATE_H
#include <stdint.h>
#include <math.h>

typedef struct
{
    float threshhold;
    float gain;
    float attack;
    float hold;
    float release;

    float gs;
    float Ca;
    float timestep;
} dynamic_gate_t;

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate);
void dynamic_gate(float *s, dynamic_gate_t *d);

#endif
