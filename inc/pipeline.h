#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdint.h>
#include <math.h>

#include "iir.h"
#include "gate.h"

typedef enum {
	CHANNEL_ONE,
	CHANNEL_TWO,
} channel_t;

void initilize(int);
void process_sample(channel_t, int16_t *, int16_t *);
#endif
