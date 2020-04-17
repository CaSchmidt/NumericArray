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

#ifndef BINARYOPERATORSIMPL_H
#define BINARYOPERATORSIMPL_H

#include <cs/ExprBase.h>

namespace cs {

  namespace impl {

    // Implementation - Addition /////////////////////////////////////////////

    template<typename scalar_T, dim_T ROWS, dim_T COLS, typename LHS, typename RHS>
    class BinAdd
        : public ExprBase<scalar_T,ROWS,COLS,BinAdd<scalar_T,ROWS,COLS,LHS,RHS>> {
    public:
      BinAdd(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs{lhs}
        , _rhs{rhs}
      {
      }

      ~BinAdd() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _lhs.template eval<i,j>() + _rhs.template eval<i,j>();
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    // Implementation - Scalar Division //////////////////////////////////////

    template<typename scalar_T, dim_T ROWS, dim_T COLS, typename OP>
    class BinSDiv
        : public ExprBase<scalar_T,ROWS,COLS,BinSDiv<scalar_T,ROWS,COLS,OP>> {
    public:
      BinSDiv(const OP& op, const scalar_T scalar) noexcept
        : _op(op)
        , _scalar{scalar}
      {
      }

      ~BinSDiv() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _op.template eval<i,j>()/_scalar;
      }

    private:
      const OP& _op;
      scalar_T _scalar;
    };

    // Implementation - Multiplication ///////////////////////////////////////

    template<typename scalar_T, dim_T I, dim_T J, dim_T k, dim_T INNER, typename LHS, typename RHS>
    struct BinMulProduct {
      static constexpr dim_T K = INNER - 1 - k;

      static constexpr scalar_T run(const LHS& lhs, const RHS& rhs)
      {
        return
            lhs.template eval<I,K>()*rhs.template eval<K,J>() +
            BinMulProduct<scalar_T,I,J,k-1,INNER,LHS,RHS>::run(lhs, rhs);
      }
    };

    template<typename scalar_T, dim_T I, dim_T J, dim_T INNER, typename LHS, typename RHS>
    struct BinMulProduct<scalar_T,I,J,0,INNER,LHS,RHS> {
      static constexpr dim_T K = INNER - 1;

      static constexpr scalar_T run(const LHS& lhs, const RHS& rhs)
      {
        return lhs.template eval<I,K>()*rhs.template eval<K,J>();
      }
    };

    template<typename scalar_T, dim_T ROWS, dim_T INNER, dim_T COLS, typename LHS, typename RHS>
    class BinMul
        : public ExprBase<scalar_T,ROWS,COLS,BinMul<scalar_T,ROWS,INNER,COLS,LHS,RHS>> {
    public:
      BinMul(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      ~BinMul() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return BinMulProduct<scalar_T,i,j,INNER-1,INNER,LHS,RHS>::run(_lhs, _rhs);
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    // Implementation - Scalar Multiplication ////////////////////////////////

    template<typename scalar_T, dim_T ROWS, dim_T COLS, typename OP>
    class BinSMul
        : public ExprBase<scalar_T,ROWS,COLS,BinSMul<scalar_T,ROWS,COLS,OP>> {
    public:
      BinSMul(const OP& op, const scalar_T scalar) noexcept
        : _op(op)
        , _scalar{scalar}
      {
      }

      ~BinSMul() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _op.template eval<i,j>()*_scalar;
      }

    private:
      const OP& _op;
      const scalar_T _scalar;
    };

    // Implementation - Subtraction //////////////////////////////////////////

    template<typename scalar_T, dim_T ROWS, dim_T COLS, typename LHS, typename RHS>
    class BinSub
        : public ExprBase<scalar_T,ROWS,COLS,BinSub<scalar_T,ROWS,COLS,LHS,RHS>>
    {
    public:
      BinSub(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      ~BinSub() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _lhs.template eval<i,j>() - _rhs.template eval<i,j>();
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

  } // namespace impl

} // namespace cs

#endif // BINARYOPERATORSIMPL_H
