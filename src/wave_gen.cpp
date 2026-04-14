/// ------------------------------------------
/// @file wave_gen.cpp
///
/// @brief source for wave generation functions
/// ------------------------------------------

#include "../inc/wave_gen.h"

/// ------------------------------------------
void save_sample_train_csv
(
    const std::string& save_dir,
    const std::string& name,
    const sample_train_t& sample_train
)
{
    std::string fullpath = save_dir + "/" + name + ".csv";
    std::ofstream out_csv(fullpath);
    out_csv << "time,val\n";

    for(auto sample : sample_train)
    {
        out_csv << sample.time << "," << sample.val << "\n";
    }
    out_csv.close();
}

/// ------------------------------------------
sample_train_t create_sinwave_sampletrain
(
    const std::vector<wave_spec_t>& waves,
    const double& start_time,
    const double& end_time,
    const double& sample_freq
)
{
    assert(start_time < end_time);
    assert(start_time != end_time);

    // before starting, find the normalisation factor for the waves
    double norm_factor = 0;
    for(auto wave : waves)
    {
        norm_factor += fabs(wave.mag);
    }

    // calculate time step and presize vector with needed space
    double time_step = (end_time - start_time) / sample_freq;
    size_t sample_count = std::ceil((end_time - start_time) / time_step);

    sample_train_t out_samples(sample_count);

    for(size_t index = 0; index < sample_count; index++)
    {
        double point_res = 0;
        double cur_time = index * time_step + start_time;
        for(auto wave : waves)
        {
            point_res += wave.mag * sin(wave.freq * cur_time + wave.phase);
        }
        point_res /= norm_factor;
        out_samples.at(index) = {.val = point_res, .time = cur_time};
    }

    return out_samples;
}

/// ------------------------------------------
sample_train_t create_noise_sampletrain
(
    const double& start_time,
    const double& end_time,
    const double& sample_freq
)
{
    assert(start_time < end_time);
    assert(start_time != end_time);

    std::mt19937 generator(time(NULL));
    std::uniform_real_distribution<double> dist(-1, 1);

    // calculate time step and presize vector with needed space
    double time_step = (end_time - start_time) / sample_freq;
    size_t sample_count = std::ceil((end_time - start_time) / time_step);

    sample_train_t out_samples(sample_count);

    for(size_t index = 0; index < sample_count; index++)
    {
        double point_res = dist(generator);
        double cur_time = index * time_step + start_time;
        out_samples.at(index) = {.val = point_res, .time = cur_time};
    }

    return out_samples;
}