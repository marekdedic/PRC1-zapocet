#include "../Main.hpp"
using namespace std;


BigInt::BigInt() : digits{}
{}

BigInt::BigInt(int input) : digits{}
{
    bool negative{input < 0};
    for(unsigned int i{0}; i < 8 * sizeof(int); i++)
    {
        digits.push_back(static_cast<bool>(input % 2));
        input = input / 2;
    }
    if(negative)
    {
        *this = -(*this);
    }
}

BigInt BigInt::operator-() const                                                // Two's complement
{
    BigInt ret{};
    ret.digits.reserve(digits.size());
    bool flag{false};
    for(std::vector<bool>::const_iterator it{digits.begin()}; it != digits.end(); ++it)
    {
        if(flag)
        {
            ret.digits.push_back(!*it);
        }
        else
        {
            ret.digits.push_back(*it);
            if(*it == true)
            {
                flag = true;
            }
        }
    }
    return ret;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    bool carryOut{};
    bool carryIn{};
    bool temp{};
    for(unsigned int i{0}; i != other.digits.size(); i++)
    {                                                                           //TODO: overflow
        carryIn = carryOut;
        temp = digits[i] xor other.digits[i];
        carryOut = (temp and carryIn) or (digits[i] and other.digits[i]);
        digits[i] = temp xor carryIn;
    }
    if(carryOut xor carryIn)
    {
        digits.push_back(carryOut);
    }
    return *this;
}

const BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt ret{*this};
    ret += other;
    return ret;
}

BigInt& BigInt::operator-=(const BigInt& other)
{
    *this += -other;
    return *this;
}

const BigInt BigInt::operator-(const BigInt& other) const
{
    BigInt ret{*this};
    ret -= other;
    return ret;
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj)
{
    for(std::vector<bool>::const_reverse_iterator it{obj.digits.rbegin()}; it != obj.digits.rend(); ++it)
    {
        os << *it;
    }
    return os;
}
