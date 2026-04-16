/// ------------------------------------------
/// @file fourier_transform_main.cpp
///
/// @brief main of FT program
/// ------------------------------------------

#include <iostream>
#include <sys/time.h>

#include "../inc/fourier_transform.h"

/// ------------------------------------------
unsigned long getMicrotime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
    // returns current time in micros
	return currentTime.tv_sec * (unsigned long)1e6 + currentTime.tv_usec;
}

using std::cout;
using std::endl;
int main()
{
    size_t start_time, end_time;

    auto wave_data = read_sample_train_csv("outputs/sinmix.csv");

    // start_time = getMicrotime();
    // auto DFT_data = DFT(wave_data);
    // end_time = getMicrotime();
    // std::cout << "DFT in " << end_time - start_time << " micros" << endl;

    // save_FT_points_csv("outputs", "DFT_sin_res", DFT_data);
    // save_sample_train_csv("outputs", "sin_IFT", create_sinwave_sampletrain(DFT_data, 0, 1, 1e3));

    start_time = getMicrotime();
    auto FFT_data = FFT(wave_data);
    end_time = getMicrotime();
    std::cout << "FFT in " << end_time - start_time << " micros" << endl;
    save_FT_points_csv("outputs", "FFT_sin_res", FFT_data);
    save_sample_train_csv("outputs", "sin_IFFT", create_sinwave_sampletrain(FFT_data, 0, 1, 1e3));

    // auto noise_data = read_sample_train_csv("outputs/noise.csv");
    // auto noise_FT = FFT(noise_data);
    // save_FT_points_csv("outputs", "noise_FT", noise_FT);

    return 0;
}