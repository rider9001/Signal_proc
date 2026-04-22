/// ------------------------------------------
/// @file fourier_transform.h
///
/// @brief header for fourier transform functions
/// ------------------------------------------
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

#include "Complex.h"
#include "wave_gen.h"

#define NO_PROG_PRINT

/// @brief Default number of threads to use, 1/4 of compiler machine threads
#define DEFAULT_THREAD_COUNT (std::thread::hardware_concurrency() / 4)

/// ------------------------------------------
/// @brief Saves fourier points as a csv file
///
/// @param save_dir directory to same to
/// @param name name to use, .csv will be appended
/// @param sample_train sample train to save
void save_FT_points_csv
(
    const std::string& save_dir,
    const std::string& name,
    const wavelist_t& FT_points
);

/// ------------------------------------------
/// @brief Performs discrete fourier transform on a set of sample points
/// Returns half as many fourier points as sample points
///
/// @param sample_points points of a sample to transform
///
/// @return freq/mag/phase data resulting from the transform
wavelist_t DFT(
    const sample_train_t& sample_points
);

/// ------------------------------------------
/// @brief Calculates DFT for a single k point
///
/// @param sample_points points of a sample to transform
/// @param k_pow current k power
///
/// @return DFT of sample for given k column
wave_spec_t DFT_point(
    const sample_train_t& sample_points,
    const double &k_pow
);

/// ------------------------------------------
/// @brief Performs fast fourier transform on a set of sample points
/// Returns # wave specs as the nearest smaller power of 2
///
/// Note: FFT can only be done on a sample list size of a power of 2
/// Sample will be extended with zero samples to reach next highest power
/// This should not affect the result, as they will not contribute energy
/// to any frequency bucket as they are zero.
///
/// @param sample_points sampled points to transform
///
/// @return freq/mag/phase data resulting from the transform
wavelist_t FFT(
    const sample_train_t& sample_points
);

/// ------------------------------------------
/// @brief Performs fast fourier transform on a set of sample points
/// Threads
///
/// @param sample_points sampled points to transform
/// @param thread_count threads to use
///
/// @return freq/mag/phase data resulting from the transform
wavelist_t FFT_threaded(
    const sample_train_t& sample_points,
    const size_t thread_count = DEFAULT_THREAD_COUNT
);

/// ------------------------------------------
/// @brief Calculates FFT for a single k point
///
/// @param sample_points points of a sample to transform
/// @param k_pow current k power
///
/// @return DFT of sample for given k column, normalised by number of samples
wave_spec_t FFT_point(
    const std::vector<Complex_C_t>& sample_points,
    const double &k_pow
);