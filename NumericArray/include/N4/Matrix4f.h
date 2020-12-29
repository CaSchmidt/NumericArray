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

#ifndef N4_MATRIX4F_H
#define N4_MATRIX4F_H

#include <algorithm>
#include <initializer_list>

#include <N4/SIMD.h>

namespace n4 {

  class Matrix4f {
  public:
    ////// Destructor ////////////////////////////////////////////////////////

    ~Matrix4f() noexcept = default;

    ////// Constructor ///////////////////////////////////////////////////////

    Matrix4f(const real_t val = 0) noexcept
    {
      set(val);
    }

    Matrix4f& operator=(const real_t val)
    {
      set(val);
      return *this;
    }

    ////// Initialize (Row-Major List!) //////////////////////////////////////

    Matrix4f(const std::initializer_list<real_t>& list) noexcept
    {
      initialize(list);
    }

    Matrix4f& operator=(const std::initializer_list<real_t>& list)
    {
      initialize(list);
      return *this;
    }

    ////// Copy //////////////////////////////////////////////////////////////

    Matrix4f(const Matrix4f& other) noexcept
    {
      copy(other);
    }

    Matrix4f& operator=(const Matrix4f& other)
    {
      copy(other);
      return *this;
    }

    ////// Move //////////////////////////////////////////////////////////////

    Matrix4f(Matrix4f&& other) noexcept
    {
      copy(other);
    }

    Matrix4f& operator=(Matrix4f&& other)
    {
      copy(other);
      return *this;
    }

    ////// Data Access ///////////////////////////////////////////////////////

    inline const real_t *data() const
    {
      return _data;
    }

    inline real_t *data()
    {
      return _data;
    }

    ////// Element Access ////////////////////////////////////////////////////

    constexpr size_t size() const
    {
      return 16;
    }

    constexpr size_t rows() const
    {
      return 4;
    }

    constexpr size_t columns() const
    {
      return 4;
    }

    inline real_t operator()(const size_t i, const size_t j) const
    {
      return _data[i + j*4]; // Column-Major!
    }

    inline real_t& operator()(const size_t i, const size_t j)
    {
      return _data[i + j*4]; // Column-Major!
    }

    ////// Functions /////////////////////////////////////////////////////////

    Matrix4f inverse() const
    {
      Matrix4f result;
      simd::inverse(result._data, _data);
      return result;
    }

    Matrix4f transpose() const
    {
      Matrix4f result;
      simd::transpose(result._data, _data);
      return result;
    }

  private:
    inline void copy(const Matrix4f& other)
    {
      simd::store(_data +  0, simd::load(other._data +  0));
      simd::store(_data +  4, simd::load(other._data +  4));
      simd::store(_data +  8, simd::load(other._data +  8));
      simd::store(_data + 12, simd::load(other._data + 12));
    }

    inline void initialize(const std::initializer_list<real_t>& list)
    {
      set(0);
      const size_t s = std::min<size_t>(list.size(), size());
      for(size_t l = 0; l < s; l++) {
        // NOTE: Row-Major Notation: l = i*4 + j
        const size_t i = l/4;
        const size_t j = l%4;
        operator()(i, j) = list.begin()[l];
      }
    }

    inline void set(const real_t val)
    {
      const simd::simd_t col = simd::set(val);
      simd::store(_data +  0, col);
      simd::store(_data +  4, col);
      simd::store(_data +  8, col);
      simd::store(_data + 12, col);
    }

    alignas(sizeof(simd::simd_t)) real_t _data[16];
  };

} // namespace n4

#endif // N4_MATRIX4F_H
