/****************************************************************************
** Copyright (c) 2019, Carsten Schmidt. All rights reserved.
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

#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>

#include "cs/impl/ArrayImpl.h"
#include "cs/IndexPolicy.h"
#include "cs/ExprBase.h"

namespace cs {

  template<typename scalar_T, dim_T ROWS, dim_T COLS>
  class Array
      : public ExprBase<scalar_T,ROWS,COLS,Array<scalar_T,ROWS,COLS>> {
  public:
    using value_type = if_float_type<scalar_T>;

    ~Array() noexcept = default;

    Array(const Array& other) noexcept
    {
      operator=(other);
    }

    Array& operator=(const Array& other) noexcept
    {
      if( this != &other ) {
        impl::ArrayCopy<scalar_T,SIZE-1,SIZE>::run(_data, other._data);
      }
      return *this;
    }

    Array(Array&& other) noexcept
    {
      operator=(std::move(other));
    }

    Array& operator=(Array&& other) noexcept
    {
      if( this != &other ) {
        impl::ArrayMove<scalar_T,SIZE-1,SIZE>::run(_data, other._data);
      }
      return *this;
    }

    Array(const scalar_T& value = scalar_T{0}) noexcept
    {
      operator=(value);
    }

    Array& operator=(const scalar_T& value) noexcept
    {
      impl::ArraySet<scalar_T,SIZE-1,SIZE>::run(_data, value);
      return *this;
    }

    Array(const std::initializer_list<scalar_T>& list) noexcept
    {
      operator=(list);
    }

    Array& operator=(const std::initializer_list<scalar_T>& list) noexcept
    {
      const std::size_t max = std::min<std::size_t>(list.size(), SIZE);
      for(std::size_t i = 0; i < max; i++) {
        _data[i] = list.begin()[i];
      }
      for(std::size_t i = max; i < static_cast<std::size_t>(SIZE); i++) {
        _data[i] = scalar_T{0};
      }
      return *this;
    }

    template<typename derived_T>
    Array(const ExprBase<scalar_T,ROWS,COLS,derived_T>& expr)
    {
      IndexPolicy::assign(*this, expr.as_derived());
    }

    template<typename derived_T>
    Array& operator=(const ExprBase<scalar_T,ROWS,COLS,derived_T>& expr) noexcept
    {
      IndexPolicy::assign(*this, expr.as_derived());
      return *this;
    }

    constexpr scalar_T operator()(const dim_T i, const dim_T j) const
    {
      return _data[IndexPolicy::index(i, j)];
    }

    inline scalar_T& operator()(const dim_T i, const dim_T j)
    {
      return _data[IndexPolicy::index(i, j)];
    }

    constexpr scalar_T operator[](const dim_T index) const
    {
      return _data[index];
    }

    inline scalar_T& operator[](const dim_T index)
    {
      return _data[index];
    }

    constexpr dim_T rows() const
    {
      return ROWS;
    }

    constexpr dim_T columns() const
    {
      return COLS;
    }

    constexpr dim_T size() const
    {
      return SIZE;
    }

    template<dim_T i, dim_T j>
    constexpr scalar_T eval() const
    {
      return _data[IndexPolicy::template index<i,j>()];
    }

    template<dim_T i, dim_T j>
    inline scalar_T& ref()
    {
      return _data[IndexPolicy::template index<i,j>()];
    }

  private:
    Array() noexcept = delete;

    using IndexPolicy = RowMajorPolicy<ROWS,COLS>;

    static constexpr dim_T SIZE = ROWS*COLS;

    value_type _data[SIZE];
  };

} // namespace cs

#endif // ARRAY_H
