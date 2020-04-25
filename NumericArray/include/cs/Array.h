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

#include <cs/impl/ArrayImpl.h>
#include <cs/ArrayPolicy.h>
#include <cs/ListAssign.h>

namespace cs {

  template<typename traits_T, typename policy_T = RowMajorPolicy<traits_T>>
  class Array
      : public ExprBase<traits_T,Array<traits_T,policy_T>> {
  public:
    using   list_type = ListAssign<traits_T>;
    using policy_type = policy_T;
    using   size_type = typename traits_T::size_type;
    using traits_type = traits_T;
    using  value_type = typename traits_T::value_type;

    ~Array() noexcept = default;

    // Copy Assignment ///////////////////////////////////////////////////////

    Array(const Array& other) noexcept
    {
      operator=(other);
    }

    Array& operator=(const Array& other) noexcept
    {
      if( this != &other ) {
        impl::ArrayCopy<traits_type,traits_type::Size-1>::run(_data, other._data);
      }
      return *this;
    }

    // Move Assignment ///////////////////////////////////////////////////////

    Array(Array&& other) noexcept
    {
      operator=(std::move(other));
    }

    Array& operator=(Array&& other) noexcept
    {
      if( this != &other ) {
        impl::ArrayMove<traits_type,traits_type::Size-1>::run(_data, other._data);
      }
      return *this;
    }

    // Scalar Assignment /////////////////////////////////////////////////////

    Array(const value_type& value = value_type{0}) noexcept
    {
      operator=(value);
    }

    Array& operator=(const value_type& value) noexcept
    {
      impl::ArraySet<traits_type,traits_type::Size-1>::run(_data, value);
      return *this;
    }

    // List Assignment ///////////////////////////////////////////////////////

    Array(const std::initializer_list<value_type>& list) noexcept
    {
      operator=(list);
    }

    Array& operator=(const std::initializer_list<value_type>& list) noexcept
    {
      const std::size_t max = std::min<std::size_t>(list.size(), traits_type::Size);
      for(std::size_t index = 0; index < max; index++) {
        const size_type i = list_type::row(static_cast<size_type>(index));
        const size_type j = list_type::column(static_cast<size_type>(index));
        operator()(i, j) = list.begin()[index];
      }
      for(std::size_t index = max; index < static_cast<std::size_t>(traits_type::Size); index++) {
        _data[index] = value_type{0};
      }
      return *this;
    }

    // Expression Assignment /////////////////////////////////////////////////

    template<typename derived_T>
    Array(const ExprBase<traits_type,derived_T>& expr)
    {
      operator=(expr);
    }

    template<typename derived_T>
    Array& operator=(const ExprBase<traits_type,derived_T>& expr) noexcept
    {
      impl::ArrayAssign<policy_type,traits_type::Size-1>::run(_data, expr);
      return *this;
    }

    // Element Access ////////////////////////////////////////////////////////

    constexpr value_type operator()(const size_type i, const size_type j) const
    {
      return _data[policy_type::index(i, j)];
    }

    inline value_type& operator()(const size_type i, const size_type j)
    {
      return _data[policy_type::index(i, j)];
    }

    constexpr value_type operator[](const size_type l) const
    {
      return _data[l];
    }

    inline value_type& operator[](const size_type l)
    {
      return _data[l];
    }

    // Query Size ////////////////////////////////////////////////////////////

    constexpr size_type rows() const
    {
      return traits_type::Rows;
    }

    constexpr size_type columns() const
    {
      return traits_type::Columns;
    }

    constexpr size_type size() const
    {
      return traits_type::Size;
    }

    // Compile-Time Element Access ///////////////////////////////////////////

    template<size_type i, size_type j>
    constexpr value_type eval() const
    {
      return _data[policy_type::template index<i,j>()];
    }

  private:
    value_type _data[traits_type::Size];
  };

} // namespace cs

#endif // ARRAY_H
