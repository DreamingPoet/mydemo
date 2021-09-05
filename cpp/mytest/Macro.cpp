// C/C++ Macro 宏定义

// 预处理指令：#define、#include、#ifdef、#else、#endif、#ifndef、#if、#elif、#line、#error、#pragma
// 关键字：_Generic、_Noreturn、_Static_assert
// 函数/宏：sqrt()、atan()、atan2()、exit()、atexit()、assert()、memcpy()、memmove()、va_start()、va_arg()、va_copy()、va_end()

// 预处理 preprocess
// 根据程序中的预处理指令，预处理器把宏名替换成其表示的内容--宏展开（macro expansion）；
// 预处理器指令从#开始运行，到后面的第1个换行符为止(指用Enter按下的换行，而不是 \n)。即：指令的长度仅限于一行；
// 在预处理开始前，编译器会把多行物理行（physical line）处理为一行逻辑行（logical line）。即：找到反斜杠\后面的换行符，把反斜杠和换行符删掉
// 双引号字符串中的文本不会被宏替换！

// 关于 #define 和 const 定义常量
// #define 定义的常量是直接替换，没有类型检查，而 const 有对应的数据类型，有类型检查。
// #define 仅展开，不分配内存；const 会分配内存；#define 定义的常量占用代码段的内存，const 定义的常量占用数据段的内存
// #define 可以通过 #undef 取消再重新定义，const 不能重定义。
// 建议！！！只使用const常量而不使用宏常量。

// 宏定义只做简单的替换，不计算，不对表达式求值
#define PI 3.14   // 定义常量
#define FOUR (2*2)  // 定义表达式
#define SIX (2 * 3)  // 不要求代码中用空格来分隔记号（token：2 * 3 代表三个token，2*3 是一个token）
#define EIGHT (2 \
  *4)    // 反斜杠扩展逻辑行 

// 在#define中使用参数
#define INVSQR(x) (1/((x)*(x))) // 求x平方的倒数
// 建议！！！用()把所有的参数和整个替换体包裹起来
// 建议！！！不要在宏中使用递增或递减运算符(++,--)

// 宏定义中的运算符 #，#@，##，以及宏__VA_ARGS__

// # :把记号(token)转换成字符串
// 例如，如果x是一个宏形参，那么#x就是转换为字符串"x"的形参名。这个过程称为字符串化（stringizing）
#define PRINT_ARG_NANE(x) printf(#x "\n")
#define PRINTSQR(x) printf("The square of " #x " is %d \n", ((x)*(x))) // ANSI C字符串可以自动串联

// ## :连接运算符
#define XNAME(n) x##n // 给传入的宏参数加上一个x前缀 
#define PRINTXN(n) printf("x" #n " is %d \n" , x##n) // 注意其中的x就等于是你键盘敲入的一个x，不代表其他任何东西

// __VA_ARGS__ :是一个宏，作用就是把...表示的参数包，原封不动的抄过去
// ... 表示可变的参数（variadic argument）,包括里面的逗号
// 可变参数不可为空
#define MYPRINT(...) \
        printf(__VA_ARGS__)

// 此处如果可变参数为空，就会出现一个多余的逗号printf(,)会报错
// “##”操作符如果一侧没有内容就会连接失败，并且删除两侧要连接的内容，此处就会删除这个多余的逗号
// 也可""以给可变参数...起个名字，而不用__VA_ARGS__，使用方法和效果是完全一样的
#define DEBUG(fomart, args...) \
        printf("debug: " fomart, ##args)

#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{

    cout << FOUR * (SIX + EIGHT) << endl; // 56
    cout << SIX / EIGHT << endl; // 0
    cout << EIGHT << endl; // 8
    cout << "EIGHT" << endl; // EIGHT 双引号字符串中的文本不会被宏替换
    cout << INVSQR(1) << endl; // 1
    cout << INVSQR(2.f) << endl; // 0.25

    int int_a = 10;
    PRINT_ARG_NANE(int_a); // int_a
    PRINTSQR(int_a); // The square of int_a is 100
    PRINTSQR(4 + 6); // The square of 4 + 6 is 100

    int XNAME(1) = 10; //  展开后：int x1 = 10;
    int XNAME(2) = 20; //  展开后：int x2 = 20;
    int x3 = 30;

    cout << x1 << endl; // 10
    cout << x2 << endl; // 20
    PRINTXN(3); // x3 is 30
    
    MYPRINT("a = %d \n", 5); // a = 5
    DEBUG("a = %d \n", 5); // debug: a = 5
    
    
    return 0;
}