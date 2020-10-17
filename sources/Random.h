#pragma once
#include <random>

class RandomGenerator {
public:
    typedef std::minstd_rand0 prng_type;
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
    double d = static_cast<double>(source_());
    return (d - source_.min()) / (source_.max() - source_.min());
}

inline float RandomGenerator::next_float()
{
    return static_cast<float>(next_double());
}
