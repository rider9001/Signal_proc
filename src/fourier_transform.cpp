/// ------------------------------------------
/// @file fourier_transform.cpp
///
/// @brief source for fourier transform functions
/// ------------------------------------------

#include "../inc/fourier_transform.h"

/// ------------------------------------------
void save_FT_points_csv
(
    const std::string& save_dir,
    const std::string& name,
    const wavelist_t& FT_points
)
{
    std::string fullpath = save_dir + "/" + name + ".csv";
    std::ofstream out_csv(fullpath);
    out_csv << "mag,freq,phase\n";

    for(auto sample : FT_points)
    {
        out_csv << sample.mag << "," << sample.freq << "," << sample.phase << "\n";
    }
    out_csv.close();
}

/// ------------------------------------------
wavelist_t DFT(
    const sample_train_t& sample_points
)
{
    const double time_delta = sample_points.at(1).time - sample_points.at(0).time;
    //freq = k / (sampleStep * sampleSize)
    const double freq_scale = 1 / (time_delta * sample_points.size());
    const double neg_rad_scale = -(2 * M_PI) / sample_points.size();

    wavelist_t FT_points(sample_points.size() / 2);

    for(size_t k = 0; k < sample_points.size() / 2; k++)
    {
        Complex_C_t complex_res = {0,0};
        double k_rad_scale = neg_rad_scale * k;

        for(size_t sample = 0; sample < sample_points.size(); sample++)
        {
            Complex_C_t e_raise = raiseEImagine(k_rad_scale * sample);
            complex_res += e_raise * sample_points.at(sample).val;
        }

        FT_points.at(k).mag = complex_res.absolute();
        FT_points.at(k).freq = k * freq_scale;
        FT_points.at(k).phase = complex_res.argument();
    }

    return FT_points;
}