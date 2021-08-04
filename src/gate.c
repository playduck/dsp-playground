#include "gate.h"

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate)
{
    float tlin = powf(10.0f, (thresshold / 20.0f));
    double lnine = log10(9.0f);
    float alphaA = expf(-lnine / (attack * samplerate));
    float alphaR = expf(-lnine / (release * samplerate));

    dynamic_gate_t g = {
        .attack = alphaA,
        .release = alphaR,
        .hold = hold,
        .gain = gain,
        .threshhold = tlin,
        .gs = 1.0f,
        .Ca = 0.0f,
        .timestep = 1.0f / samplerate};

    return g;
}

inline void dynamic_gate(float *s, dynamic_gate_t *d)
{
    float abs = fabsf(*s);
    float gc = abs < d->threshhold ? 0.0f : 1.0f;
    float gs = gc;

    d->Ca += d->timestep;
    if (d->Ca > d->hold && gc <= d->gs)
    {
        // attack
        gs = d->attack * d->gs + (1 - d->attack) * gc;
    }
    else if (d->Ca <= d->hold)
    {
        // hold
        gs = d->gs;
    }
    else if (gc > d->gs)
    {
        // release
        gs = d->release * d->gs + (1 - d->release) * gc;
        d->Ca = 0.0f;
    }

    d->gs = gs;

    *s = *s * gs + d->gain;
}
