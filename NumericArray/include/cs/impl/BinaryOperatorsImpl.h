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
#include <cs/Meta.h>
#include <cs/SIMD.h>

namespace cs {

  namespace impl {

    // Implementation - Addition /////////////////////////////////////////////

    template<typename traits_T, typename LHS, typename RHS>
    class BinAdd
        : public ExprBase<traits_T,BinAdd<traits_T,LHS,RHS>> {
    public:
      using typename ExprBase<traits_T,BinAdd<traits_T,LHS,RHS>>::size_type;
      using typename ExprBase<traits_T,BinAdd<traits_T,LHS,RHS>>::traits_type;
      using typename ExprBase<traits_T,BinAdd<traits_T,LHS,RHS>>::value_type;

      BinAdd(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs{lhs}
        , _rhs{rhs}
      {
      }

      ~BinAdd() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _lhs.template eval<i,j>() + _rhs.template eval<i,j>();
      }

      template<typename simd_policy_T>
      static constexpr bool is_simd()
      {
        return check_simd<LHS,simd_policy_T>()  &&  check_simd<RHS,simd_policy_T>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        return SIMD<value_type>::add(_lhs.block(b), _rhs.block(b));
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    // Implementation - Scalar Division //////////////////////////////////////

    template<typename traits_T, typename OP>
    class BinSDiv
        : public ExprBase<traits_T,BinSDiv<traits_T,OP>> {
    public:
      using typename ExprBase<traits_T,BinSDiv<traits_T,OP>>::size_type;
      using typename ExprBase<traits_T,BinSDiv<traits_T,OP>>::traits_type;
      using typename ExprBase<traits_T,BinSDiv<traits_T,OP>>::value_type;

      BinSDiv(const OP& op, const value_type scalar) noexcept
        : _op(op)
        , _scalar{scalar}
      {
      }

      ~BinSDiv() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _op.template eval<i,j>()/_scalar;
      }

      template<typename simd_policy_T>
      static constexpr bool is_simd()
      {
        return check_simd<OP,simd_policy_T>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        using simd = SIMD<value_type>;
        return simd::div(_op.block(b), simd::set(_scalar));
      }

    private:
      const OP& _op;
      value_type _scalar;
    };

    // Implementation - Multiplication ///////////////////////////////////////

    template<typename traits_T, std::size_t I, std::size_t J, typename LHS, typename RHS>
    struct BinMulProduct {
      using value_type = typename traits_T::value_type;

      template<std::size_t K>
      inline static value_type eval(const LHS& lhs, const RHS& rhs)
      {
        return lhs.template eval<I,K>()*rhs.template eval<K,J>();
      }
    };

    template<typename traits_T, typename traits_T::size_type INNER, typename LHS, typename RHS>
    class BinMul
        : public ExprBase<traits_T,BinMul<traits_T,INNER,LHS,RHS>> {
    public:
      using typename ExprBase<traits_T,BinMul<traits_T,INNER,LHS,RHS>>::size_type;
      using typename ExprBase<traits_T,BinMul<traits_T,INNER,LHS,RHS>>::traits_type;
      using typename ExprBase<traits_T,BinMul<traits_T,INNER,LHS,RHS>>::value_type;

      BinMul(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      ~BinMul() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        using PROD = BinMulProduct<traits_type,i,j,LHS,RHS>;
        return meta::accumulate<value_type,INNER,PROD>(_lhs, _rhs);
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    // Implementation - Scalar Multiplication ////////////////////////////////

    template<typename traits_T, typename OP>
    class BinSMul
        : public ExprBase<traits_T,BinSMul<traits_T,OP>> {
    public:
      using typename ExprBase<traits_T,BinSMul<traits_T,OP>>::size_type;
      using typename ExprBase<traits_T,BinSMul<traits_T,OP>>::traits_type;
      using typename ExprBase<traits_T,BinSMul<traits_T,OP>>::value_type;

      BinSMul(const OP& op, const value_type scalar) noexcept
        : _op(op)
        , _scalar{scalar}
      {
      }

      ~BinSMul() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _op.template eval<i,j>()*_scalar;
      }

      template<typename simd_policy_T>
      static constexpr bool is_simd()
      {
        return check_simd<OP,simd_policy_T>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        using simd = SIMD<value_type>;
        return simd::mul(_op.block(b), simd::set(_scalar));
      }

    private:
      const OP& _op;
      const value_type _scalar;
    };

    // Implementation - Element-Wise Product /////////////////////////////////

    template<typename traits_T, typename LHS, typename RHS>
    class BinProduct
        : public ExprBase<traits_T,BinProduct<traits_T,LHS,RHS>> {
    public:
      using typename ExprBase<traits_T,BinProduct<traits_T,LHS,RHS>>::size_type;
      using typename ExprBase<traits_T,BinProduct<traits_T,LHS,RHS>>::traits_type;
      using typename ExprBase<traits_T,BinProduct<traits_T,LHS,RHS>>::value_type;

      BinProduct(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      ~BinProduct() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _lhs.template eval<i,j>()*_rhs.template eval<i,j>();
      }

      template<typename simd_policy_T>
      static constexpr bool is_simd()
      {
        return check_simd<LHS,simd_policy_T>()  &&  check_simd<RHS,simd_policy_T>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        return SIMD<value_type>::mul(_lhs.block(b), _rhs.block(b));
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    // Implementation - Subtraction //////////////////////////////////////////

    template<typename traits_T, typename LHS, typename RHS>
    class BinSub
        : public ExprBase<traits_T,BinSub<traits_T,LHS,RHS>> {
    public:
      using typename ExprBase<traits_T,BinSub<traits_T,LHS,RHS>>::size_type;
      using typename ExprBase<traits_T,BinSub<traits_T,LHS,RHS>>::traits_type;
      using typename ExprBase<traits_T,BinSub<traits_T,LHS,RHS>>::value_type;

      BinSub(const LHS& lhs, const RHS& rhs) noexcept
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      ~BinSub() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _lhs.template eval<i,j>() - _rhs.template eval<i,j>();
      }

      template<typename simd_policy_T>
      static constexpr bool is_simd()
      {
        return check_simd<LHS,simd_policy_T>()  &&  check_simd<RHS,simd_policy_T>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        return SIMD<value_type>::sub(_lhs.block(b), _rhs.block(b));
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

  } // namespace impl

} // namespace cs

#endif // BINARYOPERATORSIMPL_H
