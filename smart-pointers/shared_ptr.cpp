#include <iostream>
#include <thread>

using namespace std;

class foo
{
public:
    foo(int val)
    {
        this->val = val;
    }
    void printsth()
    {
        cout << "foo test" << endl;
    }
private:
    int val;
};

shared_ptr<foo> CreateFoo(int a)
{
    return make_shared<foo>(a);
}

void user1(shared_ptr<foo> f1)
{
    f1->printsth();
}
void user2(shared_ptr<foo> f2)
{
    f2->printsth();
}

int main()
{
    shared_ptr<foo> f = CreateFoo(1);
    thread t1(user1, f);// 计数+1
    thread t2(user2, f);// 计数+1
    // 两个线程用完后,自动释放内存
}