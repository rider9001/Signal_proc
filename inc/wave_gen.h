/// ------------------------------------------
/// @file wave_gen.h
///
/// @brief header for wave generation functions
/// ------------------------------------------
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include <exception>
#include <algorithm>

#include "Complex.h"

/// @brief Structure for storing specification for a sine wave
struct wave_spec_t
{
    // Magnitude of wave (negative has effect of a -pi phase shift)
    double mag;

    // frequency of sine wave, Hz
    double freq;

    // phase shift of sine wave, radians
    double phase;
};

/// @brief List of sine waves
typedef std::vector<wave_spec_t> wavelist_t;

/// @brief Struct for storing point in time space
struct sample_p_t
{
    // value of point
    double val;

    // time of point
    double time;
};

/// @brief Typedef for sample train
typedef std::vector<sample_p_t> sample_train_t;

/// ------------------------------------------
/// @brief Saves a sample train as a csv file
///
/// @param save_dir directory to same to
/// @param name name to use, .csv will be appended
/// @param sample_train sample train to save
void save_sample_train_csv
(
    const std::string& save_dir,
    const std::string& name,
    const sample_train_t& sample_train
);

/// ------------------------------------------
/// @brief Reads a csv sampletrain
///
/// @param filepath path to sampletrain csv
///
/// @return read sample train
sample_train_t read_sample_train_csv
(
    const std::string& filepath
);

/// ------------------------------------------
/// @brief Generates a sample train from a given list of sine waves mixed together
/// Normalized to [-1, 1]
///
/// @param waves list of waves to mix into simlated wave to sample
/// @param start_time time to start simulating wave from
/// @param end_time time to end wave simulation
/// @param sample_freq number of samples to generate per second
///
/// @return vector of sample magnitudes and times
sample_train_t create_sinwave_sampletrain
(
    const wavelist_t& waves,
    const double& start_time,
    const double& end_time,
    const double& sample_freq
);

/// ------------------------------------------
/// @brief Generates sampletrain of white noise
/// Uses std::default_random_engine to generate random noise
///
/// Note: noise is random at all points, so sample freq just
/// controls number of samples returned
///
/// @param start_time time to start simulating wave from
/// @param end_time time to end wave simulation
/// @param sample_freq rate at which to sample simulated wave
///
/// @return
sample_train_t create_noise_sampletrain
(
    const double& start_time,
    const double& end_time,
    const double& sample_freq
);