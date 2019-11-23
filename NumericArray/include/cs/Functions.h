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

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

#include "cs/impl/BinaryOperatorsImpl.h"
#include "cs/impl/FunctionsImpl.h"

namespace cs {

  // Forward Declarations ////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename ARG>
  constexpr scalar_T length(const ExprBase<scalar_T,ROWS,1,ARG>& arg);

  // Cross Product ///////////////////////////////////////////////////////////

  template<typename scalar_T, typename ARG1, typename ARG2>
  constexpr impl::Cross<scalar_T,ARG1,ARG2> cross(
      const ExprBase<scalar_T,3,1,ARG1>& arg1,
      const ExprBase<scalar_T,3,1,ARG2>& arg2
      )
  {
    return impl::Cross<scalar_T,ARG1,ARG2>(arg1.as_derived(), arg2.as_derived());
  }

  // Direction ///////////////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename FROM, typename TO>
  constexpr impl::Normalize<scalar_T,ROWS,impl::BinSub<scalar_T,ROWS,1,TO,FROM>> direction(
      const ExprBase<scalar_T,ROWS,1,FROM>& from,
      const ExprBase<scalar_T,ROWS,1,TO>& to
      )
  {
    using SUB = impl::BinSub<scalar_T,ROWS,1,TO,FROM>;
    return impl::Normalize<scalar_T,ROWS,SUB>(SUB(to.as_derived(), from.as_derived()),
                                              cs::length(SUB(to.as_derived(), from.as_derived())));
  }

  // Distance ////////////////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename FROM, typename TO>
  constexpr scalar_T distance(
      const ExprBase<scalar_T,ROWS,1,FROM>& from,
      const ExprBase<scalar_T,ROWS,1,TO>& to
      )
  {
    using SUB = impl::BinSub<scalar_T,ROWS,1,TO,FROM>;
    return cs::length(SUB(to.as_derived(), from.as_derived()));
  }

  // Dot Product /////////////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename ARG1, typename ARG2>
  constexpr scalar_T dot(
      const ExprBase<scalar_T,ROWS,1,ARG1>& arg1,
      const ExprBase<scalar_T,ROWS,1,ARG2>& arg2
      )
  {
    using TRANSPOSE = impl::Transpose<scalar_T,1,ROWS,ARG1>;
    using       MUL = impl::BinMul<scalar_T,1,ROWS,1,TRANSPOSE,ARG2>;
    return MUL(arg1.as_derived(), arg2.as_derived()).template eval<0,0>();
  }

  // Length //////////////////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename ARG>
  constexpr scalar_T length(
      const ExprBase<scalar_T,ROWS,1,ARG>& arg
      )
  {
    return std::sqrt(dot(arg, arg));
  }

  // Vector Normalization ////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, typename ARG>
  constexpr impl::Normalize<scalar_T,ROWS,ARG> normalize(
      const ExprBase<scalar_T,ROWS,1,ARG>& arg
      )
  {
    return impl::Normalize<scalar_T,ROWS,ARG>(arg.as_derived(),
                                              cs::length(arg.as_derived()));
  }

  // Matrix Transposition ////////////////////////////////////////////////////

  template<typename scalar_T, dim_T ROWS, dim_T COLS, typename ARG>
  constexpr impl::Transpose<scalar_T,COLS,ROWS,ARG> transpose(
      const ExprBase<scalar_T,ROWS,COLS,ARG>& arg
      )
  {
    return impl::Transpose<scalar_T,COLS,ROWS,ARG>(arg.as_derived());
  }

} // namespace cs

#endif // FUNCTIONS_H
