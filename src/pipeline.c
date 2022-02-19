#include "pipeline.h"
#include <stdio.h>

sample_t fixed_to_float(int16_t *s)
{
    return (sample_t)((sample_t)*s / (sample_t)INT16_MAX);
}

int16_t float_to_fixed(sample_t s)
{
    // hard clipping
    s = (s >= 1.0f) ? 1.0f : s;
    s = (s <= -1.0f) ? -1.0f : s;

    return (int16_t)(roundf(s * (float)INT16_MAX));
}

void initilize(uint16_t samplerate)
{
    // crossover lowpass
    filters[0] = generate_biquad(lowpass, 2000.0f, 0.54119610f, 0.0f, samplerate);
    filters[1] = generate_biquad(lowpass, 2000.0f, 1.3065630f, 0.0f, samplerate);
    // crossover highpass
    filters[2] = generate_biquad(highpass, 2000.0f, 0.54119610f, 0.0f, samplerate);
    filters[3] = generate_biquad(highpass, 2000.0f, 1.3065630f, 0.0f, samplerate);

    // lowcut
    filters[4] = generate_biquad(highpass, 40.0f, 0.54119610f, 0.0f, samplerate);
    filters[5] = generate_biquad(highpass, 40.0f, 1.3065630f, 0.0f, samplerate);

    delay[0] = generate_delay_line(40.0f, 0.2f, samplerate);
    vb[0] = generate_virtual_bass(100.0f, 220.0f, -34.0f, samplerate);

    gate[0] = generate_gate(-40.0f, 0.7f, 0.8f, 0.00001f, 0.0f, samplerate);
    gate[1] = generate_gate(-40.0f, 0.7f, 0.8f, 0.00001f, 0.0f, samplerate);

    compressor[0] = generate_compressor(-8.0f, 4.0f, 3.0f, 0.00001f, 0.0001f, -1.0f, samplerate);
    compressor[1] = generate_compressor(-8.0f, 4.0f, 3.0f, 0.00001f, 0.0001f, -1.0f, samplerate);

    vol[0] = generate_gain(-3.0f);
    vol[1] = generate_gain(-3.0f);
}

void process_sample(int16_t *i16pSample1, int16_t *i16pSample2)
{
    sample1 = fixed_to_float(i16pSample1);
    sample2 = fixed_to_float(i16pSample2);
    float mono = (sample1 + sample2) / 2.0f;

    // lowcut
    biquad_filter(&mono, filters + 4);
    biquad_filter(&mono, filters + 5);

    float lf = mono;
    float hf = mono;

    // crossover
    biquad_filter(&lf, filters + 0);
    biquad_filter(&lf, filters + 1);

    biquad_filter(&hf, filters + 2);
    biquad_filter(&hf, filters + 3);

    // fx
    virtual_bass(&lf, vb);
    delay_line(&hf, delay);

    // dynamics
    dynamic_compressor(&lf, compressor + 0);
    dynamic_compressor(&hf, compressor + 1);

    gain(&lf, vol + 0);
    gain(&hf, vol + 1);

    dynamic_gate(&lf, gate + 0);
    dynamic_gate(&hf, gate + 1);

    *i16pSample1 = float_to_fixed(hf);
    *i16pSample2 = float_to_fixed(lf);
}
