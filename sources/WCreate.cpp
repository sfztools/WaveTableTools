#include "Expr.h"
#include "Random.h"
#include "Wavetable.h"
#include <kiss_fftr.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cstdlib>
#include <cstring>
typedef std::complex<float> cfloat;

template <class T> T clamp(T v, T lo, T hi)
{
    return std::max(std::min(v, hi), lo);
}

namespace {
    int table_size = 0;
    const char *expression = nullptr;
    const char *output_filename = nullptr;
    long default_seed = 0;
}

static bool parse_args(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: WCreate <size> <expression> <output-file> [-seed number]\n";
        return false;
    }

    unsigned nth_positional_arg = 0;

    for (int argi = 1; argi < argc; ++argi) {
        const char *arg = argv[argi];

        if (!strcmp(arg, "-seed")) {
            if (++argi >= argc) {
                std::cerr << "Flag requires an argument: " << arg << '\n';
                return false;
            }
            arg = argv[argi];
            default_seed = strtol(arg, nullptr, 0);
        }
        else {
            switch (nth_positional_arg) {
            case 0:
                table_size = atoi(arg);
                break;
            case 1:
                expression = arg;
                break;
            case 2:
                output_filename = arg;
                break;
            }
            ++nth_positional_arg;
        }
    }

    if (nth_positional_arg != 3) {
        std::cerr << "Bad number of positional arguments\n";
        return false;
    }

    if (table_size <= 0 || table_size > 8192 || (table_size & 1)) {
        std::cerr << "Invalid table size\n";
        return false;
    }

    return true;
}

static void fill_spectrum_in_series_mode(const Expr &expr, kiss_fft_cpx *spectrum, unsigned size)
{
    for (unsigned i = 1; i < size / 2 + 1; ++i) {
        float y = expr.evalInterpreted(i);
        cfloat bin = std::polar(0.5f * y, float(-M_PI / 2));
        spectrum[i].r = bin.real();
        spectrum[i].i = bin.imag();
    }
}

static bool fill_spectrum_in_partials_mode(const char *text, kiss_fft_cpx *spectrum, unsigned size)
{
    unsigned fill_index;
    const char *pos = text;

    //
    static auto skip_ws = +[](const char *&pos) {
        for (char c; (c = *pos) != '\0' && (c == ' ' || c == '\t'); ++pos);
    };

    static auto extract_number = +[](const char *&pos, float &num) -> bool {
        skip_ws(pos);
        unsigned count;
        if (sscanf(pos, "%f%n", &num, &count) != 1)
            return false;
        pos += count;
        return true;
    };

    static auto extract_char = +[](const char *&pos, char ch) -> bool {
        skip_ws(pos);
        if (*pos != ch)
            return false;
        ++pos;
        return true;
    };

    //
    fill_index = 0;
    for (unsigned i = 1; i < size / 2 + 1; ++i) {
        if (i > 1) {
            if (!extract_char(pos, ','))
                break;
        }
        if (!extract_number(pos, spectrum[i].r))
            return false;
    }

    //
    if (extract_char(pos, ';')) {
        for (unsigned i = 1; i < size / 2 + 1; ++i) {
            if (i > 1) {
                if (!extract_char(pos, ','))
                    break;
            }
            if (!extract_number(pos, spectrum[i].i))
                return false;
        }
    }

    //
    skip_ws(pos);
    if (*pos != '\0')
        return false;

    //
    for (unsigned i = 1; i < size / 2 + 1; ++i) {
        float mod = spectrum[i].r;
        float arg = spectrum[i].i;
        cfloat bin = std::polar(0.5f * mod, float(-M_PI / 2) + arg * float(M_PI * 2));
        spectrum[i].r = bin.real();
        spectrum[i].i = bin.imag();
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!parse_args(argc, argv))
        return 1;

    //
    Wavetable wt;
    wt.count = 1;
    wt.frames = table_size;
    wt.data.reset(new float[wt.frames]);

    //
    std::vector<kiss_fft_cpx> spectrum(wt.frames / 2 + 1);

    random_seed(default_seed);

    ExprPtr expr = Expr::parse(expression);
    if (expr) {
        fill_spectrum_in_series_mode(*expr, spectrum.data(), wt.frames);
    }
    else if (!fill_spectrum_in_partials_mode(expression, spectrum.data(), wt.frames)) {
        std::cerr << "Invalid expression\n";
        return 1;
    }

    //
    kiss_fftr_cfg cfg = kiss_fftr_alloc(table_size, 1, nullptr, nullptr);
    if (!cfg)
        throw std::bad_alloc();
    kiss_fftri(cfg, spectrum.data(), wt.data.get());
    kiss_fftr_free(cfg);

    // normalize to unity
    float maxAmplitude = 0.0;
    for (unsigned i = 0; i < wt.frames; ++i)
        maxAmplitude = std::max(std::fabs(wt.data[i]), maxAmplitude);
    if (maxAmplitude > 0.0f) {
        for (unsigned i = 0; i < wt.frames; ++i)
            wt.data[i] = clamp(wt.data[i] / maxAmplitude, -1.0f, 1.0f);
    }

    //
    if (0) {
        for (unsigned i = 0; i < wt.frames; ++i) {
            printf("%u %e\n", i, wt.data[i]);
        }
    }

    //
    FILE *stream = fopen(output_filename, "wb");
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
