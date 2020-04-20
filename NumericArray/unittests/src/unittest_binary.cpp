#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "TestArrayEqual.h"

using value_T = double;
using  size_T = uint8_t;

template<typename value_T>
using _Matrix = cs::NumericArray<value_T,size_T,3,3>;
template<typename value_T>
using _Vector = cs::NumericArray<value_T,size_T,3,1>;

template<typename value_T>
using _Values = std::initializer_list<value_T>;

using Matrix = _Matrix<value_T>;
using Vector = _Vector<value_T>;
using Values = _Values<value_T>;

namespace test_unary {

  TEST_CASE("cs::Array<> binary addition.", "[binary][add]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = x + x;
    REQUIRE( equals0(y, Values{2, 4, 6}) );
  }

  TEST_CASE("cs::Array<> binary subtraction.", "[binary][sub]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = x - x;
    REQUIRE( equals0(y, Values{0, 0, 0}) );
  }

  TEST_CASE("cs::Array<> binary scalar multiplication.", "[binary][smul]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const value_T s{1.5};
    Vector y;

    y = x*s;
    REQUIRE( equals0(y, Values{1.5, 3, 4.5}) );

    y = s*x;
    REQUIRE( equals0(y, Values{1.5, 3, 4.5}) );
  }

  TEST_CASE("cs::Array<> binary scalar division.", "[binary][sdiv]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const value_T s{2};

    const Vector y = x/s;
    REQUIRE( equals0(y, Values{0.5, 1, 1.5}) );
  }

} // namespace test_unary
