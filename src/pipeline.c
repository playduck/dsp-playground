#include "pipeline.h"
#include <stdio.h>

void initilize(int samplerate)
{
    for(uint8_t i = 0; i < (4*5); i++)    {
        filters[i] = generate_biquad(highpass, 800, samplerate, 2, 0);
    }

    gate[0] = generate_gate(-20, 0.05, 0.01, 0.001, 0, samplerate);
    gate[1] = generate_gate(-2, 0.05, 0.01, 0.001, 0, samplerate);

    compressor[0] = generate_compressor(-24, 50, 2, 0.0001, 0.0001, -2, samplerate);
    compressor[1] = generate_compressor(-24, 50, 2, 0.0001, 0.0001, 0, samplerate);

    vb[0] = generate_virtual_bass(200, 0.0001, samplerate);
    vb[1] = generate_virtual_bass(200, 0.0001, samplerate);
}

void process_sample(channel_t channel, volatile int16_t *sample1, volatile int16_t *sample2)
{
    switch(channel)     {
        case CHANNEL_ONE:   {
            // dynamic_gate(sample1, gate);
            // dynamic_gate(sample2, gate + 1);

            //dynamic_compressor(sample1, compressor);
            // dynamic_compressor(sample2, compressor + 1);

            // virtual_bass(sample1, vb);
            // virtual_bass(sample2, vb + 1);

            biquad_filter(sample1, filters + 0);
            // biquad_filter(sample1, filters + 1);
            // biquad_filter(sample1, filters + 2);
            // biquad_filter(sample1, filters + 3);
            // biquad_filter(sample1, filters + 4);

            biquad_filter(sample2, filters + 5);
            // biquad_filter(sample2, filters + 6);
            // biquad_filter(sample2, filters + 7);
            // biquad_filter(sample2, filters + 8);
            // biquad_filter(sample2, filters + 9);

            break;
        }
        case CHANNEL_TWO:   {
            // dynamic_gate(sample1, gate + 2);
            // dynamic_gate(sample2, gate + 3);

            *sample2 = biquad_filter(*sample2, filters + 10);
            *sample1 = biquad_filter(*sample1, filters + 11);
            *sample1 = biquad_filter(*sample1, filters + 12);
            *sample1 = biquad_filter(*sample1, filters + 13);
            *sample1 = biquad_filter(*sample1, filters + 14);

            *sample2 = biquad_filter(*sample2, filters + 15);
            *sample2 = biquad_filter(*sample2, filters + 16);
            *sample2 = biquad_filter(*sample2, filters + 17);
            *sample2 = biquad_filter(*sample2, filters + 18);
            *sample2 = biquad_filter(*sample2, filters + 19);

            break;
        }
    }
}
