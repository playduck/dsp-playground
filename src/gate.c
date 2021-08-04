#include "gate.h"

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate)
{
    float tlin = powf(10.0f, (thresshold / 20.0f));
    double lnine = log10(9.0f);
    float alphaA = expf(-lnine / (attack * samplerate));
    float alphaR = expf(-lnine / (release * samplerate));
    float OMalphaA = (1 - alphaA);
    float OMalphaR = (1 - alphaR);

    dynamic_gate_t g = {
        .alphaA = alphaA,
        .alphaR = alphaR,
        .OMalphaA = OMalphaA,
        .OMalphaR = OMalphaR,

        .hold = (hold * samplerate),
        .gain = gain,
        .threshhold = tlin,

        .gs = 1.0f,
        .Ca = 0
    };

    return g;
}

inline void dynamic_gate(float *s, dynamic_gate_t *d)
{
    gc = fabsf(*s) < d->threshhold ? 0.0f : 1.0f;
    gs = gc;

    ++d->Ca;
    if (d->Ca > d->hold && gc <= d->gs)
    {
        // attack
        gs = d->alphaA * d->gs + d->OMalphaA * gc;
    }
    else if (d->Ca <= d->hold)
    {
        // hold
        gs = d->gs;
    }
    else if (gc > d->gs)
    {
        // release
        gs = d->alphaR * d->gs + d->OMalphaR * gc;
        d->Ca = 0.0f;
    }

    d->gs = gs;

    *s = *s * gs + d->gain;
}
