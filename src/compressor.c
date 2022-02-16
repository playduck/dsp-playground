#include "compressor.h"

dynamic_compressor_t generate_compressor(float threshold, float ratio, float width, float attack, float release, float gain, uint16_t samplerate)
{
    float glin = powf(10.0f, (gain / 20.0f)) - 1.0f;

    double lnine = log10(9.0f);
    float alphaA = expf(-lnine / (attack * samplerate));
    float alphaR = expf(-lnine / (release * samplerate));
    float OMalphaA = (1 - alphaA);
    float OMalphaR = (1 - alphaR);

    dynamic_compressor_t c = {
        .alphaA = alphaA,
        .alphaR = alphaR,
        .OMalphaA = OMalphaA,
        .OMalphaR = OMalphaR,

        .ratio = ratio,
        .width = width,
        .gain = glin,
        .threshold = threshold,

        .gs = 1.0f,

        .state_error = 0
    };

    return c;
}

void dynamic_compressor(int16_t *s, dynamic_compressor_t *c)
{
    
    float xnormal = fabsf((float)*s / (float)INT16_MAX);
    float xdb = 20.0f * log10f(xnormal);

    // gain computer
    float xsc = 0.0f;
    if(xdb < (c->threshold - (c->width/2)))  {
        xsc = xdb;
    }   else if(((c->threshold - (c->width/2)) <= xdb) && (xdb <= (c->threshold + (c->width/2)))) {
        xsc = xdb + (((1/c->ratio) - 1) * powf((xdb - c->threshold + (c->width/2)), 2))/(2 * c->width);
    }   else if(xdb > (c->threshold + (c->width/2)))    {
        xsc = c->threshold + ((xdb - c->threshold)/c->ratio);
    }
    gc = xsc - xdb;

    //smoothing
    if(gc <= gs)    {
        gs = c->alphaA * gs + c->OMalphaA * gc;
    }   else if(gc > gs)    {
        gs = c->alphaR * gs + c->OMalphaR * gc;
    }

    // printf("%f\n", gs);

    c->gs = gs;
    gs += c->gain;

    float glin = powf(10.0f, gs/20.0f);

    accumulator = c->state_error;
    accumulator += (*s) * (int32_t)(glin * scale14);

    accumulator = CLAMP(accumulator, ACC_MAX, ACC_MIN);

    c->state_error = accumulator & ACC_REM;

    *s = (accumulator >> q);
}