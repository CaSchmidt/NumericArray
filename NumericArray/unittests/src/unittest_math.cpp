#include <iostream>

#include <catch.hpp>

#include "TestEquals.h"
#include "TestFormatter.h"

namespace test_binary {

  extern float test_invSqrt(const float x);
  extern float test_sqrt(const float x);

  extern double test_invSqrt(const double x);
  extern double test_sqrt(const double x);

  TEMPLATE_TEST_CASE("IEEE 754 binary floating point.", "[binary]", float, double) {
    using Fmt = FormatFloatingPoint<char,TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    constexpr TestType epsilon0 = 0x1p-10;

    constexpr TestType four = 4.0;
    constexpr TestType half = 0.5;
    constexpr TestType  two = 2.0;

    std::cout << "epsilon0 = " << Fmt(epsilon0) << std::endl;

    std::cout << "sqrt(" << Fmt(four) << ") = " << Fmt(test_sqrt(four)) << std::endl;
    REQUIRE( equals(test_sqrt(four), two, epsilon0) );

    std::cout << "invSqrt(" << Fmt(four) << ") = " << Fmt(test_invSqrt(four)) << std::endl;
    REQUIRE( equals(test_invSqrt(four), half, epsilon0) );
  }

} // namespace test_binary
