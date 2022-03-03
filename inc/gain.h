#ifndef GAIN_H
#define GAIN_H
#pragma once

#include "constant.h"
#include "pow.h"

typedef struct
{
    float current_gain_db;
    float target_gain_db;
} gain_t;

gain_t generate_gain(float gain);
void gain(sample_t *s, gain_t *g);
void set_target_range(float gain, gain_t *g);

#endif
