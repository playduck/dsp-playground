#include "delay.h"

delay_line_t generate_delay_line(float ms, float wet, uint16_t samplerate) {

    uint16_t delay_samples = (uint16_t)roundf((ms/1000.0f) * (float)samplerate);
    sample_t* delay_buffer = (sample_t*)malloc(delay_samples * sizeof(sample_t));

    if(delay_buffer != NULL)    {
        for(uint16_t i = 0; i < delay_samples; i++) {
            delay_buffer[i] = 0.0f;
        }
    }

    delay_line_t delay_line = {
        .buffer = delay_buffer,
        .delayMs = ms,
        .wet = wet,
        .sampleAmt = delay_samples,
        .readPointer = 0,
    };

    return delay_line;
}

void delay_line(sample_t* s, delay_line_t* d)   {
    uint16_t writePointer = d->readPointer;
    d->readPointer = (d->readPointer + 1) % d->sampleAmt;

    d->buffer[writePointer] = *s;
    *s = (*s) * (1-d->wet) + (d->buffer[d->readPointer]) * (d->wet);
}
