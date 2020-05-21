// cf. https://fekir.info/post/detect-member-variables/

#include <cstdio>
#include <cstdlib>

#include <type_traits>

template<typename T, typename = void>
struct if_member : std::false_type {};

template<typename T>
struct if_member<T,decltype((void)T::member,void())> : std::true_type {};

template<typename T>
inline constexpr bool if_member_v = if_member<T>::value;

struct A {
    static constexpr int member = 1;
};

struct B {
};

template<typename T>
void print(const T& t)
{
    if constexpr( if_member_v<T> ) {
        printf("member\n");
    } else {
        printf("no member\n");
    }
}

int main(int,char**)
{
    A a;
    B b;
    print(a);
    print(b);
    return EXIT_SUCCESS;
}
