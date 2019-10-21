#include <iostream>
using namespace std;

// public by default
struct MyStruct {

    int    vara;
    float  varb;
    double varc;

};

// private by default
class MyClass {

    int    vara;
    float  varb;
    double varc;

public:

    void setVarA(int a) {
        this->vara = a;
    }

    void print(void) {
        cout << vara << ' ' << varb << ' ' << varc << endl;
    }

};

int main() {

    MyStruct ms;
    ms.vara = -1;

    MyClass mc;
    mc.setVarA(-1);
    mc.print();

    return 0;
}