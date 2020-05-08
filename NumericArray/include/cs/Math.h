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

#ifndef CSMATH_H
#define CSMATH_H

#include <cmath>

#include <emmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

////// Min & Max /////////////////////////////////////////////////////////////

inline double csMax(const double& a, const double& b)
{
  return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

inline float csMax(const float& a, const float& b)
{
  return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

inline double csMin(const double& a, const double& b)
{
  return _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

inline float csMin(const float& a, const float& b)
{
  return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

////// Square Root ///////////////////////////////////////////////////////////

inline double csInvSqrt(const double& x)
{
  return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(1), _mm_sqrt_sd(_mm_set_sd(x), _mm_set_sd(x))));
}

inline float csInvSqrt(const float& x)
{
  return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
}

inline double csSqrt(const double& x)
{
  return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_set_sd(x), _mm_set_sd(x)));
}

inline float csSqrt(const float& x)
{
  return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

////// Trigonometric Functions ///////////////////////////////////////////////

inline double csCos(const double& x)
{
  return std::cos(x);
}

inline float csCos(const float& x)
{
  return std::cosf(x);
}

inline double csSin(const double& x)
{
  return std::sin(x);
}

inline float csSin(const float& x)
{
  return std::sinf(x);
}

#endif // CSMATH_H
