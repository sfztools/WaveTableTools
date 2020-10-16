#include "WaveFormula.h"
#include <kiss_fftr.h>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <cmath>

void WaveFormula::set_size(unsigned size)
{
    if (size_ == size)
        return;
    size_ = size;
    invalidate();
}

void WaveFormula::set_normalized(bool normalized)
{
    if (normalized_ == normalized)
        return;
    normalized_ = normalized;
    invalidate();
}

float* WaveFormula::get_wave() const
{
    float* wave = wave_.get();
    const unsigned size = size_;
    if (!wave) {
        wave = new float[size];
        wave_.reset(wave);
        compute_wave(wave);
        if (normalized_)
            normalize_wave(wave, size);
    }
    return wave;
}

void WaveFormula::invalidate() const
{
    wave_.reset();
}

void WaveFormula::normalize_wave(float* wave, unsigned size)
{
    float max_amplitude = 0.0;
    for (unsigned i = 0; i < size; ++i)
        max_amplitude = std::max(std::fabs(wave[i]), max_amplitude);
    if (max_amplitude > 0.0f) {
        for (unsigned i = 0; i < size; ++i)
            wave[i] = std::max(-1.0f, std::min(1.0f, wave[i] / max_amplitude));
    }
}

//------------------------------------------------------------------------------
std::complex<float>* SpectralFormula::get_spectrum() const
{
    std::complex<float>* spec = spec_.get();
    const unsigned size = get_size();
    if (!spec) {
        spec = new std::complex<float>[size / 2 + 1];
        spec_.reset(spec);
        compute_spectrum(spec);
    }
    return spec;
}

void SpectralFormula::invalidate() const
{
    WaveFormula::invalidate();
    spec_.reset();
}

void SpectralFormula::compute_wave(float* wave) const
{
    std::complex<float>* spec = get_spectrum();
    const unsigned size = get_size();

    static_assert(std::is_same<kiss_fft_scalar, float>::value,
                  "The kissfft scalar is not matching");

    kiss_fftr_cfg cfg = kiss_fftr_alloc(size, 1, nullptr, nullptr);
    if (!cfg)
        throw std::runtime_error("Cannot create the kissfft configuration");
    kiss_fftri(cfg, reinterpret_cast<const kiss_fft_cpx*>(spec), wave);
    kiss_fftr_free(cfg);
}

//------------------------------------------------------------------------------
SeriesFormula::SeriesFormula(const char* text)
{
    std::array<ExprPtr, 2> expr = Expr::parse(text);
    mag_expr_ = std::move(expr[0]);
    phase_expr_ = std::move(expr[1]);
}

bool SeriesFormula::is_valid() const
{
    return mag_expr_ != nullptr;
}

void SeriesFormula::compute_spectrum(std::complex<float>* spec) const
{
    const unsigned size = get_size();
    Expr* mag_expr = mag_expr_.get();
    Expr* phase_expr = phase_expr_.get();

    if (!mag_expr) {
        std::fill(spec, spec + size / 2 + 1, 0.0f);
        return;
    }

    spec[0] = 0.0f;
    for (unsigned i = 1; i < size / 2 + 1; ++i) {
        float mod = mag_expr->evalInterpreted(i);
        float arg = 0.0;
        if (phase_expr)
            arg = phase_expr->evalInterpreted(i) * float(M_PI * 2);
        spec[i] = std::polar(0.5f * mod, float(-M_PI / 2) + arg);
    }
}

//------------------------------------------------------------------------------
PartialsFormula::PartialsFormula(const char* text)
{
    partials_.reset(parse(text, &num_partials_));
}

bool PartialsFormula::is_valid() const
{
    return partials_ != nullptr;
}

void PartialsFormula::compute_spectrum(std::complex<float>* spec) const
{
    const std::complex<float>* partials = partials_.get();
    if (!partials)
        return;

    const size_t spec_size = get_size() / 2 + 1;
    const size_t num_partials = num_partials_;

    std::copy(partials, partials + num_partials, spec);
    std::fill(spec + num_partials, spec + spec_size, 0.0f);
}

std::complex<float>* PartialsFormula::parse(const char* text, unsigned* num_partials_ptr)
{
    unsigned fill_index;
    const char *pos = text;

    std::vector<float> mag;
    std::vector<float> phase;

    mag.reserve(64);
    phase.reserve(64);

    //
    static auto skip_ws = +[](const char *&pos) {
        auto is_ws = [](char c) -> bool {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n';
        };
        for (char c; (c = *pos) != '\0' && is_ws(c); ++pos);
    };

    static auto extract_number = +[](const char *&pos, float &num) -> bool {
        unsigned count;
        if (sscanf(pos, "%f%n", &num, &count) != 1)
            return false;
        pos += count;
        return true;
    };

    static auto extract_char = +[](const char *&pos, char ch) -> bool {
        if (*pos != ch)
            return false;
        ++pos;
        return true;
    };

    //
    mag.push_back(0.0f);
    phase.push_back(0.0f);

    fill_index = 0;
    for (unsigned i = 1;; ++i) {
        skip_ws(pos);
        if (i > 1) {
            if (!extract_char(pos, ','))
                break;
        }
        float value = 0.0f;
        extract_number(pos, value);
        mag.push_back(value);
    }

    //
    skip_ws(pos);
    if (extract_char(pos, ';')) {
        for (unsigned i = 1;; ++i) {
            skip_ws(pos);
            if (i > 1) {
                if (!extract_char(pos, ','))
                    break;
            }
            float value = 0.0f;
            extract_number(pos, value);
            phase.push_back(value * float(M_PI / 2));
        }
    }

    //
    skip_ws(pos);
    if (*pos != '\0')
        return nullptr;

    //
    while (!mag.empty() && mag.back() == 0.0f)
        mag.pop_back();
    size_t num_partials = mag.size();
    phase.resize(num_partials);

    //
    std::unique_ptr<std::complex<float>[]> partials(new std::complex<float>[num_partials]);
    for (unsigned i = 1; i < num_partials; ++i)
        partials[i] = std::polar(0.5f * mag[i], float(-M_PI / 2) + phase[i]);

    *num_partials_ptr = num_partials;
    return partials.release();
}
