#include "include/templates.h"
#include <iostream>

void test_template_function()
{
    int a = 5, b = 6;
    float c = 1.1, d = 2.2;
    Min_util m;
    // 类型信息可以省略.
    std::cout << "整数较小值: " << m.min(a, b) << std::endl;
    std::cout << "整数较小值: " << m.min<int>(a, b) << std::endl;
    std::cout << "浮点数较小值(指定浮点类型): " << m.min<float>(c, d) << std::endl;
    std::cout << "浮点数较小值(指定整数类型): " << m.min<int>(c, d) << std::endl; // 注意,如果用参数为 int 类型的 min 函数,浮点数会被截断,损失精度
}

int main()
{

    test_template_function();
}