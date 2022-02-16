#include "gate.h"

dynamic_gate_t generate_gate(float thresshold, float attack, float hold, float release, float gain, uint16_t samplerate)
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
        .Ca = 0,

        .state_error = 0
    };

    return g;
}

inline void dynamic_gate(int16_t *s, dynamic_gate_t *d)
{
    if((fabsf((float)*s / (float)INT16_MAX)) < d->threshold)   {
        gc = 0.0f;
    }   else    {
        gc = 1.0f;
    }

    d->Ca = d->Ca + 1;
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
        d->Ca = 0;
    }

    d->gs = gs;
    gs += d->gain;

    accumulator = d->state_error;
    accumulator += (*s) * (int32_t)(gs * scale14);

    accumulator = CLAMP(accumulator, ACC_MAX, ACC_MIN);

    d->state_error = accumulator & ACC_REM;

    *s = (accumulator >> q);
}
