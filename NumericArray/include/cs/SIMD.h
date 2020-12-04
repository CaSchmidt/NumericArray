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

#ifndef SIMD_H
#define SIMD_H

#include <cstddef>

#include <emmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

namespace cs {

  ////// Macros //////////////////////////////////////////////////////////////

#define SIMD_SHUFFLE_PD(x,fp1,fp0)                                                   \
  _mm_castsi128_pd(_mm_shuffle_epi32(_mm_castpd_si128(x),                            \
                                     _MM_SHUFFLE((((fp1) << 1) + 1), ((fp1) << 1),   \
                                                 (((fp0) << 1) + 1), ((fp0) << 1))))

#define SIMD_SHUFFLE_PS(x,fp3,fp2,fp1,fp0) \
  _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(x), _MM_SHUFFLE((fp3), (fp2), (fp1), (fp0))))

  ////// Traits //////////////////////////////////////////////////////////////

  template<typename T>
  struct SIMDtraits {
    // SFINAE
  };

  template<>
  struct SIMDtraits<double> {
    using  simd_type = __m128d;
    using value_type = double;

    inline static __m128d zero()
    {
      return _mm_setzero_pd();
    }
  };

  template<>
  struct SIMDtraits<float> {
    using  simd_type = __m128;
    using value_type = float;

    inline static __m128 zero()
    {
      return _mm_setzero_ps();
    }
  };

  template<typename T>
  using simd_type = typename SIMDtraits<T>::simd_type;

  ////// Implementation //////////////////////////////////////////////////////

  template<typename T>
  struct SIMD {
    using  simd_traits = SIMDtraits<T>;
    using  simd_type   = typename simd_traits::simd_type;
    using value_type   = typename simd_traits::value_type;

    static inline constexpr std::size_t    Alignment = sizeof(simd_type);
    static inline constexpr std::size_t ElementCount = sizeof(simd_type)/sizeof(value_type);

    inline static constexpr std::size_t blocks(const std::size_t count)
    {
      return (count + ElementCount - 1)/ElementCount;
    }

    inline static constexpr std::size_t size(const std::size_t count)
    {
      return blocks(count)*ElementCount;
    }

    inline static simd_type zero()
    {
      return simd_traits::zero();
    }

    // Interface - double ////////////////////////////////////////////////////

    inline static __m128d load(const double *src)
    {
      return _mm_load_pd(src);
    }

    inline static __m128d set(const double& x)
    {
      return _mm_set1_pd(x);
    }

    inline static void store(double *dest, const __m128d& x)
    {
      _mm_store_pd(dest, x);
    }

    inline static __m128d add(const __m128d& a, const __m128d& b)
    {
      return _mm_add_pd(a, b);
    }

    inline static __m128d sub(const __m128d& a, const __m128d& b)
    {
      return _mm_sub_pd(a, b);
    }

    inline static __m128d mul(const __m128d& a, const __m128d& b)
    {
      return _mm_mul_pd(a, b);
    }

    inline static __m128d div(const __m128d& a, const __m128d& b)
    {
      return _mm_div_pd(a, b);
    }

    inline static __m128d min(const __m128d& a, const __m128d& b)
    {
      return _mm_min_pd(a, b);
    }

    inline static __m128d max(const __m128d& a, const __m128d& b)
    {
      return _mm_max_pd(a, b);
    }

    inline static double scalar(const __m128d& x)
    {
      return _mm_cvtsd_f64(x);
    }

    inline static __m128d hadd(const __m128d& x)
    {
      return _mm_add_pd(x, SIMD_SHUFFLE_PD(x, 0, 1));
    }

    // Interface - float /////////////////////////////////////////////////////

    inline static __m128 load(const float *src)
    {
      return _mm_load_ps(src);
    }

    inline static __m128 set(const float& x)
    {
      return _mm_set1_ps(x);
    }

    inline static void store(float *dest, const __m128& x)
    {
      _mm_store_ps(dest, x);
    }

    inline static __m128 add(const __m128& a, const __m128& b)
    {
      return _mm_add_ps(a, b);
    }

    inline static __m128 sub(const __m128& a, const __m128& b)
    {
      return _mm_sub_ps(a, b);
    }

    inline static __m128 mul(const __m128& a, const __m128& b)
    {
      return _mm_mul_ps(a, b);
    }

    inline static __m128 div(const __m128& a, const __m128& b)
    {
      return _mm_div_ps(a, b);
    }

    inline static __m128 min(const __m128& a, const __m128& b)
    {
      return _mm_min_ps(a, b);
    }

    inline static __m128 max(const __m128& a, const __m128& b)
    {
      return _mm_max_ps(a, b);
    }

    inline static float scalar(const __m128& x)
    {
      return _mm_cvtss_f32(x);
    }

    inline static __m128 hadd(const __m128& x)
    {
      const __m128 temp = _mm_add_ps(x,    SIMD_SHUFFLE_PS(x,    2, 3, 0, 1));
      return              _mm_add_ps(temp, SIMD_SHUFFLE_PS(temp, 0, 1, 2, 3));
    }
  };

} // namespace cs

#endif // SIMD_H
