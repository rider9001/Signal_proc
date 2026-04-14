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
    wave_spec_t sinwav = {.mag = 1, .freq = 1000, .phase = 0};
    wave_spec_t sin2 = {.mag = -2, .freq = 70, .phase = 0};

    auto out_samples = create_sinwave_sampletrain({sinwav, sin2}, 0, 1, 10e3);

    cout << "time,mag" << endl;
    for(auto sample : out_samples)
    {
        cout << sample.time << "," << sample.mag << endl;
    }

    return 0;
}