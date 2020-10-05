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

#ifndef INDEXINGIMPL_H
#define INDEXINGIMPL_H

#include <type_traits>

namespace cs {

  namespace impl {

    // Implementation - 3x3 Adjoint Index Computation ////////////////////////

    template<std::size_t i>
    struct AdjointJ { /* SFINAE */ };
    template<>
    struct AdjointJ<0> : public std::integral_constant<std::size_t,1> { };
    template<>
    struct AdjointJ<1> : public std::integral_constant<std::size_t,0> { };
    template<>
    struct AdjointJ<2> : public std::integral_constant<std::size_t,0> { };

    template<std::size_t i>
    inline constexpr std::size_t AdjointJ_v = AdjointJ<i>::value;

    template<std::size_t i>
    struct AdjointK { /* SFINAE */ };
    template<>
    struct AdjointK<0> : public std::integral_constant<std::size_t,2> { };
    template<>
    struct AdjointK<1> : public std::integral_constant<std::size_t,2> { };
    template<>
    struct AdjointK<2> : public std::integral_constant<std::size_t,1> { };

    template<std::size_t i>
    inline constexpr std::size_t AdjointK_v = AdjointK<i>::value;

    // Implementation - Index Comparison /////////////////////////////////////

    template<std::size_t i1, std::size_t j1, std::size_t i2, std::size_t j2>
    struct IsIndex : public std::bool_constant<i1 == i2  &&  j1 == j2> { };

    template<std::size_t i1, std::size_t j1, std::size_t i2, std::size_t j2>
    inline constexpr bool IsIndex_v = IsIndex<i1,j1,i2,j2>::value;

    // Implementation - Next Index Computation ///////////////////////////////

    template<std::size_t i, std::size_t N>
    struct IndexJ : public std::integral_constant<std::size_t,(i + 1)%N> { };

    template<std::size_t i, std::size_t N>
    inline constexpr std::size_t IndexJ_v = IndexJ<i,N>::value;

    template<std::size_t i, std::size_t N>
    struct IndexK : public std::integral_constant<std::size_t,(i + 2)%N> { };

    template<std::size_t i, std::size_t N>
    inline constexpr std::size_t IndexK_v = IndexK<i,N>::value;

  } // namespace impl

} // namespace cs

#endif // INDEXINGIMPL_H
