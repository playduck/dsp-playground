#ifndef IIR_H
#define IIR_H
#include <math.h>

#ifndef M_PI
#define M_PI (3.1415926535897)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237)
#endif

typedef enum
{
    lowpass,
    highpass,
    bandpass,
    notch,
    peak,
    lowshelf,
    highshelf,
    none
} filter_type_t;

typedef struct
{
    filter_type_t type;
    float a[3];
    float b[3];
    float z[3];
} biquad_t;

void biquad_filter(float *s, biquad_t *b);
biquad_t generate_biquad(filter_type_t type, float Fc, float Fs, float Q, float peakGain);

#endif
