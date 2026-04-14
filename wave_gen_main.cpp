/// ------------------------------------------
/// @file wave_gen_main.cpp
///
/// @brief main of wave generation program
/// ------------------------------------------

# include <iostream>

#include "inc/wave_gen.h"

using std::cout;
using std::endl;

int main()
{
    const double sample_freq = 10e3;

    wave_spec_t sinwav = {.mag = 1, .freq = 1000, .phase = 0};
    wave_spec_t sin2 = {.mag = -2, .freq = 70, .phase = 0};

    auto sin_mixed = create_sinwave_sampletrain({sinwav, sin2}, 0, 1, sample_freq);
    save_sample_train_csv("outputs", "sinmix", sin_mixed);

    auto noise = create_noise_sampletrain(0, 1, sample_freq);
    save_sample_train_csv("outputs", "noise", noise);

    auto sin_read = read_sample_train_csv("outputs/sinmix.csv");
    save_sample_train_csv("outputs", "sinread", sin_read);

    return 0;
}