/// ------------------------------------------
/// @file filter.cpp
///
/// @brief source for time domain filter functions
/// ------------------------------------------

#include "../inc/filter.h"

/// ------------------------------------------
sample_train_t FIR_filter(
    const sample_train_t& sample_data,
    const std::vector<double>& coeffs
)
{
    sample_train_t output_samples(sample_data.size());

    for (size_t sample = 0; sample < sample_data.size(); sample++)
    {
        double sum = 0;
        for(size_t coeff = 0; coeff < coeffs.size(); coeff++)
        {
            // FIR coeffs are applied to delayed samples
            // Need to check and set tap to 0 if OOB
            if (sample < coeff) continue;

            sum += sample_data[sample - coeff].val * coeffs[coeff];
        }

        output_samples[sample] = {
            .val = sum,
            .time = sample_data[sample].time
        };
    }

    return output_samples;
}
