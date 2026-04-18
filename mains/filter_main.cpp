/// ------------------------------------------
/// @file filter_main.cpp
///
/// @brief main of time domain filter program
/// ------------------------------------------

#include <iostream>
#include <sys/time.h>

#include "../inc/wave_gen.h"
#include "../inc/filter.h"

using std::cout;
using std::endl;

/// ------------------------------------------
unsigned long getMicrotime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
    // returns current time in micros
	return currentTime.tv_sec * (unsigned long)1e6 + currentTime.tv_usec;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "Useage: [input sample filepath] [output directory] [output name (.csv not needed)]" << endl;
        return 0;
    }

    size_t start_time, end_time;

    std::vector<double> coeffs = {
    -0.021649715448617334,
    0.000000000000000020,
    0.024980440902250763,
    -0.000000000000000020,
    -0.029522339248114544,
    0.000000000000000020,
    0.036082859081028887,
    -0.000000000000000020,
    -0.046392247389894281,
    0.000000000000000020,
    0.064949146345851985,
    -0.000000000000000020,
    -0.108248577243086647,
    0.000000000000000020,
    0.324745731729259968,
    0.510109402542642476,
    0.324745731729259968,
    0.000000000000000020,
    -0.108248577243086647,
    -0.000000000000000020,
    0.064949146345851985,
    0.000000000000000020,
    -0.046392247389894281,
    -0.000000000000000020,
    0.036082859081028887,
    0.000000000000000020,
    -0.029522339248114544,
    -0.000000000000000020,
    0.024980440902250763,
    0.000000000000000020,
    -0.021649715448617334,
    };

    auto sample_data = read_sample_train_csv(argv[1]);

    cout << "Performing FIR on: " << argv[1] << endl;
    cout << sample_data.size() << " samples" << endl;
    cout << "Saving to: " << argv[2] << "/" << argv[3] << ".csv" << std::endl;

    start_time = getMicrotime();
    auto filtered_wave = FIR_filter(sample_data, coeffs);
    end_time = getMicrotime();
    cout << "Done in " << end_time - start_time << " micros" << endl;

    save_sample_train_csv(argv[2], argv[3], filtered_wave);

    return 0;
}