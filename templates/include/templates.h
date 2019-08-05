#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <iostream>

// 用于测试简单函数模板
class Min_util
{
public:
    template<class T>
    T min(T a, T b)
    {
        return a < b ? a : b;
    }
};

// 用于测试简单模板类

template<class T>
class Stack
{
private:
    T buffer[10];
    int offset = -1;
public:
    bool push(const T &t);
    bool pop(T &t);
};


#endif
