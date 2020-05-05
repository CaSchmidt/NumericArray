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
#include <cs/TypeTraits.h>

namespace cs {

  namespace impl {

    // Implementation - 3x3 Cofactor Matrix //////////////////////////////////

    template<typename traits_T, typename ARG>
    class Cofactor3x3 : public ExprBase<traits_T,Cofactor3x3<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,Cofactor3x3<traits_T,ARG>>::value_type;

      Cofactor3x3(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Cofactor3x3() noexcept = default;

      constexpr if_dimensions_t<traits_type,3,3,value_type> determinant() const
      {
        return
            _arg.template eval<0,0>()*eval<0,0>() +
            _arg.template eval<0,1>()*eval<0,1>() +
            _arg.template eval<0,2>()*eval<0,2>();
      }

      template<size_type i, size_type j>
      constexpr if_dimensions_t<traits_type,3,3,value_type> eval() const
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

      Cross(const ARG1& arg1, const ARG2& arg2) noexcept
        : _arg1(arg1)
        , _arg2(arg2)
      {
      }

      ~Cross() noexcept = default;

      template<size_type i, size_type /*j*/>
      constexpr if_dimensions_t<traits_type,3,1,value_type> eval() const
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

    // Implementation - Vector Normalization /////////////////////////////////

    template<typename traits_T, typename ARG>
    class Normalize : public ExprBase<traits_T,Normalize<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Normalize<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Normalize<traits_T,ARG>>::traits_type;
      using typename ExprBase<traits_T,Normalize<traits_T,ARG>>::value_type;

      Normalize(const ARG& arg, const value_type length)
        : _arg(arg)
        , _length{length}
      {
      }

      ~Normalize() noexcept = default;

      template<size_type i, size_type j>
      constexpr if_column_t<traits_type,value_type> eval() const
      {
        return _arg.template eval<i,j>()/_length;
      }

    private:
      const ARG&       _arg;
      const value_type _length{};
    };

    // Implementation - Matrix/Vector Transposition //////////////////////////

    template<typename traits_T, typename ARG>
    class Transpose : public ExprBase<traits_T,Transpose<traits_T,ARG>> {
    public:
      using typename ExprBase<traits_T,Transpose<traits_T,ARG>>::size_type;
      using typename ExprBase<traits_T,Transpose<traits_T,ARG>>::value_type;

      Transpose(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Transpose() noexcept = default;

      template<size_type i, size_type j>
      constexpr value_type eval() const
      {
        return _arg.template eval<j,i>();
      }

    private:
      const ARG& _arg;
    };

  } // namespace impl

} // namespace cs

#endif // FUNCTIONSIMPL_H
