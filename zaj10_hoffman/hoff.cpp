#include <iostream>
///#include
using namespace std;

int main(){
    const int foo = 2; //jakas liczba
    int *ptr; // definiowanie poinera
    ptr = const_cast<int*>( &foo );
    cout << "foo=" << foo << endl;
    *ptr = 5;
    cout << "fo2o=" << &ptr << endl;
    return 0;
}
