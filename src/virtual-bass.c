#include "virtual-bass.h"

virtual_bass_t generate_virtual_bass(float Lcutoff, float Ecutoff, float gain, uint16_t samplerate)   {
    float glin = powf(10.0f, (gain / 20.0f));

    virtual_bass_t vb = {
        .lr_lowpass = {
            generate_biquad(lowpass, Lcutoff, 0.54119610f, 0, samplerate),
            generate_biquad(lowpass, Lcutoff, 1.3065630f, 0, samplerate)
        },

        .lr_highpass = {
            generate_biquad(highpass, Lcutoff, 0.54119610f, 0, samplerate),
            generate_biquad(highpass, Lcutoff, 1.3065630f, 0, samplerate)
        },

        .nld_bandpass = {
            generate_biquad(highpass, Lcutoff, M_SQRT2_H, 0, samplerate),
            generate_biquad(lowpass, Ecutoff, M_SQRT2_H, 0, samplerate)
        },
        .gain = glin,
        .u1 = 0.0f,
        .y1 = 0.0f,
    };

    return vb;
}


inline float soft(float s)    {
    return tanhf(s);
}

inline void virtual_bass(sample_t* s, virtual_bass_t* vb)    {

    // X over
    sample_t hp = *s;
    sample_t lp = *s;

    biquad_filter(&lp, vb->lr_lowpass);
    biquad_filter(&lp, vb->lr_lowpass + 1);

    biquad_filter(&hp, vb->lr_highpass);
    biquad_filter(&hp, vb->lr_highpass + 1);

    // NLD
    float u0 = lp;
    float y0 = 0.0;

    if((u0 > 0.0f) && (vb->u1 <= 0.0f))  {
        y0 = 0.0f;
    }   else    {
        y0 = ((vb->y1 + vb->u1));
    }

    vb->u1 = u0;
    vb->y1 = y0;

    lp = y0;

    // Bandpass
    biquad_filter(&lp, vb->nld_bandpass);
    biquad_filter(&lp, vb->nld_bandpass + 1);

    // Gain & Mix
    *s = hp + (lp * vb->gain);

}
