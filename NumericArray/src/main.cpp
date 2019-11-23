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

#include <intrin.h>

#include <cstdio>
#include <cstdlib>

#include "cs/NumericArray.h"

template<typename T, cs::dim_T ROWS, cs::dim_T COLS>
void print(const cs::Array<T,ROWS,COLS>& array, const char *text = nullptr)
{
  if( text != nullptr ) {
    printf("%s\n", text);
  }
  for(cs::dim_T i = 0; i < array.rows(); i++) {
    for(cs::dim_T j = 0; j < array.columns(); j++) {
      const double d = static_cast<double>(array(i, j));
      printf(" %8.3f", d);
    }
    printf("\n");
  }
}

template<typename scalar_T, cs::dim_T ROWS, cs::dim_T COLS, typename ARG>
void print(const cs::ExprBase<scalar_T,ROWS,COLS,ARG>& expr,
           const char *text = nullptr)
{
  print(cs::Array<scalar_T,ROWS,COLS>(expr), text);
}

using Matrix = cs::Array<double,3,3>;
using Vector = cs::Array<double,3,1>;

void test_assign_list()
{
  printf("%s\n", __FUNCSIG__);
  Matrix M({1, 2, 3, 4, 5, 6, 7, 8, 9});
  print(M); printf("\n");
  M = {7, 8, 9};
  print(M); printf("\n");
  fflush(stdout);
}

void test_assign_scalar()
{
  printf("%s\n", __FUNCSIG__);
  Matrix M(1);
  print(M); printf("\n");
  M = 2;
  print(M); printf("\n");
  fflush(stdout);
}

void test_copy()
{
  printf("%s\n", __FUNCSIG__);
  const Matrix A(1);
  Matrix X(A);
  print(X); printf("\n");
  const Matrix B(2);
  X = B;
  print(X); printf("\n");
  fflush(stdout);
}

void test_move()
{
  printf("%s\n", __FUNCSIG__);
  Matrix A(1);
  Matrix X(std::move(A));
  print(X); printf("\n");
  Matrix B(2);
  X = std::move(B);
  print(X); printf("\n");
  fflush(stdout);
}

void test_set(const cs::dim_T i, const cs::dim_T j, const Matrix::value_type value)
{
  printf("%s\n", __FUNCSIG__);
  Matrix M(0);
  M(i,j) = value;
  print(M); printf("\n");
  fflush(stdout);
}

int main(int /*argc*/, char ** /*argv*/)
{
  test_assign_list();
  test_assign_scalar();
  test_copy();
  test_move();
  test_set(1, 1, 7);

  printf("***************************************************************\n");

  print(Matrix({0, 1, 2, 3, 4, 5, 6, 7, 8}) + Matrix({9, 10, 11, 12, 13, 14, 15, 16, 17}),
        "Matrix({0, 1, 2, 3, 4, 5, 6, 7, 8}) + "
        "Matrix({9, 10, 11, 12, 13, 14, 15, 16, 17}) =");

  printf("*******\n");

  Matrix W = Matrix(1) + Matrix(-7) + Matrix(6);
  print(W, "Matrix(1) + Matrix(-7) + Matrix(6) =");

  printf("*******\n");

  W = Matrix(1)*Matrix(2)*Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1});
  print(W, "Matrix(1)*Matrix(2)*Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1}) =");

  printf("*******\n");

#if 0
  using VectorT = cs::Array<double,1,3>;

  const Vector a = {1, 2, 3};
  const Vector b = {4, 5, 6};

  printf("a =\n"); print(VectorT(cs::transpose(a)));
  printf("b =\n"); print(b);

  // __debugbreak();
  const double dot = cs::dot(a, b);
  // __debugbreak();

  printf("a^T o b = %8.3f\n", dot);
#else
  const Vector a = {1, 2, 2};
  print(a, "a =");

  printf("length(a) = %8.3f\n", cs::length(a));

  // __debugbreak();
  const Vector x = cs::normalize(a);
  // __debugbreak();
  print(x, "cs::normalize(a) =");

  const Vector from(1);
  const Vector   to(from + a);
  printf("distance(Vector(1), Vector(1) + {1, 2, 2}) = %8.3f\n",
         cs::distance(from, to));
  print(cs::direction(from, to),
        "direction(Vector(1), Vector(1) + {1, 2, 2}) =");
  print(cs::cross(Vector({1, 2, 3}), Vector(0) + Vector({4, 5, 6})),
        "cross({1, 2, 3}, Vector(0) + {4, 5, 6}) =");
#endif

  return EXIT_SUCCESS;
}
