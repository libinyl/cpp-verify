#include <iostream>


class Base
{
public:
    int publicmember = 1;       // 能访问 Base 的,就能访问 publicmember
protected:
    int protectedmember = 2;    // 只有 Base 的派生类能访问 protectedmember
private:
    int privatememberr = 3;      // 只有 Base 自己能访问 privatemember
};

class Pub: public Base
{
    // publicmember is public
    // protectedmember is protected
    // privatemember is not accessable

public:
    void printmem()
    {
        std::cout << "publicmmeber in Pub:" << publicmember << std::endl;
        std::cout << "protectedmember in Pub:" << protectedmember << std::endl;
        // std::cout<<"privatemember in Pub:"<<privatemember<<std::endl; // error: use of undeclared identifier 'privatemember
    }
};

class Prot: protected Base
{
    // publicmember is protected
    // protectedmember is protected
    // privatemember is not accessable
public:
    void printmem()
    {
        std::cout << "publicmmeber in Prot:" << publicmember << std::endl;
        std::cout << "protectedmember in Prot:" << protectedmember << std::endl;
        //std::cout<<"privatemember in Prot:"<<privatemember<<std::endl;// error: use of undeclared identifier 'privatemember
    }
};

class Priv: private Base
{
    // publicmember is private
    // protectedmember is private
    // privatemember is not accessable
public:
    void printmem()
    {
        std::cout << "publicmmeber in Priv:" << publicmember << std::endl;
        std::cout << "protectedmember in Priv:" << protectedmember << std::endl;
        // std::cout<<"privatemember in Priv:"<<privatemember<<std::endl;//error: use of undeclared identifier 'privatemember
    }
};
class Noaccess: Base
{
public:
    void printmem()
    {
        std::cout << "publicmmeber in Noaccess:" << publicmember << std::endl;
        std::cout << "protectedmember in Noaccess:" << protectedmember << std::endl;
        //std::cout<<"privatemember in Noaccess:"<<privatemember<<std::endl;//error: use of undeclared identifier 'privatemember
    }
};

int main()
{
    Base bs;

    Pub pb;
    Priv pr;

    /***Base class member***/
    std::cout << "public member value of Base class:" << bs.publicmember << std::endl;
    /*
    std::cout << "protected member value of Base class:" << bs.protectedmember
              << std::endl;// error: 'protectedmember' is a protected member of 'Base'
    std::cout << "private member value of Base class:" << bs.privatememberr
              << std::endl;//error: 'privatemember' is a private member of 'Base'
    */


    /***Pub class member***/
    std::cout << "public member value of Pub class:" << pb.publicmember << std::endl;
    /*
    std::cout << "protected member value of Pub class:" << pb.protectedmember
              << std::endl;// error: 'protectedmember' is a protected member of 'Base'
    std::cout << "private member value of Pub class:" << pb.privatememberr
              << std::endl;//error: 'privatemember' is a private member of 'Base'
    */

    /***Priv class member***/
    /*
    std::cout << "public member value of Priv class:" << pr.publicmember
              << std::endl;//error: cannot cast 'Priv' to its private base class 'Base'
    std::cout << "protected member value of Priv class:" << pr.protectedmember
              << std::endl;//error: cannot cast 'Priv' to its private base class 'Base'
    std::cout << "private member value of Priv class:" << pr.privatememberr
              << std::endl;//error: cannot cast 'Priv' to its private base class 'Base'
    */

}