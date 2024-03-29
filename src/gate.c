#include "gate.h"

float gainComputedGate;
float gainSmootedGate;

dynamic_gate_t generate_gate(
    float thresshold,
    float attack,
    float hold,
    float release,
    float gain,
    uint16_t samplerate)
{
    float tlin = powf(10.0f, (thresshold / 20.0f));
    float glin = powf(10.0f, (gain / 20.0f)) - 1.0f;
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
        .gain = glin,
        .threshold = tlin,

        .gs = 1.0f,
        .Ca = 0};

    return g;
}

inline void dynamic_gate(float *s, dynamic_gate_t *d)
{
    if (fabsf(*s) < d->threshold)
    {
        gainComputedGate = 0.0f;
    }
    else
    {
        gainComputedGate = 1.0f;
    }

    d->Ca = d->Ca + 1;
    if (d->Ca > d->hold && gainComputedGate <= d->gs)
    {
        // attack
        gainSmootedGate = d->alphaA * d->gs + d->OMalphaA * gainComputedGate;
    }
    else if (d->Ca <= d->hold)
    {
        // hold
        gainSmootedGate = d->gs;
    }
    else if (gainComputedGate > d->gs)
    {
        // release
        gainSmootedGate = d->alphaR * d->gs + d->OMalphaR * gainComputedGate;
        d->Ca = 0;
    }

    // makeup
    d->gs = gainSmootedGate;
    gainSmootedGate += d->gain;

    *s = (*s) * gainSmootedGate;
}
