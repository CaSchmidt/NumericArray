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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cs/impl/GeometryImpl.h>
#include <cs/Math.h>

namespace cs {

  // NxN Identity Matrix /////////////////////////////////////////////////////

  template<typename traits_T>
  constexpr auto identity()
  {
    static_assert(if_quadratic_v<traits_T>);
    return impl::Identity<traits_T>();
  }

  // 3x3 Rotation About X Axis ///////////////////////////////////////////////

  template<typename traits_T>
  constexpr auto rotateX(const typename traits_T::value_type angle)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    return impl::RotateX<traits_T>(csCos(angle), csSin(angle));
  }

  // 3x3 Rotation About Y Axis ///////////////////////////////////////////////

  template<typename traits_T>
  constexpr auto rotateY(const typename traits_T::value_type angle)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    return impl::RotateY<traits_T>(csCos(angle), csSin(angle));
  }

  // 3x3 Rotation About Z Axis ///////////////////////////////////////////////

  template<typename traits_T>
  constexpr auto rotateZ(const typename traits_T::value_type angle)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    return impl::RotateZ<traits_T>(csCos(angle), csSin(angle));
  }

  // 3x3 Scaling Matrix //////////////////////////////////////////////////////

  template<typename traits_T>
  constexpr auto scale(const typename traits_T::value_type sx,
                       const typename traits_T::value_type sy,
                       const typename traits_T::value_type sz)
  {
    static_assert(if_dimensions_v<traits_T,3,3>);
    return impl::Scale<traits_T>(sx, sy, sz);
  }

} // namespace cs

#endif // GEOMETRY_H
