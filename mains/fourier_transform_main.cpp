/// ------------------------------------------
/// @file fourier_transform_main.cpp
///
/// @brief main of FT program
/// ------------------------------------------

#include <iostream>

#include "../inc/fourier_transform.h"

int main()
{
    auto wave_data = read_sample_train_csv("outputs/sinmix.csv");
    auto FT_data = DFT(wave_data);
    save_FT_points_csv("outputs", "FT_sin_res", FT_data);
    save_sample_train_csv("outputs", "sin_IFT", create_sinwave_sampletrain(FT_data, 0, 1, 1e3));

    auto noise_data = read_sample_train_csv("outputs/noise.csv");
    auto noise_FT = DFT(noise_data);
    save_FT_points_csv("outputs", "noise_FT", noise_FT);

    return 0;
}