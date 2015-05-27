#include "Main.hpp"
using namespace std;

int main()
{
    BigInt test{new BigInt{-INT_MAX}};
    BigInt test2{-INT_MAX};
    cout << "Hello World!" << endl;
    cout << "BigInt: " << test - test2 << endl;
    cout << "Bye!" << endl;

    return 0;
}
