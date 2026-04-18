/// ------------------------------------------
/// @file filter_main.cpp
///
/// @brief main of time domain filter program
/// ------------------------------------------

#include <iostream>
#include <sys/time.h>

#include "inc/wave_gen.h"
#include "inc/filter.h"

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
    0.056840553407447363,
    0.012327731630716732,
    -0.133497693602039308,
    0.249143370307324946,
    0.630372076513100565,
    0.249143370307324946,
    -0.133497693602039308,
    0.012327731630716732,
    0.056840553407447363,
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