#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "TestArrayEqual.h"

using  size_T = uint8_t;

template<typename value_T>
using _Matrix = cs::NumericArray<value_T,size_T,3,3>;
template<typename value_T>
using _Vector = cs::NumericArray<value_T,size_T,3,1>;

template<typename value_T>
using _Values = std::initializer_list<value_T>;

namespace impl {

  template<typename value_T>
  _Matrix<value_T> create()
  {
    _Matrix<value_T> M;
    M(0,0) = 1;  M(0,1) = 2;  M(0,2) = 3;
    M(1,0) = 4;  M(1,1) = 5;  M(1,2) = 6;
    M(2,0) = 7;  M(2,1) = 8;  M(2,2) = 9;
    return M;
  }

} // namespace impl

namespace test_assign {

  TEMPLATE_TEST_CASE("cs::Array<> copy assignment.", "[assign][copy]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M = impl::create<TestType>();

    const Matrix M1(M);
    REQUIRE( equals0(M1, _Values<TestType>{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    const Matrix M2 = M;
    REQUIRE( equals0(M2, _Values<TestType>{1, 2, 3, 4, 5, 6, 7, 8, 9}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> move assignment.", "[assign][move]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    Matrix M;

    M = impl::create<TestType>();
    const Matrix M1(std::move(M));
    REQUIRE( equals0(M1, _Values<TestType>{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    M = impl::create<TestType>();
    Matrix M2;
    M2 = std::move(M);
    REQUIRE( equals0(M2, _Values<TestType>{1, 2, 3, 4, 5, 6, 7, 8, 9}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> scalar assignment.", "[assign][scalar]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M1(1);
    REQUIRE( equals0(M1, _Values<TestType>{1, 1, 1, 1, 1, 1, 1, 1, 1}) );

    const Matrix M2 = 2;
    REQUIRE( equals0(M2, _Values<TestType>{2, 2, 2, 2, 2, 2, 2, 2, 2}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> list assignment.", "[assign][list]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE( equals0(M1, _Values<TestType>{1, 2, 3, 4, 5, 6, 7, 8, 9}) );

    const Matrix M2 = {1, 2, 3, 4, 5, 6};
    REQUIRE( equals0(M2, _Values<TestType>{1, 2, 3, 4, 5, 6, 0, 0, 0}) );
  }

} // namespace test_assign

namespace test_binary {

  TEMPLATE_TEST_CASE("cs::Array<> binary addition.", "[binary][add]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = x + x;
    REQUIRE( equals0(y, _Values<TestType>{2, 4, 6}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary subtraction.", "[binary][sub]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = x - x;
    REQUIRE( equals0(y, _Values<TestType>{0, 0, 0}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary multiplication.", "[binary][mul]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix X{1, 2, 3, 4, 5, 6, 7, 8, 9};

    const Matrix Y = X*X;
    REQUIRE( equals0(Y, _Values<TestType>{30, 36, 42, 66, 81, 96, 102, 126, 150}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary scalar multiplication.", "[binary][smul]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const TestType s{1.5};
    Vector y;

    y = x*s;
    REQUIRE( equals0(y, _Values<TestType>{1.5, 3, 4.5}) );

    y = s*x;
    REQUIRE( equals0(y, _Values<TestType>{1.5, 3, 4.5}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary scalar division.", "[binary][sdiv]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const TestType s{2};

    const Vector y = x/s;
    REQUIRE( equals0(y, _Values<TestType>{0.5, 1, 1.5}) );
  }

} // namespace test_binary

namespace test_unary {

  TEMPLATE_TEST_CASE("cs::Array<> unary plus.", "[unary][plus]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = +x;
    REQUIRE( equals0(y, _Values<TestType>{1, 2, 3}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> unary minus.", "[unary][minus]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y = -x;
    REQUIRE( equals0(y, _Values<TestType>{-1, -2, -3}) );
  }

} // namespace test_unary
