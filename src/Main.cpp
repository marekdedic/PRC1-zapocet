#include "../include/Main.hpp"
using namespace std;

int main()
{
    try
    {
        BigInt test{236};
        BigInt test2{482};
        cout << "Hello World!" << endl;
        cout << "BigInt: " << test * test2 << endl;
        cout << "Bye!" << endl;
    }
    catch(bad_alloc& e)
    {
        cerr << e.what() << endl;
        return -1; 
    }
    catch(...)
    {
        cerr << "Unknown error" << endl;
        return -1;
    }

    return 0;
}
