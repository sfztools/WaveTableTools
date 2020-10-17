#pragma once
#include "series/SeriesExpr.h"
#include <complex>
#include <memory>

class WaveFormula;
typedef std::shared_ptr<WaveFormula> WaveFormulaPtr;

//------------------------------------------------------------------------------
class WaveFormula : public std::enable_shared_from_this<WaveFormula> {
protected:
    WaveFormula() = default;

public:
    virtual ~WaveFormula() {}
    virtual bool is_valid() const = 0;
    unsigned get_size() const { return size_; }
    void set_size(unsigned size);
    bool get_normalized() const { return normalized_; }
    void set_normalized(bool normalized);
    long get_seed() const { return seed_; }
    void set_seed(long seed);
    float* get_wave() const;

protected:
    virtual void invalidate() const;
    virtual void compute_wave(float* wave) const = 0;

private:
    static void normalize_wave(float* wave, unsigned size);

private:
    unsigned size_ = 2048;
    bool normalized_ = false;
    long seed_ = 0;
    mutable std::unique_ptr<float[]> wave_;
};

//------------------------------------------------------------------------------
class SpectralFormula : public WaveFormula {
protected:
    SpectralFormula() = default;

public:
    virtual ~SpectralFormula() {}
    std::complex<float>* get_spectrum() const;

protected:
    void invalidate() const override;
    void compute_wave(float* wave) const override;
    virtual void compute_spectrum(std::complex<float>* spec) const = 0;

private:
    mutable std::unique_ptr<std::complex<float>[]> spec_;
};

//------------------------------------------------------------------------------
class SeriesFormula : public SpectralFormula {
public:
    explicit SeriesFormula(const char* text);
    bool is_valid() const override;

protected:
    void compute_spectrum(std::complex<float>* spec) const override;

private:
    ExprPtr mag_expr_;
    ExprPtr phase_expr_;
};

//------------------------------------------------------------------------------
class PartialsFormula : public SpectralFormula {
public:
    explicit PartialsFormula(const char* text);
    bool is_valid() const override;

protected:
    void compute_spectrum(std::complex<float>* spec) const override;

private:
    static std::complex<float>* parse(const char* text, unsigned* num_partials_ptr);

private:
    unsigned num_partials_ = 0;
    std::unique_ptr<std::complex<float>[]> partials_;
};
