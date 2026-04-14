/// ------------------------------------------
/// @file wave_gen.h
///
/// @brief header for wave generation functions
/// ------------------------------------------
#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Complex.h"

/// @brief Structure for storing specification for a sine wave
struct wave_spec_t
{
    // Magnitude of wave (negative has effect of a -pi phase shift)
    double mag;

    // frequency of sine wave
    double freq;

    // phase shift of sine wave
    double phase;
};

struct sample_p_t
{
    // magnitude of point
    double mag;

    // time of point
    double time;
};


/// ------------------------------------------
/// @brief Generates a sample train from a given list of sine waves mixed together
/// Normalized to [-1, 1]
///
/// @param waves list of waves to mix into simlated wave to sample
/// @param start_time time to start simulating wave from
/// @param end_time time to end wave simulation
/// @param sample_freq rate at which to sample simulated wave
///
/// @return vector of sample magnitudes and times
std::vector<sample_p_t> create_sinwave_sampletrain(
    const std::vector<wave_spec_t>& waves,
    const double& start_time,
    const double& end_time,
    const double& sample_freq
);