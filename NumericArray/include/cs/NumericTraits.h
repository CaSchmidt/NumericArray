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

#ifndef NUMERICTRAITS_H
#define NUMERICTRAITS_H

#include <type_traits>

namespace cs {

  // traits_type::value_type /////////////////////////////////////////////////

  template<typename T>
  inline constexpr bool if_value_v = std::is_floating_point_v<T>;

  template<typename T>
  using if_value_t = std::enable_if_t<if_value_v<T>,T>;


  // traits_type /////////////////////////////////////////////////////////////

  template<typename traits_T>
  inline constexpr bool if_traits_v = std::is_class_v<traits_T>  &&
      if_value_v<typename traits_T::value_type>  &&
      traits_T::Columns > 0  &&  traits_T::Rows > 0  &&
      traits_T::Columns*traits_T::Rows == traits_T::Size;

  template<typename traits_T, typename T>
  using if_traits_t = std::enable_if_t<if_traits_v<traits_T>,T>;


  // type_traits represents a column vector //////////////////////////////////

  template<typename traits_T>
  inline constexpr bool if_column_v = if_traits_v<traits_T>  &&  traits_T::Columns == 1;

  template<typename traits_T, typename T>
  using if_column_t = std::enable_if_t<if_column_v<traits_T>,T>;


  // type_traits has required dimensions /////////////////////////////////////

  template<typename traits_T, std::size_t ROWS, std::size_t COLS>
  inline constexpr bool if_dimensions_v = if_traits_v<traits_T>  &&
      traits_T::Rows == ROWS  &&  traits_T::Columns == COLS;

  template<typename traits_T, std::size_t ROWS, typename std::size_t COLS, typename T>
  using if_dimensions_t = std::enable_if_t<if_dimensions_v<traits_T,ROWS,COLS>,T>;


  // type_traits are identical ///////////////////////////////////////////////

  template<typename traits_A, typename traits_B>
  inline constexpr bool if_identical_v = if_traits_v<traits_A>  &&  if_traits_v<traits_B>  &&
      std::is_same_v<typename traits_A::value_type,typename traits_B::value_type>  &&
  traits_A::Columns == traits_B::Columns  &&  traits_A::Rows == traits_B::Rows;

  template<typename traits_A, typename traits_B, typename T>
  using if_identical_t = std::enable_if_t<if_identical_v<traits_A,traits_B>,T>;


  // type_traits with index (i,j) ////////////////////////////////////////////

  template<typename traits_T, std::size_t i, std::size_t j>
  inline constexpr bool if_index_v = if_traits_v<traits_T>  &&
      0 <= i  &&  i < traits_T::Rows  &&
      0 <= j  &&  j < traits_T::Columns;

  template<typename traits_T, std::size_t i, std::size_t j, typename T>
  using if_index_t = std::enable_if_t<if_index_v<traits_T,i,j>,T>;


  // type_traits represents a quadratic matrix ///////////////////////////////

  template<typename traits_T>
  inline constexpr bool if_quadratic_v = if_traits_v<traits_T>  &&
      traits_T::Rows == traits_T::Columns;

  template<typename traits_T, typename T>
  using if_quadratic_t = std::enable_if_t<if_quadratic_v<traits_T>,T>;


  // SIMD interface availability /////////////////////////////////////////////

  template<typename T, typename simd_policy_T, bool check_policy, typename = bool>
  struct if_simd : std::false_type {};

  template<typename T, typename simd_policy_T, bool check_policy>
  struct if_simd<T,simd_policy_T,check_policy,decltype(T::template is_simd<simd_policy_T,check_policy>(),std::declval<T>().block(0),bool())> : std::true_type {};

  template<typename T, typename simd_policy_T, bool check_policy>
  inline constexpr bool if_simd_v = if_simd<T,simd_policy_T,check_policy>::value;

  template<typename T, typename simd_policy_T, bool check_policy = true>
  constexpr std::enable_if_t<if_simd_v<T,simd_policy_T,check_policy>,bool> check_simd()
  {
    return static_cast<bool>(T::template is_simd<simd_policy_T,check_policy>());
  }

  template<typename T, typename simd_policy_T, bool check_policy = true>
  constexpr std::enable_if_t<!if_simd_v<T,simd_policy_T,check_policy>,bool> check_simd()
  {
    return false;
  }

  // RGB types ///////////////////////////////////////////////////////////////

  template<typename T>
  inline constexpr bool if_rgb_v =
      std::is_integral_v<T>  &&  std::is_unsigned_v<T>  &&  sizeof(T) == 1;

  template<typename T>
  using if_rgb_t = std::enable_if_t<if_rgb_v<T>,T>;

} // namespace cs

#endif // NUMERICTRAITS_H
