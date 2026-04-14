/// ------------------------------------------
/// @file wave_gen.cpp
///
/// @brief source for wave generation functions
/// ------------------------------------------

#include "../inc/wave_gen.h"

/// ------------------------------------------
std::vector<sample_p_t> create_sinwave_sampletrain(
    const std::vector<wave_spec_t>& waves,
    const double& start_time,
    const double& end_time,
    const double& sample_freq
)
{
    // before starting, find the normalisation factor for the waves
    double norm_factor = 0;
    for(auto wave : waves)
    {
        norm_factor += fabs(wave.mag);
    }

    // calculate time step and presize vector with needed space
    double time_step = (end_time - start_time) / sample_freq;
    size_t sample_count = std::ceil((end_time - start_time) / time_step);

    std::vector<sample_p_t> out_samples(sample_count);

    for(size_t index = 0; index < sample_count; index++)
    {
        double point_res = 0;
        double cur_time = index * time_step;
        for(auto wave : waves)
        {
            point_res += wave.mag * sin(wave.freq * cur_time + wave.phase);
        }
        point_res /= norm_factor;
        out_samples.at(index) = {.mag = point_res, .time = cur_time};
    }

    return out_samples;
}