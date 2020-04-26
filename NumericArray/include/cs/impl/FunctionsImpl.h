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

#include <type_traits>

#include <cs/impl/Indexing.h>
#include <cs/ExprBase.h>

namespace cs {

  namespace impl {

    template<typename traits_T,
             typename traits_T::size_type ROWS, typename traits_T::size_type COLS,
             typename T>
    using if_size_t = std::enable_if_t<traits_T::Rows == ROWS  &&  traits_T::Columns == COLS,T>;

    template<typename traits_T,
             typename T>
    using if_column_t = std::enable_if_t<traits_T::Columns == 1,T>;

    // Implementation - 3x3 Cofactor Matrix //////////////////////////////////

    /*
    template<typename scalar_T, typename ARG>
    class Cofactor3x3
        : public ExprBase<scalar_T,3,3,Cofactor3x3<scalar_T,ARG>> {
    public:
      Cofactor3x3(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Cofactor3x3() noexcept = default;

      constexpr scalar_T determinant() const
      {
        return
            _arg.template eval<0,0>()*eval<0,0>() +
            _arg.template eval<0,1>()*eval<0,1>() +
            _arg.template eval<0,2>()*eval<0,2>();
      }

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return sign<i,j>()*(
              _arg.template eval<AI3<i>::J,AI3<j>::J>()*
              _arg.template eval<AI3<i>::K,AI3<j>::K>() -
              _arg.template eval<AI3<i>::K,AI3<j>::J>()*
              _arg.template eval<AI3<i>::J,AI3<j>::K>()
              );
      }

    private:
      static constexpr dim_T bitZERO = 0;
      static constexpr dim_T  bitONE = 1;

      static constexpr scalar_T  PLUS =  1;
      static constexpr scalar_T MINUS = -1;

      template<dim_T i, dim_T j>
      constexpr scalar_T sign() const
      {
        return ((i ^ j) & bitONE) != bitZERO
            ? MINUS
            :  PLUS;
      }

      const ARG& _arg;
    };
    */

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
      constexpr if_size_t<traits_type,3,1,value_type> eval() const
      {
        return
            _arg1.template eval<NI<i>::j,0>()*_arg2.template eval<NI<i>::k,0>() -
            _arg1.template eval<NI<i>::k,0>()*_arg2.template eval<NI<i>::j,0>();
      }

    private:
      template<size_type i>
      using NI = NI3<size_type,i>;

      const ARG1& _arg1;
      const ARG2& _arg2;
    };

    // Implementation - Vector Normalization /////////////////////////////////

    /*
    template<typename scalar_T, dim_T ROWS, typename ARG>
    class Normalize
        : public ExprBase<scalar_T,ROWS,1,Normalize<scalar_T,ROWS,ARG>> {
    public:
      Normalize(const ARG& arg, const scalar_T length)
        : _arg(arg)
        , _length{length}
      {
      }

      ~Normalize() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _arg.template eval<i,j>()/_length;
      }

    private:
      const ARG&     _arg;
      const scalar_T _length{};
    };
    */

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
