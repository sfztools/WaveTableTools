#include "Wavetable.h"
#include <array>
#include <string>
#include <type_traits>
#include <cstdint>

template <class T>
static std::array<uint8_t, sizeof(T)> leImpl(T x)
{
    typename std::make_unsigned<T>::type u = x;
    constexpr size_t n = sizeof(T);
    std::array<uint8_t, n> b;
    for (size_t i = 0; i < n; ++i)
        b[i] = uint8_t(u >> (8 * i));
    return b;
}

static std::array<uint8_t, 2> le16(uint16_t x) { return leImpl<uint16_t>(x); }
static std::array<uint8_t, 4> le32(uint32_t x) { return leImpl<uint32_t>(x); }

static size_t writeLE16(FILE *stream, uint16_t x)
{
    return fwrite(reinterpret_cast<const char *>(le16(x).data()), 1, sizeof(x), stream);
}
static size_t writeLE32(FILE *stream, uint32_t x)
{
    return fwrite(reinterpret_cast<const char *>(le32(x).data()), 1, sizeof(x), stream);
}
static size_t writeF32(FILE *stream, float x)
{
    union { uint32_t i; float f; } u;
    u.f = x;
    return writeLE32(stream, u.i);
}

void Wavetables::saveToWAVFile(FILE *stream, const Wavetable &wt)
{
    const unsigned sampleRate = 44100;
    const unsigned channels = 1;

    fwrite("RIFF", 1, 4, stream);
    fwrite("\0\0\0\0", 1, 4, stream);
    off_t riffStart = ftell(stream);
    fwrite("WAVE", 1, 4, stream);

    // fmt chunk
    fwrite("fmt ", 1, 4, stream);
    fwrite("\0\0\0\0", 1, 4, stream);
    off_t fmtStart = ftell(stream);
    writeLE16(stream, 3); // float 32 bits
    writeLE16(stream, channels); // mono
    writeLE32(stream, sampleRate); // sample rate
    writeLE32(stream, sampleRate * channels * sizeof(float)); // bytes per second
    writeLE16(stream, channels * sizeof(float)); // frame alignment
    writeLE16(stream, 8 * sizeof(float)); // bits per sample
    writeLE16(stream, 0); // extension size
    off_t fmtEnd = ftell(stream);

    // fact chunk
    fwrite("fact", 1, 4, stream);
    writeLE32(stream, 4);
    writeLE32(stream, wt.count * wt.frames);

    // data chunk
    fwrite("data", 1, 4, stream);
    writeLE32(stream, channels * wt.count * wt.frames * sizeof(float));
    for (unsigned i = 0, n = channels * wt.count * wt.frames; i < n; ++i) {
        float sample = wt.data[i];
        writeF32(stream, sample);
    }

    // clm chunk
    if (wt.frames <= 8192) {
        fwrite("clm ", 1, 4, stream);
        //
        std::string data;
        data.reserve(256);
        data.append("<!>");
        data.push_back("0123456789"[(wt.frames / 1000) % 10]);
        data.push_back("0123456789"[(wt.frames / 100) % 10]);
        data.push_back("0123456789"[(wt.frames / 10) % 10]);
        data.push_back("0123456789"[wt.frames % 10]);
        data.push_back(' ');
        data.append("10000000");
        data.push_back(' ');
        data.append("wavetable (jpcima.sdf1.org)");
        //
        writeLE32(stream, data.size());
        fwrite(data.data(), 1, data.size(), stream);
    }

    off_t riffEnd = ftell(stream);

    fflush(stream);
    fseek(stream, fmtStart - 4, SEEK_SET);
    writeLE32(stream, fmtEnd - fmtStart);
    fflush(stream);
    fseek(stream, riffStart - 4, SEEK_SET);
    writeLE32(stream, riffEnd - riffStart);
    fflush(stream);
}
