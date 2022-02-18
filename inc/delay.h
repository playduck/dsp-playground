#ifndef DELAY_H
#define DELAY_H
#pragma once

#include "constant.h"

typedef struct {
    sample_t* buffer;
    float wet;
    float delayMs;

    uint16_t readPointer;
    uint16_t sampleAmt;

} delay_line_t;

delay_line_t generate_delay_line(float ms, float wet, uint16_t samplerate);
void delay_line(sample_t* s, delay_line_t* d);

#endif
