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

namespace cs {

  namespace impl {

    // Implementation - Cyclic Index Computation /////////////////////////////

    template<typename size_T, size_T i, size_T N>
    struct NextIndex {
      using size_type = size_T;

      static constexpr size_type j = (i + 1)%N;
      static constexpr size_type k = (i + 2)%N;
    };

    template<typename size_T, size_T i>
    using NI3 = NextIndex<size_T,i,3>;

    // Implementation - 3x3 Adjoint Index Computation ////////////////////////

    /*
    template<dim_T i>
    struct AdjointIndex3x3 {
      // SFINAE
    };

    template<>
    struct AdjointIndex3x3<0> {
      static constexpr dim_T J = 1;
      static constexpr dim_T K = 2;
    };

    template<>
    struct AdjointIndex3x3<1> {
      static constexpr dim_T J = 0;
      static constexpr dim_T K = 2;
    };

    template<>
    struct AdjointIndex3x3<2> {
      static constexpr dim_T J = 0;
      static constexpr dim_T K = 1;
    };

    template<dim_T i>
    using AI3 = AdjointIndex3x3<i>;
    */

  } // namespace impl

} // namespace cs

#endif // INDEXINGIMPL_H
