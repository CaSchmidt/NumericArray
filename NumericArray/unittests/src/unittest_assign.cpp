#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "TestArrayEqual.h"

using  Matrix = cs::NumericArray<double,uint8_t,3,3>;
using value_T = Matrix::value_type;

using Values = std::initializer_list<value_T>;

namespace impl {

  Matrix create()
  {
    Matrix M;
    M(0,0) = 1;  M(0,1) = 2;  M(0,2) = 3;
    M(1,0) = 4;  M(1,1) = 5;  M(1,2) = 6;
    M(2,0) = 7;  M(2,1) = 8;  M(2,2) = 9;
    return M;
  }

} // namespace impl

namespace test_assign {

  TEST_CASE("cs::Array<> copy assignment.", "[assign][copy]") {
    const Matrix M = impl::create();

    const Matrix M1(M);
    REQUIRE( equals0(M1, Values{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    const Matrix M2 = M;
    REQUIRE( equals0(M2, Values{1, 2, 3, 4, 5, 6, 7, 8, 9}) );
  }

  TEST_CASE("cs::Array<> move assignment.", "[assign][move]") {
    Matrix M;

    M = impl::create();
    const Matrix M1(std::move(M));
    REQUIRE( equals0(M1, Values{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    M = impl::create();
    Matrix M2;
    M2 = std::move(M);
    REQUIRE( equals0(M2, Values{1, 2, 3, 4, 5, 6, 7, 8, 9}) );
  }

  TEST_CASE("cs::Array<> scalar assignment.", "[assign][scalar]") {
    const Matrix M1(1);
    REQUIRE( equals0(M1, Values{1, 1, 1, 1, 1, 1, 1, 1, 1}) );

    const Matrix M2 = 2;
    REQUIRE( equals0(M2, Values{2, 2, 2, 2, 2, 2, 2, 2, 2}) );
  }

  TEST_CASE("cs::Array<> list assignment.", "[assign][list]") {
    const Matrix M1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE( equals0(M1, Values{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    const Matrix M2 = {1, 2, 3, 4, 5, 6};
    REQUIRE( equals0(M2, Values{1, 2, 3, 4, 5, 6, 0, 0, 0}) );
  }

} // namespace test_assign
