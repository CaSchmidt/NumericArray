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

#ifndef ARRAYPOLICY_H
#define ARRAYPOLICY_H

#include <type_traits>

namespace cs {

  template<typename traits_T, template<typename> typename derived_T>
  struct ArrayPolicyBase {
    using traits_type = traits_T;
    using policy_type = derived_T<traits_type>;

    template<typename T>
    using make_policy = derived_T<T>;

    /*
     * NOTE:
     * Two policies are considered identical IFF both underlying template classes
     * instantiated with both policies' traits lead to identical complete types.
     */
    template<typename other_T>
    inline static constexpr bool is_same_v =
        std::is_same_v<policy_type,typename other_T::template make_policy<traits_type>>
    &&
    std::is_same_v<typename policy_type::template make_policy<typename other_T::traits_type>,other_T>;
  };

  template<typename traits_T>
  struct RowMajorPolicy : public ArrayPolicyBase<traits_T,RowMajorPolicy> {
    using traits_type = traits_T;
    using   size_type = typename traits_type::size_type;

    template<size_type l>
    static constexpr size_type column()
    {
      return l%traits_type::Columns;
    }

    template<size_type i, size_type j>
    static constexpr size_type index()
    {
      return i*traits_type::Columns + j;
    }

    static constexpr size_type index(const size_type i, const size_type j)
    {
      return i*traits_type::Columns + j;
    }

    template<size_type l>
    static constexpr size_type row()
    {
      return l/traits_type::Columns;
    }
  };

} // namespace cs

#endif // ARRAYPOLICY_H
