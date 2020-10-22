#pragma once
#include <memory>
#include <cstdio>
#include <cstdint>

struct Wavetable {
    unsigned count = 0; // number of subtables
    unsigned frames = 0; // number of frames per subtable
    std::unique_ptr<float[]> data; // wave data [count * frames]
};

typedef std::shared_ptr<Wavetable> Wavetable_s;
typedef std::unique_ptr<Wavetable> Wavetable_u;

namespace Wavetables {
    void saveToWAVFile(
        FILE *stream, const Wavetable &wt,
        const char *chunkId = nullptr, const void *chunkData = nullptr, uint32_t chunkSize = 0);
}
