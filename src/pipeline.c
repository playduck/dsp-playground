#include "pipeline.h"


void initilize(int samplerate)
{
    for(uint8_t i = 0; i < 4*5; i++)    {
        filters[i] = generate_biquad(highpass, 100 * i, samplerate, 0.707, 0);
    }

    gate[0] = generate_gate(-100, 0.08, 0.04, 0.00001, 0, samplerate);
    gate[1] = generate_gate(-100, 0.08, 0.04, 0.00001, 0, samplerate);
    gate[2] = generate_gate(-100, 0.08, 0.04, 0.00001, 0, samplerate);
    gate[3] = generate_gate(-100, 0.08, 0.04, 0.00001, 0, samplerate);
}

void process_sample(channel_t channel, volatile int16_t *sample1, volatile int16_t *sample2)
{
    s1 = *sample1;
    s2 = *sample2;
    s1 /= INT16_MAX;
    s2 /= INT16_MAX;

    switch(channel)     {
        case CHANNEL_ONE:   {
            dynamic_gate(&s1, gate);
            dynamic_gate(&s2, gate + 1);

            biquad_filter(&s1, filters + 0);
            biquad_filter(&s1, filters + 1);
            biquad_filter(&s1, filters + 2);
            biquad_filter(&s1, filters + 3);
            biquad_filter(&s1, filters + 4);

            biquad_filter(&s2, filters + 5);
            biquad_filter(&s2, filters + 6);
            biquad_filter(&s2, filters + 7);
            biquad_filter(&s2, filters + 8);
            biquad_filter(&s2, filters + 9);

            break;
        }
        case CHANNEL_TWO:   {
            dynamic_gate(&s1, gate + 2);
            dynamic_gate(&s2, gate + 3);

            biquad_filter(&s1, filters + 10);
            biquad_filter(&s1, filters + 11);
            biquad_filter(&s1, filters + 12);
            biquad_filter(&s1, filters + 13);
            biquad_filter(&s1, filters + 14);

            biquad_filter(&s2, filters + 15);
            biquad_filter(&s2, filters + 16);
            biquad_filter(&s2, filters + 17);
            biquad_filter(&s2, filters + 18);
            biquad_filter(&s2, filters + 19);

            break;
        }
    }

    *sample1 = (int16_t)roundf(s1 * INT16_MAX);
    *sample2 = (int16_t)roundf(s2 * INT16_MAX);
}
