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

#ifndef UNARYOPERATORSIMPL_H
#define UNARYOPERATORSIMPL_H

#include <cs/ExprBase.h>
#include <cs/SIMD.h>

namespace cs {

  namespace impl {

    // Implementation - Unary Minus //////////////////////////////////////////

    template<typename traits_T, typename OP>
    class UnaMinus
        : public ExprBase<traits_T,UnaMinus<traits_T,OP>>
    {
    public:
      using typename ExprBase<traits_T,UnaMinus<traits_T,OP>>::size_type;
      using typename ExprBase<traits_T,UnaMinus<traits_T,OP>>::traits_type;
      using typename ExprBase<traits_T,UnaMinus<traits_T,OP>>::value_type;

      UnaMinus(const OP& op) noexcept
        : _op(op)
      {
      }

      ~UnaMinus() noexcept = default;

      template<size_type i, size_type j>
      constexpr value_type eval() const
      {
        return -_op.template eval<i,j>();
      }

      static inline constexpr bool is_simd = check_simd<OP>();

      constexpr simd_type<value_type> block(const size_type b) const
      {
        constexpr value_type mONE = static_cast<value_type>(-1);
        using                simd = SIMD<value_type>;
        return simd::mul(simd::set(mONE), _op.block(b));
      }

    private:
      const OP& _op;
    };

    // Implementation - Unary Plus ///////////////////////////////////////////

    template<typename traits_T, typename OP>
    class UnaPlus
        : public ExprBase<traits_T,UnaPlus<traits_T,OP>>
    {
    public:
      using typename ExprBase<traits_T,UnaPlus<traits_T,OP>>::size_type;
      using typename ExprBase<traits_T,UnaPlus<traits_T,OP>>::traits_type;
      using typename ExprBase<traits_T,UnaPlus<traits_T,OP>>::value_type;

      UnaPlus(const OP& op) noexcept
        : _op(op)
      {
      }

      ~UnaPlus() noexcept = default;

      template<size_type i, size_type j>
      constexpr value_type eval() const
      {
        return _op.template eval<i,j>();
      }

      static inline constexpr bool is_simd = check_simd<OP>();

      constexpr simd_type<value_type> block(const size_type b) const
      {
        return _op.block(b);
      }

    private:
      const OP& _op;
    };

  } // namespace impl

} // namespace cs

#endif // UNARYOPERATORSIMPL_H
