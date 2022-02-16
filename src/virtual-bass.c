#include "virtual-bass.h"

virtual_bass_t generate_virtual_bass(float Lcutoff, float Ecutoff, float gain, uint16_t samplerate)   {
    float glin = powf(10.0f, (gain / 20.0f));


    virtual_bass_t vb = {
        .lr_lowpass = {
            generate_biquad(lowpass, Lcutoff, samplerate, 0.54119610f, 0),
            generate_biquad(lowpass, Lcutoff, samplerate, 1.3065630f, 0)
        },
        
        .lr_highpass = {
            generate_biquad(highpass, Lcutoff, samplerate, 0.54119610f, 0),
            generate_biquad(highpass, Lcutoff, samplerate, 1.3065630f, 0)
        },
  
        .nld_bandpass = {
            generate_biquad(highpass, Lcutoff, samplerate, 0.7071f, 0),
            generate_biquad(lowpass, Ecutoff, samplerate, 0.7071f, 0)
        },
        .gain = glin,
        .u1 = 0.0f,
        .y1 = 0.0f,

        .state_error = 0
    };

    return vb;
}


inline float soft(float s)    {
    return tanhf(s);
}

inline void virtual_bass(int16_t* s, virtual_bass_t* vb)    {

    // X over
    int16_t hp = *s;
    int16_t lp = *s;

    biquad_filter(&lp, vb->lr_lowpass);
    biquad_filter(&lp, vb->lr_lowpass + 1);

    biquad_filter(&hp, vb->lr_highpass);
    biquad_filter(&hp, vb->lr_highpass + 1);

    // NLD
    float u0 = (float)lp / (float)INT16_MAX;
    float y0 = 0.0;

    if((u0 > 0.0f) && (vb->u1 <= 0.0f))  {
        y0 = 0.0f;
    }   else    {
        y0 = ((vb->y1 + vb->u1));
    }

    vb->u1 = u0;
    vb->y1 = y0;

    lp = (int16_t)roundf(y0 * INT16_MAX);

    // Bandpass
    biquad_filter(&lp, vb->nld_bandpass);
    biquad_filter(&lp, vb->nld_bandpass + 1);

    // Gain
    // *s = lp;
    // return;

    accumulator = vb->state_error;
    accumulator += lp * (int32_t)(scale14 * (vb->gain));

    accumulator = CLAMP(accumulator, ACC_MAX, ACC_MIN);

    vb->state_error = accumulator & ACC_REM;

    // Mix
    *s = hp + (accumulator >> q);
    // *s = (accumulator >> q);

    
}
