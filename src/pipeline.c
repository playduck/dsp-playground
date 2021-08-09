#include "pipeline.h"
#include <stdio.h>

void initilize(int samplerate)
{
    for(uint8_t i = 0; i < (4*5); i++)    {
        filters[i] = generate_biquad(lowpass, 600, samplerate, 0.707, 0);
    }

    gate[0] = generate_gate(-5, 0.08, 0.5, 0.00001, 0, samplerate);
    gate[1] = generate_gate(-5, 0.08, 0.08, 0.00001, 0, samplerate);
    gate[2] = generate_gate(-5, 0.08, 0.5, 0.00001, 0, samplerate);
    gate[3] = generate_gate(-5, 0.08, 0.5, 0.00001, 0, samplerate);
}

void process_sample(channel_t channel, volatile int16_t *sample1, volatile int16_t *sample2)
{
    switch(channel)     {
        case CHANNEL_ONE:   {
            // dynamic_gate(sample1, gate);
            // dynamic_gate(sample2, gate + 1);

            *sample1 = biquad_filter(*sample1, filters + 0);
            *sample1 = biquad_filter(*sample1, filters + 1);
            *sample1 = biquad_filter(*sample1, filters + 2);
            *sample1 = biquad_filter(*sample1, filters + 3);
            *sample1 = biquad_filter(*sample1, filters + 4);

            *sample2 = biquad_filter(*sample2, filters + 5);
            *sample2 = biquad_filter(*sample2, filters + 6);
            *sample2 = biquad_filter(*sample2, filters + 7);
            *sample2 = biquad_filter(*sample2, filters + 8);
            *sample2 = biquad_filter(*sample2, filters + 9);

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
