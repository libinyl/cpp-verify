#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

/**
 * 1. 专门用于较大算数类型赋值给较小算数类型.
 *    显式地告知编译器,程序员确实不在乎精度损失,于是编译器不再警告.
 * 2. 用于从 void*类型转换为其他指针类型时,指定 void*指针的长度,避免未定义的bian
 *
 */

int main()
{

    double v = 1.04;

    /**
     * 编译告警:
     * warning: implicit conversion from 'double' to 'int' changes value
     * from 1.04 to 1 [-Wliteral-conversion]
     *
     */
    int a = v;

    // 显式转换,无告警
    int b = static_cast<int>(v);

    /**************************************/


    void *p = &a;

    /**
     * 编译错误, 不可以用 void *类型初始化整型指针 ,因为不知道 p 的长度,结果未定义
     * error: cannot initialize a variable of type 'int *' with an lvalue of type 'void *'
     */
    //int *c = p;
    int *c = static_cast<int *>(p);// 正确,指定 p 的转换长度与其原来的长度相同

    cout << a << endl;
}