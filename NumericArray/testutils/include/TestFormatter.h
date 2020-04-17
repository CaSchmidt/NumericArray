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

#ifndef TESTFORMATTER_H
#define TESTFORMATTER_H

#include <iomanip>
#include <ostream>
#include <type_traits>

////// Formatting Floating Point Numbers /////////////////////////////////////

template<typename CharT, typename T>
class FormatFloatingPoint {
public:
  FormatFloatingPoint(const std::enable_if_t<std::is_floating_point_v<T>,T>& value,
                      const int     width = 0,
                      const CharT  format = static_cast<CharT>('g'),
                      const int precision = -1,
                      const CharT    fill = static_cast<CharT>(' ')) noexcept
    : _fill{fill}
    , _precision{precision}
    , _value{value}
    , _width{width}
  {
    if(        format == static_cast<CharT>('a')  ||  format == static_cast<CharT>('A') ) {
      _format = std::ios_base::fixed | std::ios_base::scientific;
    } else if( format == static_cast<CharT>('e')  ||  format == static_cast<CharT>('E') ) {
      _format = std::ios_base::scientific;
    } else if( format == static_cast<CharT>('f')  ||  format == static_cast<CharT>('F') ) {
      _format = std::ios_base::fixed;
    } else {
      _format = 0;
    }
    if( format == static_cast<CharT>('A')  ||
        format == static_cast<CharT>('E')  ||
        format == static_cast<CharT>('F') ) {
      _format |= std::ios_base::uppercase;
    }
  }

  ~FormatFloatingPoint() noexcept = default;

  constexpr CharT fill() const
  {
    return _fill;
  }

  constexpr std::ios_base::fmtflags format() const
  {
    return _format;
  }

  constexpr int precision() const
  {
    return _precision > 0
        ? _precision
        : 6;
  }

  constexpr T value() const
  {
    return _value;
  }

  constexpr int width() const
  {
    return _width > 0
        ? _width
        : 1;
  }

private:
  FormatFloatingPoint() noexcept = delete;

  FormatFloatingPoint(const FormatFloatingPoint&) noexcept = delete;
  FormatFloatingPoint& operator=(const FormatFloatingPoint&) noexcept = delete;

  FormatFloatingPoint(FormatFloatingPoint&&) noexcept = delete;
  FormatFloatingPoint& operator=(FormatFloatingPoint&&) noexcept = delete;

  const CharT             _fill{};
  std::ios_base::fmtflags _format{};
  const int               _precision{};
  const T                 _value{};
  const int               _width{};
};

template<typename CharT, typename T, class Traits>
constexpr std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& os,
                                                       const FormatFloatingPoint<CharT,T>& fmt)
{
  return ( os
           << std::setfill(fmt.fill())
           << std::setw(fmt.width())
           << std::setprecision(fmt.precision())
           << std::resetiosflags(std::ios_base::floatfield | std::ios_base::uppercase)
           << std::setiosflags(fmt.format())
           << fmt.value() );
}

////// Formatting Integral Numbers ///////////////////////////////////////////

template<typename CharT, typename T>
class FormatInteger {
public:
  FormatInteger(const std::enable_if_t<std::is_integral<T>::value,T>& value,
                const int   width = 0,
                const int    base = 10,
                const CharT& fill = static_cast<CharT>(' ')) noexcept
    : _base{base}
    , _fill{fill}
    , _value{value}
    , _width{width}
  {
  }

  ~FormatInteger() noexcept = default;

  constexpr int base() const
  {
    return _base < 2
        ? 2
        : _base > 36
          ? 36
          : _base;
  }

  constexpr CharT fill() const
  {
    return _fill;
  }

  constexpr T value() const
  {
    return _value;
  }

  constexpr int width() const
  {
    return _width > 0
        ? _width
        : 1;
  }

private:
  FormatInteger() noexcept = delete;

  FormatInteger(const FormatInteger&) noexcept = delete;
  FormatInteger& operator=(const FormatInteger&) noexcept = delete;

  FormatInteger(FormatInteger&&) noexcept = delete;
  FormatInteger& operator=(FormatInteger&&) noexcept = delete;

  const int   _base{};
  const CharT _fill{};
  const T     _value{};
  const int   _width{};
};

template<typename CharT, typename T, class Traits>
constexpr std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& os,
                                                       const FormatInteger<CharT,T>& fmt)
{
  return ( os
           << std::setfill(fmt.fill())
           << std::setw(fmt.width())
           << std::resetiosflags(std::ios_base::basefield)
           << std::setbase(fmt.base())
           << fmt.value() );
}

#endif // TESTFORMATTER_H
