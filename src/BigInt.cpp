#include "../include/BigInt.hpp"
using namespace std;

BigInt::BigInt() : digits{}
{}

BigInt::BigInt(int input) : digits{}
{
    try
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
    catch(bad_alloc& e)
    {
        cerr << e.what() << endl;
        abort(); 
    }
    catch(...)
    {
        cerr << "Unknown error" << endl;
        abort();
    }
}

BigInt BigInt::operator-() const                                                // Two's complement
{
    try
    {
        BigInt ret{};
        ret.digits.reserve(digits.size());
        bool flag{false};
        for(vector<bool>::const_iterator it{digits.begin()}; it != digits.end(); ++it)
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
    catch(bad_alloc& e)
    {
        cerr << e.what() << endl;
        abort(); 
    }
    catch(...)
    {
        cerr << "Unknown error" << endl;
        abort();
    }
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    try
    {
        bool carryOut{};
        bool carryIn{};
        bool temp{};
        for(unsigned int i{0}; i != other.digits.size(); i++)
        {
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
    catch(bad_alloc& e)
    {
        cerr << e.what() << endl;
        abort(); 
    }
    catch(...)
    {
        cerr << "Unknown error" << endl;
        abort();
    }
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

BigInt& BigInt::operator*=(const BigInt& other)
{
    try
    {
        unsigned int x = digits.size();
        unsigned int y = other.digits.size();
        BigInt neg = -*this;
        vector<bool> A{};
        vector<bool> S{};
        vector<bool> P{};
    
        // Fill
        P.push_back(false);
        for(unsigned int i{0}; i < y + 1; i++)
        {
            A.push_back(false);
            S.push_back(false);
        }
        for(unsigned int i{0}; i < x; i++)
        {
            A.push_back(digits[i]);
            S.push_back(neg.digits[i]);
        }
         for(unsigned int i{0}; i < y; i++)
        {
            P.push_back(other.digits[i]);
        }
        for(unsigned int i{0}; i < x; i++)
        {
            P.push_back(false);
        }
    
        //Booth's algorithm
        bool carryOut{};
        bool carryIn{};
        bool temp{};
        for(unsigned int i = 0; i < y; i++)
        {
            carryOut = false;
            if(P[0] and !P[1])
            {
                // P += A
                for(unsigned int i{0}; i != A.size(); i++)
                {
                    carryIn = carryOut;
                    temp = P[i] xor A[i];
                    carryOut = (temp and carryIn) or (P[i] and A[i]);
                    P[i] = temp xor carryIn;
                }
            }
            if(!P[0] and P[1])
            {
                // P += S
                for(unsigned int i{0}; i != S.size(); i++)
                {
                    carryIn = carryOut;
                    temp = P[i] xor S[i];
                    carryOut = (temp and carryIn) or (P[i] and S[i]);
                    P[i] = temp xor carryIn;
                }
            }
            for(unsigned int i{0}; i != P.size() - 1; i++)
            {
                P[i] = P[i + 1];
            }
        }
        P.erase(P.begin());
        digits = P;
        return *this;
    }
    catch(bad_alloc& e)
    {
        cerr << e.what() << endl;
        abort(); 
    }
    catch(...)
    {
        cerr << "Unknown error" << endl;
        abort();
    }
}

const BigInt BigInt::operator*(const BigInt& other) const
{
    BigInt ret{*this};
    ret *= other;
    return ret;
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj)
{
    for(vector<bool>::const_reverse_iterator it{obj.digits.rbegin()}; it != obj.digits.rend(); ++it)
    {
        os << *it;
    }
    return os;
}
