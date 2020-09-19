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

#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <cs/Math.h>
#include <cs/NumericTraits.h>

namespace cs {

  ////// No Data Manipulator /////////////////////////////////////////////////

  template<typename policy_T>
  class NoManipulator {
  public:
    using policy_type = policy_T;
    using traits_type = typename policy_type::traits_type;
    using  value_type = typename traits_type::value_type;

    static_assert(if_traits_v<traits_type>);

    NoManipulator(value_type *) noexcept
    {
    }

    ~NoManipulator() noexcept = default;

  private:
    NoManipulator() noexcept = delete;
  };


  ////// Generic Array<i,j> Property /////////////////////////////////////////

  template<typename policy_T, typename policy_T::size_type i, typename policy_T::size_type j>
  class ArrayProperty {
  public:
    using policy_type = policy_T;
    using traits_type = typename policy_type::traits_type;
    using  value_type = typename traits_type::value_type;

    static_assert(if_index_v<traits_type,i,j>);

    ArrayProperty(value_type *data) noexcept
      : _data{&data[policy_type::template index<i,j>()]}
    {
    }

    ~ArrayProperty() noexcept = default;

    inline operator value_type() const
    {
      return *_data;
    }

    inline value_type operator=(const value_type value)
    {
      *_data = value;
      return *_data;
    }

  private:
    ArrayProperty() noexcept = delete;

    value_type *_data{nullptr};
  };


  ////// RGB Color Manipulator ///////////////////////////////////////////////

  template<typename policy_T, typename policy_T::size_type i>
  class RGBProperty {
  public:
    using policy_type = policy_T;
    using    rgb_type = if_rgb_t<unsigned char>;
    using traits_type = typename policy_type::traits_type;
    using  value_type = typename traits_type::value_type;

    static_assert(if_index_v<traits_type,i,0>);

    RGBProperty(value_type *data) noexcept
      : _data{&data[policy_type::template index<i,0>()]}
    {
    }

    ~RGBProperty() noexcept = default;

    inline operator rgb_type() const
    {
      constexpr value_type  ONE = 1;
      constexpr value_type ZERO = 0;
      return static_cast<rgb_type>(csClamp(*_data, ZERO, ONE)*RGB_MAX);
    }

    inline rgb_type operator=(const rgb_type value)
    {
      *_data = static_cast<value_type>(value)/RGB_MAX;
      return operator rgb_type();
    }

  private:
    static constexpr value_type RGB_MAX = 255;

    RGBProperty() noexcept = delete;

    value_type *_data{nullptr};
  };

  template<typename policy_T>
  class Color3Manip {
  public:
    using policy_type = policy_T;
    using traits_type = typename policy_type::traits_type;
    using  value_type = typename traits_type::value_type;

    static_assert(if_dimensions_v<traits_type,3,1>);

    Color3Manip(value_type *data) noexcept
      : r(data)
      , g(data)
      , b(data)
    {
    }

    ~Color3Manip() noexcept = default;

    RGBProperty<policy_T,0> r;
    RGBProperty<policy_T,1> g;
    RGBProperty<policy_T,2> b;

  private:
    Color3Manip() noexcept = delete;
  };


  ////// 3x1 Column Vector Manipulator ///////////////////////////////////////

  template<typename policy_T>
  class Vector3Manip {
  public:
    using policy_type = policy_T;
    using traits_type = typename policy_type::traits_type;
    using  value_type = typename traits_type::value_type;

    static_assert(if_dimensions_v<traits_type,3,1>);

    Vector3Manip(value_type *data) noexcept
      : x(data)
      , y(data)
      , z(data)
    {
    }

    ~Vector3Manip() noexcept = default;

    ArrayProperty<policy_type,0,0> x;
    ArrayProperty<policy_type,1,0> y;
    ArrayProperty<policy_type,2,0> z;

  private:
    Vector3Manip() noexcept = delete;
  };

} // namespace cs

#endif // MANIPULATOR_H
