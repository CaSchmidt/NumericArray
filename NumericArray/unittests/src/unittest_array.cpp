//#define TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
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

template<typename value_T, typename size_T, size_T ROWS, size_T COLS>
struct MyTraits {
  using  size_type = cs::if_size_t<size_T>;
  using value_type = cs::if_value_t<value_T>;

  static constexpr size_type Columns = COLS;
  static constexpr size_type    Rows = ROWS;
  static constexpr size_type    Size = COLS*ROWS;
};

template<typename T>
struct FloatInfo {
  // SFINAE
};

template<>
struct FloatInfo<float> {
  static constexpr float epsilon0 = static_cast<float>(0x1p-20);
};

template<>
struct FloatInfo<double> {
  static constexpr double epsilon0 = Konst<double>::epsilon0;
};

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

  TEMPLATE_TEST_CASE("cs::Array<> all binary operations.", "[binary][all]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix I{1,  0, 0, 0, 1, 0, 0, 0, 1};
    const Matrix M{0, -2, 2, 1, 0, 1, 2, 2, 0};
    const Vector x{1, 2, 3};
    const TestType alpha = 2;

    const Vector y = (I*(M*x))/alpha - alpha*x + x;
    REQUIRE( equals0(y, _Values<TestType>{0, 0, 0}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary addition.", "[binary][add]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y1 = x + x;
    REQUIRE( equals0(y1, _Values<TestType>{2, 4, 6}) );

    Vector y2{1, 2, 3};
    y2 += x;
    REQUIRE( equals0(y2, _Values<TestType>{2, 4, 6}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary subtraction.", "[binary][sub]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};

    const Vector y1 = x - x;
    REQUIRE( equals0(y1, _Values<TestType>{0, 0, 0}) );

    Vector y2{1, 2, 3};
    y2 -= x;
    REQUIRE( equals0(y2, _Values<TestType>{0, 0, 0}) );
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

    y = x;
    y *= s;
    REQUIRE( equals0(y, _Values<TestType>{1.5, 3, 4.5}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary scalar division.", "[binary][sdiv]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const TestType s{2};

    const Vector y1 = x/s;
    REQUIRE( equals0(y1, _Values<TestType>{0.5, 1, 1.5}) );

    Vector y2{1, 2, 3};
    y2 /= s;
    REQUIRE( equals0(y2, _Values<TestType>{0.5, 1, 1.5}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> binary element-wise product.", "[binary][product]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector a{1, 2, 3};
    const Vector b{2, 3, 4};

    const Vector y1 = a%b;
    REQUIRE( equals0(y1, _Values<TestType>{2, 6, 12}) );

    Vector y2{1, 2, 3};
    y2 %= b;
    REQUIRE( equals0(y2, _Values<TestType>{2, 6, 12}) );
  }

} // namespace test_binary

namespace test_function {

  TEMPLATE_TEST_CASE("cs::Array<> function array_cast().", "[function][cast]", float, double) {
    using Vector = _Vector<TestType>;
    using MyVector = cs::Array<cs::RowMajorPolicy<MyTraits<TestType,size_T,3,1>>>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const MyVector x1{1, 2, 3};
    const Vector x2{1, 2, 3};

    const Vector y2 = cs::array_cast<Vector::traits_type>(x1) + x2;
    REQUIRE( equals0(y2, _Values<TestType>{2, 4, 6}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function clamp().", "[function][clamp]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const TestType lo{1.5}, hi{2.5};

    const Vector y = cs::clamp(x, lo, hi);
    REQUIRE( equals0(y, _Values<TestType>{1.5, 2, 2.5}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function cross().", "[function][cross]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 3};
    const Vector y{4, 5, 6};

    const Vector z = cs::cross(x, y);
    REQUIRE( equals0(z, _Values<TestType>{-3, 6, -3}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function determinant().", "[function][determinant]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M{3, 1, 1, 5, 2, 1, 3, 1, 2};

    const TestType y = cs::determinant(M);
    REQUIRE( equals0(y, TestType{1}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function direction().", "[function][direction]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector o{1, 2, 3};
    const Vector x{1, 2, 2};

    const Vector y = cs::direction(o, o + x);
    REQUIRE( equals(y, _Values<TestType>{.333333333, .666666666, .666666666},
                    FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function distance().", "[function][distance]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector o{1, 2, 3};
    const Vector x{1, 2, 2};

    const TestType y = cs::distance(o, o + x);
    REQUIRE( equals(y, TestType{3}, FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function dot().", "[function][dot]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 2};

    const TestType y = cs::dot(x, x);
    REQUIRE( y == TestType{9} );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function inverse().", "[function][inverse]", float, double) {
    using Matrix = _Matrix<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M{3, 1, 1, 5, 2, 1, 3, 1, 2};

    const Matrix Minv = cs::inverse(M);
    REQUIRE( equals(Minv, _Values<TestType>{3, -1, -1, -7, 3, 2, -1, 0, 1},
                    FloatInfo<TestType>::epsilon0) );

    const Matrix I = M*Minv;
    REQUIRE( equals(I, _Values<TestType>{1, 0, 0, 0, 1, 0, 0, 0, 1},
                    FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function length().", "[function][length]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 2};

    const TestType y = cs::length(x);
    REQUIRE( equals(y, TestType{3}, FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function normalize().", "[function][normalize]", float, double) {
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Vector x{1, 2, 2};

    const Vector y = cs::normalize(x);
    REQUIRE( equals(y, _Values<TestType>{.333333333, .666666666, .666666666},
                    FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> function transpose().", "[function][transpose]", float, double) {
    using Matrix23 = cs::NumericArray<TestType,size_T,2,3>;
    using Matrix32 = cs::NumericArray<TestType,size_T,3,2>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix23 X{1, 2, 3, 4, 5, 6};

    const Matrix32 Y = cs::transpose(X);
    REQUIRE( (Y.rows() == X.columns()  &&  Y.columns() == X.rows()  &&
              equals0(Y, _Values<TestType>{1, 4, 2, 5, 3, 6}) ) );
  }

} // namespace test_function

namespace test_geometry {

  TEMPLATE_TEST_CASE("cs::Array<> identity() matrix.", "[geometry][identity]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M = cs::identity<Matrix::traits_type>();
    const Vector x{1, 2, 3};

    const Vector y = M*x;
    REQUIRE( equals0(y, _Values<TestType>{1, 2, 3}) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> rotateX() matrix.", "[geometry][rotatex]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix Rx = cs::rotateX<Matrix::traits_type>(Konst<TestType>::PI/2);
    const Vector y0 = cs::yAxis<Vector::traits_type>();
    const Vector z0 = cs::zAxis<Vector::traits_type>();

    const Vector a = Rx*y0;
    REQUIRE( equals(a, _Values<TestType>{0, 0, 1}, FloatInfo<TestType>::epsilon0) );

    const Vector b = Rx*z0;
    REQUIRE( equals(b, _Values<TestType>{0, -1, 0}, FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> rotateY() matrix.", "[geometry][rotatey]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix Ry = cs::rotateY<Matrix::traits_type>(Konst<TestType>::PI/2);
    const Vector x0 = cs::xAxis<Vector::traits_type>();
    const Vector z0 = cs::zAxis<Vector::traits_type>();

    const Vector a = Ry*x0;
    REQUIRE( equals(a, _Values<TestType>{0, 0, -1}, FloatInfo<TestType>::epsilon0) );

    const Vector b = Ry*z0;
    REQUIRE( equals(b, _Values<TestType>{1, 0, 0}, FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> rotateZ() matrix.", "[geometry][rotatez]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix Rz = cs::rotateZ<Matrix::traits_type>(Konst<TestType>::PI/2);
    const Vector x0 = cs::xAxis<Vector::traits_type>();
    const Vector y0 = cs::yAxis<Vector::traits_type>();

    const Vector a = Rz*x0;
    REQUIRE( equals(a, _Values<TestType>{0, 1, 0}, FloatInfo<TestType>::epsilon0) );

    const Vector b = Rz*y0;
    REQUIRE( equals(b, _Values<TestType>{-1, 0, 0}, FloatInfo<TestType>::epsilon0) );
  }

  TEMPLATE_TEST_CASE("cs::Array<> scale() matrix.", "[geometry][scale]", float, double) {
    using Matrix = _Matrix<TestType>;
    using Vector = _Vector<TestType>;

    std::cout << "*** " << Catch::getResultCapture().getCurrentTestName() << std::endl;

    const Matrix M = cs::scale<Matrix::traits_type>(2, 3, 4);
    const Vector x{1, 2, 3};

    const Vector y = M*x;
    REQUIRE( equals0(y, _Values<TestType>{2, 6, 12}) );
  }

} // namespace test_geometry

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
