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

void initilize(int);
void process_sample(channel_t,volatile int16_t *,volatile int16_t *);
#endif
