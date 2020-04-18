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

#ifndef NA_MATH_H
#define NA_MATH_H

#include <emmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

namespace cs {

  inline double invSqrt(const double& x)
  {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(1), _mm_sqrt_sd(_mm_set1_pd(x), _mm_set1_pd(x))));
  }

  inline float invSqrt(const float& x)
  {
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
  }

  inline double sqrt(const double& x)
  {
    return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_set1_pd(x), _mm_set1_pd(x)));
  }

  inline float sqrt(const float& x)
  {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
  }

} // namespace cs

#endif // NA_MATH_H
