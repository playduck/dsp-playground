#include "iir.h"

inline void biquad_filter(float *s, biquad_t *b)
{
    float out = *s * b->a[0] + b->z[1];
    b->z[1] = (*s * b->a[1]) + (b->z[2] - b->b[1] * out);
    b->z[2] = (*s * b->a[2]) - (b->b[2] * out);
    *s = out;
}

// https://www.earlevel.com/main/2011/01/02/biquad-formulas/
biquad_t generate_biquad(filter_type_t type, float Fc, float Fs, float Q, float peakGain)
{
    float a0 = 0, a1 = 0, a2 = 0, b1 = 0, b2 = 0, norm = 0;

    float V = powf(10, fabsf(peakGain) / 20);
    float K = tanf(M_PI * Fc / Fs);

    switch (type)
    {
    case lowpass:
        norm = 1 / (1 + K / Q + K * K);
        a0 = K * K * norm;
        a1 = 2 * a0;
        a2 = a0;
        b1 = 2 * (K * K - 1) * norm;
        b2 = (1 - K / Q + K * K) * norm;
        break;

    case highpass:
        norm = 1 / (1 + K / Q + K * K);
        a0 = 1 * norm;
        a1 = -2 * a0;
        a2 = a0;
        b1 = 2 * (K * K - 1) * norm;
        b2 = (1 - K / Q + K * K) * norm;
        break;

    case bandpass:
        norm = 1 / (1 + K / Q + K * K);
        a0 = K / Q * norm;
        a1 = 0;
        a2 = -a0;
        b1 = 2 * (K * K - 1) * norm;
        b2 = (1 - K / Q + K * K) * norm;
        break;

    case notch:
        norm = 1 / (1 + K / Q + K * K);
        a0 = (1 + K * K) * norm;
        a1 = 2 * (K * K - 1) * norm;
        a2 = a0;
        b1 = a1;
        b2 = (1 - K / Q + K * K) * norm;
        break;

    case peak:
        if (peakGain >= 0)
        { // boost
            norm = 1 / (1 + 1 / Q * K + K * K);
            a0 = (1 + V / Q * K + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = (1 - V / Q * K + K * K) * norm;
            b1 = a1;
            b2 = (1 - 1 / Q * K + K * K) * norm;
        }
        else
        { // cut
            norm = 1 / (1 + V / Q * K + K * K);
            a0 = (1 + 1 / Q * K + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = (1 - 1 / Q * K + K * K) * norm;
            b1 = a1;
            b2 = (1 - V / Q * K + K * K) * norm;
        }
        break;
    case lowshelf:
        if (peakGain >= 0)
        { // boost
            norm = 1 / (1 + M_SQRT2 * K + K * K);
            a0 = (1 + sqrtf(2 * V) * K + V * K * K) * norm;
            a1 = 2 * (V * K * K - 1) * norm;
            a2 = (1 - sqrtf(2 * V) * K + V * K * K) * norm;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - M_SQRT2 * K + K * K) * norm;
        }
        else
        { // cut
            norm = 1 / (1 + sqrtf(2 * V) * K + V * K * K);
            a0 = (1 + M_SQRT2 * K + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = (1 - M_SQRT2 * K + K * K) * norm;
            b1 = 2 * (V * K * K - 1) * norm;
            b2 = (1 - sqrtf(2 * V) * K + V * K * K) * norm;
        }
        break;
    case highshelf:
        if (peakGain >= 0)
        { // boost
            norm = 1 / (1 + M_SQRT2 * K + K * K);
            a0 = (V + sqrtf(2 * V) * K + K * K) * norm;
            a1 = 2 * (K * K - V) * norm;
            a2 = (V - sqrtf(2 * V) * K + K * K) * norm;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - M_SQRT2 * K + K * K) * norm;
        }
        else
        { // cut
            norm = 1 / (V + sqrtf(2 * V) * K + K * K);
            a0 = (1 + M_SQRT2 * K + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = (1 - M_SQRT2 * K + K * K) * norm;
            b1 = 2 * (K * K - V) * norm;
            b2 = (V - sqrtf(2 * V) * K + K * K) * norm;
        }
        break;
    case none:
    default:
        type = none;
        a0 = 0;
        a1 = 0;
        a2 = 0;
        b1 = 0;
        b2 = 0;
        break;
    }

    biquad_t flt = {
        .type = type,
        .a = {a0, a1, a2},
        .b = {0, b1, b2},
        .z = {0, 0, 0}};

    return flt;
}
