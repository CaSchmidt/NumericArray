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

#include <cs/impl/BinaryOperatorsImpl.h>
#include <cs/impl/FunctionsImpl.h>
#include <cs/Math.h>

namespace cs {

  // Forward Declarations ////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  constexpr typename traits_T::value_type length(const ExprBase<traits_T,ARG>& arg);

  // Cast ////////////////////////////////////////////////////////////////////

  template<typename to_T, typename from_T, typename ARG>
  constexpr auto array_cast(const ExprBase<from_T,ARG>& arg)
  {
    static_assert(if_identical_v<to_T,from_T>);
    return impl::Cast<to_T,ARG>(arg.as_derived());
  }

  // Cross Product ///////////////////////////////////////////////////////////

  template<typename traits_T, typename ARG1, typename ARG2>
  constexpr auto cross(const ExprBase<traits_T,ARG1>& arg1,
                       const ExprBase<traits_T,ARG2>& arg2)
  {
    static_assert(if_dimensions_v<traits_T,3,1>);
    return impl::Cross<traits_T,ARG1,ARG2>(arg1.as_derived(), arg2.as_derived());
  }

  // Determinant /////////////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  constexpr typename traits_T::value_type determinant(const ExprBase<traits_T,ARG>& arg)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    using COFACTOR = impl::Cofactor3x3<traits_T,ARG>;
    return COFACTOR(arg.as_derived()).determinant();
  }

  // Direction ///////////////////////////////////////////////////////////////

  template<typename traits_T, typename FROM, typename TO>
  constexpr auto direction(const ExprBase<traits_T,FROM>& from,
                           const ExprBase<traits_T,TO>& to)
  {
    static_assert(if_column_v<traits_T>);
    using SUB = impl::BinSub<traits_T,TO,FROM>;
    return impl::Normalize<traits_T,SUB>(SUB(to.as_derived(), from.as_derived()),
                                         length(SUB(to.as_derived(), from.as_derived())));
  }

  // Distance ////////////////////////////////////////////////////////////////

  template<typename traits_T, typename FROM, typename TO>
  constexpr typename traits_T::value_type distance(const ExprBase<traits_T,FROM>& from,
                                                   const ExprBase<traits_T,TO>& to)
  {
    static_assert(if_column_v<traits_T>);
    using SUB = impl::BinSub<traits_T,TO,FROM>;
    return length(SUB(to.as_derived(), from.as_derived()));
  }

  // Dot Product /////////////////////////////////////////////////////////////

  template<typename value_T, typename size_T, size_T ROWS,
           template<typename v_T, typename s_T, s_T, s_T> typename traits_T,
           typename ARG1, typename ARG2>
  constexpr value_T dot(const ExprBase<traits_T<value_T,size_T,ROWS,1>,ARG1>& arg1,
                        const ExprBase<traits_T<value_T,size_T,ROWS,1>,ARG2>& arg2)
  {
    using TRANSPOSE = impl::Transpose<traits_T<value_T,size_T,1,ROWS>,ARG1>;
    using       MUL = impl::BinMul<traits_T<value_T,size_T,1,1>,ROWS,TRANSPOSE,ARG2>;
    return MUL(arg1.as_derived(), arg2.as_derived()).as_scalar();
  }

  template<typename traits_T, typename ARG1, typename ARG2>
  constexpr typename traits_T::value_type dot1(const ExprBase<traits_T,ARG1>& arg1,
                                               const ExprBase<traits_T,ARG2>& arg2)
  {
    static_assert(if_column_v<traits_T>);
    return csMax(typename traits_T::value_type{0}, dot(arg1, arg2));
  }

  // Inverse /////////////////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  constexpr auto inverse(const ExprBase<traits_T,ARG>& arg)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    using  COFACTOR = impl::Cofactor3x3<traits_T,ARG>;
    using TRANSPOSE = impl::Transpose<traits_T,COFACTOR>;
    using      SDIV = impl::BinSDiv<traits_T,TRANSPOSE>;
    return SDIV(TRANSPOSE(COFACTOR(arg.as_derived())),
                COFACTOR(arg.as_derived()).determinant());
  }

  // Length //////////////////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  constexpr typename traits_T::value_type length(const ExprBase<traits_T,ARG>& arg)
  {
    static_assert(if_column_v<traits_T>);
    return csSqrt(dot(arg, arg));
  }

  // Vector Normalization ////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  constexpr auto normalize(const ExprBase<traits_T,ARG>& arg)
  {
    static_assert(if_column_v<traits_T>);
    return impl::Normalize<traits_T,ARG>(arg.as_derived(),
                                         length(arg.as_derived()));
  }

  // Vector/Matrix Transposition /////////////////////////////////////////////

  template<typename value_T, typename size_T, size_T ROWS, size_T COLS,
           template<typename v_T, typename s_T, s_T, s_T> typename traits_T,
           typename ARG>
  constexpr auto transpose(const ExprBase<traits_T<value_T,size_T,ROWS,COLS>,ARG>& arg)
  {
    return impl::Transpose<traits_T<value_T,size_T,COLS,ROWS>,ARG>(arg.as_derived());
  }

} // namespace cs

#endif // FUNCTIONS_H
