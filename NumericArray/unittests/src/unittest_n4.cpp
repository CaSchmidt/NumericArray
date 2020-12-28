#include <iostream>

#include <catch.hpp>

#include <N4/N4.h>

#include <N4/Math.h> // TODO

using n4::real_t;

struct Vec4fTraits {
  static constexpr bool have_w = true;
};

using Vec4f = n4::Vector4f<Vec4fTraits>;

constexpr real_t W0 = Vec4fTraits::have_w ? 1 : 0;

namespace test_konst {

  constexpr real_t epsilon0 = 0x1p-20;

} // namespace test_konst

namespace test_util {

  inline bool equals(const real_t a, const real_t b,
                     const real_t epsilon0 = test_konst::epsilon0)
  {
    return n4::abs(a - b) <= epsilon0;
  }

  inline bool equals(const Vec4f& v, const std::initializer_list<real_t>& list,
                     const real_t epsilon0 = test_konst::epsilon0)
  {
    if( v.size() != list.size() ) {
      return false;
    }
    for(std::size_t i = 0; i < v.size(); i++) {
      if( !equals(v(i), list.begin()[i], epsilon0) ) {
        return false;
      }
    }
    return true;
  }

  void print(const real_t v, const char *ident = nullptr)
  {
    if( ident != nullptr ) {
      printf("%s = \n", ident);
    }
    printf("%8.3f\n", v);
    printf("\n");
  }

  void print(const Vec4f& v, const char *ident = nullptr)
  {
    if( ident != nullptr ) {
      printf("%s =\n", ident);
    }
    for(std::size_t i = 0; i < v.size(); i++) {
      printf("%8.3f\n", v(i));
    }
    printf("\n");
  }

} // namespace test_util

#define PRINTr(real)  test_util::print(real, #real)
#define PRINTe(expr)  test_util::print(expr, #expr)

namespace test_n4 {

  const Vec4f a{1, 2, 3};
  const Vec4f b{2, 3, 4};

  const Vec4f delta3{1, 2, 2}; // length == 3
  const Vec4f delta5{0, 3, 4}; // length == 5
  const Vec4f delta7{2, 3, 6}; // length == 7

  TEST_CASE("N4 global constants.", "[global]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    PRINTe(a);
    PRINTe(b);
    PRINTr(W0);
  }

  TEST_CASE("N4 binary operators.", "[binary]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(a + b    , {3, 5, 7, W0}              , 0) );
    REQUIRE( test_util::equals(a - b    , {-1, -1, -1, W0}           , 0) );
    REQUIRE( test_util::equals(a * b    , {2, 6, 12, W0}             , 0) );
    REQUIRE( test_util::equals(a / b    , {0.5, 2.0f/3.0f, 0.75, W0})     );
    REQUIRE( test_util::equals(2*a - a  , {1, 2, 3, W0}              , 0) );
    REQUIRE( test_util::equals(a*2 - a  , {1, 2, 3, W0}              , 0) );
    REQUIRE( test_util::equals(4*a/2 - a, {1, 2, 3, W0}              , 0) );
  }

  TEST_CASE("N4 functions.", "[functions]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(n4::cross(a, b)             , {-1, 2, -1, W0}       , 0) );
    REQUIRE( test_util::equals(n4::dot(a, b)               , 20                    , 0) );
    REQUIRE( test_util::equals(n4::length(delta3)          , 3)                         );
    REQUIRE( test_util::equals(n4::distance(a, a + delta7) , 7)                         );
    REQUIRE( test_util::equals(n4::direction(a + delta5, a), {0, -0.6f, -0.8f, W0})     );
    REQUIRE( test_util::equals(n4::normalize(delta5)       , {0, 0.6f, 0.8f, W0})       );
    REQUIRE( test_util::equals(n4::length(n4::normalize(a)), 1)                         );
  }

  TEST_CASE("N4 unary operators.", "[unary]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(+a, {1, 2, 3, W0}   , 0) );
    REQUIRE( test_util::equals(-a, {-1, -2, -3, W0}, 0) );
  }

} // namespace test_n4
