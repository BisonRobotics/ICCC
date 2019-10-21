#include <iostream>

using namespace std;

struct MyStruct {
    long int L; // 8 bytes
    float F;    // 4 bytes
    short S;    // 2 bytes
    char tag;   // 1 byte
};

int main() {

    cout << sizeof(MyStruct) << endl;

    MyStruct arr[2];

    return 0;
}