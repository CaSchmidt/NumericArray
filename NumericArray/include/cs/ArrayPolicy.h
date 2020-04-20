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

#ifndef ARRAYPOLICY_H
#define ARRAYPOLICY_H

#include <cs/impl/ArrayPolicyImpl.h>
#include <cs/TypeTraits.h>

namespace cs {

  /*
   * NOTE:
   *
   * i := [0,ROWS-1] -> Row Index
   * j := [0,COLS-1] -> Column Index
   * l := [0,SIZE-1] -> Linear Mapping to Row-Major Array Index
   *
   *
   *
   * Explanation of Row-Major Array Index:
   *
   * {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
   * ->
   * [ 0  1   2   3 ]
   * [ 4  5   6   7 ]
   * [ 8  9  10  11 ]
   *
   * A Policy's column() and row() functions need to be implemented accordingly;
   * even for a Column-Major Policy!
   */

  template<typename traits_T>
  struct RowMajorPolicy {
    using   size_type = if_size_type<typename traits_T::size_type>;
    using traits_type = traits_T;

    enum : size_type {
      Columns = traits_type::Columns,
      Rows    = traits_type::Rows
    };

    static constexpr size_type column(const size_type l)
    {
      return l%Columns;
    }

    template<size_type i, size_type j>
    static constexpr size_type index()
    {
      return i*Columns + j;
    }

    static constexpr size_type index(const size_type i, const size_type j)
    {
      return i*Columns + j;
    }

    static constexpr size_type row(const size_type l)
    {
      return l/Columns;
    }

    template<typename dest_T, typename src_T>
    static constexpr void assign(dest_T& dest, const src_T& src)
    {
      impl::RowMajorRowIter<Rows-1,Rows,Columns,dest_T,src_T>::run(dest, src);
    }
  };

} // namespace cs

#endif // ARRAYPOLICY_H