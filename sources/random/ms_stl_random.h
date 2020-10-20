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

#if __has_cpp_attribute(nodiscard)
#   define _NODISCARD [[nodiscard]]
#else
#   define _NODISCARD
#endif

// FUNCTION TEMPLATE generate_canonical
template <class _Real, size_t _Bits, class _Gen>
_NODISCARD _Real generate_canonical(_Gen& _Gx) { // build a floating-point value from random sequence
    const size_t _Digits  = static_cast<size_t>(numeric_limits<_Real>::digits);
    const size_t _Minbits = _Digits < _Bits ? _Digits : _Bits;

    const _Real _Gxmin = static_cast<_Real>((_Gx.min)());
    const _Real _Gxmax = static_cast<_Real>((_Gx.max)());
    const _Real _Rx    = (_Gxmax - _Gxmin) + _Real{1};

    const int _Ceil = static_cast<int>(std::ceil(static_cast<_Real>(_Minbits) / std::log2(_Rx)));
    const int _Kx   = _Ceil < 1 ? 1 : _Ceil;

    _Real _Ans{0};
    _Real _Factor{1};

    for (int _Idx = 0; _Idx < _Kx; ++_Idx) { // add in another set of bits
        _Ans += (static_cast<_Real>(_Gx()) - _Gxmin) * _Factor;
        _Factor *= _Rx;
    }

    return _Ans / _Factor;
}

#define _NRAND(eng, resty) (generate_canonical<resty, static_cast<size_t>(-1)>(eng))

// ALIAS TEMPLATE _Enable_if_seed_seq_t
template <class _Seed_seq, class _Self, class _Engine = _Self>
using _Enable_if_seed_seq_t = typename enable_if<
    !is_convertible<typename remove_cv<_Seed_seq>::type,
        typename _Self::
            result_type>::value && !is_same<typename remove_cv<_Seed_seq>::type, _Self>::value && !is_same<typename remove_cv<_Seed_seq>::type, _Engine>::value,
    int>::type;

// CLASS TEMPLATE _Circ_buf FOR subtract_with_carry, subtract_with_carry_01, AND mersenne_twister
template <class _Ty, size_t _Nw>
struct _Circ_buf { // holds historical values for generators
    _Ty _At(size_t _Ix) const {
        return _Ax[_Base(_Ix)];
    }

    bool _Equals(const _Circ_buf& _Right) const {
        const _Ty* _Last1 = _Ax + _Idx;
        const _Ty* _Last2 = _Right._Ax + _Right._Idx;
        const _Ty* _First;
        const _Ty* _Last;
        const _Ty* _Other;
        bool _Use2 = _Base() < _Right._Base();

        if (_Use2) { // _Right's range is higher up in the array
                     // than ours, so scan it first
            _First = _Right._Ax + _Right._Base();
            _Last  = _Last2;
            _Other = _Ax + _Base();
        } else { // our range is higher up in the array
                 // than _Right's, so scan ours first
            _First = _Ax + _Base();
            _Last  = _Last1;
            _Other = _Right._Ax + _Right._Base();
        }

        ptrdiff_t _Nx0 = _Nw;
        while (0 < _Nx0) { // scan
                           // note: may need up to three passes; each scan starts at the
                           // current highest array position and ends at the end of the
                           // array or the _Idx value, whichever comes first; the
                           // equality test succeeds only by reaching the _Idx value.
            const _Ty* _Limit = _First < _Last ? _Last : _Use2 ? _Right._Ax + 2 * _Nw : _Ax + 2 * _Nw;
            _Nx0 -= _Limit - _First;
            while (_First != _Limit) {
                if (*_First++ != *_Other++) {
                    return false;
                }
            }

            _First = _Other;
            _Last  = _Use2 ? _Last1 : _Last2;
            _Other = _Use2 ? _Right._Ax : _Ax;
            _Use2  = !_Use2;
        }
        return true;
    }

    size_t _Base(size_t _Ix = 0) const {
        return (_Ix += _Idx) < _Nw ? (_Ix + _Nw) : (_Ix - _Nw);
    }

    unsigned int _Idx;
    _Ty _Ax[2 * _Nw];
};

// CLASS TEMPLATE mersenne_twister
template <class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx, _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
class mersenne_twister : public _Circ_buf<_Ty, _Nx> { // mersenne twister generator
public:
    using result_type = _Ty;

    static constexpr int word_size   = _Wx;
    static constexpr int state_size  = _Nx;
    static constexpr int shift_size  = _Mx;
    static constexpr int mask_bits   = _Rx;
    static constexpr _Ty parameter_a = _Px;
    static constexpr int output_u    = _Ux;
    static constexpr int output_s    = _Sx;
    static constexpr _Ty output_b    = _Bx;
    static constexpr int output_t    = _Tx;
    static constexpr _Ty output_c    = _Cx;
    static constexpr int output_l    = _Lx;

    static constexpr _Ty default_seed = 5489U;

    mersenne_twister() : _Dxval(_WMSK) {
        seed(default_seed, static_cast<_Ty>(1812433253));
    }

    explicit mersenne_twister(_Ty _Xx0, _Ty _Dxarg = _WMSK, _Ty _Fxarg = static_cast<_Ty>(1812433253))
        : _Dxval(_Dxarg) {
        seed(_Xx0, _Fxarg);
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, mersenne_twister> = 0>
    explicit mersenne_twister(_Gen& _Gx) : _Dxval(_WMSK) {
        seed(_Gx);
    }

    void seed(_Ty _Xx0 = default_seed, _Ty _Fx = static_cast<_Ty>(1812433253)) {
        // set initial values from specified value
        _Ty _Prev = this->_Ax[0] = _Xx0 & _WMSK;
        for (size_t _Ix = 1; _Ix < _Nx; ++_Ix) {
            _Prev = this->_Ax[_Ix] = (_Ix + _Fx * (_Prev ^ (_Prev >> (_Wx - 2)))) & _WMSK;
        }

        this->_Idx = _Nx;
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, mersenne_twister> = 0>
    void seed(_Gen& _Gx, bool = false) { // set initial values from range
        for (size_t _Ix = 0; _Ix < _Nx; ++_Ix) {
            this->_Ax[_Ix] = _Gx() & _WMSK;
        }

        this->_Idx = _Nx;
    }

    template <class _Elem, class _S_Traits>
    basic_ostream<_Elem, _S_Traits>& _Write(basic_ostream<_Elem, _S_Traits>& _Ostr) const { // write state to _Ostr
        for (size_t _Ix = 0; _Ix < _Nx; ++_Ix) {
            _Ostr << this->_At(_Ix) << ' ';
        }

        return _Ostr;
    }

    _NODISCARD result_type(min)() const {
        return 0;
    }

    _NODISCARD result_type(max)() const {
        return _WMSK;
    }

    _NODISCARD result_type operator()() {
        if (this->_Idx == _Nx) {
            _Refill_upper();
        } else if (2 * _Nx <= this->_Idx) {
            _Refill_lower();
        }

        _Ty _Res = this->_Ax[this->_Idx++] & _WMSK;
        _Res ^= (_Res >> _Ux) & _Dxval;
        _Res ^= (_Res << _Sx) & _Bx;
        _Res ^= (_Res << _Tx) & _Cx;
        _Res ^= (_Res & _WMSK) >> _Lx;
        return _Res;
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void) (*this)();
        }
    }

protected:
        void _Refill_lower() { // compute values for the lower half of the history array
        size_t _Ix;
        for (_Ix = 0; _Ix < _Nx - _Mx; ++_Ix) { // fill in lower region
            _Ty _Tmp       = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix + _Nx + 1] & _LMSK);
            this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix + _Nx + _Mx];
        }

        for (; _Ix < _Nx - 1; ++_Ix) { // fill in upper region (avoids modulus operation)
            _Ty _Tmp       = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix + _Nx + 1] & _LMSK);
            this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix - _Nx + _Mx];
        }

        _Ty _Tmp       = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[0] & _LMSK);
        this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Mx - 1];
        this->_Idx     = 0;
    }

    void _Refill_upper() { // compute values for the upper half of the history array
        size_t _Ix;
        for (_Ix = _Nx; _Ix < 2 * _Nx; ++_Ix) { // fill in values
            _Ty _Tmp       = (this->_Ax[_Ix - _Nx] & _HMSK) | (this->_Ax[_Ix - _Nx + 1] & _LMSK);
            this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix - _Nx + _Mx];
        }
    }

    _Ty _Dxval;

    static constexpr _Ty _WMSK = ~((~_Ty{0} << (_Wx - 1)) << 1);
    static constexpr _Ty _HMSK = (_WMSK << _Rx) & _WMSK;
    static constexpr _Ty _LMSK = ~_HMSK & _WMSK;
};

// CLASS TEMPLATE mersenne_twister_engine
template <class _Ty, size_t _Wx, size_t _Nx, size_t _Mx, size_t _Rx, _Ty _Px, size_t _Ux, _Ty _Dx, size_t _Sx, _Ty _Bx,
    size_t _Tx, _Ty _Cx, size_t _Lx, _Ty _Fx>
class mersenne_twister_engine : public mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx> {
public:
    static constexpr unsigned long long _Max = (((1ULL << (_Wx - 1)) - 1) << 1) + 1;

    static_assert(0 < _Mx && _Mx <= _Nx && 2U < _Wx && _Rx <= _Wx && _Ux <= _Wx && _Sx <= _Wx && _Tx <= _Wx
                      && _Lx <= _Wx && _Wx <= numeric_limits<_Ty>::digits && _Px <= _Max && _Bx <= _Max && _Cx <= _Max
                      && _Dx <= _Max && _Fx <= _Max,
        "invalid template argument for mersenne_twister_engine");

    using _Mybase     = mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>;
    using result_type = _Ty;

    static constexpr size_t word_size              = _Wx;
    static constexpr size_t state_size             = _Nx;
    static constexpr size_t shift_size             = _Mx;
    static constexpr size_t mask_bits              = _Rx;
    static constexpr _Ty xor_mask                  = _Px;
    static constexpr size_t tempering_u            = _Ux;
    static constexpr _Ty tempering_d               = _Dx;
    static constexpr size_t tempering_s            = _Sx;
    static constexpr _Ty tempering_b               = _Bx;
    static constexpr size_t tempering_t            = _Tx;
    static constexpr _Ty tempering_c               = _Cx;
    static constexpr size_t tempering_l            = _Lx;
    static constexpr _Ty initialization_multiplier = _Fx;

    static constexpr result_type default_seed = 5489U;

    mersenne_twister_engine() : _Mybase(default_seed, _Dx, _Fx) {}

    explicit mersenne_twister_engine(result_type _Xx0) : _Mybase(_Xx0, _Dx, _Fx) {}

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, mersenne_twister_engine> = 0>
    explicit mersenne_twister_engine(_Seed_seq& _Seq) : _Mybase(default_seed, _Dx, _Fx) {
        seed(_Seq);
    }

    void seed(result_type _Xx0 = default_seed) { // set initial values from specified value
        _Mybase::seed(_Xx0, _Fx);
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, mersenne_twister_engine> = 0>
    void seed(_Seed_seq& _Seq) { // reset sequence from seed sequence
        constexpr int _Kx = (_Wx + 31) / 32;
        unsigned long _Arr[_Kx * _Nx];
        _Seq.generate(&_Arr[0], &_Arr[_Kx * _Nx]);

        int _Idx0 = 0;
        _Ty _Sum  = 0;
        for (size_t _Ix = 0; _Ix < _Nx; ++_Ix, _Idx0 += _Kx) { // pack _Kx words
            this->_Ax[_Ix] = _Arr[_Idx0];
            for (int _Jx = 1; _Jx < _Kx; ++_Jx) {
                this->_Ax[_Ix] |= static_cast<_Ty>(_Arr[_Idx0 + _Jx]) << (32 * _Jx);
            }

            this->_Ax[_Ix] &= this->_WMSK;

            if (_Ix == 0) {
                _Sum = this->_Ax[_Ix] >> _Rx;
            } else {
                _Sum |= this->_Ax[_Ix];
            }
        }

        if (_Sum == 0) {
            this->_Ax[0] = this->_WMSK;
        }

        this->_Idx = _Nx;
    }

    _NODISCARD static constexpr result_type(min)() {
        return 0;
    }

    _NODISCARD static constexpr result_type(max)() {
        return _Mybase::_WMSK;
    }
};

using mt19937 = mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15,
    0xefc60000, 18, 1812433253>;

// CLASS TEMPLATE uniform_real
template <class _Ty = double>
class uniform_real { // uniform real distribution
public:
    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = uniform_real;

        param_type() {
            _Init(_Ty{0}, _Ty{1});
        }

        explicit param_type(_Ty _Min0, _Ty _Max0 = _Ty{1}) {
            _Init(_Min0, _Max0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Min == _Right._Min && _Max == _Right._Max;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD result_type a() const {
            return _Min;
        }

        _NODISCARD result_type b() const {
            return _Max;
        }

        void _Init(_Ty _Min0, _Ty _Max0) { // set internal state
            assert(_Min0 <= _Max0 && (0 <= _Min0 || _Max0 <= _Min0 + (numeric_limits<_Ty>::max)()) &&
                "invalid min and max arguments for uniform_real");
            _Min = _Min0;
            _Max = _Max0;
        }

        result_type _Min;
        result_type _Max;
    };

    uniform_real() : _Par(_Ty{0}, _Ty{1}) {}

    explicit uniform_real(_Ty _Min0, _Ty _Max0 = _Ty{1}) : _Par(_Min0, _Max0) {}

    explicit uniform_real(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD result_type a() const {
        return _Par.a();
    }

    _NODISCARD result_type b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return _Par._Min;
    }

    _NODISCARD result_type(max)() const {
        return _Par._Max;
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Min0;
        _Ty _Max0;
        _In(_Istr, _Min0);
        _In(_Istr, _Max0);
        _Par._Init(_Min0, _Max0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Min);
        _Out(_Ostr, _Par._Max);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        return _NRAND(_Eng, _Ty) * (_Par0._Max - _Par0._Min) + _Par0._Min;
    }

    param_type _Par;
};

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    uniform_real<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const uniform_real<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

// CLASS TEMPLATE uniform_real_distribution
template <class _Ty = double>
class uniform_real_distribution : public uniform_real<_Ty> { // uniform real distribution
public:
    using _Mybase     = uniform_real<_Ty>;
    using _Mypbase    = typename _Mybase::param_type;
    using result_type = typename _Mybase::result_type;

    struct param_type : _Mypbase { // parameter package
        using distribution_type = uniform_real_distribution;

        param_type() : _Mypbase(_Ty{0}, _Ty{1}) {}

        explicit param_type(_Ty _Min0, _Ty _Max0 = _Ty{1}) : _Mypbase(_Min0, _Max0) {}

        param_type(const _Mypbase& _Right) : _Mypbase(_Right) {}
    };

    uniform_real_distribution() : _Mybase(_Ty{0}, _Ty{1}) {}

    explicit uniform_real_distribution(_Ty _Min0, _Ty _Max0 = _Ty{1}) : _Mybase(_Min0, _Max0) {}

    explicit uniform_real_distribution(const param_type& _Par0) : _Mybase(_Par0) {}
};

template <class _Ty>
_NODISCARD bool operator==(const uniform_real_distribution<_Ty>& _Left, const uniform_real_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const uniform_real_distribution<_Ty>& _Left, const uniform_real_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

#undef _NRAND

#undef _NODISCARD

} // namespace ms_stl
