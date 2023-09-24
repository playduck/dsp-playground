#include "pipeline.h"

int32_t accumulator;

gain_t vol[2];
delay_line_t delay[2];
biquad_t filters[5 * 4];
dynamic_gate_t gate[4];
dynamic_compressor_t compressor[4];
virtual_bass_t vb[2];

sample_t sample1, sample2;

inline sample_t fixed_to_float(int16_t *s)
{
    return (sample_t)((sample_t)*s / (sample_t)UINT16_MAX);
}

inline int16_t float_to_fixed(sample_t* s)
{
    // hard clipping
    *s = CLAMP(*s, 1.0f, -1.0f);

    return (int16_t)(roundf(*s * (float)INT16_MAX));
}

void initilize(uint16_t samplerate)
{
    powFastSetTable();

    vol[0] = generate_gain(-3.0f);
    vol[1] = generate_gain(-3.0f);

    filters[0] = generate_biquad(lowpass, 2000, 0.54119610f, 0, samplerate);
    filters[1] = generate_biquad(lowpass, 2000, 1.3065630f, 0, samplerate);

    filters[2] = generate_biquad(highpass, 2000, 0.54119610f, 0, samplerate);
    filters[3] = generate_biquad(highpass, 2000, 1.3065630f, 0, samplerate);

    filters[4] = generate_biquad(highpass, 20, M_SQRT2_H, 0, samplerate);
    filters[5] = generate_biquad(highpass, 20, M_SQRT2_H, 0, samplerate);

    filters[6] = generate_biquad(peak, 80, 0.5, 3, samplerate);
    filters[7] = generate_biquad(peak, 55, 1.3, 1, samplerate);
    filters[8] = generate_biquad(peak, 2000, 0.5,  -1, samplerate);
    filters[9] = generate_biquad(highshelf, 8000, M_SQRT2_H, 4, samplerate);

    delay[0] = generate_delay_line(20, 0.2, samplerate);

    gate[0] = generate_gate(-40, 0.7, 0.8, 0.00001, 0, samplerate);
    gate[1] = generate_gate(-40, 0.7, 0.8, 0.00001, 0, samplerate);

    compressor[0] = generate_compressor(-8, 4, 3, 0.00001, 0.0001, 0, samplerate);
    compressor[1] = generate_compressor(-8, 4, 3, 0.00001, 0.0001, 0, samplerate);

    vb[0] = generate_virtual_bass(120, 250, -14.0, samplerate);
    vb[1] = generate_virtual_bass(120, 250, -14.0, samplerate);
}

float mono = 0.0f;
float hf = 0.0f, lf = 0.0f;

inline void process_sample(int16_t *i16pSample1, int16_t *i16pSample2)
{
    sample1 = fixed_to_float(i16pSample1);
    sample2 = fixed_to_float(i16pSample2);

    // mono = (sample1 + sample2) / 2.0f;
    // mono *= powf(10.0f, -4.0f / 20.0f); //-4dB

    // biquad_filter(&mono, filters + 4);
    // biquad_filter(&mono, filters + 5);

    // biquad_filter(&mono, filters + 6);
    // biquad_filter(&mono, filters + 7);
    // biquad_filter(&mono, filters + 8);
    // biquad_filter(&mono, filters + 9);

    // gain(&mono, vol + 0);
    // virtual_bass(&mono, vb);
    virtual_bass(&sample1, vb);
    virtual_bass(&sample2, vb + 1);
    // // dynamic_compressor(&mono, compressor + 0);

    // lf = mono;
    // hf = mono;

    // biquad_filter(&lf, filters + 0);
    // biquad_filter(&lf, filters + 1);

    // biquad_filter(&hf, filters + 2);
    // biquad_filter(&hf, filters + 3);

    // delay_line(&hf, delay);

    // dynamic_compressor(&lf, compressor + 0);
    // dynamic_compressor(&hf, compressor + 1);

    // gain(&lf, vol + 0);
    // gain(&hf, vol + 1);

    // dynamic_gate(&lf, gate + 0);
    // dynamic_gate(&hf, gate + 1);

    // lf *= 0.5;
    // hf *= 1.2;

    *i16pSample1 = float_to_fixed(&sample1);
    *i16pSample2 = float_to_fixed(&sample2);
}
