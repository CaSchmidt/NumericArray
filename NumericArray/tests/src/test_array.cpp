#include <cstdio>
#include <cstdlib>

#include <cs/NumericArray.h>

using  size_T = uint8_t;
using value_T = double;

using Matrix = cs::NumericArray<value_T,size_T,3,3>;
using Vector = cs::NumericArray<value_T,size_T,3,1>;

Matrix M;
Vector v;

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

int main(int /*argc*/, char ** /*argv*/)
{
  return EXIT_SUCCESS;
}
