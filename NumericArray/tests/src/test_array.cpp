#include <cstdio>
#include <cstdlib>

#include <cs/NumericArray.h>

using value_T = double;
using  size_T = uint8_t;

using Vector = cs::NumericArray<value_T,size_T,3,1>;
using Matrix = cs::NumericArray<value_T,size_T,3,3>;

/*
void test_axpy(const value_T alpha, const Vector& x, const Vector& y)
{
  const Vector z = alpha*x + y;
}
*/

Vector y;

void test_copy(const Vector& x)
{
  y = x;
}

void test_set(const value_T v)
{
  y = v;
}

int main(int argc, char **argv)
{
  return EXIT_SUCCESS;
}
