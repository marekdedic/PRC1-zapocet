#ifndef BIGINT_HPP
#define BIGINT_HPP

class BigInt
{
public:
    BigInt();
    BigInt(int input);
    BigInt(const BigInt&) = delete;
    BigInt(BigInt&&) = delete;
    BigInt& operator= (const BigInt&) = delete;
    BigInt& operator= (BigInt&&) = delete;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
private:
    std::vector<bool> digits;
};

#endif // BIGINT_HPP
