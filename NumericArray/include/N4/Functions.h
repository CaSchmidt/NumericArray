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

#ifndef N4_FUNCTIONS_H
#define N4_FUNCTIONS_H

#include <N4/ExprBase.h>
#include <N4/SIMD.h>

namespace n4 {

  ////// Implementation //////////////////////////////////////////////////////

  namespace impl {

    template<typename traits_T, typename ARG1, typename ARG2>
    class Cross : public ExprBase<traits_T,Cross<traits_T,ARG1,ARG2>> {
    public:
      Cross(const ARG1& arg1, const ARG2& arg2)
        : _arg1(arg1)
        , _arg2(arg2)
      {
      }

      inline simd::simd_t eval() const
      {
        return simd::cross(_arg1.eval(), _arg2.eval());
      }

    private:
      const ARG1& _arg1;
      const ARG2& _arg2;
    };

    template<typename traits_T, typename FROM, typename TO>
    class Direction : public ExprBase<traits_T,Direction<traits_T,FROM,TO>> {
    public:
      Direction(const FROM& from, const TO& to)
        : _from(from)
        , _to(to)
      {
      }

      inline simd::simd_t eval() const
      {
        const simd::simd_t x = simd::sub(_to.eval(), _from.eval());
        return simd::div(x, simd::sqrt(simd::dot(x, x)));
      }

    private:
      const FROM& _from;
      const TO& _to;
    };

    template<typename traits_T, typename ARG>
    class Normalized : public ExprBase<traits_T,Normalized<traits_T,ARG>> {
    public:
      Normalized(const ARG& arg)
        : _arg(arg)
      {
      }

      inline simd::simd_t eval() const
      {
        const simd::simd_t x = _arg.eval();
        return simd::div(x, simd::sqrt(simd::dot(x, x)));
      }

    private:
      const ARG& _arg;
    };

  } // namespace impl

  ////// User Interface //////////////////////////////////////////////////////

  template<typename traits_T, typename ARG1, typename ARG2>
  inline auto cross(const ExprBase<traits_T,ARG1>& arg1, const ExprBase<traits_T,ARG2>& arg2)
  {
    return impl::Cross<traits_T,ARG1,ARG2>(arg1.as_derived(), arg2.as_derived());
  }

  template<typename traits_T, typename FROM, typename TO>
  inline auto direction(const ExprBase<traits_T,FROM>& from, const ExprBase<traits_T,TO>& to)
  {
    return impl::Direction<traits_T,FROM,TO>(from.as_derived(), to.as_derived());
  }

  template<typename traits_T, typename FROM, typename TO>
  inline real_t distance(const ExprBase<traits_T,FROM>& from, const ExprBase<traits_T,TO>& to)
  {
    const simd::simd_t delta = simd::sub(to.as_derived().eval(), from.as_derived().eval());
    return simd::to_real(simd::sqrt(simd::dot(delta, delta)));
  }

  template<typename traits_T, typename ARG1, typename ARG2>
  inline real_t dot(const ExprBase<traits_T,ARG1>& arg1, const ExprBase<traits_T,ARG2>& arg2)
  {
    return simd::to_real(simd::dot(arg1.as_derived().eval(), arg2.as_derived().eval()));
  }

  template<typename traits_T, typename ARG>
  inline real_t length(const ExprBase<traits_T,ARG>& arg)
  {
    const simd::simd_t x = arg.as_derived().eval();
    return simd::to_real(simd::sqrt(simd::dot(x, x)));
  }

  template<typename traits_T, typename ARG>
  inline auto normalized(const ExprBase<traits_T,ARG>& arg)
  {
    return impl::Normalized<traits_T,ARG>(arg.as_derived());
  }

} // namespace n4

#endif // N4_FUNCTIONS_H
