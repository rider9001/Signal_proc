/// ------------------------------------------
/// @file filter.h
///
/// @brief header for time domain filter functions
/// ------------------------------------------
#pragma once

#include <vector>
#include <string>

#include "wave_gen.h"
#include "fourier_transform.h"

/// ------------------------------------------
/// @brief Applies an FIR filter to sample train using the
/// given FIR coefficents
///
/// @param sample_data samples to apply filter to
/// @param coeffs coefficents of FIR filter
///
/// @return filtered sample train
sample_train_t FIR_filter(
    const sample_train_t& sample_data,
    const std::vector<double>& coeffs
);