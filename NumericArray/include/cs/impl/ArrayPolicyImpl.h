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

#ifndef ARRAYPOLICYIMPL_H
#define ARRAYPOLICYIMPL_H

namespace cs {

  namespace impl {

    /*
     * NOTE:
     * i,j := [ROWS-1,0], [COLS-1,0] -> Loop Variable, Counting DOWN!
     * I,J := [0,ROWS-1], [0,COLS-1] -> Absolute Row/Column
     */

    /*************************************************************************
     * Implementation - Row Major Traits *************************************
     *************************************************************************/

    // Row Major Traits - Inner Loop: Iterate Columns ////////////////////////

    template<auto I, auto j, auto ROWS, auto COLS, typename dest_T, typename src_T>
    struct RowMajorColumnIter {
      static constexpr auto J = COLS - 1 - j;

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        dest.template ref<I,J>() = src.template eval<I,J>();
        RowMajorColumnIter<I,j-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

    // Row Major Traits - Inner Loop: Iterate Columns (Last Column) //////////

    template<auto I, auto ROWS, auto COLS, typename dest_T, typename src_T>
    struct RowMajorColumnIter<I,0,ROWS,COLS,dest_T,src_T> {
      static constexpr auto J = COLS - 1;

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        dest.template ref<I,J>() = src.template eval<I,J>();
      }
    };

    // Row Major Traits - Outer Loop: Iterate Rows ///////////////////////////

    template<auto i, auto ROWS, auto COLS, typename dest_T, typename src_T>
    struct RowMajorRowIter {
      static const auto I = ROWS - 1 - i;

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        RowMajorColumnIter<I,COLS-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
        RowMajorRowIter<i-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

    // Row Major Traits - Outer Loop: Iterate Rows (Last Row) ////////////////

    template<auto ROWS, auto COLS, typename dest_T, typename src_T>
    struct RowMajorRowIter<0,ROWS,COLS,dest_T,src_T> {
      static constexpr auto I = ROWS - 1;

      static constexpr void run(dest_T& dest, const src_T& src)
      {
        RowMajorColumnIter<I,COLS-1,ROWS,COLS,dest_T,src_T>::run(dest, src);
      }
    };

  } // namespace impl

} // namespace cs

#endif // ARRAYPOLICYIMPL_H
