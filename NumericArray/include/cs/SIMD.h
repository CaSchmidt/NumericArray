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

  template<typename T>
  struct SIMD {
    // SFINAE
  };

  template<>
  struct SIMD<double> {
    using  simd_type = __m128d;
    using value_type = double;

    static inline constexpr std::size_t  Alignment = sizeof(simd_type);
    static inline constexpr std::size_t ValueCount = sizeof(simd_type)/sizeof(value_type);

    inline static constexpr std::size_t blocks(const std::size_t count)
    {
      return (count + ValueCount - 1)/ValueCount;
    }

    inline static constexpr std::size_t size(const std::size_t count)
    {
      return blocks(count)*ValueCount;
    }

    inline static simd_type load(const value_type *src)
    {
      return _mm_load_pd(src);
    }

    inline static simd_type set(const value_type& x)
    {
      return _mm_set1_pd(x);
    }

    inline static void store(value_type *dest, const simd_type& x)
    {
      _mm_store_pd(dest, x);
    }

    inline static simd_type add(const simd_type& a, const simd_type& b)
    {
      return _mm_add_pd(a, b);
    }

    inline static simd_type sub(const simd_type& a, const simd_type& b)
    {
      return _mm_sub_pd(a, b);
    }

    inline static simd_type mul(const simd_type& a, const simd_type& b)
    {
      return _mm_mul_pd(a, b);
    }

    inline static simd_type div(const simd_type& a, const simd_type& b)
    {
      return _mm_div_pd(a, b);
    }
  };

  template<>
  struct SIMD<float> {
    using  simd_type = __m128;
    using value_type = float;

    static inline constexpr std::size_t  Alignment = sizeof(simd_type);
    static inline constexpr std::size_t ValueCount = sizeof(simd_type)/sizeof(value_type);

    inline static constexpr std::size_t blocks(const std::size_t count)
    {
      return (count + ValueCount - 1)/ValueCount;
    }

    inline static constexpr std::size_t size(const std::size_t count)
    {
      return blocks(count)*ValueCount;
    }

    inline static simd_type load(const value_type *src)
    {
      return _mm_load_ps(src);
    }

    inline static simd_type set(const value_type& x)
    {
      return _mm_set1_ps(x);
    }

    inline static void store(value_type *dest, const simd_type& x)
    {
      _mm_store_ps(dest, x);
    }

    inline static simd_type add(const simd_type& a, const simd_type& b)
    {
      return _mm_add_ps(a, b);
    }

    inline static simd_type sub(const simd_type& a, const simd_type& b)
    {
      return _mm_sub_ps(a, b);
    }

    inline static simd_type mul(const simd_type& a, const simd_type& b)
    {
      return _mm_mul_ps(a, b);
    }

    inline static simd_type div(const simd_type& a, const simd_type& b)
    {
      return _mm_div_ps(a, b);
    }
  };

  template<typename T>
  using simd_type = typename SIMD<T>::simd_type;

} // namespace cs

#endif // SIMD_H
