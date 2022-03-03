#include "gain.h"

gain_t generate_gain(float gain)
{
    gain_t g = {
        .current_gain_db = -100.0f,
        .target_gain_db = gain};

    return g;
}

inline void gain(sample_t *s, gain_t *g)
{
    // single pole low pass, b = 0.0001, d = 1-b 0.9999 -> tau = -1/ln(d) = 9949 samples
    // https://tomroelandts.com/articles/low-pass-single-pole-iir-filter
    g->current_gain_db += 0.0001f * (g->target_gain_db - g->current_gain_db);

    float linGain = powf(10.0f, g->current_gain_db / 20.0f);
    // float linGain = powFastLookup(g->current_gain_db / 20.0f, BASE10);

    *s = (*s) * linGain;
}

void set_target_range(float gain, gain_t *g)
{
    g->target_gain_db = gain;
}
