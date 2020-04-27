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

    // Implementation - Next Index Computation ///////////////////////////////

    template<typename size_T, size_T i, size_T N>
    struct NextIndex {
      using size_type = size_T;

      static constexpr size_type j = (i + 1)%N;
      static constexpr size_type k = (i + 2)%N;
    };

    // Implementation - 3x3 Adjoint Index Computation ////////////////////////

    template<typename size_T, size_T i>
    struct AdjointIndex3x3 {
      using size_type = size_T;

      static constexpr size_type j = i == 0 ? 1
                                            : i == 1 ? 0
                                                     : i == 2 ? 0
                                                              : 3;
      static constexpr size_type k = i == 0 ? 2
                                            : i == 1 ? 2
                                                     : i == 2 ? 1
                                                              : 3;
    };

  } // namespace impl

} // namespace cs

#endif // INDEXINGIMPL_H
