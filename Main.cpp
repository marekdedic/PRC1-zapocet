#include "Main.hpp"
using namespace std;

int main()
{
    BigInt* test{new BigInt{31}};
    cout << "Hello World!" << endl;
    cout << "BigInt: " << *test << endl;
    cout << "Bye!" << endl;
}
