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
    const double freq_scale = 1.0 / (time_delta * sample_points.size());
    const double neg_rad_scale = -(2 * M_PI) / sample_points.size();

    wavelist_t FT_points(sample_points.size() / 2);

    for(size_t k = 0; k < sample_points.size() / 2; k++)
    {
        double k_pow = k * neg_rad_scale;
        FT_points.at(k) = DFT_point(sample_points, k_pow);
        FT_points.at(k).freq = k * freq_scale;

        #ifndef NO_PROG_PRINT
        std::cout << k + 1 << " / " << sample_points.size() / 2 << "\r";
        #endif
    }

    return FT_points;
}

/// ------------------------------------------
wave_spec_t DFT_point(
    const sample_train_t& sample_points,
    const double &k_pow
)
{
    Complex_C_t complex_res = {0,0};
    for(size_t sample = 0; sample < sample_points.size(); sample++)
    {
        Complex_C_t e_raise = raiseEImagine(k_pow * sample);
        complex_res += e_raise * sample_points.at(sample).val;
    }

    return {
        .mag = complex_res.absolute(),
        // freq is calculated in main DFT function
        .freq = 0,
        .phase = complex_res.argument()
    };
}

/// ------------------------------------------
wavelist_t FFT(
    const sample_train_t& sample_points
)
{
    // Check if sample count is a power of 2
    size_t sample_len = sample_points.size();
    if ((sample_len & (sample_len - 1)) != 0)
    {
        // extend the count to the next highest power if not a power of 2
        sample_len = pow(2, std::ceil(log2(sample_len)));
    }

    const double time_delta = sample_points.at(1).time - sample_points.at(0).time;
    //freq = k / (sampleStep * sampleSize)
    const double freq_scale = 1.0 / (time_delta * sample_len);

    // create sample train with padded zero entires
    std::vector<Complex_C_t> used_points(sample_len, {0, 0});
    for(size_t i = 0; i < sample_points.size(); i++)
    {
        used_points[i].m_real = sample_points[i].val;
    }

    wavelist_t FT_points(sample_len / 2);

    for(size_t k = 0; k < sample_len / 2; k++)
    {
        const double k_rad_scale = -(2 * M_PI) * k;
        FT_points.at(k) = FFT_point(used_points, k_rad_scale);
        FT_points.at(k).freq = freq_scale * k;

        #ifndef NO_PROG_PRINT
        std::cout << k + 1 << " / " << sample_len / 2 << "\r";
        #endif
    }

    return FT_points;
}

/// ------------------------------------------
wavelist_t FFT_threaded(
    const sample_train_t& sample_points,
    const size_t thread_count
)
{
    // Check if sample count is a power of 2
    size_t sample_len = sample_points.size();
    if ((sample_len & (sample_len - 1)) != 0)
    {
        // extend the count to the next highest power if not a power of 2
        sample_len = pow(2, std::ceil(log2(sample_len)));
    }

    const double time_delta = sample_points.at(1).time - sample_points.at(0).time;
    //freq = k / (sampleStep * sampleSize)
    const double freq_scale = 1.0 / (time_delta * sample_len);

    // create sample train with padded zero entires
    std::vector<Complex_C_t> used_points(sample_len, {0, 0});
    for(size_t i = 0; i < sample_points.size(); i++)
    {
        used_points[i].m_real = sample_points[i].val;
    }

    wavelist_t FT_points(sample_len / 2);

    // setup lambda for the worker threads
    auto FFT_worker_lambda = [](
        std::vector<Complex_C_t>& used_points,
        wavelist_t& FT_points,
        const size_t& thread_count,
        const size_t& thread_num,
        const double& freq_scale
    )
    {
        // start each thread in FFT col of its thread number, each thread steps forward the number of threads
        // e.g: start (2/2) thread at index 1, 1->3->5 etc
        for(size_t k = thread_num; k < FT_points.size() / 2; k += thread_count)
        {
            const double k_rad_scale = -(2 * M_PI) * k;
            FT_points.at(k) = FFT_point(used_points, k_rad_scale);
            FT_points.at(k).freq = freq_scale * k;
        }
    };

    std::vector<std::thread> thread_list(thread_count);

    // dispatch worker threads
    for(size_t thread = 0; thread < thread_list.size(); thread++)
    {
        thread_list[thread] = std::thread(
            FFT_worker_lambda,
            std::ref(used_points),
            std::ref(FT_points),
            std::ref(thread_count),
            std::ref(thread),
            std::ref(freq_scale)
        );
    }

    // wait for threads to finish
    for(size_t thread = 0; thread < thread_list.size(); thread++)
    {
        thread_list[thread].join();
    }

    return FT_points;
}

/// ------------------------------------------
wave_spec_t FFT_point(
    const std::vector<Complex_C_t>& sample_points,
    const double &k_pow
)
{
    const size_t N = sample_points.size();
    size_t step = 2;

    Complex_C_t *working_vec, *result_vec;

    // fill result vector with sample point data
    result_vec = new Complex_C_t[N];
    std::copy(sample_points.begin(), sample_points.end(), result_vec);

    while(step <= N)
    {
        // pass previous results onto working vector
        working_vec = result_vec;

        // used multiple times, precalculate
        const size_t result_width = N / step;

        // create new buffer for this rounds results
        result_vec = (Complex_C_t*) malloc(sizeof(Complex_C_t) * result_width);

        Complex_C_t E_NEGIK2PI_N = raiseEImagine(k_pow / step);
        for (size_t sample = 0; sample < result_width; sample++)
        {
            result_vec[sample] = working_vec[sample] +
            working_vec[sample + result_width] * E_NEGIK2PI_N;
        }

        // double step size
        step *= 2;

        // clear memory of working buffer
        delete[] working_vec;
    }

    Complex_C_t result = result_vec[0];
    delete[] result_vec;

    return
    {
        .mag = result.absolute(),
        .freq = 0,
        .phase = result.argument()
    };
}