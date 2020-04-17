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

#include <cs/Array.h>

#include "TestEquals.h"

template<typename scalar_T, cs::dim_T ROWS, cs::dim_T COLS>
inline bool equals(const cs::Array<scalar_T,ROWS,COLS>& A,
                   const std::initializer_list<scalar_T>& list,
                   const scalar_T& epsilon0 = Konst<scalar_T>::epsilon0)
{
  if( static_cast<std::size_t>(A.size()) != list.size() ) {
    return false;
  }
  for(std::size_t index = 0; index < list.size(); index++) {
    const cs::dim_T i = static_cast<cs::dim_T>(index)/A.columns();
    const cs::dim_T j = static_cast<cs::dim_T>(index)%A.columns();
    if( !equals(A(i, j), list.begin()[index], epsilon0) ) {
      return false;
    }
  }
  return true;
}

template<typename scalar_T, cs::dim_T ROWS, cs::dim_T COLS>
constexpr bool equals0(const cs::Array<scalar_T,ROWS,COLS>& A,
                       const std::initializer_list<scalar_T>& list)
{
  return equals(A, list, Konst<scalar_T>::ZERO);
}

#endif // TESTARRAYEQUAL_H
