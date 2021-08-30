#include <iostream>
#include <stdio.h>

// 可变参数模板，是指能够使用任意数量任意类型参数的函数或类模板
// ... 左侧为参数包（parameter pack ），右侧为展开成多个单独的参数，中间空格任意


// ezprint01
void ezprint() {}

// ezprint02
template <typename T>
void ezprint(const T& arg) {std::cout << arg << std::endl;}

// ezprint03
template <typename T, typename... Types>
void ezprint(const T &first, const Types &...args)
{
    std::cout << first ;
    ezprint(args...);
}

// ezprint04，此模板函数永远不会被调用，但是可以编译通过
// 谁更特化调用谁，总有比04更特化的函数存在
template <typename... Types>
void ezprint(const Types &...args)
{
    ezprint(args...);
}

template<int T1, int T2, typename T3>
void testfun(T1, T2, const T3& c)
{
    std::cout << T1 << T2 << c << std::endl;
}


template<int T4, typename T5>
void testfun(T4, T4, const T5& c)
{
    std::cout << T4 << T4 << c << std::endl;
}

int main()
{

    // ezprint(12334, " asdf");
    // ezprint(12334, " asdf");
    testfun(1,2,"asdf");
    //testfun(1,1,"sdaf");
    return 0;
}