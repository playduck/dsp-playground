#ifndef POW_H
#define POW_H
#pragma once

#include "constant.h"

#define BASE2 1.0f
#define BASEE 1.44269504088896f
#define BASE10 3.32192809488736f
#define BASEN(n) (logf(n) * 1.44269504088896)

void powFastSetTable();

float powFastLookup(
    const float val,
    const float ilog2);

#endif
