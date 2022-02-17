#ifndef PIPELINE_H
#define PIPELINE_H
#pragma once

#include <stdint.h>
#include <math.h>

#include "constant.h"

#include "iir.h"
#include "gate.h"
#include "compressor.h"
#include "virtual-bass.h"

typedef enum {
	CHANNEL_ONE = 0,
	CHANNEL_TWO = 2,
} channel_t;

int32_t accumulator;

biquad_t filters[5*4];
dynamic_gate_t gate[4];
dynamic_compressor_t compressor[4];
virtual_bass_t vb[2];

sample_t sample1, sample2;

void initilize(uint16_t samplerate);
void process_sample(channel_t channel, int16_t *i16pSample1, int16_t *i16pSample2);
#endif
