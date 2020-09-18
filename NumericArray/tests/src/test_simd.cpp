#include <cstdio>
#include <cstdlib>

#include <cs/NumericTraits.h>

struct PolicyA {};
struct PolicyB {};

template<typename child_T>
struct Expression {};

template<typename child_T>
struct SIMDexpr {
  using child_type = child_T;

  template<typename simd_policy_T>
  static constexpr bool is_simd()
  {
    return cs::check_simd<child_type,simd_policy_T>();
  }

  int block(const int i) const
  {
    return i;
  }
};

template<typename policy_T>
struct Array {
  using policy_type = policy_T;

  template<typename simd_policy_T>
  static constexpr bool is_simd()
  {
    return std::is_same_v<simd_policy_T,policy_type>;
  }

  int block(const int i) const
  {
    return i;
  }
};

template<typename expr_T, typename policy_T>
void check(const int i)
{
  printf("check %2d: ", i);
  if constexpr( cs::check_simd<expr_T,policy_T>() ) {
    printf("SIMD\n");
  } else {
    printf("no SIMD\n");
  }
}

int main(int /*argc*/, char ** /*argv*/)
{
  check<Array<PolicyA>,PolicyA>(1);
  check<Array<PolicyA>,PolicyB>(2);

  check<SIMDexpr<Array<PolicyA>>,PolicyA>(3);
  check<SIMDexpr<Array<PolicyA>>,PolicyB>(4);

  check<Expression<Array<PolicyA>>,PolicyA>(3);
  check<Expression<Array<PolicyA>>,PolicyB>(4);

  check<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<Array<PolicyA>>>>>,PolicyA>(5);
  check<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<Array<PolicyA>>>>>,PolicyB>(5);

  check<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<Array<PolicyA>>>>>>>>>>,PolicyA>(10);
  check<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<SIMDexpr<Array<PolicyA>>>>>>>>>>,PolicyB>(10);

  return EXIT_SUCCESS;
}
