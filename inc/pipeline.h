#ifndef PIPELINE_H
#define PIPELINE_H
#pragma once

#include "constant.h"
#include "pow.h"
#include "gain.h"
#include "delay.h"
#include "iir.h"
#include "gate.h"
#include "compressor.h"
#include "virtual-bass.h"

void initilize(uint16_t samplerate);
void process_sample(int16_t *i16pSample1, int16_t *i16pSample2);
#endif
