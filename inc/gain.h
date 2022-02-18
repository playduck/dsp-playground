#ifndef GAIN_H
#define GAIN_H
#pragma once

#include "constant.h"

typedef struct {
    float current_gain_db;
    float target_gain_db;
} gain_t;

static float gain_step = 0.001f; // dB/s

gain_t generate_gain(float gain);
void gain(sample_t* s, gain_t* g);
void set_target_range(float linear, gain_t* g);

#endif
