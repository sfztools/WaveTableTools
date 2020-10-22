#include "Wavetable.h"
#include "utility/unicodefile.h"
#include <sndfile.hh>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>

namespace {
    int num_stages = 0;
    const char *input1_filename = nullptr;
    const char *input2_filename = nullptr;
    const char *output_filename = nullptr;
    bool no_last = false;
}

static bool parse_args(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: WMorph <stages> <input-file-1> <input-file-2> <output-file> [-nolast]\n";
        return false;
    }

    unsigned nth_positional_arg = 0;

    for (int argi = 1; argi < argc; ++argi) {
        const char *arg = argv[argi];

        if (!strcmp(arg, "-nolast")) {
            no_last = true;
        }
        else {
            switch (nth_positional_arg) {
            case 0:
                num_stages = atoi(arg);
                break;
            case 1:
                input1_filename = arg;
                break;
            case 2:
                input2_filename = arg;
                break;
            case 3:
                output_filename = arg;
                break;
            }
            ++nth_positional_arg;
        }
    }

    if (nth_positional_arg != 4) {
        std::cerr << "Bad number of positional arguments\n";
        return false;
    }

    if (num_stages < 3 || num_stages > 256) {
        std::cerr << "Invalid nuber of stages\n";
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!parse_args(argc, argv))
        return 1;

    SndfileHandle snd1(input1_filename);
    if (snd1.error()) {
        std::cerr << "Cannot open sound file: " << input1_filename << '\n';
        return 1;
    }
    SndfileHandle snd2(input2_filename);
    if (snd2.error()) {
        std::cerr << "Cannot open sound file: " << input2_filename << '\n';
        return 1;
    }

    //
    const sf_count_t frames = snd1.frames();
    if (frames < 2 || frames > 8192) {
        std::cerr << "Invalid number of frames in input file 1.\n";
        return 1;
    }
    if (frames != snd2.frames()) {
        std::cerr << "The number of frames does not match in the input files.\n";
        return 1;
    }
    if (snd1.channels() != 1) {
        std::cerr << "The input file 1 does not contain exactly one audio channel.\n";
        return 1;
    }
    if (snd2.channels() != 1) {
        std::cerr << "The input file 2 does not contain exactly one audio channel.\n";
        return 1;
    }

    //
    std::unique_ptr<float[]> wave1(new float[frames]);
    std::unique_ptr<float[]> wave2(new float[frames]);

    if (snd1.read(wave1.get(), frames) != frames) {
        std::cerr << "Cannot read the input file 1.\n";
        return 1;
    }
    if (snd2.read(wave2.get(), frames) != frames) {
        std::cerr << "Cannot read the input file 2.\n";
        return 1;
    }

    snd1 = SndfileHandle();
    snd2 = SndfileHandle();

    //
    const unsigned num_stages = ::num_stages;
    const unsigned num_stages_written = num_stages - (no_last ? 1 : 0);

    Wavetable wt;
    wt.count = num_stages_written;
    wt.frames = frames;
    wt.data.reset(new float[num_stages_written * frames]);

    for (unsigned t = 0; t < num_stages_written; ++t) {
        float *table = &wt.data[t * frames];
        float ratio = float(t) / float(num_stages - 1);
        for (unsigned i = 0; i < frames; ++i)
            table[i] = (1 - ratio) * wave1[i] + ratio * wave2[i];
    }

    FILE *stream = fopen_utf8(output_filename, "wb");
    if (!stream) {
        std::cerr << "Cannot open file for writing.\n";
        return 1;
    }
    Wavetables::saveToWAVFile(stream, wt);
    int stream_err = ferror(stream);
    fclose(stream);

    if (stream_err) {
        std::cerr << "Could not write the output file.\n";
        return 1;
    }

    return 0;
}
