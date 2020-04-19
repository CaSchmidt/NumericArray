#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "TestArrayEqual.h"

using  Vector = cs::NumericArray<double,uint8_t,3,1>;
using value_T = Vector::value_type;

using Values = std::initializer_list<value_T>;

namespace test_unary {

  TEST_CASE("cs::Array<> unary plus.", "[unary][plus]") {
    const Vector x{1, 2, 3};

    const Vector y = +x;
    REQUIRE( equals0(y, Values{1, 2, 3}) );
  }

  TEST_CASE("cs::Array<> unary minus.", "[unary][minus]") {
    const Vector x{1, 2, 3};

    const Vector y = -x;
    REQUIRE( equals0(y, Values{-1, -2, -3}) );
  }

} // namespace test_unary
