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

int main(int /*argc*/, char ** /*argv*/)
{
  return EXIT_SUCCESS;
}
