/// ------------------------------------------
/// @file fourier_transform_main.cpp
///
/// @brief main of FT program
/// ------------------------------------------

#include <iostream>
#include <sys/time.h>

#include "../inc/fourier_transform.h"

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
    const size_t threads = 4;

    size_t start_time, end_time;

    if (argc != 4)
    {
        cout << "Useage: [input sample filepath] [output directory] [output name (.csv not needed)]" << endl;
        return 0;
    }

    auto sample_data = read_sample_train_csv(argv[1]);

    cout << "Performing FFT on: " << argv[1] << endl;
    cout << sample_data.size() << " samples" << endl;
    cout << "Saving to: " << argv[2] << "/" << argv[3] << ".csv" << std::endl;

    start_time = getMicrotime();
    auto FTT_data = FFT_threaded(sample_data, threads);
    end_time = getMicrotime();
    cout << "Done in " << end_time - start_time << " micros" << endl;

    save_FT_points_csv(argv[2], argv[3], FTT_data);

    return 0;
}