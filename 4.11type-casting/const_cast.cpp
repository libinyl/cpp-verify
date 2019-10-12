#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

/**
 * const_cast 用于改变对象的*底层* const 属性.去掉(cast away the const)或添加 const 属性.
 * 参考 4.11.3 和 6.4 节p209
 *
 * 重要: 只能改变属性,不能改变类型.
 *
 * 由此 const 的意义也就凸显出来.当存在一个 const 对象时以及对它的引用const p 时,无法改变它;
 * 需要用 const_cast返回一个对这个 const 对象的非 const 指针,这时就确实可以改变它的值了.
 * 注意,与直觉不同,转换结果没有对原对象进行复制.用新指针更改数据,原对象确实改变.
 *
 */
class Integer
{
public:
    explicit Integer(int i)
    {
        this->a = i;
    }
    void set(int i)
    {
        this->a = i;
    }
    void printVal() const
    {
        cout << a << endl;
    }
private:
    int a;
};

int main()
{
    const Integer i(1);
    //i.set(5); 错误,不可对 const 对象赋值
    //Integer m = const_cast<Integer>(i); 错误,只能改变*底层*const 的属性
    Integer *p = const_cast<Integer *>(&i);// 正确
    p->set(4);
    i.printVal();

}