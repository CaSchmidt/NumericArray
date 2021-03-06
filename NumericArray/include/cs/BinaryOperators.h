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

#include <cs/impl/BinaryOperatorsImpl.h>

namespace cs {

  template<typename traits_T, typename LHS, typename RHS>
  inline auto operator+(const ExprBase<traits_T,LHS>& lhs, const ExprBase<traits_T,RHS>& rhs)
  {
    return impl::BinAdd<traits_T,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename traits_T, typename LHS, typename RHS>
  inline auto operator-(const ExprBase<traits_T,LHS>& lhs, const ExprBase<traits_T,RHS>& rhs)
  {
    return impl::BinSub<traits_T,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename value_T, std::size_t ROWS, std::size_t INNER, std::size_t COLS,
           template<typename v_T, std::size_t, std::size_t> typename traits_T,
           typename LHS, typename RHS>
  inline auto operator*(const ExprBase<traits_T<value_T,ROWS,INNER>,LHS>& lhs,
                        const ExprBase<traits_T<value_T,INNER,COLS>,RHS>& rhs)
  {
    return impl::BinMul<traits_T<value_T,ROWS,COLS>,INNER,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename traits_T, typename OP>
  inline auto operator*(const ExprBase<traits_T,OP>& op,
                        const typename traits_T::value_type scalar)
  {
    return impl::BinSMul<traits_T,OP>(op.as_derived(), scalar);
  }

  template<typename traits_T, typename OP>
  inline auto operator*(const typename traits_T::value_type scalar,
                        const ExprBase<traits_T,OP>& op)
  {
    return impl::BinSMul<traits_T,OP>(op.as_derived(), scalar);
  }

  template<typename traits_T, typename OP>
  inline auto operator/(const ExprBase<traits_T,OP>& op,
                        const typename traits_T::value_type scalar)
  {
    return impl::BinSDiv<traits_T,OP>(op.as_derived(), scalar);
  }

  template<typename traits_T, typename LHS, typename RHS>
  inline auto operator%(const ExprBase<traits_T,LHS>& a, const ExprBase<traits_T,RHS>& b)
  {
    return impl::BinProduct<traits_T,LHS,RHS>(a.as_derived(), b.as_derived());
  }

} // namespace cs

#endif // BINARYOPERATORS_H
