#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdint.h>
#include <math.h>

#include "iir.h"
#include "gate.h"

typedef enum {
	CHANNEL_ONE = 0,
	CHANNEL_TWO = 2,
} channel_t;

biquad_t filters[5*4];
dynamic_gate_t gate[4];

float s1, s2;

void initilize(int);
void process_sample(channel_t,volatile int16_t *,volatile int16_t *);
#endif
