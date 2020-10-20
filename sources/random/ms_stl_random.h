// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// Based on `microsoft/STL` file `stl/inc/random` at revision a8b62af

#include <limits>
#include <type_traits>
#include <iosfwd>
#include <cmath>
#include <cstddef>
#include <cassert>

namespace ms_stl {

using namespace std;

#if !defined(NODISCARD_)
#   if __has_cpp_attribute(nodiscard)
#       define NODISCARD_ [[nodiscard]]
#   else
#       define NODISCARD_
#   endif
#endif

// FUNCTION TEMPLATE generate_canonical
template <class Real_, size_t Bits_, class Gen_>
NODISCARD_ Real_ generate_canonical(Gen_& Gx_) { // build a floating-point value from random sequence
    const size_t Digits_  = static_cast<size_t>(numeric_limits<Real_>::digits);
    const size_t Minbits_ = Digits_ < Bits_ ? Digits_ : Bits_;

    const Real_ Gxmin_ = static_cast<Real_>((Gx_.min)());
    const Real_ Gxmax_ = static_cast<Real_>((Gx_.max)());
    const Real_ Rx_    = (Gxmax_ - Gxmin_) + Real_{1};

    const int Ceil_ = static_cast<int>(std::ceil(static_cast<Real_>(Minbits_) / std::log2(Rx_)));
    const int Kx_   = Ceil_ < 1 ? 1 : Ceil_;

    Real_ Ans_{0};
    Real_ Factor_{1};

    for (int Idx_ = 0; Idx_ < Kx_; ++Idx_) { // add in another set of bits
        Ans_ += (static_cast<Real_>(Gx_()) - Gxmin_) * Factor_;
        Factor_ *= Rx_;
    }

    return Ans_ / Factor_;
}

#define NRAND_(eng, resty) (generate_canonical<resty, static_cast<size_t>(-1)>(eng))

// ALIAS TEMPLATE Enable_if_seed_seq_t_
template <class Seed_seq_, class Self_, class Engine_ = Self_>
using Enable_if_seed_seq_t_ = typename enable_if<
    !is_convertible<typename remove_cv<Seed_seq_>::type,
        typename Self_::
            result_type>::value && !is_same<typename remove_cv<Seed_seq_>::type, Self_>::value && !is_same<typename remove_cv<Seed_seq_>::type, Engine_>::value,
    int>::type;

// CLASS TEMPLATE Circ_buf_ FOR subtract_with_carry, subtract_with_carry_01, AND mersenne_twister
template <class Ty_, size_t Nw_>
struct Circ_buf_ { // holds historical values for generators
    Ty_ At_(size_t Ix_) const {
        return Ax_[Base_(Ix_)];
    }

    bool Equals_(const Circ_buf_& Right_) const {
        const Ty_* Last1_ = Ax_ + Idx_;
        const Ty_* Last2_ = Right_.Ax_ + Right_.Idx_;
        const Ty_* First_;
        const Ty_* Last_;
        const Ty_* Other_;
        bool Use2_ = Base_() < Right_.Base_();

        if (Use2_) { // Right_'s range is higher up in the array
                     // than ours, so scan it first
            First_ = Right_.Ax_ + Right_.Base_();
            Last_  = Last2_;
            Other_ = Ax_ + Base_();
        } else { // our range is higher up in the array
                 // than Right_'s, so scan ours first
            First_ = Ax_ + Base_();
            Last_  = Last1_;
            Other_ = Right_.Ax_ + Right_.Base_();
        }

        ptrdiff_t Nx0_ = Nw_;
        while (0 < Nx0_) { // scan
                           // note: may need up to three passes; each scan starts at the
                           // current highest array position and ends at the end of the
                           // array or the Idx_ value, whichever comes first; the
                           // equality test succeeds only by reaching the Idx_ value.
            const Ty_* Limit_ = First_ < Last_ ? Last_ : Use2_ ? Right_.Ax_ + 2 * Nw_ : Ax_ + 2 * Nw_;
            Nx0_ -= Limit_ - First_;
            while (First_ != Limit_) {
                if (*First_++ != *Other_++) {
                    return false;
                }
            }

            First_ = Other_;
            Last_  = Use2_ ? Last1_ : Last2_;
            Other_ = Use2_ ? Right_.Ax_ : Ax_;
            Use2_  = !Use2_;
        }
        return true;
    }

    size_t Base_(size_t Ix_ = 0) const {
        return (Ix_ += Idx_) < Nw_ ? (Ix_ + Nw_) : (Ix_ - Nw_);
    }

    unsigned int Idx_;
    Ty_ Ax_[2 * Nw_];
};

// CLASS TEMPLATE mersenne_twister
template <class Ty_, int Wx_, int Nx_, int Mx_, int Rx_, Ty_ Px_, int Ux_, int Sx_, Ty_ Bx_, int Tx_, Ty_ Cx_, int Lx_>
class mersenne_twister : public Circ_buf_<Ty_, Nx_> { // mersenne twister generator
public:
    using result_type = Ty_;

    static constexpr int word_size   = Wx_;
    static constexpr int state_size  = Nx_;
    static constexpr int shift_size  = Mx_;
    static constexpr int mask_bits   = Rx_;
    static constexpr Ty_ parameter_a = Px_;
    static constexpr int output_u    = Ux_;
    static constexpr int output_s    = Sx_;
    static constexpr Ty_ output_b    = Bx_;
    static constexpr int output_t    = Tx_;
    static constexpr Ty_ output_c    = Cx_;
    static constexpr int output_l    = Lx_;

    static constexpr Ty_ default_seed = 5489U;

    mersenne_twister() : Dxval_(WMSK_) {
        seed(default_seed, static_cast<Ty_>(1812433253));
    }

    explicit mersenne_twister(Ty_ Xx0_, Ty_ Dxarg_ = WMSK_, Ty_ Fxarg_ = static_cast<Ty_>(1812433253))
        : Dxval_(Dxarg_) {
        seed(Xx0_, Fxarg_);
    }

    template <class Gen_, Enable_if_seed_seq_t_<Gen_, mersenne_twister> = 0>
    explicit mersenne_twister(Gen_& Gx_) : Dxval_(WMSK_) {
        seed(Gx_);
    }

    void seed(Ty_ Xx0_ = default_seed, Ty_ Fx_ = static_cast<Ty_>(1812433253)) {
        // set initial values from specified value
        Ty_ Prev_ = this->Ax_[0] = Xx0_ & WMSK_;
        for (size_t Ix_ = 1; Ix_ < Nx_; ++Ix_) {
            Prev_ = this->Ax_[Ix_] = (Ix_ + Fx_ * (Prev_ ^ (Prev_ >> (Wx_ - 2)))) & WMSK_;
        }

        this->Idx_ = Nx_;
    }

    template <class Gen_, Enable_if_seed_seq_t_<Gen_, mersenne_twister> = 0>
    void seed(Gen_& Gx_, bool = false) { // set initial values from range
        for (size_t Ix_ = 0; Ix_ < Nx_; ++Ix_) {
            this->Ax_[Ix_] = Gx_() & WMSK_;
        }

        this->Idx_ = Nx_;
    }

    template <class Elem_, class S_Traits_>
    basic_ostream<Elem_, S_Traits_>& Write_(basic_ostream<Elem_, S_Traits_>& Ostr_) const { // write state to Ostr_
        for (size_t Ix_ = 0; Ix_ < Nx_; ++Ix_) {
            Ostr_ << this->At_(Ix_) << ' ';
        }

        return Ostr_;
    }

    NODISCARD_ result_type(min)() const {
        return 0;
    }

    NODISCARD_ result_type(max)() const {
        return WMSK_;
    }

    NODISCARD_ result_type operator()() {
        if (this->Idx_ == Nx_) {
            Refill_upper_();
        } else if (2 * Nx_ <= this->Idx_) {
            Refill_lower_();
        }

        Ty_ Res_ = this->Ax_[this->Idx_++] & WMSK_;
        Res_ ^= (Res_ >> Ux_) & Dxval_;
        Res_ ^= (Res_ << Sx_) & Bx_;
        Res_ ^= (Res_ << Tx_) & Cx_;
        Res_ ^= (Res_ & WMSK_) >> Lx_;
        return Res_;
    }

    void discard(unsigned long long Nskip_) { // discard Nskip_ elements
        for (; 0 < Nskip_; --Nskip_) {
            (void) (*this)();
        }
    }

protected:
        void Refill_lower_() { // compute values for the lower half of the history array
        size_t Ix_;
        for (Ix_ = 0; Ix_ < Nx_ - Mx_; ++Ix_) { // fill in lower region
            Ty_ Tmp_       = (this->Ax_[Ix_ + Nx_] & HMSK_) | (this->Ax_[Ix_ + Nx_ + 1] & LMSK_);
            this->Ax_[Ix_] = (Tmp_ >> 1) ^ (Tmp_ & 1 ? Px_ : 0) ^ this->Ax_[Ix_ + Nx_ + Mx_];
        }

        for (; Ix_ < Nx_ - 1; ++Ix_) { // fill in upper region (avoids modulus operation)
            Ty_ Tmp_       = (this->Ax_[Ix_ + Nx_] & HMSK_) | (this->Ax_[Ix_ + Nx_ + 1] & LMSK_);
            this->Ax_[Ix_] = (Tmp_ >> 1) ^ (Tmp_ & 1 ? Px_ : 0) ^ this->Ax_[Ix_ - Nx_ + Mx_];
        }

        Ty_ Tmp_       = (this->Ax_[Ix_ + Nx_] & HMSK_) | (this->Ax_[0] & LMSK_);
        this->Ax_[Ix_] = (Tmp_ >> 1) ^ (Tmp_ & 1 ? Px_ : 0) ^ this->Ax_[Mx_ - 1];
        this->Idx_     = 0;
    }

    void Refill_upper_() { // compute values for the upper half of the history array
        size_t Ix_;
        for (Ix_ = Nx_; Ix_ < 2 * Nx_; ++Ix_) { // fill in values
            Ty_ Tmp_       = (this->Ax_[Ix_ - Nx_] & HMSK_) | (this->Ax_[Ix_ - Nx_ + 1] & LMSK_);
            this->Ax_[Ix_] = (Tmp_ >> 1) ^ (Tmp_ & 1 ? Px_ : 0) ^ this->Ax_[Ix_ - Nx_ + Mx_];
        }
    }

    Ty_ Dxval_;

    static constexpr Ty_ WMSK_ = ~((~Ty_{0} << (Wx_ - 1)) << 1);
    static constexpr Ty_ HMSK_ = (WMSK_ << Rx_) & WMSK_;
    static constexpr Ty_ LMSK_ = ~HMSK_ & WMSK_;
};

// CLASS TEMPLATE mersenne_twister_engine
template <class Ty_, size_t Wx_, size_t Nx_, size_t Mx_, size_t Rx_, Ty_ Px_, size_t Ux_, Ty_ Dx_, size_t Sx_, Ty_ Bx_,
    size_t Tx_, Ty_ Cx_, size_t Lx_, Ty_ Fx_>
class mersenne_twister_engine : public mersenne_twister<Ty_, Wx_, Nx_, Mx_, Rx_, Px_, Ux_, Sx_, Bx_, Tx_, Cx_, Lx_> {
public:
    static constexpr unsigned long long Max_ = (((1ULL << (Wx_ - 1)) - 1) << 1) + 1;

    static_assert(0 < Mx_ && Mx_ <= Nx_ && 2U < Wx_ && Rx_ <= Wx_ && Ux_ <= Wx_ && Sx_ <= Wx_ && Tx_ <= Wx_
                      && Lx_ <= Wx_ && Wx_ <= numeric_limits<Ty_>::digits && Px_ <= Max_ && Bx_ <= Max_ && Cx_ <= Max_
                      && Dx_ <= Max_ && Fx_ <= Max_,
        "invalid template argument for mersenne_twister_engine");

    using Mybase_     = mersenne_twister<Ty_, Wx_, Nx_, Mx_, Rx_, Px_, Ux_, Sx_, Bx_, Tx_, Cx_, Lx_>;
    using result_type = Ty_;

    static constexpr size_t word_size              = Wx_;
    static constexpr size_t state_size             = Nx_;
    static constexpr size_t shift_size             = Mx_;
    static constexpr size_t mask_bits              = Rx_;
    static constexpr Ty_ xor_mask                  = Px_;
    static constexpr size_t tempering_u            = Ux_;
    static constexpr Ty_ tempering_d               = Dx_;
    static constexpr size_t tempering_s            = Sx_;
    static constexpr Ty_ tempering_b               = Bx_;
    static constexpr size_t tempering_t            = Tx_;
    static constexpr Ty_ tempering_c               = Cx_;
    static constexpr size_t tempering_l            = Lx_;
    static constexpr Ty_ initialization_multiplier = Fx_;

    static constexpr result_type default_seed = 5489U;

    mersenne_twister_engine() : Mybase_(default_seed, Dx_, Fx_) {}

    explicit mersenne_twister_engine(result_type Xx0_) : Mybase_(Xx0_, Dx_, Fx_) {}

    template <class Seed_seq_, Enable_if_seed_seq_t_<Seed_seq_, mersenne_twister_engine> = 0>
    explicit mersenne_twister_engine(Seed_seq_& Seq_) : Mybase_(default_seed, Dx_, Fx_) {
        seed(Seq_);
    }

    void seed(result_type Xx0_ = default_seed) { // set initial values from specified value
        Mybase_::seed(Xx0_, Fx_);
    }

    template <class Seed_seq_, Enable_if_seed_seq_t_<Seed_seq_, mersenne_twister_engine> = 0>
    void seed(Seed_seq_& Seq_) { // reset sequence from seed sequence
        constexpr int Kx_ = (Wx_ + 31) / 32;
        unsigned long Arr_[Kx_ * Nx_];
        Seq_.generate(&Arr_[0], &Arr_[Kx_ * Nx_]);

        int Idx0_ = 0;
        Ty_ Sum_  = 0;
        for (size_t Ix_ = 0; Ix_ < Nx_; ++Ix_, Idx0_ += Kx_) { // pack Kx_ words
            this->Ax_[Ix_] = Arr_[Idx0_];
            for (int Jx_ = 1; Jx_ < Kx_; ++Jx_) {
                this->Ax_[Ix_] |= static_cast<Ty_>(Arr_[Idx0_ + Jx_]) << (32 * Jx_);
            }

            this->Ax_[Ix_] &= this->WMSK_;

            if (Ix_ == 0) {
                Sum_ = this->Ax_[Ix_] >> Rx_;
            } else {
                Sum_ |= this->Ax_[Ix_];
            }
        }

        if (Sum_ == 0) {
            this->Ax_[0] = this->WMSK_;
        }

        this->Idx_ = Nx_;
    }

    NODISCARD_ static constexpr result_type(min)() {
        return 0;
    }

    NODISCARD_ static constexpr result_type(max)() {
        return Mybase_::WMSK_;
    }
};

using mt19937 = mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15,
    0xefc60000, 18, 1812433253>;

// CLASS TEMPLATE uniform_real
template <class Ty_ = double>
class uniform_real { // uniform real distribution
public:
    using result_type = Ty_;

    struct param_type { // parameter package
        using distribution_type = uniform_real;

        param_type() {
            Init_(Ty_{0}, Ty_{1});
        }

        explicit param_type(Ty_ Min0_, Ty_ Max0_ = Ty_{1}) {
            Init_(Min0_, Max0_);
        }

        NODISCARD_ bool operator==(const param_type& Right_) const {
            return Min_ == Right_.Min_ && Max_ == Right_.Max_;
        }

        NODISCARD_ bool operator!=(const param_type& Right_) const {
            return !(*this == Right_);
        }

        NODISCARD_ result_type a() const {
            return Min_;
        }

        NODISCARD_ result_type b() const {
            return Max_;
        }

        void Init_(Ty_ Min0_, Ty_ Max0_) { // set internal state
            assert(Min0_ <= Max0_ && (0 <= Min0_ || Max0_ <= Min0_ + (numeric_limits<Ty_>::max)()) &&
                "invalid min and max arguments for uniform_real");
            Min_ = Min0_;
            Max_ = Max0_;
        }

        result_type Min_;
        result_type Max_;
    };

    uniform_real() : Par_(Ty_{0}, Ty_{1}) {}

    explicit uniform_real(Ty_ Min0_, Ty_ Max0_ = Ty_{1}) : Par_(Min0_, Max0_) {}

    explicit uniform_real(const param_type& Par0_) : Par_(Par0_) {}

    NODISCARD_ result_type a() const {
        return Par_.a();
    }

    NODISCARD_ result_type b() const {
        return Par_.b();
    }

    NODISCARD_ param_type param() const {
        return Par_;
    }

    void param(const param_type& Par0_) { // set parameter package
        Par_ = Par0_;
    }

    NODISCARD_ result_type(min)() const {
        return Par_.Min_;
    }

    NODISCARD_ result_type(max)() const {
        return Par_.Max_;
    }

    void reset() {} // clear internal state

    template <class Engine_>
    NODISCARD_ result_type operator()(Engine_& Eng_) const {
        return Eval_(Eng_, Par_);
    }

    template <class Engine_>
    NODISCARD_ result_type operator()(Engine_& Eng_, const param_type& Par0_) const {
        return Eval_(Eng_, Par0_);
    }

    template <class Elem_, class Traits_>
    basic_istream<Elem_, Traits_>& Read_(basic_istream<Elem_, Traits_>& Istr_) { // read state from Istr_
        Ty_ Min0_;
        Ty_ Max0_;
        In_(Istr_, Min0_);
        In_(Istr_, Max0_);
        Par_.Init_(Min0_, Max0_);
        return Istr_;
    }

    template <class Elem_, class Traits_>
    basic_ostream<Elem_, Traits_>& Write_(basic_ostream<Elem_, Traits_>& Ostr_) const { // write state to Ostr_
        Out_(Ostr_, Par_.Min_);
        Out_(Ostr_, Par_.Max_);
        return Ostr_;
    }

private:
    template <class Engine_>
    result_type Eval_(Engine_& Eng_, const param_type& Par0_) const {
        return NRAND_(Eng_, Ty_) * (Par0_.Max_ - Par0_.Min_) + Par0_.Min_;
    }

    param_type Par_;
};

template <class Elem_, class Traits_, class Ty_>
basic_istream<Elem_, Traits_>& operator>>(basic_istream<Elem_, Traits_>& Istr_,
    uniform_real<Ty_>& Dist_) { // read state from Istr_
    return Dist_.Read_(Istr_);
}

template <class Elem_, class Traits_, class Ty_>
basic_ostream<Elem_, Traits_>& operator<<(basic_ostream<Elem_, Traits_>& Ostr_,
    const uniform_real<Ty_>& Dist_) { // write state to Ostr_
    return Dist_.Write_(Ostr_);
}

// CLASS TEMPLATE uniform_real_distribution
template <class Ty_ = double>
class uniform_real_distribution : public uniform_real<Ty_> { // uniform real distribution
public:
    using Mybase_     = uniform_real<Ty_>;
    using Mypbase_    = typename Mybase_::param_type;
    using result_type = typename Mybase_::result_type;

    struct param_type : Mypbase_ { // parameter package
        using distribution_type = uniform_real_distribution;

        param_type() : Mypbase_(Ty_{0}, Ty_{1}) {}

        explicit param_type(Ty_ Min0_, Ty_ Max0_ = Ty_{1}) : Mypbase_(Min0_, Max0_) {}

        param_type(const Mypbase_& Right_) : Mypbase_(Right_) {}
    };

    uniform_real_distribution() : Mybase_(Ty_{0}, Ty_{1}) {}

    explicit uniform_real_distribution(Ty_ Min0_, Ty_ Max0_ = Ty_{1}) : Mybase_(Min0_, Max0_) {}

    explicit uniform_real_distribution(const param_type& Par0_) : Mybase_(Par0_) {}
};

template <class Ty_>
NODISCARD_ bool operator==(const uniform_real_distribution<Ty_>& Left_, const uniform_real_distribution<Ty_>& Right_) {
    return Left_.param() == Right_.param();
}

template <class Ty_>
NODISCARD_ bool operator!=(const uniform_real_distribution<Ty_>& Left_, const uniform_real_distribution<Ty_>& Right_) {
    return !(Left_ == Right_);
}

#undef NRAND_

#undef NODISCARD_

} // namespace ms_stl
