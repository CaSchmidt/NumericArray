/****************************************************************************
** Copyright (c) 2020, Carsten Schmidt. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#ifndef N4_SIMD_H
#define N4_SIMD_H

#define HAVE_SSE2

#include <xmmintrin.h>
#ifdef HAVE_SSE2
# include <emmintrin.h>
#endif

#include <N4/TypeTraits.h>

namespace simd {

  ////// Types ///////////////////////////////////////////////////////////////

  using n4::real_t;

  using simd_t = __m128;

  ////// Macros //////////////////////////////////////////////////////////////

#ifdef HAVE_SSE2
# define SIMD_SHUFFLE(x,p3,p2,p1,p0) \
  _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(x), _MM_SHUFFLE((p3), (p2), (p1), (p0))))

# define SIMD_SHL(x,count) \
  _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(x), (count)))

# define SIMD_SHR(x,count) \
  _mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(x), (count)))
#else
# define SIMD_SHUFFLE(x,p3,p2,p1,p0) \
  _mm_shuffle_ps(x, x, _MM_SHUFFLE((p3), (p2), (p1), (p0)))
#endif

  ////// Elementary Functions ////////////////////////////////////////////////

  inline simd_t add(const simd_t& a, const simd_t& b)
  {
    return _mm_add_ps(a, b);
  }

  inline simd_t div(const simd_t& a, const simd_t& b)
  {
    return _mm_div_ps(a, b);
  }

  inline simd_t hadd(const simd_t& x)
  {
    const simd_t y = _mm_add_ps(x, SIMD_SHUFFLE(x, 2, 3, 0, 1));
    return           _mm_add_ps(y, SIMD_SHUFFLE(y, 0, 1, 2, 3));
  }

  inline simd_t load(const real_t *ptr)
  {
    return _mm_load_ps(ptr);
  }

  inline simd_t mul(const simd_t& a, const simd_t& b)
  {
    return _mm_mul_ps(a, b);
  }

  inline simd_t set(const real_t val)
  {
    return _mm_set1_ps(val);
  }

  inline simd_t sqrt(const simd_t& x)
  {
    return _mm_sqrt_ps(x);
  }

  inline void store(real_t *ptr, const simd_t& x)
  {
    _mm_store_ps(ptr, x);
  }

  inline simd_t sub(const simd_t& a, const simd_t& b)
  {
    return _mm_sub_ps(a, b);
  }

  inline real_t to_real(const simd_t& x)
  {
    return _mm_cvtss_f32(x);
  }

  ////// 3D Vector Functions /////////////////////////////////////////////////

  /*
   *         a0   b0   a1*b2 - a2*b1
   * a X b = a1 X b1 = a2*b0 - a0*b2
   *         a2   b2   a0*b1 - a1*b0
   */
  inline simd_t cross(const simd_t& a, const simd_t& b)
  {
    const simd_t prod1 = _mm_mul_ps(SIMD_SHUFFLE(a, 3, 0, 2, 1),
                                    SIMD_SHUFFLE(b, 3, 1, 0, 2));
    const simd_t prod2 = _mm_mul_ps(SIMD_SHUFFLE(a, 3, 1, 0, 2),
                                    SIMD_SHUFFLE(b, 3, 0, 2, 1));
    return _mm_sub_ps(prod1, prod2);
  }

  inline simd_t dot(const simd_t& a, const simd_t& b)
  {
    const simd_t prod = mul(a, b);
    return hadd(SIMD_SHR(SIMD_SHL(prod, 4), 4));
  }

  ////// 4x4 Matrix Functions ////////////////////////////////////////////////

  inline void transpose(simd_t& col0, simd_t& col1, simd_t& col2, simd_t& col3)
  {
    const simd_t tmp0 = _mm_unpacklo_ps(col0, col2);
    const simd_t tmp1 = _mm_unpackhi_ps(col0, col2);
    const simd_t tmp2 = _mm_unpacklo_ps(col1, col3);
    const simd_t tmp3 = _mm_unpackhi_ps(col1, col3);
    col0 = _mm_unpacklo_ps(tmp0, tmp2);
    col1 = _mm_unpackhi_ps(tmp0, tmp2);
    col2 = _mm_unpacklo_ps(tmp1, tmp3);
    col3 = _mm_unpackhi_ps(tmp1, tmp3);
  }

} // namespace simd

#endif // N4_SIMD_H
