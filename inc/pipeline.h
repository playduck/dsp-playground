#ifndef PIPELINE_H
#define PIPELINE_H
#pragma once

#include "constant.h"

#include "gain.h"
#include "delay.h"
#include "iir.h"
#include "gate.h"
#include "compressor.h"
#include "virtual-bass.h"

int32_t accumulator;

gain_t vol[2];
delay_line_t delay[2];
biquad_t filters[5*4];
dynamic_gate_t gate[4];
dynamic_compressor_t compressor[4];
virtual_bass_t vb[2];

sample_t sample1, sample2;

void initilize(uint16_t samplerate);
void process_sample(int16_t *i16pSample1, int16_t *i16pSample2);
#endif
