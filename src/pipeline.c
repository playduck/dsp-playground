#include "pipeline.h"
#include <stdio.h>

sample_t fixed_to_float(int16_t* s)  {
    return (sample_t)((sample_t) *s / (sample_t)INT16_MAX);
}

int16_t float_to_fixed(sample_t s)   {
    return (int16_t)(roundf(tanhf(s) * INT16_MAX));
}

void initilize(uint16_t samplerate)
{
    for(uint8_t i = 0; i < (4*5); i++)    {
        filters[i] = generate_biquad(highpass, 180, M_SQRT2_H, 0, samplerate);
    }

    gate[0] = generate_gate(-26, 0.1, 0.2, 0.0001, 0, samplerate);
    gate[1] = generate_gate(-26, 0.1, 0.2, 0.0001, 0, samplerate);

    compressor[0] = generate_compressor(-8, 4, 3, 0.00001, 0.0001, -1, samplerate);
    compressor[1] = generate_compressor(-8, 4, 3, 0.00001, 0.0001, -1, samplerate);

    vb[0] = generate_virtual_bass(180, 280, -28.0, samplerate);
    vb[1] = generate_virtual_bass(180, 280, -28.0, samplerate);
}

void process_sample(channel_t channel, int16_t *i16pSample1, int16_t *i16pSample2)
{

    sample1 = fixed_to_float(i16pSample1);
    sample2 = fixed_to_float(i16pSample2);

    switch(channel)     {
        case CHANNEL_ONE:   {
            dynamic_gate(&sample1, gate);
            dynamic_gate(&sample2, gate + 1);

            virtual_bass(&sample1, vb);
            virtual_bass(&sample2, vb + 1);

            dynamic_compressor(&sample1, compressor);
            dynamic_compressor(&sample2, compressor + 1);

            biquad_filter(&sample1, filters + 0);
            biquad_filter(&sample2, filters + 1);
            break;
        }
        case CHANNEL_TWO:   {
            break;
        }
    }

    *i16pSample1 = float_to_fixed(sample1);
    *i16pSample2 = float_to_fixed(sample2);

}
