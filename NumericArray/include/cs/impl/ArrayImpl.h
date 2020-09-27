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

#include <cs/SIMD.h>

namespace cs {

  namespace impl {

    // Implementation - Assign Array /////////////////////////////////////////

    template<typename policy_T, typename EXPR>
    struct ArrayAssign {
      using policy_type = policy_T;
      using traits_type = typename policy_type::traits_type;
      using  value_type = typename traits_type::value_type;

      template<std::size_t l>
      inline static void eval(value_type *dest, const EXPR& src)
      {
        constexpr std::size_t i = policy_type::row(l);
        constexpr std::size_t j = policy_type::column(l);

        dest[l] = src.template eval<i,j>();
      }
    };

    template<typename policy_T, typename EXPR>
    struct BlockAssign {
      using policy_type = policy_T;
      using traits_type = typename policy_type::traits_type;
      using  value_type = typename traits_type::value_type;
      using        simd = SIMD<value_type>;

      template<std::size_t b>
      inline static void eval(value_type *dest, const EXPR& src)
      {
        constexpr std::size_t l = b*simd::ElementCount;

        simd::store(dest + l, src.block(b));
      }
    };

    // Implementation - Copy Array ///////////////////////////////////////////

    template<typename traits_T>
    struct ArrayCopy {
      using traits_type = traits_T;
      using  value_type = typename traits_type::value_type;

      template<std::size_t l>
      inline static void eval(value_type *dest, const value_type *src)
      {
        dest[l] = src[l];
      }
    };

    template<typename traits_T>
    struct BlockCopy {
      using traits_type = traits_T;
      using  value_type = typename traits_type::value_type;
      using        simd = SIMD<value_type>;

      template<std::size_t b>
      inline static void eval(value_type *dest, const value_type *src)
      {
        constexpr std::size_t l = b*simd::ElementCount;

        simd::store(dest + l, simd::load(src + l));
      }
    };

    // Implementation - Move Array ///////////////////////////////////////////

    template<typename traits_T>
    struct ArrayMove {
      using traits_type = traits_T;
      using  value_type = typename traits_type::value_type;

      template<std::size_t l>
      inline static void eval(value_type *dest, value_type *src)
      {
        dest[l] = std::move(src[l]);
      }
    };

    // Implementation - Set Array ////////////////////////////////////////////

    template<typename traits_T>
    struct ArraySet {
      using traits_type = traits_T;
      using  value_type = typename traits_type::value_type;

      template<std::size_t l>
      inline static void eval(value_type *dest, const value_type value)
      {
        dest[l] = value;
      }
    };

    template<typename traits_T>
    struct BlockSet {
      using traits_type = traits_T;
      using  value_type = typename traits_type::value_type;
      using        simd = SIMD<value_type>;

      template<std::size_t b>
      inline static void eval(value_type *dest, const value_type value)
      {
        constexpr std::size_t l = b*simd::ElementCount;

        simd::store(dest + l, simd::set(value));
      }
    };

  } // namespace impl

} // namespace cs

#endif // ARRAYIMPL_H
