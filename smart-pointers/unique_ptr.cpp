#include <iostream>
#include <memory>
using namespace std;
class foo
{
public:
    void printsth()
    {
        cout << "foo test" << endl;
    }
};

int main()
{
    // 正常使用
    foo *f = new foo();
    delete f;   //手动释放内存

    // 使用 unique_ptr
    unique_ptr<foo> p(new foo);
    p->printsth();
    //自动释放内存 
}