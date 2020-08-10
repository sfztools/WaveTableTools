#include "Random.h"
#include <random>

static std::minstd_rand0 source;

void random_seed(long seed)
{
    source.seed(seed);
}

float random_next_float()
{
    double d = static_cast<double>(source());
    return static_cast<float>((d - source.min()) / (source.max() - source.min()));
}
