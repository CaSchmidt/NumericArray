// cf. https://fekir.info/post/detect-member-variables/

#include <cstdio>
#include <cstdlib>

#include <type_traits>

template<typename T, typename = bool>
struct if_simd : std::false_type { };

template<typename T>
struct if_simd<T,decltype((void)T::is_simd,std::declval<T>().block(0),bool())> : std::true_type { };

template<typename T>
inline constexpr bool if_simd_v = if_simd<T>::value;

template<typename T>
constexpr std::enable_if_t<if_simd_v<T>,bool> check_simd()
{
  return static_cast<bool>(T::is_simd);
}

template<typename T>
constexpr std::enable_if_t<!if_simd_v<T>,bool> check_simd()
{
  return false;
}

struct A {
#if 1
  static inline constexpr bool is_simd = true;
#else
  static constexpr bool is_simd() 
  {
    return true;
  }
#endif

  constexpr int block(int) const
  {
    return 0;
  }
};

struct B {
};

template<typename T>
struct C {
#if 1
  static inline constexpr bool is_simd = check_simd<T>();
#else
  static constexpr bool is_simd() 
  {
    return check_simd<T>();
  }
#endif

  int block(int) const
  {
    return 0;
  }

  T t;
};

int main(int, char**)
{
  if constexpr( check_simd<A>() ) {
    printf("A\n");
  }
  if constexpr( check_simd<B>() ) {
    printf("B\n");
  }
  if constexpr( check_simd< C<C<A>> >() ) {
    printf("C\n");
  }
  return EXIT_SUCCESS;
}
