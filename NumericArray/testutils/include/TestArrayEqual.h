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

#ifndef TESTARRAYEQUAL_H
#define TESTARRAYEQUAL_H

#include <cs/NumericArray.h>

#include "TestEquals.h"

template<typename array_T>
inline bool equals(const array_T& A,
                   const std::initializer_list<typename array_T::value_type>& list,
                   const typename array_T::value_type& epsilon0 = Konst<typename array_T::value_type>::epsilon0)
{
  using size_type = typename array_T::size_type;
  if( static_cast<std::size_t>(A.size()) != list.size() ) {
    return false;
  }
  for(std::size_t index = 0; index < list.size(); index++) {
    const size_type i = array_T::policy_type::row(static_cast<size_type>(index));
    const size_type j = array_T::policy_type::column(static_cast<size_type>(index));
    if( !equals(A(i, j), list.begin()[index], epsilon0) ) {
      return false;
    }
  }
  return true;
}

template<typename array_T>
constexpr bool equals0(const array_T& A,
                       const std::initializer_list<typename array_T::value_type>& list)
{
  return equals(A, list, Konst<typename array_T::value_type>::ZERO);
}

#endif // TESTARRAYEQUAL_H
