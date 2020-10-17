// SPDX-License-Identifier: BSD-2-Clause

// This code is part of the sfizz library and is licensed under a BSD 2-clause
// license. You should have receive a LICENSE.md file along with the code.
// If not, contact the sfizz maintainers at https://github.com/sfztools/sfizz

#pragma once
#include "SIMDConfig.h"
#include <algorithm>
#if SFIZZ_HAVE_SSE
#include <xmmintrin.h>
#endif

template <class T>
constexpr T clamp(T v, T lo, T hi)
{
    return std::max(std::min(v, hi), lo);
}

/**
 * @brief Compute the 3rd-order Hermite interpolation polynomial.
 *
 * @tparam R
 * @param x
 * @return R
 */
template <class R>
R hermite3(R x)
{
    x = std::abs(x);
    R x2 = x * x;
    R x3 = x2 * x;
    R y = 0;
    R q = R(5./2.) * x2; // a reoccurring term
    R p1 = R(1) - q + R(3./2.) * x3;
    R p2 = R(2) - R(4) * x + q - R(1./2.) * x3;
    y = (x < R(2)) ? p2 : y;
    y = (x < R(1)) ? p1 : y;
    return y;
}

#if SFIZZ_HAVE_SSE
/**
 * @brief Compute 4 parallel elements of the 3rd-order Hermite interpolation polynomial.
 *
 * @param x
 * @return __m128
 */
inline __m128 hermite3x4(__m128 x)
{
    x = _mm_andnot_ps(_mm_set1_ps(-0.0f), x);
    __m128 x2 = _mm_mul_ps(x, x);
    __m128 x3 = _mm_mul_ps(x2, x);
    __m128 y = _mm_set1_ps(0.0f);
    __m128 q = _mm_mul_ps(_mm_set1_ps(5./2.), x2);
    __m128 p1 = _mm_add_ps(_mm_sub_ps(_mm_set1_ps(1), q), _mm_mul_ps(_mm_set1_ps(3./2.), x3));
    __m128 p2 = _mm_sub_ps(_mm_add_ps(_mm_sub_ps(_mm_set1_ps(2), _mm_mul_ps(_mm_set1_ps(4), x)), q), _mm_mul_ps(_mm_set1_ps(1./2.), x3));
    __m128 m2 = _mm_cmple_ps(x, _mm_set1_ps(2));
    y = _mm_or_ps(_mm_and_ps(m2, p2), _mm_andnot_ps(m2, y));
    __m128 m1 = _mm_cmple_ps(x, _mm_set1_ps(1));
    y = _mm_or_ps(_mm_and_ps(m1, p1), _mm_andnot_ps(m1, y));
    return y;
}
#endif

/**
 * @brief Compute the 3rd-order B-spline interpolation polynomial.
 *
 * @tparam R
 * @param x
 * @return R
 */
template <class R>
R bspline3(R x)
{
    x = std::abs(x);
    R x2 = x * x;
    R x3 = x2 * x;
    R y = 0;
    R p1 = R(2./3.) - x2 + R(1./2.) * x3;
    R p2 = R(4./3.) - R(2) * x + x2 - R(1./6.) * x3;
    y = (x < R(2)) ? p2 : y;
    y = (x < R(1)) ? p1 : y;
    return y;
}

#if SFIZZ_HAVE_SSE
/**
 * @brief Compute 4 parallel elements of the 3rd-order B-spline interpolation polynomial.
 *
 * @param x
 * @return __m128
 */
inline __m128 bspline3x4(__m128 x)
{
    x = _mm_andnot_ps(_mm_set1_ps(-0.0f), x);
    __m128 x2 = _mm_mul_ps(x, x);
    __m128 x3 = _mm_mul_ps(x2, x);
    __m128 y = _mm_set1_ps(0.0f);
    __m128 p1 = _mm_add_ps(_mm_sub_ps(_mm_set1_ps(2./3.), x2), _mm_mul_ps(_mm_set1_ps(1./2.), x3));
    __m128 p2 = _mm_sub_ps(_mm_add_ps(_mm_sub_ps(_mm_set1_ps(4./3.), _mm_mul_ps(_mm_set1_ps(2), x)), x2), _mm_mul_ps(_mm_set1_ps(1./6.), x3));
    __m128 m2 = _mm_cmple_ps(x, _mm_set1_ps(2));
    y = _mm_or_ps(_mm_and_ps(m2, p2), _mm_andnot_ps(m2, y));
    __m128 m1 = _mm_cmple_ps(x, _mm_set1_ps(1));
    y = _mm_or_ps(_mm_and_ps(m1, p1), _mm_andnot_ps(m1, y));
    return y;
}
#endif
