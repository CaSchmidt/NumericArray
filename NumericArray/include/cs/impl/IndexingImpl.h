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

#include <cstddef>

namespace cs {

  namespace impl {

    // Implementation - 3x3 Adjoint Index Computation ////////////////////////

    template<std::size_t i>
    struct AdjointIndex3x3 {
      static constexpr std::size_t j = i == 0 ? 1
                                              : i == 1 ? 0
                                                       : i == 2 ? 0
                                                                : 3;
      static constexpr std::size_t k = i == 0 ? 2
                                              : i == 1 ? 2
                                                       : i == 2 ? 1
                                                                : 3;
    };

    // Implementation - Index Comparison /////////////////////////////////////

    template<std::size_t i1, std::size_t j1, std::size_t i2, std::size_t j2>
    struct IsIndex {
      static constexpr bool value = i1 == i2  &&  j1 == j2;
    };

    // Implementation - Next Index Computation ///////////////////////////////

    template<std::size_t i, std::size_t N>
    struct NextIndex {
      static constexpr std::size_t j = (i + 1)%N;
      static constexpr std::size_t k = (i + 2)%N;
    };

  } // namespace impl

} // namespace cs

#endif // INDEXINGIMPL_H
