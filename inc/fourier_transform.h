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

#include "Complex.h"
#include "wave_gen.h"

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
/// @return freq/mag data resulting from the transform
wavelist_t DFT(
    const sample_train_t& sample_points
);