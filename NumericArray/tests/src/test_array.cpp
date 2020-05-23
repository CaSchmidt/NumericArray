#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <cs/NumericArray.h>

using  size_T = uint8_t;
using value_T = double;

using Matrix = cs::NumericArray<value_T,size_T,3,3>;
using Vector = cs::NumericArray<value_T,size_T,3,1>;

Matrix M;
Vector v;

template<typename array_T>
void print(const array_T& array)
{
  using size_type = typename array_T::size_type;
  for(size_type i = 0; i < array.rows(); i++) {
    for(size_type j = 0; j < array.columns(); j++) {
      printf("  %.1f", array(i, j));
    }
    printf("\n");
  }
}

#if 0
void test_gemm(const value_T alpha, const Matrix& A, const Matrix& B,
               const value_T beta, const Matrix& C)
{
  M = alpha*A*B + beta*C;
}
#endif

#if 0
void test_gemv(const value_T alpha, const Matrix& A, const Vector& x,
               const value_T beta, const Vector& y)
{
  v = alpha*(A*x) + beta*y;
}
#endif

#if 0
void test_axpy(const value_T alpha, const Vector&x, const Vector& y)
{
  v = alpha*x + y;
}
#endif

#if 1
void test_copy(const Vector& x)
{
  v = x;
}
#endif

#if 1
void test_set(const value_T v)
{
  ::v = v;
}
#endif

#if 0
value_T test_distance(const Vector& a, const Vector& b)
{
  return cs::distance(a, b);
}
#endif

#if 0
void test_identity()
{
  M = cs::identity<Matrix::traits_type>();
}
#endif

#if 0
void test_identity(const Vector& x)
{
  v = cs::identity<Matrix::traits_type>()*x;
}
#endif

#if 0
void test_scale(const value_T sx, const value_T sy, const value_T sz)
{
  M = cs::scale<Matrix::traits_type>(sx, sy, sz);
}
#endif

#if 0
value_T test_max(const value_T a, const value_T b)
{
  return csMax(a, b);
}
#endif

#if 0
value_T test_min(const value_T a, const value_T b)
{
  return csMin(a, b);
}
#endif

#if 0
value_T test_dot1(const Vector& a, const Vector& b)
{
  return cs::dot1(a, b);
}
#endif

#if 0
void test_clamp(const Vector& x, const value_T lo, const value_T hi)
{
  v = cs::clamp(x, lo, hi);
}
#endif

#if 0
void test_direction(const Vector& from, const Vector& to)
{
  v = cs::direction(from, to);
}
#endif

#if 0
namespace test_manip {

  using Vector3 = cs::Array<cs::Vector3Manip<cs::RowMajorPolicy<cs::ArrayTraits<double,uint8_t,3,1>>>>;

  Vector3 v;

  void test_manip_1()
  {
    v.x = 1;
    v.y = 2;
    v.z = 3;
    //print(v);
  }

} // namespace test_manip
#endif

#if 1
void test_simd(const Vector& a, const Vector& b)
{
  v = a + b;
}
#endif

int main(int /*argc*/, char ** /*argv*/)
{
  //test_manip::test_manip_1();
  //test_identity();
  //test_scale(1, 2, 3);
  //print(M);
  return EXIT_SUCCESS;
}
