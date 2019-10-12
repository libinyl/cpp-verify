#include <iostream>
using namespace std;
/**
 * string 的移动语义
 * 移动语义去除了拷贝的开销,直接更改对象对内存的引用,提升性能
 *
 * @return
 */

int main()
{
    string a = "123";
    string b(move(a));  // 假定 a 不再使用,移动到 b.这里是传入的是 a 的右值引用.
    cout << a << endl;  // a移动到了 b,输出为空,没有报错
    cout << b << endl;
}