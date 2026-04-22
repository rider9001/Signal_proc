/// ------------------------------------------
/// @file wave_gen_main.cpp
///
/// @brief main of wave generation program
/// ------------------------------------------

# include <iostream>

#include "../inc/wave_gen.h"

using std::cout;
using std::endl;

int main()
{
    const double sample_freq = pow(2,18);

    const double start_time = 0;
    const double end_time = 1;

    wave_spec_t sinwav = {.mag = 1, .freq = 15e3, .phase = 0};
    wave_spec_t sin2 = {.mag = 1, .freq = 100, .phase = 0};
    wave_spec_t sin3 = {.mag = 1, .freq = 30e3, .phase = 0};

    auto sin_mixed = create_sinwave_sampletrain({sinwav, sin2, sin3}, start_time, end_time, sample_freq);
    save_sample_train_csv("outputs", "sinmix", sin_mixed);

    auto noise = create_noise_sampletrain(start_time, end_time, sample_freq);
    save_sample_train_csv("outputs", "noise", noise);

    auto square = create_square_sampletrain(1e3, start_time, end_time, sample_freq);
    save_sample_train_csv("outputs", "square", square);

    return 0;
}