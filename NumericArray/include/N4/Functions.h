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

#include <N4/Dispatch.h>
#include <N4/TypeTraits.h>

namespace n4 {

  ////// Implementation //////////////////////////////////////////////////////

  namespace impl {

    struct Clamp {
      inline static simd_t eval(const simd_t& x, const simd_t& lo, const simd_t& hi)
      {
        return simd::clamp(x, lo, hi);
      }
    };

    struct Cross {
      inline static simd_t eval(const simd_t& a, const simd_t& b)
      {
        return simd::cross(a, b);
      }
    };

    struct Direction {
      inline static simd_t eval(const simd_t& from, const simd_t& to)
      {
        const simd_t x = simd::sub(to, from);
        return simd::div(x, simd::sqrt(simd::dot(x, x)));
      }
    };

    struct Max {
      inline static simd_t eval(const simd_t& a, const simd_t& b)
      {
        return simd::max(a, b);
      }
    };

    struct Min {
      inline static simd_t eval(const simd_t& a, const simd_t& b)
      {
        return simd::min(a, b);
      }
    };

    struct Normalize {
      inline static simd_t eval(const simd_t& x)
      {
        return simd::div(x, simd::sqrt(simd::dot(x, x)));
      }
    };

  } // namespace impl

  ////// User Interface //////////////////////////////////////////////////////

  template<typename traits_T, typename ARG>
  inline auto clamp(const ExprBase<traits_T,ARG>& arg, const real_t lo, const real_t hi)
  {
    return impl::DispatchVSS<traits_T,ARG,impl::Clamp>(arg.as_derived(), lo, hi);
  }

  template<typename traits_T, typename ARG1, typename ARG2>
  inline auto cross(const ExprBase<traits_T,ARG1>& arg1, const ExprBase<traits_T,ARG2>& arg2)
  {
    return impl::DispatchVV<traits_T,ARG1,ARG2,impl::Cross>(arg1.as_derived(), arg2.as_derived());
  }

  template<typename traits_T, typename FROM, typename TO>
  inline auto direction(const ExprBase<traits_T,FROM>& from, const ExprBase<traits_T,TO>& to)
  {
    return impl::DispatchVV<traits_T,FROM,TO,impl::Direction>(from.as_derived(), to.as_derived());
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

  template<typename traits_T, typename ARG1>
  inline auto max(const ExprBase<traits_T,ARG1>& arg1, const real_t arg2)
  {
    return impl::DispatchVS<traits_T,ARG1,impl::Max>(arg1.as_derived(), arg2);
  }

  template<typename traits_T, typename ARG2>
  inline auto max(const real_t arg1, const ExprBase<traits_T,ARG2>& arg2)
  {
    return impl::DispatchSV<traits_T,ARG2,impl::Max>(arg1, arg2.as_derived());
  }

  template<typename traits_T, typename ARG1>
  inline auto min(const ExprBase<traits_T,ARG1>& arg1, const real_t arg2)
  {
    return impl::DispatchVS<traits_T,ARG1,impl::Min>(arg1.as_derived(), arg2);
  }

  template<typename traits_T, typename ARG2>
  inline auto min(const real_t arg1, const ExprBase<traits_T,ARG2>& arg2)
  {
    return impl::DispatchSV<traits_T,ARG2,impl::Min>(arg1, arg2.as_derived());
  }

  template<typename traits_T, typename ARG>
  inline auto normalize(const ExprBase<traits_T,ARG>& arg)
  {
    return impl::DispatchV<traits_T,ARG,impl::Normalize>(arg.as_derived());
  }

} // namespace n4

#endif // N4_FUNCTIONS_H
