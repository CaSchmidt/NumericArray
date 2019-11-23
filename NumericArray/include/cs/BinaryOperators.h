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

#ifndef BINARYOPERATORS_H
#define BINARYOPERATORS_H

#include "cs/impl/BinaryOperatorsImpl.h"

namespace cs {

  template<typename scalar_T, dim_T ROWS, dim_T COLS, typename LHS, typename RHS>
  constexpr impl::BinAdd<scalar_T,ROWS,COLS,LHS,RHS> operator+(
      const ExprBase<scalar_T,ROWS,COLS,LHS>& lhs,
      const ExprBase<scalar_T,ROWS,COLS,RHS>& rhs
      )
  {
    return impl::BinAdd<scalar_T,ROWS,COLS,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename scalar_T, dim_T ROWS, dim_T COLS, typename LHS, typename RHS>
  constexpr impl::BinSub<scalar_T,ROWS,COLS,LHS,RHS> operator-(
      const ExprBase<scalar_T,ROWS,COLS,LHS>& lhs,
      const ExprBase<scalar_T,ROWS,COLS,RHS>& rhs
      )
  {
    return impl::BinSub<scalar_T,ROWS,COLS,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename scalar_T, dim_T ROWS, dim_T INNER, dim_T COLS, typename LHS, typename RHS>
  constexpr impl::BinMul<scalar_T,ROWS,INNER,COLS,LHS,RHS> operator*(
      const ExprBase<scalar_T,ROWS,INNER,LHS>& lhs,
      const ExprBase<scalar_T,INNER,COLS,RHS>& rhs
      )
  {
    return impl::BinMul<scalar_T,ROWS,INNER,COLS,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

} // namespace cs

#endif // BINARYOPERATORS_H
