#include "series/SeriesExpr.h"
#include "Random.h"
#include "Wavetable.h"
#include "WaveFormula.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

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

static void display_wave(const float* data, unsigned size, int rows, int cols)
{
    if ((rows & 1) == 0)
        --rows;
    if ((cols & 1) == 0)
        --cols;

    if (rows < 1 || cols < 1)
        return;

    std::unique_ptr<char[]> text(new char[rows * (cols + 1) + 1]);
    {
        char *p = text.get();
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c)
                *p++ = ' ';
            *p++ = '\n';
        }
        *p++ = '\0';
    }
    auto put_char = [&text, rows, cols](int r, int c, char ch) {
        if (r >= 0 && c >= 0 && r < rows && c < cols)
            text[r * (cols + 1) + c] = ch;
    };
    auto put_hline = [&put_char](int r, int c1, int c2, char ch) {
        for (int c = c1; c <= c2; ++c)
            put_char(r, c, ch);
    };
    auto put_vline = [&put_char](int r1, int r2, int c, char ch) {
        for (int r = r1; r <= r2; ++r)
            put_char(r, c, ch);
    };

    auto lerp = [data, size](float x) {
        float index = x * size;
        unsigned i1 = (unsigned)index % size;
        unsigned i2 = ((unsigned)index + 1) % size;
        float mu = index - i1;
        return (1 - mu) * data[i1] + mu * data[i2];
    };


    // borders
    put_hline(0, 0, cols - 1, '-');
    put_hline(rows - 1, 0, cols - 1, '-');
    put_vline(0, rows - 1, 0, '|');
    put_vline(0, rows - 1, cols - 1, '|');
    // corners
    put_char(0, 0, '+');
    put_char(0, cols - 1, '+');
    put_char(rows - 1, 0, '+');
    put_char(rows - 1, cols - 1, '+');
    // axes
    put_hline(rows / 2, 1, cols - 2, '.');
    put_vline(1, rows - 2, cols / 2, '.');

    // data points
    float rr = 0.0f;
    for (int c = 1; c < cols - 1; ++c) {
        float x = (float)(c - 1) / (float)(cols - 2);
        float y = lerp(x);
        float oldrr = rr;
        rr = 1 + 0.5f * (1 - y) * (rows - 2);
        put_char((int)std::lround(rr), c, '*');
        if (c > 1) {
            int r1 = (int)std::lround(oldrr);
            int r2 = (int)std::lround(rr);
            int rinc = (r1 < r2) ? +1 : -1;
            for (int r = r1; r != r2; r += rinc) {
                float mu = (r - oldrr) / (rr - oldrr);
                float midrr = (1 - mu) * oldrr + mu * rr;
                put_char((int)std::lround(midrr), c, '*');
            }
        }
    }

    //
    fputs(text.get(), stdout);
}

static WaveFormulaPtr create_formula(const char* expr)
{
    WaveFormulaPtr formula;

    if (!formula) {
        formula.reset(new SeriesFormula(expr));
        if (!formula->is_valid())
            formula.reset();
    }

    if (!formula) {
        formula.reset(new PartialsFormula(expr));
        if (!formula->is_valid())
            formula.reset();
    }

    return formula;
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
    WaveFormulaPtr formula = create_formula(expression);
    if (!formula) {
        std::cerr << "Invalid expression\n";
        return 1;
    }
    formula->set_size(wt.frames);
    formula->set_amplitude_type(WaveFormula::AmplitudeType::normalized);
    formula->set_seed(default_seed);

    //
    const float* wave = formula->get_wave();
    std::copy(wave, wave + wt.frames, wt.data.get());

    //
    if (1)
        display_wave(wt.data.get(), wt.frames, 20, 80);

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
