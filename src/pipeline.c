#include "pipeline.h"

biquad_t filters[5*2];
dynamic_gate_t gate[2];

float s1, s2;

void initilize(int samplerate)
{
    filters[0] = generate_biquad(highpass, 5200, samplerate, 1.707, 0);
    filters[1] = generate_biquad(lowpass, 440, samplerate, 0.707, 6);

    gate[0] = generate_gate(-8, 0.08, 0.04, 0.00001, 0, samplerate);
    gate[1] = generate_gate(-8, 0.08, 0.04, 0.00001, 0, samplerate);
}

void process_sample(int16_t *sample1, int16_t *sample2)
{
    s1 = *sample1;
    s2 = *sample2;
    s1 /= INT16_MAX;
    s2 /= INT16_MAX;

    dynamic_gate(&s1, gate);
    dynamic_gate(&s2, gate + 1);

    biquad_filter(&s1, filters);
    biquad_filter(&s2, filters + 1);

    *sample1 = (int16_t)roundf(s2 * INT16_MAX);
    *sample2 = (int16_t)roundf(s2 * INT16_MAX);
}
