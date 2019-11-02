#include <iostream>
#include <array>
#include "MyArray.h"

using namespace std;

int main() {

    // our own implementation of an array 
    // object with bounds checking
    {
        MyArray ma(4);
        ma.setAt(3.14159, 0);
        cout << ma.getAt(0) << endl;
    }

    // STL array object
    {
        array<double, 4> ma;
        ma.at(0) = 3.14159;
        cout << ma.at(0) << endl;
        cout << ma[0] << endl;
    }

    return 0;
}