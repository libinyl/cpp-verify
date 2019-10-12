#include <iostream>
#include <vector>
#include <iterator>
#include <string>


class Quote
{
public:
    Quote() = default;
    ~Quote() = default;
    std::string isbn() const;
    virtual double net_price(std::size n) const;
private:
    std::string isbn;
};

class Bulk_quote: public Quote
{
    double net_price(std::size n) const;
};

int main()
{

}