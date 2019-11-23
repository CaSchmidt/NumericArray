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

#include "cs/impl/Indexing.h"
#include "cs/ExprBase.h"

namespace cs {

  namespace impl {

    // Implementation - Vector Cross Product /////////////////////////////////

    template<typename scalar_T, typename ARG1, typename ARG2>
    class Cross
        : public ExprBase<scalar_T,3,1,Cross<scalar_T,ARG1,ARG2>> {
    public:
      Cross(const ARG1& arg1, const ARG2& arg2) noexcept
        : _arg1(arg1)
        , _arg2(arg2)
      {
      }

      ~Cross() noexcept = default;

      template<dim_T i, dim_T /*j*/>
      constexpr scalar_T eval() const
      {
        return
            _arg1.template eval<CI3<i>::J,0>()*_arg2.template eval<CI3<i>::K,0>() -
            _arg1.template eval<CI3<i>::K,0>()*_arg2.template eval<CI3<i>::J,0>();
      }

    private:
      const ARG1& _arg1;
      const ARG2& _arg2;
    };

    // Implementation - Vector Normalization /////////////////////////////////

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

    // Implementation - Matrix/Vector Transposition //////////////////////////

    template<typename scalar_T, dim_T ROWS, dim_T COLS, typename ARG>
    class Transpose
        : public ExprBase<scalar_T,ROWS,COLS,Transpose<scalar_T,ROWS,COLS,ARG>> {
    public:
      Transpose(const ARG& arg) noexcept
        : _arg(arg)
      {
      }

      ~Transpose() noexcept = default;

      template<dim_T i, dim_T j>
      constexpr scalar_T eval() const
      {
        return _arg.template eval<j,i>();
      }

    private:
      const ARG& _arg;
    };

  } // namespace impl

} // namespace cs

#endif // FUNCTIONSIMPL_H
