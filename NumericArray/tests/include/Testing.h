#ifndef TESTING_H
#define TESTING_H

#include <cs/NumericArray.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

template<typename T>
struct Konst {
  static constexpr T epsilon0 = static_cast<T>(1.0 / 1024.0 / 1024.0 / 1024.0);
  static constexpr T     ZERO = static_cast<T>(0.0);
};

template<typename scalar_T>
constexpr bool equals(const scalar_T& a, const scalar_T& b,
                      const scalar_T& epsilon0 = Konst<scalar_T>::epsilon0)
{
  return std::abs(a - b) <= epsilon0;
}

template<typename scalar_T>
constexpr bool equals0(const scalar_T& a, const scalar_T& b)
{
  return equals(a, b, Konst<scalar_T>::ZERO);
}

template<typename scalar_T, cs::dim_T ROWS, cs::dim_T COLS>
inline bool equals(const cs::Array<scalar_T,ROWS,COLS>& A,
                   const std::initializer_list<scalar_T>& list,
                   const scalar_T& epsilon0 = Konst<scalar_T>::epsilon0)
{
  if( static_cast<std::size_t>(A.size()) != list.size() ) {
    return false;
  }

  for(std::size_t index = 0; index < list.size(); index++) {
    const cs::dim_T i = static_cast<cs::dim_T>(index)/A.columns();
    const cs::dim_T j = static_cast<cs::dim_T>(index)%A.columns();
    if( !equals(A(i, j), list.begin()[index], epsilon0) ) {
      return false;
    }
  }

  return true;
}

template<typename scalar_T, cs::dim_T ROWS, cs::dim_T COLS>
constexpr bool equals0(const cs::Array<scalar_T,ROWS,COLS>& A,
                       const std::initializer_list<scalar_T>& list)
{
  return equals(A, list, Konst<scalar_T>::ZERO);
}

#endif // TESTING_H
