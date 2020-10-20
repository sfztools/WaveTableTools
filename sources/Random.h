#pragma once
#include "random/ms_stl_random.h"

class RandomGenerator {
public:
    typedef ms_stl::mt19937 prng_type;
    typedef typename prng_type::result_type result_type;

public:
    void seed(long seed);
    double next_double();
    float next_float();

private:
    prng_type source_;
};

//------------------------------------------------------------------------------
inline void RandomGenerator::seed(long seed)
{
    source_.seed(seed);
}

inline double RandomGenerator::next_double()
{
    ms_stl::uniform_real_distribution<double> dist(0, 1);
    return dist(source_);
}

inline float RandomGenerator::next_float()
{
    ms_stl::uniform_real_distribution<float> dist(0, 1);
    return dist(source_);
}
