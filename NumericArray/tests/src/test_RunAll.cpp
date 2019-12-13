#include <cstdio>
#include <cstdlib>

#include "Testing.h"

using scalar_T = double;

using Matrix = cs::Array<scalar_T,3,3>;
using Vector = cs::Array<scalar_T,3,1>;

TEST_CASE("NumericArray<> can be copied", "[copy_assign]") {
  const Vector a({1, 2, 3});
  Vector x(a);
  REQUIRE(equals0(x, {1.0, 2.0, 3.0}));

  const Vector b({4, 5, 6});
  x = b;
  REQUIRE(equals0(x, {4.0, 5.0, 6.0}));
}

TEST_CASE("NumericArray<> can be moved", "[move_assign]") {
  Vector a({1, 2, 3});
  Vector x(std::move(a));
  REQUIRE(equals0(x, {1.0, 2.0, 3.0}));

  Vector b({4, 5, 6});
  x = std::move(b);
  REQUIRE(equals0(x, {4.0, 5.0, 6.0}));
}

TEST_CASE("NumericArray<> can be assigned a scalar", "[scalar_assign]") {
  Vector x(1.0);
  REQUIRE(equals0(x, {1.0, 1.0, 1.0}));

  x = 2.0;
  REQUIRE(equals0(x, {2.0, 2.0, 2.0}));
}

TEST_CASE("NumericArray<> can be assigned a list", "[list_assign]") {
  Matrix M({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
  REQUIRE(equals0(M, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}));

  M = {7.0, 8.0, 9.0};
  REQUIRE(equals0(M, {7.0, 8.0, 9.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));
}
