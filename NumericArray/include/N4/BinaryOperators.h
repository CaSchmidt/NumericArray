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

#ifndef N4_BINARYOPERATORS_H
#define N4_BINARYOPERATORS_H

#include <N4/ExprBase.h>
#include <N4/Matrix4f.h>
#include <N4/SIMD.h>

namespace n4 {

  ////// Implementation //////////////////////////////////////////////////////

  namespace impl {

    template<typename traits_T, typename LHS, typename RHS>
    class BinAdd : public ExprBase<traits_T,BinAdd<traits_T,LHS,RHS>> {
    public:
      BinAdd(const LHS& lhs, const RHS& rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::add(_lhs.eval(), _rhs.eval());
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    template<typename traits_T, typename LHS, typename RHS>
    class BinDiv : public ExprBase<traits_T,BinDiv<traits_T,LHS,RHS>> {
    public:
      BinDiv(const LHS& lhs, const RHS& rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::div(_lhs.eval(), _rhs.eval());
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    template<typename traits_T, typename LHS, typename RHS>
    class BinMul : public ExprBase<traits_T,BinMul<traits_T,LHS,RHS>> {
    public:
      BinMul(const LHS& lhs, const RHS& rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::mul(_lhs.eval(), _rhs.eval());
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

    template<typename traits_T, typename LHS>
    class BinSDiv : public ExprBase<traits_T,BinSDiv<traits_T,LHS>> {
    public:
      BinSDiv(const LHS& lhs, const real_t rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::div(_lhs.eval(), simd::set(_rhs));
      }

    private:
      const LHS&   _lhs;
      const real_t _rhs;
    };

    template<typename traits_T, typename LHS>
    class BinSMul : public ExprBase<traits_T,BinSMul<traits_T,LHS>> {
    public:
      BinSMul(const LHS& lhs, const real_t rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::mul(_lhs.eval(), simd::set(_rhs));
      }

    private:
      const LHS&   _lhs;
      const real_t _rhs;
    };

    template<typename traits_T, typename LHS, typename RHS>
    class BinSub : public ExprBase<traits_T,BinSub<traits_T,LHS,RHS>> {
    public:
      BinSub(const LHS& lhs, const RHS& rhs)
        : _lhs(lhs)
        , _rhs(rhs)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::sub(_lhs.eval(), _rhs.eval());
      }

    private:
      const LHS& _lhs;
      const RHS& _rhs;
    };

  } // namespace impl

  ////// User Interface //////////////////////////////////////////////////////

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

  template<typename traits_T, typename LHS, typename RHS>
  inline auto operator*(const ExprBase<traits_T,LHS>& lhs, const ExprBase<traits_T,RHS>& rhs)
  {
    return impl::BinMul<traits_T,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename traits_T, typename LHS>
  inline auto operator*(const ExprBase<traits_T,LHS>& lhs, const real_t rhs)
  {
    return impl::BinSMul<traits_T,LHS>(lhs.as_derived(), rhs);
  }

  template<typename traits_T, typename RHS>
  inline auto operator*(const real_t lhs, const ExprBase<traits_T,RHS>& rhs)
  {
    return impl::BinSMul<traits_T,RHS>(rhs.as_derived(), lhs);
  }

  template<typename traits_T, typename LHS, typename RHS>
  inline auto operator/(const ExprBase<traits_T,LHS>& lhs, const ExprBase<traits_T,RHS>& rhs)
  {
    return impl::BinDiv<traits_T,LHS,RHS>(lhs.as_derived(), rhs.as_derived());
  }

  template<typename traits_T, typename LHS>
  inline auto operator/(const ExprBase<traits_T,LHS>& lhs, const real_t rhs)
  {
    return impl::BinSDiv<traits_T,LHS>(lhs.as_derived(), rhs);
  }

} // namespace n4

#endif // N4_BINARYOPERATORS_H