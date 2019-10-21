#include <iostream>

using namespace std;

double notverydescriptive( 
        int descriptive, double variable5 ) {

    return ( descriptive * variable5 ) / 3;

}

double returnsdouble(void) {
    return 9.00004;
}

int main(void) { // <-- execution always start here

    double pi = 3.14159265;

    double f = 
        notverydescriptive(
            5, 
            returnsdouble()
        );

    cout << f << endl;

    return 0;
}


