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

#ifndef NUMERIC_MATH_H
#define NUMERIC_MATH_H

#include <math.h>

#include <emmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

////// Absolute Value ////////////////////////////////////////////////////////

inline double csAbs(const double& x)
{
  return ::fabs(x);
}

inline float csAbs(const float& x)
{
  return ::fabsf(x);
}

////// Inverse Trigonometric Functions ///////////////////////////////////////

inline double csACos(const double& x)
{
  return ::acos(x);
}

inline float csACos(const float& x)
{
  return ::acosf(x);
}

inline double csASin(const double& x)
{
  return ::asin(x);
}

inline float csASin(const float& x)
{
  return ::asinf(x);
}

inline double csATan2(const double& y, const double& x)
{
  return ::atan2(y, x);
}

inline float csATan2(const float& y, const float& x)
{
  return ::atan2f(y, x);
}

////// Clamp /////////////////////////////////////////////////////////////////

inline double csClamp(const double& v, const double& lo, const double& hi)
{
  return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(lo), _mm_min_sd(_mm_set_sd(v), _mm_set_sd(hi))));
}

inline float csClamp(const float& v, const float& lo, const float& hi)
{
  return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(lo), _mm_min_ss(_mm_set_ss(v), _mm_set_ss(hi))));
}

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

////// Power /////////////////////////////////////////////////////////////////

inline double csPow(const double& x, const double& y)
{
  return ::pow(x, y);
}

inline float csPow(const float& x, const float& y)
{
  return ::powf(x, y);
}

////// Remainder /////////////////////////////////////////////////////////////

inline double csRemndr(const double& x, const double& y)
{
  return ::fmod(x, y);
}

inline float csRemndr(const float& x, const float& y)
{
  return ::fmodf(x, y);
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
  return ::cos(x);
}

inline float csCos(const float& x)
{
  return ::cosf(x);
}

template<typename T>
inline T csCosPI2(const signed int i)
{
  static const T tab[4] = { 1, 0, -1, 0 };
  return tab[i & 0x3];
}

inline double csSin(const double& x)
{
  return ::sin(x);
}

inline float csSin(const float& x)
{
  return ::sinf(x);
}

template<typename T>
inline T csSinPI2(const signed int i)
{
  static const T tab[4] = { 0, 1, 0, -1 };
  return tab[i & 0x3];
}

inline double csTan(const double& x)
{
  return ::tan(x);
}

inline float csTan(const float& x)
{
  return ::tanf(x);
}

#endif // NUMERIC_MATH_H
