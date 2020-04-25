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

#ifndef ARRAYPOLICYIMPL_H
#define ARRAYPOLICYIMPL_H

#include <cs/ExprBase.h>

namespace cs {

  namespace impl {

    template<typename policy_T, auto COUNT>
    struct RowMajorIter {
      using policy_type = policy_T;
      using   size_type = typename policy_T::size_type;
      using traits_type = typename policy_T::traits_type;
      using  value_type = typename policy_T::value_type;

      static constexpr size_type l = traits_type::Size - 1 - COUNT;

      template<typename derived_T>
      static constexpr void run(value_type *dest, const ExprBase<traits_type,derived_T>& src)
      {
        constexpr size_type i = policy_type::template row<l>();
        constexpr size_type j = policy_type::template column<l>();

        dest[l] = src.as_derived().template eval<i,j>();
        RowMajorIter<policy_type,COUNT-1>::run(dest, src);
      }
    };

    template<typename policy_T>
    struct RowMajorIter<policy_T,0> {
      using policy_type = policy_T;
      using   size_type = typename policy_T::size_type;
      using traits_type = typename policy_T::traits_type;
      using  value_type = typename policy_T::value_type;

      static constexpr size_type l = traits_type::Size - 1;

      template<typename derived_T>
      static constexpr void run(value_type *dest, const ExprBase<traits_type,derived_T>& src)
      {
        constexpr size_type i = policy_type::template row<l>();
        constexpr size_type j = policy_type::template column<l>();

        dest[l] = src.as_derived().template eval<i,j>();
      }
    };

  } // namespace impl

} // namespace cs

#endif // ARRAYPOLICYIMPL_H
