// #ifndef PIPELINE_H
#define PIPELINE_H

#include <stdint.h>
#include <math.h>

#include "iir.h"
#include "gate.h"

void initilize(int);
void process_sample(int16_t *, int16_t *);
// #endif
