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

#ifndef GEOMETRYIMPL_H
#define GEOMETRYIMPL_H

#include <cs/impl/IndexingImpl.h>
#include <cs/ExprBase.h>

namespace cs {

  namespace impl {

    // Implementation - Nx1 Elementary Axis //////////////////////////////////

    template<typename traits_T, typename traits_T::size_type DIM>
    class Axis : public ExprBase<traits_T,Axis<traits_T,DIM>> {
    public:
      using typename ExprBase<traits_T,Axis<traits_T,DIM>>::size_type;
      using typename ExprBase<traits_T,Axis<traits_T,DIM>>::traits_type;
      using typename ExprBase<traits_T,Axis<traits_T,DIM>>::value_type;

      static_assert(if_column_v<traits_T>  &&  DIM >= 0  &&  DIM < traits_type::Rows);

      Axis() noexcept = default;

      ~Axis() noexcept = default;

      template<size_type i, size_type>
      inline value_type eval() const
      {
        if constexpr( i == DIM ) {
          return value_type{1};
        }
        return value_type{0};
      }
    };

    // Implementation - NxN Identity Matrix //////////////////////////////////

    template<typename traits_T>
    class Identity : public ExprBase<traits_T,Identity<traits_T>> {
    public:
      using typename ExprBase<traits_T,Identity<traits_T>>::size_type;
      using typename ExprBase<traits_T,Identity<traits_T>>::traits_type;
      using typename ExprBase<traits_T,Identity<traits_T>>::value_type;

      static_assert(if_quadratic_v<traits_type>);

      Identity() noexcept = default;

      ~Identity() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        if constexpr( II<i,j,j,i> ) {
          return value_type{1};
        }
        return value_type{0};
      }

    private:
      template<size_type i1, size_type j1, size_type i2, size_type j2>
      static constexpr bool II = IsIndex<size_type,i1,j1,i2,j2>::value;
    };

    // Implementation - Rotation about x axis ////////////////////////////////

    template<typename traits_T>
    class RotateX : public ExprBase<traits_T,RotateX<traits_T>> {
    public:
      using typename ExprBase<traits_T,RotateX<traits_T>>::size_type;
      using typename ExprBase<traits_T,RotateX<traits_T>>::traits_type;
      using typename ExprBase<traits_T,RotateX<traits_T>>::value_type;

      static_assert(if_dimensions_v<traits_T,3,3>);

      RotateX(const value_type COS, const value_type SIN) noexcept
        : _COS{COS}
        , _SIN{SIN}
      {
      }

      ~RotateX() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        if constexpr( II<i,j,0,0> ) {
          return value_type{1};
        } else if constexpr( II<i,j,j,i> ) {
          return _COS;
        } else if constexpr( II<i,j,1,2> ) {
          return -_SIN;
        } else if constexpr( II<i,j,2,1> ) {
          return _SIN;
        }
        return value_type{0};
      }

    private:
      template<size_type i1, size_type j1, size_type i2, size_type j2>
      static constexpr bool II = IsIndex<size_type,i1,j1,i2,j2>::value;

      const value_type _COS{}, _SIN{};
    };

    // Implementation - Rotation about y axis ////////////////////////////////

    template<typename traits_T>
    class RotateY : public ExprBase<traits_T,RotateY<traits_T>> {
    public:
      using typename ExprBase<traits_T,RotateY<traits_T>>::size_type;
      using typename ExprBase<traits_T,RotateY<traits_T>>::traits_type;
      using typename ExprBase<traits_T,RotateY<traits_T>>::value_type;

      static_assert(if_dimensions_v<traits_T,3,3>);

      RotateY(const value_type COS, const value_type SIN) noexcept
        : _COS{COS}
        , _SIN{SIN}
      {
      }

      ~RotateY() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        if constexpr( II<i,j,1,1> ) {
          return value_type{1};
        } else if constexpr( II<i,j,j,i> ) {
          return _COS;
        } else if constexpr( II<i,j,0,2> ) {
          return _SIN;
        } else if constexpr( II<i,j,2,0> ) {
          return -_SIN;
        }
        return value_type{0};
      }

    private:
      template<size_type i1, size_type j1, size_type i2, size_type j2>
      static constexpr bool II = IsIndex<size_type,i1,j1,i2,j2>::value;

      const value_type _COS{}, _SIN{};
    };

    // Implementation - Rotation about z axis ////////////////////////////////

    template<typename traits_T>
    class RotateZ : public ExprBase<traits_T,RotateZ<traits_T>> {
    public:
      using typename ExprBase<traits_T,RotateZ<traits_T>>::size_type;
      using typename ExprBase<traits_T,RotateZ<traits_T>>::traits_type;
      using typename ExprBase<traits_T,RotateZ<traits_T>>::value_type;

      static_assert(if_dimensions_v<traits_T,3,3>);

      RotateZ(const value_type COS, const value_type SIN) noexcept
        : _COS{COS}
        , _SIN{SIN}
      {
      }

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        if constexpr( II<i,j,2,2> ) {
          return value_type{1};
        } else if constexpr( II<i,j,j,i> ) {
          return _COS;
        } else if constexpr( II<i,j,0,1> ) {
          return -_SIN;
        } else if constexpr( II<i,j,1,0> ) {
          return _SIN;
        }
        return value_type{0};
      }

    private:
      template<size_type i1, size_type j1, size_type i2, size_type j2>
      static constexpr bool II = IsIndex<size_type,i1,j1,i2,j2>::value;

      const value_type _COS{}, _SIN{};
    };

    // Implementation - 3x3 scaling along elementary axes ////////////////////

    template<typename traits_T>
    class Scale : public ExprBase<traits_T,Scale<traits_T>> {
    public:
      using typename ExprBase<traits_T,Scale<traits_T>>::size_type;
      using typename ExprBase<traits_T,Scale<traits_T>>::traits_type;
      using typename ExprBase<traits_T,Scale<traits_T>>::value_type;

      static_assert(if_dimensions_v<traits_T,3,3>);

      Scale(const value_type sx, const value_type sy, const value_type sz) noexcept
        : _sx{sx}
        , _sy{sy}
        , _sz{sz}
      {
      }

      ~Scale() noexcept = default;

      template<size_type i, size_type j>
      inline value_type eval() const
      {
        if constexpr( II<i,j,0,0> ) {
          return _sx;
        } else if constexpr( II<i,j,1,1> ) {
          return _sy;
        } else if constexpr( II<i,j,2,2> ) {
          return _sz;
        }
        return value_type{0};
      }

    private:
      template<size_type i1, size_type j1, size_type i2, size_type j2>
      static constexpr bool II = IsIndex<size_type,i1,j1,i2,j2>::value;

      const value_type _sx{}, _sy{}, _sz{};
    };

  } // namespace impl

} // namespace cs

#endif // GEOMETRYIMPL_H
