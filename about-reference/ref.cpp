#include <chrono>
#include <iostream>
class A
{
    char buf[1024 * 1024] = {'\0'};
    char buf1[1024 * 512] = {'\0'};
};
A callee_val(A a)
{
    return a;
}
A &callee_ref(A &a)
{
    return a;
}

void caller(bool pass_by_value)
{
    A _a;
    A b = pass_by_value ? callee_val(_a) : callee_ref(_a);
}


using namespace std;
using namespace chrono;
int main()
{
    auto s1 = system_clock::now();
    caller(true);
    auto e1 = system_clock::now();
    auto t1 = duration_cast<nanoseconds>(e1 - s1);

    auto s2 = system_clock::now();
    caller(false);
    auto e2 = system_clock::now();
    auto t2 = duration_cast<nanoseconds>(e2 - s2);

    cout << "pass by value 耗时 " << t1.count() << " ns;" << endl;
    cout << "pass by reference 耗时 " << t2.count() << " ns;" << endl;
    return 0;
}
