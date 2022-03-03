#include "pow.h"

const uint8_t precision = 10;
uint16_t pTable[1024]; // 2^10

// https://www.hxa.name/articles/content/fast-pow-adjustable_hxa7241_2007.html
const float _2p23 = 8388608.0f;

/**
 * Initialize powFast lookup table.
 *
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
void powFastSetTable()
{
    /* step along table elements and x-axis positions */
    float zeroToOne = 1.0f / ((float)(1 << precision) * 2.0f); /* A */
    int i;                                                     /* B */
    for (i = 0; i < (1 << precision); ++i)                     /* C */
    {
        /* make y-axis value for table element */
        const float f = ((float)pow(2.0f, zeroToOne) - 1.0f) * _2p23;
        pTable[i] = (unsigned int)(f < _2p23 ? f : (_2p23 - 1.0f));

        zeroToOne += 1.0f / (float)(1 << precision);
    } /* D */
}

/**
 * Get pow (fast!).
 *
 * @val        power to raise radix to
 * @ilog2      one over log, to required radix, of two
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
float powFastLookup(
    const float val,
    const float ilog2)
{
    /* build float bits */
    const int i = (int)((val * (_2p23 * ilog2)) + (127.0f * _2p23));

    /* replace mantissa with lookup */
    const int it = (i & 0xFF800000) | pTable[(i & 0x7FFFFF) >>  /* E */
                                             (23 - precision)]; /* F */

    /* convert bits to float */
    return *(float *)(&it);
}
