#include <cstdio>
#include <cstdlib>

#include <cs/NumericArray.h>

using  size_T = uint8_t;
using value_T = double;

using Matrix = cs::NumericArray<value_T,size_T,3,3>;
using Vector = cs::NumericArray<value_T,size_T,3,1>;

Matrix M;
Vector v;

void test_gemm(const value_T alpha, const Matrix& A, const Matrix& B,
               const value_T beta, const Matrix& C)
{
  M = alpha*A*B + beta*C;
}

void test_gemv(const value_T alpha, const Matrix& A, const Vector& x,
               const value_T beta, const Vector& y)
{
  v = alpha*(A*x) + beta*y;
}

void test_axpy(const value_T alpha, const Vector&x, const Vector& y)
{
  v = alpha*x + y;
}

void test_copy(const Vector& x)
{
  v = x;
}

void test_set(const value_T v)
{
  ::v = v;
}

value_T test_distance(const Vector& a, const Vector& b)
{
  return cs::distance(a, b);
}

void test_identity()
{
  M = cs::identity<Matrix::traits_type>();
}

void test_identity(const Vector& x)
{
  v = cs::identity<Matrix::traits_type>()*x;
}

void test_scale(const value_T sx, const value_T sy, const value_T sz)
{
  M = cs::scale<Matrix::traits_type>(sx, sy, sz);
}

value_T test_max(const value_T a, const value_T b)
{
  return csMax(a, b);
}

value_T test_min(const value_T a, const value_T b)
{
  return csMin(a, b);
}

value_T test_dot1(const Vector& a, const Vector& b)
{
  return cs::dot1(a, b);
}

int main(int /*argc*/, char ** /*argv*/)
{
  //test_identity();
  //test_scale(1, 2, 3);
  /*
  for(size_T i = 0; i < M.rows(); i++) {
    for(size_T j = 0; j < M.columns(); j++) {
      printf("  %.1f", M(i, j));
    }
    printf("\n");
  }
  */
  return EXIT_SUCCESS;
}
