#include "gain.h"

gain_t generate_gain(float gain)    {
    gain_t g = {
        .current_gain_db = -100.0f,
        .target_gain_db = gain
    };

    return g;
}

void gain(sample_t* s, gain_t* g) {
    float gDiff = g->current_gain_db - g->target_gain_db;

    if(fabsf(gDiff) <= (2.0f * gain_step))    {
        g->current_gain_db = g->target_gain_db;
    }   else if(gDiff > 0.0f)   {
        // ramp up
        g->current_gain_db -= gain_step;
    }   else if(gDiff < 0.0f)   {
        // ramp down
        g->current_gain_db += gain_step;
    }

    float linGain = powf(10.0f, g->current_gain_db / 20.0f);

    *s = (*s) * linGain;
}


void set_target_range(float linear, gain_t* g)  {
    linear = CLAMP(linear, 0.00001f, 1.0f);

    float gain = 20.0f * log10f(linear);

    g->target_gain_db = gain;
}
