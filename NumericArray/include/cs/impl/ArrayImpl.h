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

#ifndef ARRAYIMPL_H
#define ARRAYIMPL_H

#include <cs/TypeTraits.h>

namespace cs {

  namespace impl {

    /*
     * NOTE:
     * i := [SIZE-1,0] -> Loop Variable, Counting DOWN!
     * I := [0,SIZE-1] -> Absolute Index
     */

    // Implementation - Copy Array ///////////////////////////////////////////

    template<typename T, dim_T i, dim_T SIZE>
    struct ArrayCopy {
      static constexpr dim_T I = SIZE - 1 - i;

      static constexpr void run(T *dest, const T *src)
      {
        dest[I] = src[I];
        ArrayCopy<T,i-1,SIZE>::run(dest, src);
      }
    };

    template<typename T, dim_T SIZE>
    struct ArrayCopy<T,0,SIZE> {
      static constexpr dim_T I = SIZE - 1;

      static constexpr void run(T *dest, const T *src)
      {
        dest[I] = src[I];
      }
    };

    // Implementation - Move Array ///////////////////////////////////////////

    template<typename T, dim_T i, dim_T SIZE>
    struct ArrayMove {
      static constexpr dim_T I = SIZE - 1 - i;

      static constexpr void run(T *dest, const T *src)
      {
        dest[I] = std::move(src[I]);
        ArrayMove<T,i-1,SIZE>::run(dest, src);
      }
    };

    template<typename T, dim_T SIZE>
    struct ArrayMove<T,0,SIZE> {
      static constexpr dim_T I = SIZE - 1;

      static constexpr void run(T *dest, const T *src)
      {
        dest[I] = std::move(src[I]);
      }
    };

    // Implementation - Set Array ////////////////////////////////////////////

    template<typename T, dim_T i, dim_T SIZE>
    struct ArraySet {
      static constexpr dim_T I = SIZE - 1 - i;

      static constexpr void run(T *dest, const T& value)
      {
        dest[I] = value;
        ArraySet<T,i-1,SIZE>::run(dest, value);
      }
    };

    template<typename T, dim_T SIZE>
    struct ArraySet<T,0,SIZE> {
      static constexpr dim_T I = SIZE - 1;

      static constexpr void run(T *dest, const T& value)
      {
        dest[I] = value;
      }
    };

  } // namespace impl

} // namespace cs

#endif // ARRAYIMPL_H
