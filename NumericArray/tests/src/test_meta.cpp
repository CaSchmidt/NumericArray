#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <array>
#include <functional>
#include <utility>

#include <cs/Meta.h>

struct MyFor0 {
  template<std::size_t FOR_i>
  inline static void eval()
  {
    std::cout << FOR_i << std::endl;
  }
};

struct MyFor {
  template<std::size_t FOR_i>
  inline static void eval(const char *s, const int& i)
  {
    std::cout << FOR_i << ": " << s << " " << i << std::endl;
  }
};

struct MyDot {
  inline static double accumulate(const double& a, const double& b)
  {
    return a + b;
  }

  template<std::size_t I>
  inline static double eval(const double *a, const double *b)
  {
    return a[I]*b[I];
  }
};

double my_dot(const double *a, const double *b)
{
  return cs::meta::accumulate<double,3,MyDot>(a, b);
}

int main(int /*argc*/, char ** /*argv*/)
{
  cs::meta::for_each<3,MyFor0>();
  cs::meta::for_each<3,MyFor>("Hello, World!", 1);

  std::array<double,3> a{1, 2, 2};
  std::array<double,3> b{1, 2, 2};

  std::cout << "dot = " << my_dot(a.data(), b.data()) << std::endl;

  return EXIT_SUCCESS;
}
