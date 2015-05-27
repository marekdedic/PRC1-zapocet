#ifndef BIGINT_HPP
#define BIGINT_HPP

class BigInt
{
public:
    BigInt();
    BigInt(int input);

    BigInt operator-() const;
    BigInt& operator+=(const BigInt& other);
    const BigInt operator+(const BigInt& other) const;
    BigInt& operator-=(const BigInt& other);
    const BigInt operator-(const BigInt& other) const;
    BigInt& operator*=(const BigInt& other);
    const BigInt operator*(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
private:
    std::vector<bool> digits;
};

#endif // BIGINT_HPP
