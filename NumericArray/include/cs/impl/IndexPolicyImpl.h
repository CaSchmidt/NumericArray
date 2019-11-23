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

#ifndef INDEXPOLICYIMPL_H
#define INDEXPOLICYIMPL_H

#include "cs/Types.h"

namespace cs {

  namespace impl {

    /*
     * NOTE:
     * i,j := [ROWS-1,0], [COLS-1,0] -> Loop Variable, Counting DOWN!
     * I,J := [0,ROWS-1], [0,COLS-1] -> Absolute Row/Column
     */

    // Implementation - Row Major Traits /////////////////////////////////////

    template<dim_T I, dim_T j, dim_T ROWS, dim_T COLS, typename dest_T, typename src_T>
    struct RowMajorColumnIter { // Inner Loop: Iterate Columns
      enum Index : dim_T {
        J = COLS - 1 - j
      };

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        dest.template ref<I,J>() = src.template eval<I,J>();
        RowMajorColumnIter<I,j-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

    template<dim_T I, dim_T ROWS, dim_T COLS, typename dest_T, typename src_T>
    struct RowMajorColumnIter<I,0,ROWS,COLS,dest_T,src_T> {
      enum Index : dim_T {
        J = COLS - 1
      };

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        dest.template ref<I,J>() = src.template eval<I,J>();
      }
    };

    template<dim_T i, dim_T ROWS, dim_T COLS, typename dest_T, typename src_T>
    struct RowMajorRowIter { // Outer Loop: Iterate Rows
      enum Index : dim_T {
        I = ROWS - 1 - i
      };

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        RowMajorColumnIter<I,COLS-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
        RowMajorRowIter<i-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

    template<dim_T ROWS, dim_T COLS, typename dest_T, typename src_T>
    struct RowMajorRowIter<0,ROWS,COLS,dest_T,src_T> {
      enum Index : dim_T {
        I = ROWS - 1
      };

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        RowMajorColumnIter<I,COLS-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

  } // namespace impl

} // namespace cs

#endif // INDEXPOLICYIMPL_H
