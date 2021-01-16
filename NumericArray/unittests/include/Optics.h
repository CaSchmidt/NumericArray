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

#ifndef OPTICS_H
#define OPTICS_H

#include <N4/N4.h>

namespace optics {

  ////// Types ///////////////////////////////////////////////////////////////

  using n4::real_t;

  struct DirectionTraits {
    static constexpr bool have_w = false;
  };

  using Direction = n4::Vector4f<DirectionTraits,n4::Normal3fManipulator>;

  struct NormalTraits {
    static constexpr bool have_w = false;
  };

  using Normal = n4::Vector4f<NormalTraits,n4::Normal3fManipulator>;

  ////// Constants ///////////////////////////////////////////////////////////

  inline constexpr real_t ZERO = 0;
  inline constexpr real_t  ONE = 1;

  ////// Helpers /////////////////////////////////////////////////////////////

  template<typename traits_T, typename EXPR>
  inline auto to_direction(const n4::ExprBase<traits_T,EXPR>& expr)
  {
    return n4::expr_cast<Direction::traits_type,traits_T,EXPR>(expr);
  }

  template<typename traits_T, typename EXPR>
  inline auto to_normal(const n4::ExprBase<traits_T,EXPR>& expr)
  {
    return n4::expr_cast<Normal::traits_type,traits_T,EXPR>(expr);
  }

  ////// Implementation //////////////////////////////////////////////////////

  // cf. GLSL v4.60, 8.5. Geometric Functions
  inline Direction refract(const Direction& I, const Normal& N, const real_t eta)
  {
    const real_t DOT = n4::dot(I, to_direction(N));
    const real_t k = ONE - eta*eta*std::max<real_t>(0, ONE - DOT*DOT);
    return k >= ZERO
        ? eta*I - (eta*DOT + n4::sqrt(k))*to_direction(N)
        : Direction();
  }

} // namespace optics

#endif // OPTICS_H
