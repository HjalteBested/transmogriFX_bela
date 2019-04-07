//
// klingon-tone overdrive effect
//  Approximate voicing of King of Tone overdrive pedal
//

#include "iir_1pole.h"

#ifndef KLINGON_H
#define KLINGON_H

typedef struct klingon_t
{
    float fs;  // Sampling frequency
    float clipper_fs; // nonlinear processing sampling frequency
    unsigned int oversample;  // Oversampling rate
    unsigned int blksz;
    float inverse_oversample_float;

    // User control settings
    float gain;   // Distortion amount
    float tone;   // Tone control
    float level;  // Output level
    bool bypass;

    // Processing buffers
    float *procbuf;

    // State variables
    float xn1;
    float xc1;

    // Pre and post emphasis EQ
    iir_1p anti_alias;
    iir_1p pre_emph589;
    iir_1p pre_emph482;
    iir_1p pre_emph159;
    iir_1p post_emph;
    iir_1p tone_lp;
    iir_1p tone_hp;

    // Gain stages
    float g482;  // first stage pre-emphasis 1 gain
    float g589;  // first stage pre-emphasis 2 gain
    float g159;  // second stage pre-emphais gain
    float gclip; // gain when diodes are fully on

} klingon;

// Allocate the klingon struct and set default values
klingon* make_klingon(klingon* kot, unsigned int oversample, unsigned int bsz, float fs);
void klingon_cleanup(klingon* kot);

// Typical real-time user-configurable parameters
void kot_set_drive(klingon* kot, float drive_db);   // 0 dB to 45 dB
void kot_set_tone(klingon* kot, float lp_level_db); // high frequency cut, -60dB to 0dB
void kot_set_level(klingon* kot, float outlevel_db); // -40 dB to +0 dB
bool kot_set_bypass(klingon* kot, bool bypass);

// Run the klingon effect
void klingon_tick(klingon* kot, float* x);

#endif //KLINGON_H
