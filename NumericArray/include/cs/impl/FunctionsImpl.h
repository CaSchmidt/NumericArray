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

#ifndef FUNCTIONSIMPL_H
#define FUNCTIONSIMPL_H

#include <cs/impl/IndexingImpl.h>
#include <cs/ExprBase.h>
#include <cs/Math.h>
#include <cs/Meta.h>
#include <cs/SIMD.h>

namespace cs {

  namespace impl {

    // Implementation - Cast /////////////////////////////////////////////////

    template<typename traits_T, typename ARG>
    class Cast : public ExprBase<traits_T,Cast<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Cast<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Cast<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,Cast<traits_T,ARG>>::value_type;

      static_assert(if_identical_v<traits_type,typename ARG::traits_type>);

      Cast(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Cast() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _arg.template eval<i,j>();
      }

      template<typename simd_policy_T, bool check_policy>
      static constexpr bool is_simd()
      {
        return check_simd<ARG,simd_policy_T,check_policy>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        return _arg.block(b);
      }

    private:
      const ARG& _arg;
    };

    // Implementation - Clamp ////////////////////////////////////////////////

    template<typename traits_T, typename ARG>
    class SClamp : public ExprBase<traits_T,SClamp<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,SClamp<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,SClamp<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,SClamp<traits_T,ARG>>::value_type;

      SClamp(const ARG& arg, const value_type lo, const value_type hi) noexcept
        : _arg(arg)
        , _lo{lo}
        , _hi{hi}
      {
      }

      ~SClamp() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return csClamp(_arg.template eval<i,j>(), _lo, _hi);
      }

      template<typename simd_policy_T, bool check_policy>
      static constexpr bool is_simd()
      {
        return check_simd<ARG,simd_policy_T,check_policy>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        using simd = SIMD<value_type>;
        return simd::max(simd::set(_lo), simd::min(_arg.block(b), simd::set(_hi)));
      }

    private:
      const ARG& _arg;
      const value_type _lo{}, _hi{};
    };

    // Implementation - 3x3 Cofactor Matrix //////////////////////////////////

    template<typename traits_T, typename ARG>
    class Cofactor3x3 : public ExprBase<traits_T,Cofactor3x3<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::value_type;

      static_assert(if_dimensions_v<traits_type,3,3>);

      Cofactor3x3(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Cofactor3x3() noexcept = default;

      inline value_type determinant() const
      {
        return
            _arg.template eval<0,0>()*eval<0,0>() +
            _arg.template eval<0,1>()*eval<0,1>() +
            _arg.template eval<0,2>()*eval<0,2>();
      }

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return sign<i,j>()*(
              _arg.template eval<AI<i>::j,AI<j>::j>()*
              _arg.template eval<AI<i>::k,AI<j>::k>() -
              _arg.template eval<AI<i>::k,AI<j>::j>()*
              _arg.template eval<AI<i>::j,AI<j>::k>()
              );
      }

    private:
      template<size_type i>
      using AI = AdjointIndex3x3<size_type,i>;

      static constexpr size_type bitZERO = 0;
      static constexpr size_type  bitONE = 1;

      static constexpr value_type  PLUS =  1;
      static constexpr value_type MINUS = -1;

      template<size_type i, size_type j>
      constexpr value_type sign() const
      {
        return ((i ^ j) & bitONE) != bitZERO
            ? MINUS
            :  PLUS;
      }

      const ARG& _arg;
    };

    // Implementation - Vector Cross Product /////////////////////////////////

    template<typename traits_T, typename ARG1, typename ARG2>
    class Cross : public ExprBase<traits_T,Cross<traits_T,ARG1,ARG2>> {
    public:
      using typename ExprBase<traits_T,Cross<traits_T,ARG1,ARG2>>::size_type;
      using typename ExprBase<traits_T,Cross<traits_T,ARG1,ARG2>>::traits_type;
      using typename ExprBase<traits_T,Cross<traits_T,ARG1,ARG2>>::value_type;

      static_assert(if_dimensions_v<traits_type,3,1>);

      Cross(const ARG1& arg1, const ARG2& arg2) noexcept
        : _arg1(arg1)
        , _arg2(arg2)
      {
      }

      ~Cross() noexcept = default;

      template<size_type i, size_type /*j*/>
      inline value_type eval() const
      {
        return
            _arg1.template eval<NI<i>::j,0>()*_arg2.template eval<NI<i>::k,0>() -
            _arg1.template eval<NI<i>::k,0>()*_arg2.template eval<NI<i>::j,0>();
      }

    private:
      template<size_type i>
      using NI = NextIndex<size_type,i,3>;

      const ARG1& _arg1;
      const ARG2& _arg2;
    };

    // Implementation - Dot Product //////////////////////////////////////////

    template<typename traits_T, typename ARG1, typename ARG2>
    struct DotProduct {
      using value_type = typename traits_T::value_type;

      template<std::size_t i>
      inline static value_type eval(const ARG1& arg1, const ARG2& arg2)
      {
        return arg1.template eval<i,0>()*arg2.template eval<i,0>();
      }
    };

    template<typename traits_T, typename ARG1, typename ARG2>
    struct DotProductSIMD {
      using value_type = typename traits_T::value_type;
      using  simd      = SIMD<value_type>;
      using  simd_type = typename simd::simd_type;

      template<std::size_t b>
      inline static void eval(simd_type& x, const ARG1& arg1, const ARG2& arg2)
      {
        x = simd::add(x, simd::mul(arg1.block(b), arg2.block(b)));
      }
    };

    template<typename traits_T, typename traits_T::size_type INNER, typename ARG1, typename ARG2>
    class Dot : public ExprBase<traits_T,Dot<traits_T,INNER,ARG1,ARG2>> {
    public:
      using typename ExprBase<traits_T,Dot<traits_T,INNER,ARG1,ARG2>>::size_type;
      using typename ExprBase<traits_T,Dot<traits_T,INNER,ARG1,ARG2>>::traits_type;
      using typename ExprBase<traits_T,Dot<traits_T,INNER,ARG1,ARG2>>::value_type;

      static_assert(if_dimensions_v<traits_type,1,1>);

      Dot(const ARG1& arg1, const ARG2& arg2) noexcept
        : _arg1(arg1)
        , _arg2(arg2)
      {
      }

      ~Dot() noexcept = default;

      template<size_type /*i*/, size_type /*j*/>
      inline value_type eval() const
      {
        struct NoPolicy { };
        if constexpr( check_simd<ARG1,NoPolicy,false>()  &&  check_simd<ARG2,NoPolicy,false>() ) {
          using PROD      = DotProductSIMD<traits_type,ARG1,ARG2>;
          using simd      = SIMD<value_type>;
          using simd_type = typename simd::simd_type;

          simd_type x = simd::zero();
          meta::for_each<simd::blocks(INNER),PROD>(x, _arg1, _arg2);
          x = simd::hadd(x);

          return simd::scalar(x);
        }
        using PROD = DotProduct<traits_type,ARG1,ARG2>;
        return meta::accumulate<value_type,INNER,PROD>(_arg1, _arg2);
      }

    private:
      const ARG1& _arg1;
      const ARG2& _arg2;
    };

    // Implementation - Maximum //////////////////////////////////////////////

    template<typename traits_T, typename ARG>
    class SMax : public ExprBase<traits_T,SMax<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,SMax<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,SMax<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,SMax<traits_T,ARG>>::value_type;

      SMax(const ARG& arg, const value_type scalar) noexcept
        : _arg(arg)
        , _scalar(scalar)
      {
      }

      ~SMax() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return csMax(_arg.template eval<i,j>(), _scalar);
      }

      template<typename simd_policy_T, bool check_policy>
      static constexpr bool is_simd()
      {
        return check_simd<ARG,simd_policy_T,check_policy>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        using simd = SIMD<value_type>;
        return simd::max(_arg.block(b), simd::set(_scalar));
      }

    private:
      const ARG& _arg;
      const value_type _scalar{};
    };

    // Implementation - Minimum //////////////////////////////////////////////

    template<typename traits_T, typename ARG>
    class SMin : public ExprBase<traits_T,SMin<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,SMin<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,SMin<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,SMin<traits_T,ARG>>::value_type;

      SMin(const ARG& arg, const value_type scalar) noexcept
        : _arg(arg)
        , _scalar(scalar)
      {
      }

      ~SMin() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return csMin(_arg.template eval<i,j>(), _scalar);
      }

      template<typename simd_policy_T, bool check_policy>
      static constexpr bool is_simd()
      {
        return check_simd<ARG,simd_policy_T,check_policy>();
      }

      inline simd_type<value_type> block(const size_type b) const
      {
        using simd = SIMD<value_type>;
        return simd::min(_arg.block(b), simd::set(_scalar));
      }

    private:
      const ARG& _arg;
      const value_type _scalar{};
    };

    // Implementation - Matrix/Vector Transposition //////////////////////////

    template<typename traits_T, typename ARG>
    class Transpose : public ExprBase<traits_T,Transpose<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Transpose<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Transpose<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,Transpose<traits_T,ARG>>::value_type;

      Transpose(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Transpose() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        return _arg.template eval<j,i>();
      }

    private:
      const ARG& _arg;
    };

  } // namespace impl

} // namespace cs

#endif // FUNCTIONSIMPL_H
