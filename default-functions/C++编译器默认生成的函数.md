## 默认类成员函数

若不显示指明,C++编译器会为类生成以下函数:

- 构造函数
- 析构函数
- 拷贝构造函数
- 拷贝赋值函数
- 移动构造函数

同时还会生成全局默认操作符函数:

- operator
- operator,
- operator &
- operator &&
- operator *
- operator->
- operator->*
- operator new
- operator delete

### 参考

https://blog.csdn.net/lixiaogang_theanswer/article/details/81090622