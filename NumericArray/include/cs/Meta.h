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

#ifndef META_H
#define META_H

#include <utility>

namespace cs {

  namespace meta {

    namespace impl {

      ////// For Each Metaprogram //////////////////////////////////////////////

      template<std::size_t I, std::size_t N, typename E, typename... Rargs>
      struct ForEachImpl {
        static_assert(N > 0  &&  I > 0);

        inline static void run(Rargs&&... args)
        {
          E::template eval<N-1-I>(std::forward<Rargs>(args)...);
          ForEachImpl<I-1,N,E,Rargs...>::run(std::forward<Rargs>(args)...);
        }
      };

      template<std::size_t N, typename E, typename... Rargs>
      struct ForEachImpl<0,N,E,Rargs...> {
        static_assert(N > 0);

        inline static void run(Rargs&&... args)
        {
          E::template eval<N-1>(std::forward<Rargs>(args)...);
        }
      };

      ////// Accumulate Metaprogram ////////////////////////////////////////////

      template<std::size_t I, std::size_t N, typename value_T, typename E, typename... Rargs>
      struct AccumulateImpl {
        static_assert(N > 0  &&  I > 0);

        inline static value_T run(Rargs&&... args)
        {
          return E::accumulate(E::template eval<N-1-I>(std::forward<Rargs>(args)...),
                               AccumulateImpl<I-1,N,value_T,E,Rargs...>::run(std::forward<Rargs>(args)...));
        }
      };

      template<std::size_t N, typename value_T, typename E, typename... Rargs>
      struct AccumulateImpl<0,N,value_T,E,Rargs...> {
        static_assert(N > 0);

        inline static value_T run(Rargs&&... args)
        {
          return E::template eval<N-1>(std::forward<Rargs>(args)...);
        }
      };

    } // namespace impl

    template<std::size_t N, typename F, typename... Rargs>
    inline void for_each(Rargs&&... args)
    {
      static_assert(N > 0);
      impl::ForEachImpl<N-1,N,F,Rargs...>::run(std::forward<Rargs>(args)...);
    }

    template<typename T, std::size_t N, typename F, typename... Rargs>
    inline T accumulate(Rargs&&... args)
    {
      static_assert(N > 0);
      return impl::AccumulateImpl<N-1,N,T,F,Rargs...>::run(std::forward<Rargs>(args)...);
    }

  } // namespace meta

} // namespace cs

#endif // META_H
