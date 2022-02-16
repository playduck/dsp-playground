#include "virtual-bass.h"

virtual_bass_t generate_virtual_bass(float Hc, float level, uint16_t samplerate)   {

    virtual_bass_t vb = {
        .lr_highpass = {
            generate_biquad(highpass, Hc, samplerate, 0.54119610f, 0),
            generate_biquad(highpass, Hc, samplerate, 1.3065630f, 0)
        },
        .lr_lowpass = {
            generate_biquad(lowpass, Hc, samplerate, 0.54119610f, 0),
            generate_biquad(lowpass, Hc, samplerate, 1.3065630f, 0)
        },
        .nld_highpass = generate_biquad(highpass, Hc, samplerate, 0.70710678f, 0),

        .env = 0,
        .level = level,
        .timeConstant = powf(0.5, MAX((Hc / 100.0), 1.0)),
        
        .state_error = 0
    };

    return vb;
}


inline float nld(float s, float e, float level)    {
    e = (e > 0.0) ? MAX(1.0/e, 1000.0) : 1000.0;
    float e2 = e*e; 
    float e3 = e*e2; 
    float s2 = s*s; 
    float s3 = s*s2; 
    float s4 = s*s2; 

    return e*s2*level + e2*s3*level*0.9 + e3*s4*level*0.5;
}

inline float soft(float s)    {
    return tanhf(s);
}

inline void virtual_bass(int16_t* s, virtual_bass_t* vb)    {

    // FIL 1
    int16_t lf = *s;
    //biquad_filter(&lf, vb->lr_lowpass);
   //biquad_filter(&lf, vb->lr_lowpass + 1);
    //biquad_filter(&lf, &vb->nld_highpass);

    biquad_filter(s, vb->lr_highpass);
    biquad_filter(s, vb->lr_highpass + 1);

    float lfnorm = (float)lf / (float)INT16_MAX;

    vb->env = MAX(vb->env, fabs(lfnorm));

    // NLD
   // lfnorm = soft(nld(lfnorm, vb->env, vb->level));
    //printf("%f\n", lfnorm);
    //lf = (int16_t)roundf(lfnorm * INT16_MAX);


    // MIX

    // accumulator = vb->state_error;
    // accumulator += (*s) + lf;

    // accumulator = CLAMP(accumulator, ACC_MAX, ACC_MIN);

    // vb->state_error = accumulator & ACC_REM;
    // *s = accumulator;
    //*s = *s + lf;

    // FIL 2


    vb->env = vb->env * vb->timeConstant;
}
