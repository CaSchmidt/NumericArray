#include <iostream>

#include <catch.hpp>

#include <N4/N4.h>

using n4::real_t;

struct Vec4fTraits {
  static constexpr bool have_w = true;
};

using Vec4f = n4::Vector4f<Vec4fTraits>;

constexpr real_t W0 = Vec4fTraits::have_w ? 1 : 0;

using Mat4f = n4::Matrix4f;

namespace test_konst {

  constexpr real_t epsilon0 = 0x1p-20;

} // namespace test_konst

namespace test_util {

  bool equals(const real_t a, const real_t b,
              const real_t epsilon0 = test_konst::epsilon0)
  {
    return n4::abs(a - b) <= epsilon0;
  }

  bool equals(const Vec4f& v, const std::initializer_list<real_t>& list,
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

  bool equals(const Mat4f& M, const std::initializer_list<real_t>& list,
              const real_t epsilon0 = test_konst::epsilon0)
  {
    if( M.size() != list.size() ) {
      return false;
    }
    for(std::size_t l = 0; l < list.size(); l++) {
      // NOTE: Row-Major Notation: l = i*4 + j
      const std::size_t i = l/4;
      const std::size_t j = l%4;
      if( !equals(M(i, j), list.begin()[l], epsilon0) ) {
        return false;
      }
    }
    return true;
  }

  bool equals(const Mat4f& A, const Mat4f& B,
              const real_t epsilon0 = test_konst::epsilon0)
  {
    for(std::size_t l = 0; l < A.size(); l++) {
      if( !equals(A.data()[l], B.data()[l], epsilon0) ) {
        return false;
      }
    }
    return true;
  }

  inline void do_print(const real_t x)
  {
    if( n4::abs(x) == real_t(0) ) {
      printf("%8.3f", 0.0);
    } else {
      printf("%8.3f", x);
    }
  }

  void print(const real_t v, const char *ident = nullptr)
  {
    if( ident != nullptr ) {
      printf("%s = \n", ident);
    }
    do_print(v); printf("\n");
    printf("\n");
    fflush(stdout);
  }

  void print(const Vec4f& v, const char *ident = nullptr)
  {
    if( ident != nullptr ) {
      printf("%s =\n", ident);
    }
    for(std::size_t i = 0; i < v.size(); i++) {
      do_print(v(i)); printf("\n");
    }
    printf("\n");
    fflush(stdout);
  }

  void print(const Mat4f& M, const char *ident = nullptr)
  {
    if( ident != nullptr ) {
      printf("%s =\n", ident);
    }
    for(std::size_t i = 0; i < M.rows(); i++) {
      for(std::size_t j = 0; j < M.columns(); j++) {
        printf("  "); do_print(M(i, j));
      }
      printf("\n");
    }
    printf("\n");
    fflush(stdout);
  }

} // namespace test_util

#define PRINTreal(real)  test_util::print(real, #real)
#define PRINTexpr(expr)  test_util::print(expr, #expr)
#define PRINTmatr(matr)  test_util::print(matr, #matr)

namespace test_n4 {

  ////// Begin Global Constants //////////////////////////////////////////////

  const Vec4f a{1, 2, 3};
  const Vec4f b{2, 3, 4};

  const Vec4f delta3{1, 2, 2}; // length == 3
  const Vec4f delta5{0, 3, 4}; // length == 5
  const Vec4f delta7{2, 3, 6}; // length == 7

  const Mat4f M{
     0,  1,  2,  3,
     4,  5,  6,  7,
     8,  9, 10, 11,
    12, 13, 14, 15
  };

  ////// End Global Constants ////////////////////////////////////////////////

  TEST_CASE("N4 global constants.", "[N4][global]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    PRINTexpr(a);
    PRINTexpr(b);
    PRINTreal(W0);
    PRINTmatr(M);
  }

  TEST_CASE("N4 Vector4f binary operators.", "[Vector4f][binary]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(a + b    , {3, 5, 7, W0}                              , 0) );
    REQUIRE( test_util::equals(a - b    , {-1, -1, -1, W0}                           , 0) );
    REQUIRE( test_util::equals(a * b    , {2, 6, 12, W0}                             , 0) );
    REQUIRE( test_util::equals(a / b    , {0.5, 0.666666f, 0.75, W0}                    ) );
    REQUIRE( test_util::equals(2*a - a  , {1, 2, 3, W0}                              , 0) );
    REQUIRE( test_util::equals(a*2 - a  , {1, 2, 3, W0}                              , 0) );
    REQUIRE( test_util::equals(4*a/2 - a, {1, 2, 3, W0}                              , 0) );
    REQUIRE( test_util::equals(6/a,       {6, 3, 2, W0}                              , 0) );
    REQUIRE( test_util::equals(n4::translate(1, 1, 1)*a, {1 + W0, 2 + W0, 3 + W0, W0}, 0) );
  }

  TEST_CASE("N4 Vector4f functions.", "[Vector4f][functions]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(n4::cross(a, b)             , {-1, 2, -1, W0}       , 0) );
    REQUIRE( test_util::equals(n4::dot(a, b)               , 20                    , 0) );
    REQUIRE( test_util::equals(n4::length(delta3)          , 3)                         );
    REQUIRE( test_util::equals(n4::distance(a, a + delta7) , 7)                         );
    REQUIRE( test_util::equals(n4::direction(a + delta5, a), {0, -0.6f, -0.8f, W0})     );
    REQUIRE( test_util::equals(n4::normalize(delta5)       , {0, 0.6f, 0.8f, W0})       );
    REQUIRE( test_util::equals(n4::length(n4::normalize(a)), 1)                         );
  }

  TEST_CASE("N4 Vector4f unary operators.", "[Vector4f][unary]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(+a, {1, 2, 3, W0}   , 0) );
    REQUIRE( test_util::equals(-a, {-1, -2, -3, W0}, 0) );
  }

  TEST_CASE("N4 Matrix4f functions.", "[Matrix4f][functions]") {
    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    REQUIRE( test_util::equals(M.transpose(), {  0, 4,  8, 12,
                                                 1, 5,  9, 13,
                                                 2, 6, 10, 14,
                                                 3, 7, 11, 15 }) );

    const Mat4f M1{
      1, 0, 0, 0,
      0, 0, 1, 0,
      0, 1, 0, 0,
      0, 0, 0, 1
    };
    PRINTmatr(M1);

    REQUIRE( test_util::equals(M1.inverse(), { 1, 0, 0, 0,
                                               0, 0, 1, 0,
                                               0, 1, 0, 0,
                                               0, 0, 0, 1 }) );

    const Mat4f M2{
      4, 0, 0, 0,
      0, 0, 2, 0,
      0, 1, 2, 0,
      1, 0, 0, 1
    };
    PRINTmatr(M2);

    REQUIRE( test_util::equals(M2.inverse(), {  0.25, 0,   0, 0,
                                                0,   -1,   1, 0,
                                                0,    0.5, 0, 0,
                                               -0.25, 0,   0, 1 }) );

    const Mat4f Rx{ // Rotate 90° about x-axis
      1, 0,  0, 0,
      0, 0, -1, 0,
      0, 1,  0, 0,
      0, 0,  0, 1
    };
    PRINTmatr(Rx);

    REQUIRE( test_util::equals(Rx.inverse(), Rx.transpose()) );
  }

} // namespace test_n4
