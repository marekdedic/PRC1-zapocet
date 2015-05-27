#include "../Main.hpp"
using namespace std;


BigInt::BigInt() : digits{}
{}

BigInt::BigInt(int input) : digits{}
{
    for(unsigned int i = 0; i < 8 * sizeof(int); i++)
    {
        digits.push_back(input % 2);
        input = input / 2;
    }
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj)
{
    for(auto it = obj.digits.begin(); it != obj.digits.end(); ++it)
    {
        os << *it;
    }
    return os;
}
